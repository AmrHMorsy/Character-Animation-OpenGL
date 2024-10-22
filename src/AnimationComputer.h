#include "Includes.h"




class AnimationComputer{
    
private:
    
    Bone * root_bone ;
    std::vector<float> num_keyframes ;
    float walking_speed, running_speed ;

public:
    
    AnimationComputer() ;
    void set( Bone * rootbone, std::vector<float> numkeyframes ) ;
    glm::mat4 run( float angle, glm::vec3 &position, glm::vec3 direction, float keyframe ) ;
    glm::mat4 walk( float angle, glm::vec3 &position, glm::vec3 direction, float keyframe ) ;
    void update_position( glm::vec3 &position, glm::vec3 direction, float speed ) ;
    glm::mat4 compute_transformation( glm::vec3 position, float angle ) ;
    glm::mat4 compute_animations( Bone * bone, int active_animation, float ratio ) ;
    void precompute_animations() ;
    void setup_animations( Bone * bone, std::vector<int> animations, int target ) ;
    void blend_animations( std::vector<int> animations, int target, int base ) ;
    void merge_animations( Bone * bone, std::vector<int> animations, int target) ;
    void apply_animations( Bone * bone, float keyframe, int active_animation, int start_animation, float num_keyframes, int target ) ;
    DecomposedTransformation interpolate( DecomposedTransformation dt1, DecomposedTransformation dt2, float factor ) ;
    DecomposedTransformation decompose( glm::mat4 transformation ) ;
    glm::mat4 recompose( DecomposedTransformation dt ) ;
    float easeInOut( float t ) ;
    std::vector<float> get_num_keyframes() ; 
    ~AnimationComputer() ;
    
} ;
