#include "Skybox.h"





class Animator{
    
private:
    
    glm::mat4 model ; 
    float keyframe, angle, steering_angle ;
    Bone * root_bone ;
    int active_animation ;
    std::vector<Mesh*> meshes ;
    glm::vec3 direction, position ;
    std::queue<int> animation_queue ;
    std::vector<bool> is_precomputed ;
    std::vector<float> num_keyframes ;
    AnimationComputer * animation_computer ; 
    
public:
    
    Animator( Bone * rootbone, std::vector<Mesh*> mshes, std::vector<float> numkeyframes, std::vector<bool> isprecomputed, AnimationComputer * animationcomputer ) ;
    void set_direction( float requested_steer_angle ) ;
    void set_animation( int animation ) ;
    bool animate() ;
    void move() ;
    void execute_animation() ;
    void apply_animations( Bone * bone ) ;
    void apply_transformation( Bone * bone ) ;
    void reset_vertices() ;
    void update_vertices() ;
    void update_vertex( int mesh_index, int vertex_index ) ;
    bool reset_animation() ;
    glm::mat4 get_model() ; 
    ~Animator() ;
    
} ;
