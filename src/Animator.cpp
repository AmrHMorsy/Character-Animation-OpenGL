#include "Animator.h"






Animator::Animator( Bone * rootbone, std::vector<Mesh*> mshes, std::vector<float> numkeyframes, std::vector<bool> isprecomputed, AnimationComputer * animationcomputer )
{
    angle = 0.0f ;
    position = glm::vec3(0.0f) ;
    direction = glm::vec3(0.0f, 0.0f, 1.0f) ;
    keyframe = 0.0f ;
    meshes = mshes ;
    root_bone = rootbone ;
    num_keyframes = numkeyframes ;
    is_precomputed = isprecomputed ;
    animation_computer = animationcomputer ; 
    model = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, 0.0f) ) * glm::scale( glm::mat4(1.0f), glm::vec3( 0.01f, 0.01f, 0.01f ) ) ;
}

void Animator::set_direction( float requested_steer_angle )
{
    if( steering_angle != requested_steer_angle ){
        steering_angle = requested_steer_angle ;
        angle += steering_angle ;
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(steering_angle), glm::vec3(0.0f, 1.0f, 0.0f)) ;
        direction = glm::vec3(rotation * glm::vec4(direction, 0.0f)) ;
    }
}

void Animator::set_animation( int animation )
{
    animation_queue.push( animation ) ;
}

void Animator::move()
{
    if( active_animation == WALK_ANIMATION )
        model = animation_computer->walk( angle, position, direction, keyframe ) ;
    else if( active_animation == RUN_ANIMATION )
        model = animation_computer->run( angle, position, direction, keyframe ) ;
}

bool Animator::animate()
{
    if( !animation_queue.empty() ){
        if( keyframe == 0 )
            active_animation = animation_queue.front() ;
        if( keyframe < num_keyframes[active_animation]-1 ){
            execute_animation() ;
            return true ;
        }
        else
            return reset_animation() ;
    }
    return false ;
}

bool Animator::reset_animation()
{
    keyframe = 0.0f ;
    int last_animation = animation_queue.front() ;
    animation_queue.pop() ;
    if( last_animation == animation_queue.front() ){
        while( !animation_queue.empty() )
            animation_queue.pop();
    }
    return animate() ;
}

void Animator::execute_animation()
{
    move() ;
    keyframe++ ;
    apply_animations( root_bone ) ;
    apply_transformation( root_bone ) ;
    reset_vertices() ;
    update_vertices() ;
}

void Animator::apply_animations( Bone * bone )
{
    if( bone->flag[active_animation] ){
        if( is_precomputed[active_animation] )
            bone->local_transformation = bone->precomputed_animations[active_animation][keyframe];
        else
            bone->local_transformation = animation_computer->compute_animations( bone, active_animation, (keyframe/num_keyframes[active_animation]) ) ;
    }
    for( int i = 0 ; i < bone->children.size() ; i++ )
        apply_animations( bone->children[i] ) ;
}

void Animator::apply_transformation( Bone * bone )
{
    if( bone->parent )
        bone->transformation = bone->parent->transformation * bone->inverse_offset * bone->local_transformation * bone->offset ;
    else
        bone->transformation = bone->inverse_offset * bone->local_transformation * bone->offset ;
    
    for( int i = 0 ; i < bone->children.size() ; i++ )
        apply_transformation( bone->children[i] ) ;
}

void Animator::reset_vertices()
{
    for( int i = 0 ; i < meshes.size() ; i++ ){
        for( int j = 0 ; j < meshes[i]->num_vertices ; j++ )
            meshes[i]->vertices[j] = meshes[i]->original_vertices[j] ;
    }
}

void Animator::update_vertices()
{
    for( int i = 0 ; i < meshes.size() ; i++ ){
        for( int j = 0 ; j < meshes[i]->num_vertices/8 ; j++ )
            update_vertex( i, j ) ;
    }
}

void Animator::update_vertex( int mesh_index, int vertex_index )
{
    glm::vec3 new_vertex(0.0f) ;
    glm::vec3 old_vertex( meshes[mesh_index]->vertices[vertex_index * 8], meshes[mesh_index]->vertices[ (vertex_index * 8) + 1 ], meshes[mesh_index]->vertices[ (vertex_index * 8) + 2 ] ) ;
        
    for( int i = 0 ; i < meshes[mesh_index]->bones[vertex_index].size() ; i++ ){
        
        Bone * bone = meshes[mesh_index]->bones[vertex_index][i] ;
        float weight = meshes[mesh_index]->weights[vertex_index][i] ;
        glm::vec4 v = bone->transformation * glm::vec4(old_vertex, 1.0f) ;
        new_vertex += weight * glm::vec3(v) ;
        
    }
        
    meshes[ mesh_index ]->vertices[ vertex_index * 8 ] = new_vertex.x ;
    meshes[ mesh_index ]->vertices[ (vertex_index * 8) + 1 ] = new_vertex.y ;
    meshes[ mesh_index ]->vertices[ (vertex_index * 8) + 2 ] = new_vertex.z ;
}

glm::mat4 Animator::get_model()
{
    return model ;
}

Animator::~Animator(){}
