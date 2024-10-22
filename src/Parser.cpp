#include "Parser.h"



Parser::Parser()
{
    animation_builder = new AnimationBuilder() ;
    animation_computer = new AnimationComputer() ;
}

void Parser::parse( std::string file_name )
{
    Assimp::Importer importer ;
    const aiScene * scene = importer.ReadFile( file_name, aiProcess_Triangulate | aiProcess_GenNormals ) ;
    if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
        generate_error( importer.GetErrorString() ) ;
    
    traverse_meshes( scene->mRootNode, scene, NULL ) ;
}

void Parser::parse_fbx( std::string file_name )
{
    Assimp::Importer importer ;
    const aiScene * scene = importer.ReadFile( file_name, aiProcess_Triangulate ) ;
    if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
        generate_error( importer.GetErrorString() ) ;
    parse_bone_heirarchy( scene->mRootNode->mChildren[4] , scene, NULL ) ;
    for( int i = 5  ; i < scene->mRootNode->mNumChildren ; i++ )
        traverse_meshes( scene->mRootNode->mChildren[i], scene, NULL ) ;
    bone_mapping[scene->mRootNode->mChildren[4]->mName.C_Str()] = root_bone ;
    normalize_weights() ;
    animation_builder->set( root_bone, bone_mapping ) ;
    animation_builder->build_animations() ;
    animation_computer->set(root_bone, animation_builder->get_num_keyframes()) ;
    animation_computer->precompute_animations() ;
    fill_min_meshes() ;
}

void Parser::fill_min_meshes()
{
    min_meshes = new MinMesh * [ meshes.size() ]  ;
    for( int i = 0 ; i < meshes.size() ; i++ ){
        min_meshes[i] = new MinMesh() ;
        min_meshes[i]->albedo = meshes[i]->albedo ;
        min_meshes[i]->metallic = meshes[i]->metallic ;
        min_meshes[i]->roughness = meshes[i]->roughness ;
        min_meshes[i]->num_vertices = meshes[i]->num_vertices ;
        min_meshes[i]->vertices = meshes[i]->vertices ;
        min_meshes[i]->num_indices = meshes[i]->num_indices ;
        min_meshes[i]->indices = meshes[i]->indices ;
        min_meshes[i]->original_vertices = meshes[i]->original_vertices ;
    }
}

void Parser::parse_bone_heirarchy( aiNode * node, const aiScene * scene, Bone * parent )
{
    Bone * bone = new Bone() ;
    
    if( parent ){
        bone->parent = parent ;
        parent->children.push_back( bone ) ;
    }
    else{
        root_bone = bone ;
        bone->parent = NULL ;
    }

    bone->name = node->mName.C_Str() ;
    bone->transformation = glm::mat4(1.0f) ;
    bone->local_transformation = glm::mat4( 1.0f ) ;
    bone->animations.resize(NUM_ANIMATIONS) ;
    bone->flag.resize(NUM_ANIMATIONS) ;
    bone->precomputed_animations.resize( NUM_ANIMATIONS ) ;
    for( int i = 0 ; i < NUM_ANIMATIONS ; i++ ){
        bone->animations[i] = glm::mat4(1.0f) ;
        bone->flag[i] = true ;
    }
    for( int i = IDLE_ANIMATIONS_STARTING_INDEX ; i < NUM_ANIMATIONS ; i++ )
        bone->flag[i] = false ;
    
    bone->offset = glm::mat4( 1.0f ) ;
    bone->inverse_offset = glm::mat4( 1.0f ) ;
    for( unsigned int i = 0 ; i < node->mNumChildren ; i++ )
        parse_bone_heirarchy( node->mChildren[i], scene, bone ) ;
}

void Parser::traverse_meshes( aiNode * node, const aiScene * scene, aiNode * parent )
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
        meshes.push_back( parse_mesh( scene->mMeshes[node->mMeshes[i]], scene ) );

    for (unsigned int i = 0; i < node->mNumChildren; i++)
        traverse_meshes( node->mChildren[i], scene, node ) ;
}

Mesh * Parser::parse_mesh( aiMesh * mesh, const aiScene * scene )
{
    Mesh * m = new Mesh() ;
    
    extract_vertices( mesh, m ) ;
    
    extract_indices( mesh, m ) ;
    
    extract_albedo( mesh, scene, m ) ;

    extract_bones( mesh, m ) ;
    
    return m ;
}

void Parser::extract_vertices( aiMesh * mesh, Mesh * m )
{
    m->bones.resize( mesh->mNumVertices ) ;
    m->weights.resize( mesh->mNumVertices ) ;

    m->num_vertices = mesh->mNumVertices * 8 ;
    m->vertices = new float[ m->num_vertices ] ;
    
    for( unsigned int j = 0 ; j < mesh->mNumVertices ; j++ ){
        
        m->vertices[(8*j)] = mesh->mVertices[j].x ;
        m->vertices[(8*j)+1] = mesh->mVertices[j].y ;
        m->vertices[(8*j)+2] = mesh->mVertices[j].z ;
        
        if( mesh->mTextureCoords[0] ){
            m->vertices[(8*j)+3] = mesh->mTextureCoords[0][j].x ;
            m->vertices[(8*j)+4] = mesh->mTextureCoords[0][j].y ;
        }
        else{
            m->vertices[(8*j)+3] = 0.0f ;
            m->vertices[(8*j)+4] = 0.0f ;
        }
        
        m->vertices[(8*j)+5] = mesh->mNormals[j].x ;
        m->vertices[(8*j)+6] = mesh->mNormals[j].y ;
        m->vertices[(8*j)+7] = mesh->mNormals[j].z ;
    }
    
    m->original_vertices = new float[ m->num_vertices ] ;
    for( int p = 0 ; p < m->num_vertices ; p++ )
        m->original_vertices[p] = m->vertices[p] ;
}

void Parser::extract_indices( aiMesh * mesh, Mesh * m )
{
    m->num_indices = 0 ;
    for( unsigned int j = 0 ; j < mesh->mNumFaces ; j++ ) {
        for( unsigned int k = 0 ; k < mesh->mFaces[j].mNumIndices ; k++ )
            m->num_indices++ ;
    }
    m->indices = new unsigned int[m->num_indices] ;
    int counter = 0 ;
    for( unsigned int j = 0 ; j < mesh->mNumFaces ; j++ ) {
        for( unsigned int k = 0 ; k < mesh->mFaces[j].mNumIndices ; k++ ){
            m->indices[counter] = mesh->mFaces[j].mIndices[k] ;
            counter++ ;
        }
    }
}

void Parser::extract_albedo( aiMesh * mesh, const aiScene * scene, Mesh * m )
{
    if( scene->mMaterials[mesh->mMaterialIndex] ){
        float roughness, metallic ;
        aiColor3D color(0.0f, 0.0f, 0.0f) ;
        aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex] ;
        if( material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS )
            m->albedo = glm::vec3(color[0], color[1], color[2]) ;
        if (material->Get("ROUGHNESS_FACTOR", 0, 0, roughness) != AI_SUCCESS)
            m->roughness = 1.0f ;
        if( material->Get("METALLIC_FACTOR", 0, 0, metallic) != AI_SUCCESS )
            m->metallic = 0.0f ;
        m->metallic = metallic ;
        m->roughness = roughness ; 
    }
}

void Parser::extract_bones( aiMesh * mesh, Mesh * m )
{
    for( unsigned int j = 0 ; j < mesh->mNumBones ; j++ ) {
        std::string bone_name = mesh->mBones[j]->mName.data ;
        Bone * bone = retrieve_bone( bone_name ) ;
        if( bone ){
            bone->offset = convert_to_GLM( mesh->mBones[j]->mOffsetMatrix ) ;
            bone->inverse_offset = glm::inverse( bone->offset ) ;
            bone->local_transformation = glm::mat4( 1.0f ) ;
            bone->transformation = glm::mat4( 1.0f ) ;
            bone->affected_vertices.push_back( get_affected_vertices(mesh->mBones[j], bone, m) ) ;
            bone_mapping[ bone_name ] = bone ;
        }
        else
            generate_error( bone_name + " Bone Unfound in Bone Tree" ) ;
    }
}

Bone * Parser::retrieve_bone( std::string bone_name )
{
    std::map<std::string, Bone*>::iterator it = bone_mapping.find( bone_name ) ;
    
    if( it != bone_mapping.end() )
        return it->second ;
    else
        return search_bone( root_bone, bone_name ) ;
}

std::vector<unsigned int> Parser::get_affected_vertices( aiBone * bone, Bone * b, Mesh * m )
{
    std::vector<unsigned int> affected_vertices ;
        
    for( unsigned int k = 0 ; k < bone->mNumWeights ; k++ ){
        affected_vertices.push_back( bone->mWeights[k].mVertexId ) ;
        register_bone_vertex_dependency( m, b, bone->mWeights[k].mVertexId, bone->mWeights[k].mWeight ) ;
    }
    
    return affected_vertices ;
}

void Parser::register_bone_vertex_dependency( Mesh * m, Bone * bone, unsigned int vertex_index, float weight )
{
    m->bones[vertex_index].push_back( bone ) ;
    m->weights[vertex_index].push_back( weight ) ;
}

Bone * Parser::search_bone( Bone * node, std::string bone_name )
{
    if( node->name == bone_name )
        return node ;
    
    for( int i = 0 ; i < node->children.size() ; i++ ){
        Bone * bone = search_bone( node->children[i], bone_name ) ;
        if( bone )
            return bone ;
    }
    
    return NULL ;
}

glm::mat4 Parser::convert_to_GLM( const aiMatrix4x4& aiMat )
{
    return glm::mat4(
        aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1,
        aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2,
        aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3,
        aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4
    ) ;
}

void Parser::normalize_weights()
{
    for( int i = 0 ; i < meshes.size() ; i++ ){
        for( int j = 0 ; j < meshes[i]->weights.size() ; j++ ){
            float total = 0 ;
            for( int k = 0 ; k < meshes[i]->weights[j].size() ; k++ )
                total += meshes[i]->weights[j][k] ;
            for( int k = 0 ; k < meshes[i]->weights[j].size() ; k++ )
                meshes[i]->weights[j][k] /= total ;
        }
    }
}

std::vector<Mesh*> Parser::get_meshes()
{
    return meshes ;
}

std::map<std::string, Bone*> Parser::get_bone_mapping()
{
    return bone_mapping ;
}

Bone * Parser::get_root_bone()
{
    return root_bone ;
}

std::vector<float> Parser::get_num_keyframes()
{
    return animation_computer->get_num_keyframes() ;
}

std::vector<bool> Parser::get_precomputed_animations()
{
    return animation_builder->get_precomputed_animations() ;
}

AnimationComputer * Parser::get_animation_computer()
{
    return animation_computer ; 
}

void Parser::generate_error( std::string error_msg )
{
    std::cerr << "ERROR::" << error_msg << std::endl ;
    
    return ;
}

MinMesh ** Parser::get_min_meshes()
{
    return min_meshes ;
}

Parser::~Parser()
{
    delete animation_computer ;
    animation_computer = NULL ;
    delete animation_builder ;
    animation_builder = NULL ;
}
