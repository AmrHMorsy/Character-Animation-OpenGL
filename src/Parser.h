#include "AnimationBuilder.h"




class Parser {
    
private:
        
    MinMesh ** min_meshes ;
    Bone * root_bone ;
    std::vector<Mesh*> meshes ;
    AnimationBuilder * animation_builder ;
    AnimationComputer * animation_computer ;
    std::map<std::string, Bone*> bone_mapping ;
    std::map<int, std::string> bone_name_mapping ;
    
public:

    Parser() ;
    void parse( std::string file_name ) ; 
    void parse_fbx( std::string file_name ) ;
    void normalize_weights() ;
    void store_animations() ;
    void store_sit_animation() ;
    void store_stand_animation() ; 
    void store_head_animation() ;
    void store_put_hand_behind_back_animation() ;
    void store_put_hand_side_animation() ;
    void store_walk_animation() ;
    void fill_min_meshes() ;
    void parse_bone_heirarchy( aiNode * node, const aiScene * scene, Bone * parent ) ;
    void traverse_meshes( aiNode * node, const aiScene * scene, aiNode * parent ) ;
    Mesh * parse_mesh( aiMesh * mesh, const aiScene * scene ) ;
    void extract_vertices( aiMesh * mesh, Mesh * m ) ;
    void extract_indices( aiMesh * mesh, Mesh * m ) ;
    void extract_albedo( aiMesh * mesh, const aiScene * scene, Mesh * m ) ;
    void extract_bones( aiMesh * mesh, Mesh * m ) ;
    Bone * retrieve_bone( std::string bone_name ) ;
    std::vector<unsigned int> get_affected_vertices( aiBone * bone, Bone * b, Mesh * m ) ;
    void register_bone_vertex_dependency( Mesh * m, Bone * bone, unsigned int vertex_index, float weight ) ;
    Bone * search_bone( Bone * node, std::string bone_name ) ;
    glm::mat4 convert_to_GLM( const aiMatrix4x4 & from ) ;
    std::vector<Mesh*> get_meshes() ;
    std::map<std::string, Bone*> get_bone_mapping() ;
    Bone * get_root_bone() ;
    std::vector<float> get_num_keyframes() ; 
    std::vector<bool> get_precomputed_animations() ;
    AnimationComputer * get_animation_computer() ;
    void generate_error( std::string error_msg ) ;
    MinMesh ** get_min_meshes() ; 
    ~Parser() ;
    
} ;
