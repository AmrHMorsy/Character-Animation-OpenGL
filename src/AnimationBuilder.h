#include "AnimationComputer.h"






class AnimationBuilder{
    
private:
    
    std::vector<bool> is_precomputed ; 
    std::vector<float> num_keyframes ;
    std::map<std::string, Bone*> bone_mapping ;
    Bone * root_bone, * left_arm, * right_arm, * left_forearm, * right_forearm, * left_thigh, * right_thigh, * left_shin, * right_shin, * left_shin2, * right_shin2, * head, * left_thumb1, * left_thumb2, * left_thumb3, * right_thumb1, * right_thumb2, * right_thumb3, * right_index1, * right_index2, * right_index3, * right_middle1, * right_middle2, * right_middle3, * right_ring1, * right_ring2, * right_ring3, * right_pinky1, * right_pinky2, * right_pinky3, * left_index1, * left_index2, * left_index3, * left_middle1, * left_middle2, * left_middle3, * left_ring1, * left_ring2, * left_ring3, * left_pinky1, * left_pinky2, * left_pinky3, * diaphram, * right_hand, * left_hand, * lower_right_lip1, * lower_left_lip1, * upper_right_lip1, * upper_left_lip1, * lower_right_lip2, * lower_left_lip2, * upper_right_lip2, * upper_left_lip2, * right_eyebrow, * left_eyebrow, * right_eyelid_top1, * right_eyelid_top2, * right_eyelid_top3, * left_eyelid_top1, * left_eyelid_top2 , * left_eyelid_top3, * head2, * lower_body, * left_foot, * right_foot, * upper_body, * upper_body1, * upper_body2, * spine, * spine1, * spine2 ; 
    
    // * upper_body1, * upper_body2 ;
    
public:
    
    AnimationBuilder() ;
    void set( Bone * rootbone, std::map<std::string, Bone*> bone_map ) ;
    void prepare_bones() ;
    void build_animations() ;
    void run() ;
    void sit() ;
    void stand() ;
    void walk() ;
    void move_head() ;
    void breath() ;
    void check_wrist() ;
    void say_hi() ;
    void clench_fist() ;
    void scratch_head() ;
    void smile() ;
    void blink() ;
    std::vector<float> get_num_keyframes() ;
    std::vector<bool> get_precomputed_animations() ;
    void generate_error( std::string msg ) ;
    ~AnimationBuilder() ;
    
} ;
