#include "AnimationBuilder.h"





AnimationBuilder::AnimationBuilder(){}

void AnimationBuilder::set( Bone * rootbone, std::map<std::string, Bone*> bone_map )
{
    is_precomputed.resize( NUM_ANIMATIONS ) ;
    for( int i = 0 ; i < NUM_ANIMATIONS ; i++ )
        is_precomputed[i] = true ;
    num_keyframes.resize(NUM_ANIMATIONS) ;
    root_bone = rootbone ;
    bone_mapping = bone_map ;
    prepare_bones() ;
}

void AnimationBuilder::prepare_bones()
{
    left_arm = bone_mapping[ LEFT_ARM ] ;
    if( !left_arm )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_ARM) + "\033[0m" ) ;
    
    right_arm = bone_mapping[ RIGHT_ARM ] ;
    if( !right_arm )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_ARM) + "\033[0m" ) ;

    left_forearm = bone_mapping[ LEFT_FOREARM ] ;
    if( !left_forearm )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_FOREARM) + "\033[0m" ) ;

    right_forearm = bone_mapping[ RIGHT_FOREARM ] ;
    if( !right_forearm )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_FOREARM) + "\033[0m" ) ;

    left_thigh = bone_mapping[ LEFT_THIGH ] ;
    if( !left_thigh )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_THIGH) + "\033[0m");
    
    right_thigh = bone_mapping[ RIGHT_THIGH ] ;
    if( !right_thigh )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_THIGH) + "\033[0m");

    left_shin = bone_mapping[ LEFT_SHIN ] ;
    if( !left_shin )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_SHIN) + "\033[0m");
    
    right_shin = bone_mapping[ RIGHT_SHIN ] ;
    if( !right_shin )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_SHIN) + "\033[0m");
    
    left_shin2 = bone_mapping[ LEFT_SHIN2 ] ;
    if( !left_shin2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_SHIN2) + "\033[0m");
    
    right_shin2 = bone_mapping[ RIGHT_SHIN2 ] ;
    if( !right_shin2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_SHIN2) + "\033[0m");

    head = bone_mapping[ HEAD ] ;
    if( !head )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(HEAD) + "\033[0m" ) ;
    
    left_thumb1 = bone_mapping[ LEFT_THUMB1 ] ;
    if( !left_thumb1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_THUMB1) + "\033[0m" ) ;

    left_thumb2 = bone_mapping[ LEFT_THUMB2 ] ;
    if( !left_thumb2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_THUMB2) + "\033[0m" ) ;

    left_thumb3 = bone_mapping[ LEFT_THUMB3 ] ;
    if( !left_thumb3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_THUMB3) + "\033[0m" ) ;

    right_thumb1 = bone_mapping[ RIGHT_THUMB1 ] ;
    if( !right_thumb1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_THUMB1) + "\033[0m" ) ;

    right_thumb2 = bone_mapping[ RIGHT_THUMB2 ] ;
    if( !right_thumb2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_THUMB2) + "\033[0m" ) ;

    right_thumb3 = bone_mapping[ RIGHT_THUMB3 ] ;
    if( !right_thumb3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_THUMB3) + "\033[0m" ) ;
    
    right_index1 = bone_mapping[ RIGHT_INDEX1 ] ;
    if( !right_index1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_INDEX1) + "\033[0m" ) ;
    
    right_index2 = bone_mapping[ RIGHT_INDEX2 ] ;
    if( !right_index2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_INDEX2) + "\033[0m" ) ;
    
    right_index3 = bone_mapping[ RIGHT_INDEX3 ] ;
    if( !right_index3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_INDEX3) + "\033[0m" ) ;
    
    right_middle1 = bone_mapping[ RIGHT_MIDDLE1 ] ;
    if( !right_middle1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_MIDDLE1) + "\033[0m" ) ;
    
    right_middle2 = bone_mapping[ RIGHT_MIDDLE2 ] ;
    if( !right_middle2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_MIDDLE2) + "\033[0m" ) ;
    
    right_middle3 = bone_mapping[ RIGHT_MIDDLE3 ] ;
    if( !right_middle3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_MIDDLE3) + "\033[0m" ) ;
    
    right_ring1 = bone_mapping[ RIGHT_RING1 ] ;
    if( !right_ring1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_RING1) + "\033[0m" ) ;
    
    right_ring2 = bone_mapping[ RIGHT_RING2 ] ;
    if( !right_ring2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_RING2) + "\033[0m" ) ;
    
    right_ring3 = bone_mapping[ RIGHT_RING3 ] ;
    if( !right_ring3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_RING3) + "\033[0m" ) ;
    
    right_pinky1 = bone_mapping[ RIGHT_PINKY1 ] ;
    if( !right_pinky1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_PINKY1) + "\033[0m" ) ;

    right_pinky2 = bone_mapping[ RIGHT_PINKY2 ] ;
    if( !right_pinky2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_PINKY2) + "\033[0m" ) ;

    right_pinky3 = bone_mapping[ RIGHT_PINKY3 ] ;
    if( !right_pinky3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_PINKY3) + "\033[0m" ) ;

    left_index1 = bone_mapping[ LEFT_INDEX1 ] ;
    if( !left_index1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_INDEX1) + "\033[0m" ) ;
    
    left_index2 = bone_mapping[ LEFT_INDEX2 ] ;
    if( !left_index2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_INDEX2) + "\033[0m" ) ;
    
    left_index3 = bone_mapping[ LEFT_INDEX3 ] ;
    if( !left_index3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_INDEX3) + "\033[0m" ) ;

    left_middle1 = bone_mapping[ LEFT_MIDDLE1 ] ;
    if( !left_middle1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_MIDDLE1) + "\033[0m" ) ;

    left_middle2 = bone_mapping[ LEFT_MIDDLE2 ] ;
    if( !left_middle2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_MIDDLE2) + "\033[0m" ) ;
    
    left_middle3 = bone_mapping[ LEFT_MIDDLE3 ] ;
    if( !left_middle3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_MIDDLE3) + "\033[0m" ) ;

    left_ring1 = bone_mapping[ LEFT_RING1 ] ;
    if( !left_ring1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_RING1) + "\033[0m" ) ;

    left_ring2 = bone_mapping[ LEFT_RING2 ] ;
    if( !left_ring2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_RING2) + "\033[0m" ) ;

    left_ring3 = bone_mapping[ LEFT_RING3 ] ;
    if( !left_ring3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_RING3) + "\033[0m" ) ;

    left_pinky1 = bone_mapping[ LEFT_PINKY1 ] ;
    if( !left_pinky1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_PINKY1) + "\033[0m" ) ;

    left_pinky2 = bone_mapping[ LEFT_PINKY2 ] ;
    if( !left_pinky2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_PINKY2) + "\033[0m" ) ;

    left_pinky3 = bone_mapping[ LEFT_PINKY3 ] ;
    if( !left_pinky3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_PINKY3) + "\033[0m" ) ;

    diaphram = bone_mapping[ DIAPHRAM ] ;
    if( !diaphram )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(DIAPHRAM) + "\033[0m" ) ;
    
    right_hand = bone_mapping[ RIGHT_HAND ] ;
    if( !right_hand )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_HAND) + "\033[0m" ) ;
    
    lower_right_lip1 = bone_mapping[ LOWER_LIP_RIGHT1 ] ;
    if( !lower_right_lip1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LOWER_LIP_RIGHT1) + "\033[0m" ) ;
    
    lower_left_lip1 = bone_mapping[ LOWER_LIP_LEFT1 ] ;
    if( !lower_left_lip1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LOWER_LIP_LEFT1) + "\033[0m" ) ;

    upper_right_lip1 = bone_mapping[ UPPER_LIP_RIGHT1 ] ;
    if( !upper_right_lip1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(UPPER_LIP_RIGHT1) + "\033[0m" ) ;

    upper_left_lip1 = bone_mapping[ UPPER_LIP_LEFT1 ] ;
    if( !upper_left_lip1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(UPPER_LIP_LEFT1) + "\033[0m" ) ;
    
    lower_right_lip2 = bone_mapping[ LOWER_LIP_RIGHT2 ] ;
    if( !lower_right_lip2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LOWER_LIP_RIGHT2) + "\033[0m" ) ;
    
    lower_left_lip2 = bone_mapping[ LOWER_LIP_LEFT2 ] ;
    if( !lower_left_lip2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LOWER_LIP_LEFT2) + "\033[0m" ) ;

    upper_right_lip2 = bone_mapping[ UPPER_LIP_RIGHT2 ] ;
    if( !upper_right_lip2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(UPPER_LIP_RIGHT2) + "\033[0m" ) ;

    upper_left_lip2 = bone_mapping[ UPPER_LIP_LEFT2 ] ;
    if( !upper_left_lip2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(UPPER_LIP_LEFT2) + "\033[0m" ) ;
    
    right_eyebrow = bone_mapping[ RIGHT_EYEBROW ] ;
    if( !right_eyebrow )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_EYEBROW) + "\033[0m" ) ;
    
    left_eyebrow = bone_mapping[ LEFT_EYEBROW ] ;
    if( !left_eyebrow )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_EYEBROW) + "\033[0m" ) ;
    
    right_eyelid_top1 = bone_mapping[ RIGHT_EYELID_TOP1 ] ;
    if( !right_eyelid_top1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_EYELID_TOP1) + "\033[0m" ) ;
    
    right_eyelid_top2 = bone_mapping[ RIGHT_EYELID_TOP2 ] ;
    if( !right_eyelid_top2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_EYELID_TOP2) + "\033[0m" ) ;

    right_eyelid_top3 = bone_mapping[ RIGHT_EYELID_TOP3 ] ;
    if( !right_eyelid_top3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_EYELID_TOP3) + "\033[0m" ) ;

    left_eyelid_top1 = bone_mapping[ LEFT_EYELID_TOP1 ] ;
    if( !left_eyelid_top1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_EYELID_TOP1) + "\033[0m" ) ;
    
    left_eyelid_top2 = bone_mapping[ LEFT_EYELID_TOP2 ] ;
    if( !left_eyelid_top2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_EYELID_TOP2) + "\033[0m" ) ;
    
    left_eyelid_top3 = bone_mapping[ LEFT_EYELID_TOP3 ] ;
    if( !left_eyelid_top3 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_EYELID_TOP3) + "\033[0m" ) ;
    
    left_hand = bone_mapping[ LEFT_HAND ] ;
    if( !left_hand )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_HAND) + "\033[0m" ) ;
    
    head2 = bone_mapping[ HEAD2 ] ;
    if( !head2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(HEAD2) + "\033[0m" ) ;

    lower_body = bone_mapping[ LOWER_BODY ] ;
    if( !lower_body )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LOWER_BODY) + "\033[0m" ) ;
    
    left_foot = bone_mapping[ LEFT_FOOT ] ;
    if( !left_foot )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(LEFT_FOOT) + "\033[0m" ) ;

    right_foot = bone_mapping[ RIGHT_FOOT ] ;
    if( !right_foot )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(RIGHT_FOOT) + "\033[0m" ) ;
        
    spine = bone_mapping[ SPINE ] ;
    if( !spine )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(SPINE) + "\033[0m" ) ;
    
    spine1 = bone_mapping[ SPINE1 ] ;
    if( !spine1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(SPINE1) + "\033[0m" ) ;
    
    spine2 = bone_mapping[ SPINE2 ] ;
    if( !spine2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(SPINE2) + "\033[0m" ) ;

    upper_body = bone_mapping[ UPPER_BODY ] ;
    if( !upper_body )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(UPPER_BODY) + "\033[0m" ) ;

    upper_body1 = bone_mapping[ UPPER_BODY1 ] ;
    if( !upper_body1 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(UPPER_BODY1) + "\033[0m" ) ;
    
    upper_body2 = bone_mapping[ UPPER_BODY2 ] ;
    if( !upper_body2 )
        generate_error( "BUILD ANIMATION ERROR: COULD NOT FIND BONE \033[1;31m" + std::string(UPPER_BODY2) + "\033[0m" ) ;
}

void AnimationBuilder::build_animations()
{
    run() ;
    sit() ;
    stand() ;
    walk() ;
    say_hi() ;
    move_head() ;
    clench_fist() ;
    breath() ;
    check_wrist() ;
    scratch_head() ;
    smile() ;
    blink() ;
}

void AnimationBuilder::run()
{
    num_keyframes[LEFT_SPRINT] = NUM_KEYFRAMES_LEFT_SPRINT ;
    num_keyframes[MERGE_RIGHT] = NUM_KEYFRAMES_MERGE_RIGHT ;
    num_keyframes[RIGHT_SPRINT] = NUM_KEYFRAMES_RIGHT_SPRINT ;
    num_keyframes[MERGE_LEFT] = NUM_KEYFRAMES_MERGE_LEFT ;

    left_arm->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-54.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_arm->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(54.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_forearm->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_forearm->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thigh->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    glm::mat4 inwards = glm::rotate( glm::mat4(1.0f), glm::radians(-35.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    glm::mat4 outwards = glm::rotate( glm::mat4(1.0f), glm::radians(-35.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_thigh->animations[LEFT_SPRINT] = inwards * outwards ;
    left_shin->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_shin->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    spine2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    upper_body2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    left_thumb1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_middle1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky1->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky2->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky3->animations[LEFT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    
    left_arm->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_forearm->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_forearm->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thigh->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thigh->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_shin->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(40.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    spine2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    upper_body2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    left_thumb1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_middle1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky1->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky2->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky3->animations[MERGE_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;

    inwards = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) );
    outwards = glm::rotate( glm::mat4(1.0f), glm::radians(54.0f), glm::vec3( 1.0f, 0.0f, 0.0f ));
    left_arm->animations[RIGHT_SPRINT] = inwards * outwards ;
    right_arm->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-54.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_forearm->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_forearm->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thigh->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    inwards = glm::rotate( glm::mat4(1.0f), glm::radians(-35.0f), glm::vec3( 1.0f, 0.0f, 0.0f )) ;
    outwards = glm::rotate( glm::mat4(1.0f), glm::radians(35.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) );
    right_thigh->animations[RIGHT_SPRINT] = inwards * outwards ;
    left_shin->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(40.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_shin->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(40.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    spine2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    upper_body2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    left_thumb1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_middle1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky1->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky2->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky3->animations[RIGHT_SPRINT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;

    left_arm->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_forearm->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_forearm->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thigh->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thigh->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_shin->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(40.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    spine2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    upper_body2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    left_thumb1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_middle1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky1->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky2->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky3->animations[MERGE_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
}

void AnimationBuilder::walk()
{
    num_keyframes[LEFT_STRIDE] = NUM_KEYFRAMES_LEFT_STRIDE ;
    num_keyframes[JOIN_RIGHT] = NUM_KEYFRAMES_JOIN_RIGHT ;
    num_keyframes[RIGHT_STRIDE] = NUM_KEYFRAMES_RIGHT_STRIDE ;
    num_keyframes[JOIN_LEFT] = NUM_KEYFRAMES_JOIN_LEFT ;

    left_arm->animations[LEFT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_arm->animations[LEFT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_forearm->animations[LEFT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[LEFT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_thigh->animations[LEFT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(10.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-25.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    glm::mat4 inwards = glm::rotate( glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    glm::mat4 outwards = glm::rotate( glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_thigh->animations[LEFT_STRIDE] = inwards * outwards ;
    
    left_arm->animations[JOIN_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[JOIN_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_forearm->animations[JOIN_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[JOIN_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_thigh->animations[JOIN_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thigh->animations[JOIN_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_shin->animations[JOIN_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;

    inwards = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) );
    outwards = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 1.0f, 0.0f, 0.0f ));
    left_arm->animations[RIGHT_STRIDE] = inwards * outwards ;
    right_arm->animations[RIGHT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_forearm->animations[RIGHT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[RIGHT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_thigh->animations[RIGHT_STRIDE] = glm::rotate( glm::mat4(1.0f), glm::radians(10.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    inwards = glm::rotate( glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3( 1.0f, 0.0f, 0.0f )) ;
    outwards = glm::rotate( glm::mat4(1.0f), glm::radians(15.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) );
    right_thigh->animations[RIGHT_STRIDE] = inwards * outwards ;

    left_arm->animations[JOIN_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[JOIN_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_forearm->animations[JOIN_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[JOIN_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_thigh->animations[JOIN_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thigh->animations[JOIN_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_shin->animations[JOIN_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(20.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
}

void AnimationBuilder::sit()
{
    is_precomputed[SIT_ANIMATION] = false ;
    num_keyframes[SIT_ANIMATION] = NUM_KEYFRAMES_SIT ;
    
    root_bone->animations[SIT_ANIMATION] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, -150.0f)) ;
    left_arm->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_hand->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(60.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_hand->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-60.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_forearm->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(60.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-25.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(60.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(25.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_thigh->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3( 1.0f, 0.0f, 0.0f) ) ;
    right_thigh->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_shin->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_shin2->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-1.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_shin->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_shin2->animations[SIT_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(5.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
}

void AnimationBuilder::stand()
{
    is_precomputed[STAND_ANIMATION] = false ;
    num_keyframes[STAND_ANIMATION] = NUM_KEYFRAMES_STAND ;
    
    left_arm->animations[STAND_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[STAND_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_forearm->animations[STAND_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[STAND_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_thigh->animations[STAND_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thigh->animations[STAND_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
}

void AnimationBuilder::move_head()
{
    num_keyframes[RIGHT_HEAD_ANIMATION] = NUM_KEYFRAMES_RIGHT_HEAD_ANIMATION ;
    num_keyframes[LEFT_HEAD_ANIMATION] = NUM_KEYFRAMES_LEFT_HEAD_ANIMATION ;
    num_keyframes[UP_HEAD_ANIMATION] = NUM_KEYFRAMES_UP_HEAD_ANIMATION ;
    num_keyframes[DOWN_HEAD_ANIMATION] = NUM_KEYFRAMES_DOWN_HEAD_ANIMATION ;
    num_keyframes[RESET_HEAD] = NUM_KEYFRAMES_RESET_HEAD ;
    
    head->animations[RIGHT_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) ) ;
    head2->animations[RIGHT_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) ) ;
    head->animations[LEFT_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(15.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) ) ;
    head2->animations[LEFT_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(15.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) ) ;
    head->animations[UP_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(15.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[UP_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(15.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[DOWN_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[DOWN_HEAD_ANIMATION] = glm::rotate( glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;

    head->flag[RESET_HEAD] = head2->flag[RESET_HEAD] = head->flag[RIGHT_HEAD_ANIMATION] = head->flag[LEFT_HEAD_ANIMATION] = head->flag[UP_HEAD_ANIMATION] = head->flag[DOWN_HEAD_ANIMATION] = head2->flag[RIGHT_HEAD_ANIMATION] = head2->flag[LEFT_HEAD_ANIMATION] = head2->flag[UP_HEAD_ANIMATION] = head2->flag[DOWN_HEAD_ANIMATION] = true ;
}

void AnimationBuilder::breath()
{
    num_keyframes[INHALE] = NUM_KEYFRAMES_INHALE ;
    num_keyframes[EXHALE] = NUM_KEYFRAMES_EXHALE ;
    
    diaphram->animations[INHALE] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.05f));
    
    diaphram->flag[INHALE] = diaphram->flag[EXHALE] = true ;
}

void AnimationBuilder::check_wrist()
{
    num_keyframes[CHECK_WRIST] = NUM_KEYFRAMES_CHECK_WRIST ;
    num_keyframes[RESET_ARM] = NUM_KEYFRAMES_RESET_ARM ;
    
    right_arm->animations[CHECK_WRIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    right_forearm->animations[CHECK_WRIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f) ) * glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    head->animations[CHECK_WRIST] = glm::rotate( glm::mat4(1.0f), glm::radians(15.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[CHECK_WRIST] = glm::rotate( glm::mat4(1.0f), glm::radians(15.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_arm->animations[RESET_ARM] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[RESET_ARM] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    
    head2->flag[CHECK_WRIST] = head->flag[CHECK_WRIST] = right_arm->flag[CHECK_WRIST] = right_forearm->flag[CHECK_WRIST] = head->flag[RESET_ARM] = head2->flag[RESET_ARM] = right_arm->flag[RESET_ARM] = right_forearm->flag[RESET_ARM] = true ; ;
}

void AnimationBuilder::say_hi()
{
    num_keyframes[RAISE_HAND] = NUM_KEYFRAMES_RAISE_HAND ;
    num_keyframes[LOWER_HAND] = NUM_KEYFRAMES_LOWER_HAND ;
    num_keyframes[WAVE_HAND_LEFT] = NUM_KEYFRAMES_WAVE_HAND_LEFT ;
    num_keyframes[WAVE_HAND_RIGHT] = NUM_KEYFRAMES_WAVE_HAND_RIGHT ;
    
    right_arm->animations[RAISE_HAND] = glm::rotate( glm::mat4(1.0f), glm::radians(80.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    right_forearm->animations[RAISE_HAND] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[RAISE_HAND] = glm::rotate( glm::mat4(1.0f), glm::radians(-7.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[RAISE_HAND] = glm::rotate( glm::mat4(1.0f), glm::radians(-7.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    upper_right_lip2->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_left_lip2->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_right_lip2->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_left_lip2->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_right_lip1->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    upper_left_lip1->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    lower_right_lip1->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    lower_left_lip1->animations[RAISE_HAND] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    right_arm->animations[WAVE_HAND_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(80.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    right_forearm->animations[WAVE_HAND_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[WAVE_HAND_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-7.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[WAVE_HAND_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(-7.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    upper_right_lip2->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_left_lip2->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_right_lip2->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_left_lip2->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_right_lip1->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    upper_left_lip1->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    lower_right_lip1->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    lower_left_lip1->animations[WAVE_HAND_LEFT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    right_hand->animations[WAVE_HAND_LEFT] = glm::rotate( glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f) ) ;
    right_arm->animations[WAVE_HAND_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(80.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    right_forearm->animations[WAVE_HAND_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head->animations[WAVE_HAND_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-7.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    head2->animations[WAVE_HAND_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-7.5f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    upper_right_lip2->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_left_lip2->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_right_lip2->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_left_lip2->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_right_lip1->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    upper_left_lip1->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    lower_right_lip1->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    lower_left_lip1->animations[WAVE_HAND_RIGHT] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    right_hand->animations[WAVE_HAND_RIGHT] = glm::rotate( glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f) ) ;
    right_arm->animations[LOWER_HAND] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[LOWER_HAND] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    
    right_hand->flag[RAISE_HAND] = head2->flag[RAISE_HAND] = head->flag[RAISE_HAND] = right_arm->flag[RAISE_HAND] = right_forearm->flag[RAISE_HAND] = lower_right_lip2->flag[RAISE_HAND] = lower_left_lip2->flag[RAISE_HAND] = lower_right_lip1->flag[RAISE_HAND] = lower_left_lip1->flag[RAISE_HAND] = upper_right_lip1->flag[RAISE_HAND] = upper_left_lip1->flag[RAISE_HAND] = upper_right_lip2->flag[RAISE_HAND] = upper_left_lip2->flag[RAISE_HAND] = right_hand->flag[WAVE_HAND_LEFT] = head2->flag[WAVE_HAND_LEFT] = head->flag[WAVE_HAND_LEFT] = right_arm->flag[WAVE_HAND_LEFT] = right_forearm->flag[WAVE_HAND_LEFT] = lower_right_lip2->flag[WAVE_HAND_LEFT] = lower_left_lip2->flag[WAVE_HAND_LEFT] = lower_right_lip1->flag[WAVE_HAND_LEFT] = lower_left_lip1->flag[WAVE_HAND_LEFT] = upper_right_lip1->flag[WAVE_HAND_LEFT] = upper_left_lip1->flag[WAVE_HAND_LEFT] = upper_right_lip2->flag[WAVE_HAND_LEFT] = upper_left_lip2->flag[WAVE_HAND_LEFT] = right_hand->flag[WAVE_HAND_RIGHT] = head2->flag[WAVE_HAND_RIGHT] = head->flag[WAVE_HAND_RIGHT] = right_arm->flag[WAVE_HAND_RIGHT] = right_forearm->flag[WAVE_HAND_RIGHT] = lower_right_lip2->flag[WAVE_HAND_RIGHT] = lower_left_lip2->flag[WAVE_HAND_RIGHT] = lower_right_lip1->flag[WAVE_HAND_RIGHT] = lower_left_lip1->flag[WAVE_HAND_RIGHT] = upper_right_lip1->flag[WAVE_HAND_RIGHT] = upper_left_lip1->flag[WAVE_HAND_RIGHT] = upper_right_lip2->flag[WAVE_HAND_RIGHT] = upper_left_lip2->flag[WAVE_HAND_RIGHT] = right_hand->flag[LOWER_HAND] = head2->flag[LOWER_HAND] = head->flag[LOWER_HAND] = right_arm->flag[LOWER_HAND] = right_forearm->flag[LOWER_HAND] = lower_right_lip2->flag[LOWER_HAND] = lower_left_lip2->flag[LOWER_HAND] = lower_right_lip1->flag[LOWER_HAND] = lower_left_lip1->flag[LOWER_HAND] = upper_right_lip1->flag[LOWER_HAND] = upper_left_lip1->flag[LOWER_HAND] = upper_right_lip2->flag[LOWER_HAND] = upper_left_lip2->flag[LOWER_HAND] = true;
}

void AnimationBuilder::clench_fist()
{
    num_keyframes[CLENCH_FIST] = NUM_KEYFRAMES_CLENCH_FIST  ;
    num_keyframes[UNCLENCH_FIST] = NUM_KEYFRAMES_UNCLENCH_FIST ;

    right_thumb1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_thumb3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    left_thumb1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_thumb3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_index3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    left_middle1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_middle3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_ring3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky1->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky2->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    left_pinky3->animations[CLENCH_FIST] = glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    
    right_thumb1->flag[CLENCH_FIST] = right_thumb2->flag[CLENCH_FIST] = right_thumb3->flag[CLENCH_FIST] = right_index1->flag[CLENCH_FIST] = right_index2->flag[CLENCH_FIST] = right_index3->flag[CLENCH_FIST] = right_middle1->flag[CLENCH_FIST] = right_middle2->flag[CLENCH_FIST] = right_middle3->flag[CLENCH_FIST] = right_ring1->flag[CLENCH_FIST] = right_ring2->flag[CLENCH_FIST] = right_ring3->flag[CLENCH_FIST] = right_pinky1->flag[CLENCH_FIST] = right_pinky2->flag[CLENCH_FIST] = right_pinky3->flag[CLENCH_FIST] = left_thumb1->flag[CLENCH_FIST] = left_thumb3->flag[CLENCH_FIST] = left_index2->flag[CLENCH_FIST] = left_thumb2->flag[CLENCH_FIST] = left_index1->flag[CLENCH_FIST] = left_index3->flag[CLENCH_FIST] = left_middle1->flag[CLENCH_FIST] = left_middle2->flag[CLENCH_FIST] = right_middle3->flag[CLENCH_FIST] = left_ring1->flag[CLENCH_FIST] = left_ring2->flag[CLENCH_FIST] = left_ring3->flag[CLENCH_FIST] = left_pinky1->flag[CLENCH_FIST] = left_pinky2->flag[CLENCH_FIST] = left_pinky3->flag[CLENCH_FIST] = right_thumb1->flag[UNCLENCH_FIST] = right_thumb2->flag[UNCLENCH_FIST] = right_thumb3->flag[UNCLENCH_FIST] = right_index1->flag[UNCLENCH_FIST] = right_index2->flag[UNCLENCH_FIST] = right_index3->flag[UNCLENCH_FIST] = right_middle1->flag[UNCLENCH_FIST] = right_middle2->flag[UNCLENCH_FIST] = right_middle3->flag[UNCLENCH_FIST] = right_ring1->flag[UNCLENCH_FIST] = right_ring2->flag[UNCLENCH_FIST] = right_ring3->flag[UNCLENCH_FIST] = right_pinky1->flag[UNCLENCH_FIST] = right_pinky2->flag[UNCLENCH_FIST] = right_pinky3->flag[UNCLENCH_FIST] = left_thumb1->flag[UNCLENCH_FIST] = left_thumb3->flag[UNCLENCH_FIST] = left_index2->flag[UNCLENCH_FIST] = left_thumb2->flag[UNCLENCH_FIST] = left_index1->flag[UNCLENCH_FIST] = left_index3->flag[UNCLENCH_FIST] = left_middle1->flag[UNCLENCH_FIST] = left_middle2->flag[UNCLENCH_FIST] = right_middle3->flag[UNCLENCH_FIST] = left_ring1->flag[UNCLENCH_FIST] = left_ring2->flag[UNCLENCH_FIST] = left_ring3->flag[UNCLENCH_FIST] = left_pinky1->flag[UNCLENCH_FIST] = left_pinky2->flag[UNCLENCH_FIST] = left_pinky3->flag[UNCLENCH_FIST] = true ;
}

void AnimationBuilder::scratch_head()
{
    num_keyframes[PUT_HAND_ON_HEAD] = NUM_KEYFRAMES_PUT_HAND_ON_HEAD ;
    num_keyframes[SCRATCH_INWARDS] = NUM_KEYFRAMES_SCRATCH_INWARDS ;
    num_keyframes[SCRATCH_OUTWARDS] = NUM_KEYFRAMES_SCRATCH_OUTWARDS ;
    num_keyframes[RESET_HANDS] = NUM_KEYFRAMES_RESET_HANDS ;
    
    right_arm->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(120.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    right_forearm->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_hand->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(12.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_index1->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index2->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle2->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[PUT_HAND_ON_HEAD] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(120.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    right_forearm->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_hand->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(12.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_index1->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_index2->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index2->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_index3->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle2->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle2->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_middle3->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring2->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring3->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky2->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[SCRATCH_INWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(70.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_pinky3->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(50.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(120.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * glm::rotate( glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f) ) ;
    right_forearm->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(90.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_hand->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(12.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_index1->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ) ;
    right_middle1->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_ring1->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_pinky1->animations[SCRATCH_OUTWARDS] = glm::rotate( glm::mat4(1.0f), glm::radians(30.0f), glm::vec3( 1.0f, 0.0f, 1.0f ) ) ;
    right_arm->animations[RESET_HANDS] = glm::rotate( glm::mat4(1.0f), glm::radians(27.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;
    right_forearm->animations[RESET_HANDS] = glm::rotate( glm::mat4(1.0f), glm::radians(14.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) ) ;

    right_pinky3->flag[PUT_HAND_ON_HEAD] = right_pinky2->flag[PUT_HAND_ON_HEAD] = right_pinky1->flag[PUT_HAND_ON_HEAD] = right_ring3->flag[PUT_HAND_ON_HEAD] = right_ring2->flag[PUT_HAND_ON_HEAD] = right_ring1->flag[PUT_HAND_ON_HEAD] = right_middle3->flag[PUT_HAND_ON_HEAD] = right_middle2->flag[PUT_HAND_ON_HEAD] = right_middle1->flag[PUT_HAND_ON_HEAD] = right_index3->flag[PUT_HAND_ON_HEAD] = right_index2->flag[PUT_HAND_ON_HEAD] = right_index1->flag[PUT_HAND_ON_HEAD] = right_forearm->flag[PUT_HAND_ON_HEAD] = right_arm->flag[PUT_HAND_ON_HEAD] = right_hand->flag[PUT_HAND_ON_HEAD] = right_index2->flag[SCRATCH_INWARDS] = right_index2->flag[SCRATCH_OUTWARDS] = right_index3->flag[SCRATCH_INWARDS] = right_index3->flag[SCRATCH_OUTWARDS] = right_middle2->flag[SCRATCH_INWARDS] = right_middle2->flag[SCRATCH_OUTWARDS] = right_middle3->flag[SCRATCH_INWARDS] = right_middle3->flag[SCRATCH_OUTWARDS] = right_ring2->flag[SCRATCH_INWARDS] = right_ring2->flag[SCRATCH_OUTWARDS] = right_ring3->flag[SCRATCH_INWARDS] = right_ring3->flag[SCRATCH_OUTWARDS] = right_pinky2->flag[SCRATCH_INWARDS] = right_pinky2->flag[SCRATCH_OUTWARDS] = right_pinky3->flag[SCRATCH_INWARDS] = right_pinky3->flag[SCRATCH_OUTWARDS] = right_arm->flag[SCRATCH_INWARDS] = right_forearm->flag[SCRATCH_INWARDS] = right_hand->flag[SCRATCH_INWARDS] = right_index1->flag[SCRATCH_INWARDS] = right_middle1->flag[SCRATCH_INWARDS] = right_ring1->flag[SCRATCH_INWARDS] = right_pinky1->flag[SCRATCH_INWARDS] = right_arm->flag[SCRATCH_OUTWARDS] = right_forearm->flag[SCRATCH_OUTWARDS] = right_hand->flag[SCRATCH_OUTWARDS] = right_index1->flag[SCRATCH_OUTWARDS] = right_middle1->flag[SCRATCH_OUTWARDS] = right_ring1->flag[SCRATCH_OUTWARDS] = right_pinky1->flag[SCRATCH_OUTWARDS] = right_arm->flag[RESET_HANDS] = right_forearm->flag[RESET_HANDS] = right_hand->flag[RESET_HANDS] = right_index1->flag[RESET_HANDS] = right_index2->flag[RESET_HANDS] = right_index3->flag[RESET_HANDS] = right_middle1->flag[RESET_HANDS] = right_middle2->flag[RESET_HANDS] = right_middle3->flag[RESET_HANDS] = right_ring1->flag[RESET_HANDS] = right_ring2->flag[RESET_HANDS] = right_ring3->flag[RESET_HANDS] = right_pinky1->flag[RESET_HANDS] = right_pinky2->flag[RESET_HANDS] = right_pinky3->flag[RESET_HANDS] = true ;
}

void AnimationBuilder::smile()
{
    num_keyframes[SMILE] = NUM_KEYFRAMES_SMILE ;
    num_keyframes[FROWN] = NUM_KEYFRAMES_FROWN ;
    
    upper_right_lip2->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_left_lip2->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_right_lip2->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(-0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    lower_left_lip2->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.015f, 0.0f, 0.0f) ) * glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.015f) ) ;
    upper_right_lip1->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    upper_left_lip1->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.01f) ) ;
    lower_right_lip1->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    lower_left_lip1->animations[SMILE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.01f) ) ;
    
    lower_right_lip2->flag[SMILE] = lower_left_lip2->flag[SMILE] = lower_right_lip1->flag[SMILE] = lower_left_lip1->flag[SMILE] = upper_right_lip1->flag[SMILE] = upper_left_lip1->flag[SMILE] = upper_right_lip2->flag[SMILE] = upper_left_lip2->flag[SMILE] = upper_right_lip1->flag[FROWN] = upper_left_lip1->flag[FROWN] = upper_right_lip2->flag[FROWN] = upper_left_lip2->flag[FROWN] = lower_right_lip1->flag[FROWN] = lower_left_lip1->flag[FROWN] = lower_right_lip2->flag[FROWN] = lower_left_lip2->flag[FROWN] = true ;
}

void AnimationBuilder::blink()
{
    num_keyframes[OPEN_EYE] = NUM_KEYFRAMES_OPEN_EYE ;
    num_keyframes[CLOSE_EYE] = NUM_KEYFRAMES_CLOSE_EYE ;
    
    right_eyelid_top1->animations[CLOSE_EYE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.02f) ) ;
    right_eyelid_top2->animations[CLOSE_EYE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.02f) ) ;
    right_eyelid_top3->animations[CLOSE_EYE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.02f) ) ;
    left_eyelid_top1->animations[CLOSE_EYE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.02f) ) ;
    left_eyelid_top2->animations[CLOSE_EYE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.02f) ) ;
    left_eyelid_top3->animations[CLOSE_EYE] = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.02f) ) ;
    
    right_eyelid_top1->flag[OPEN_EYE] = right_eyelid_top2->flag[OPEN_EYE] = right_eyelid_top3->flag[OPEN_EYE] = left_eyelid_top1->flag[OPEN_EYE] = left_eyelid_top2->flag[OPEN_EYE] = left_eyelid_top3->flag[OPEN_EYE] = right_eyelid_top1->flag[CLOSE_EYE] = right_eyelid_top2->flag[CLOSE_EYE] = right_eyelid_top3->flag[CLOSE_EYE] = left_eyelid_top1->flag[CLOSE_EYE] = left_eyelid_top2->flag[CLOSE_EYE] = left_eyelid_top3->flag[CLOSE_EYE] = true ;
}

std::vector<float> AnimationBuilder::get_num_keyframes()
{
    return num_keyframes ;
}

std::vector<bool> AnimationBuilder::get_precomputed_animations()
{
    return is_precomputed ;
}

void AnimationBuilder::generate_error( std::string msg )
{
    std::cout << msg << std::endl ;
    
    exit(1) ;
}

AnimationBuilder::~AnimationBuilder(){}
