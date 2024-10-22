#include "AnimationComputer.h"




AnimationComputer::AnimationComputer()
{
    walking_speed = 0.075f ; 
    running_speed = 0.15f ;
}

void AnimationComputer::set( Bone * rootbone, std::vector<float> numkeyframes )
{
    root_bone = rootbone ;
    num_keyframes = numkeyframes ;
}

glm::mat4 AnimationComputer::run( float angle, glm::vec3 &position, glm::vec3 direction, float keyframe )
{
    float start = 0.0f ;
    float end = NUM_KEYFRAMES_LEFT_SPRINT ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, running_speed ) ;
        return compute_transformation( position, angle ) ;
    }
    start += NUM_KEYFRAMES_LEFT_SPRINT ;
    end += NUM_KEYFRAMES_MERGE_RIGHT ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, running_speed/3.0f ) ;
        return compute_transformation( position, angle ) ;
    }
    
    start += NUM_KEYFRAMES_MERGE_RIGHT ;
    end += NUM_KEYFRAMES_RIGHT_SPRINT ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, running_speed ) ;
        return compute_transformation( position, angle ) ;
    }
    
    start += NUM_KEYFRAMES_RIGHT_SPRINT ;
    end += NUM_KEYFRAMES_MERGE_LEFT ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, running_speed/3.0f ) ;
        return compute_transformation( position, angle ) ;
    }
}

glm::mat4 AnimationComputer::walk( float angle, glm::vec3 &position, glm::vec3 direction, float keyframe )
{
    float start = 0.0f ;
    float end = NUM_KEYFRAMES_LEFT_STRIDE ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, walking_speed ) ;
        return compute_transformation( position, angle ) ;
    }
    
    start += NUM_KEYFRAMES_LEFT_STRIDE ;
    end += NUM_KEYFRAMES_JOIN_RIGHT ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, walking_speed/3.0f ) ;
        return compute_transformation( position, angle ) ;
    }
    
    start += NUM_KEYFRAMES_JOIN_RIGHT ;
    end += NUM_KEYFRAMES_RIGHT_STRIDE ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, walking_speed ) ;
        return compute_transformation( position, angle ) ;
    }
    
    start += NUM_KEYFRAMES_RIGHT_STRIDE ;
    end += NUM_KEYFRAMES_JOIN_LEFT ;
    if( ( keyframe >= start) && ( keyframe < end ) ){
        update_position( position, direction, walking_speed/3.0f ) ;
        return compute_transformation( position, angle ) ;
    }
}

void AnimationComputer::update_position( glm::vec3 &position, glm::vec3 direction, float speed )
{
    position += (speed)*direction ;
    position.y = -0.3f ;
}

glm::mat4 AnimationComputer::compute_transformation( glm::vec3 position, float angle )
{
    return glm::translate( glm::mat4(1.0f), position ) * glm::rotate( glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale( glm::mat4(1.0f), glm::vec3( 0.01f, 0.01f, 0.01f ) ) ;
}

glm::mat4 AnimationComputer::compute_animations( Bone * bone, int active_animation, float ratio )
{
    return recompose( interpolate( decompose( bone->local_transformation ), decompose( bone->animations[active_animation] ), easeInOut(ratio)) ) ;
}

void AnimationComputer::precompute_animations()
{
    setup_animations( root_bone, {LEFT_SPRINT, MERGE_RIGHT, RIGHT_SPRINT, MERGE_LEFT}, RUN_ANIMATION );
    blend_animations( {LEFT_SPRINT, MERGE_RIGHT, RIGHT_SPRINT, MERGE_LEFT}, RUN_ANIMATION, MERGE_LEFT ) ;
    merge_animations( root_bone, {LEFT_SPRINT, MERGE_RIGHT, RIGHT_SPRINT, MERGE_LEFT}, RUN_ANIMATION) ;

    setup_animations( root_bone, {LEFT_STRIDE, JOIN_RIGHT, RIGHT_STRIDE, JOIN_LEFT}, WALK_ANIMATION);
    blend_animations( {LEFT_STRIDE, JOIN_RIGHT, RIGHT_STRIDE, JOIN_LEFT}, WALK_ANIMATION, JOIN_LEFT ) ;
    merge_animations( root_bone, {LEFT_STRIDE, JOIN_RIGHT, RIGHT_STRIDE, JOIN_LEFT}, WALK_ANIMATION) ;
    
    setup_animations( root_bone, {CLOSE_EYE, OPEN_EYE}, BLINK ) ;
    blend_animations( {CLOSE_EYE, OPEN_EYE}, BLINK, STAND_ANIMATION ) ;
    merge_animations( root_bone, {CLOSE_EYE, OPEN_EYE}, BLINK ) ;
    
    setup_animations( root_bone, {INHALE, EXHALE}, BREATH ) ;
    blend_animations( {INHALE, EXHALE}, BREATH, STAND_ANIMATION ) ;
    merge_animations( root_bone, {INHALE, EXHALE}, BREATH ) ;

    setup_animations( root_bone, {SMILE, FROWN}, GRIN ) ;
    blend_animations( {SMILE, FROWN}, GRIN, STAND_ANIMATION ) ;
    merge_animations( root_bone, {SMILE, FROWN}, GRIN ) ;

    setup_animations( root_bone, {CHECK_WRIST, RESET_ARM}, CHECK_WATCH ) ;
    blend_animations( {CHECK_WRIST, RESET_ARM}, CHECK_WATCH, STAND_ANIMATION ) ;
    merge_animations( root_bone, {CHECK_WRIST, RESET_ARM}, CHECK_WATCH ) ;

    setup_animations( root_bone, {CLENCH_FIST, UNCLENCH_FIST}, MAKE_FIST ) ;
    blend_animations( {CLENCH_FIST, UNCLENCH_FIST}, MAKE_FIST, STAND_ANIMATION ) ;
    merge_animations( root_bone, {CLENCH_FIST, UNCLENCH_FIST}, MAKE_FIST ) ;

    setup_animations( root_bone, {RAISE_HAND, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, LOWER_HAND}, SAY_HI ) ;
    blend_animations( {RAISE_HAND, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, LOWER_HAND}, SAY_HI, STAND_ANIMATION ) ;
    merge_animations( root_bone, {RAISE_HAND, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, WAVE_HAND_LEFT, WAVE_HAND_RIGHT, LOWER_HAND}, SAY_HI ) ;

    setup_animations( root_bone, {PUT_HAND_ON_HEAD, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, RESET_HANDS}, SCRATCH_HEAD ) ;
    blend_animations( {PUT_HAND_ON_HEAD, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, RESET_HANDS}, SCRATCH_HEAD, STAND_ANIMATION ) ;
    merge_animations( root_bone, {PUT_HAND_ON_HEAD, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, SCRATCH_INWARDS, SCRATCH_OUTWARDS, RESET_HANDS}, SCRATCH_HEAD ) ;
    
    setup_animations( root_bone, {RIGHT_HEAD_ANIMATION, LEFT_HEAD_ANIMATION, UP_HEAD_ANIMATION, DOWN_HEAD_ANIMATION, RESET_HEAD}, LOOK_AROUND ) ;
    blend_animations( {RIGHT_HEAD_ANIMATION, LEFT_HEAD_ANIMATION, UP_HEAD_ANIMATION, DOWN_HEAD_ANIMATION, RESET_HEAD}, LOOK_AROUND, STAND_ANIMATION ) ;
    merge_animations( root_bone, {RIGHT_HEAD_ANIMATION, LEFT_HEAD_ANIMATION, UP_HEAD_ANIMATION, DOWN_HEAD_ANIMATION, RESET_HEAD}, LOOK_AROUND ) ;
}

void AnimationComputer::setup_animations( Bone * bone, std::vector<int> animations, int target)
{
    for( int i = 0 ; i < animations.size() ; i++ ){
        bone->precomputed_animations[animations[i]].resize( num_keyframes[animations[i]] ) ;
        bone->precomputed_animations[target].resize( bone->precomputed_animations[target].size() + num_keyframes[animations[i]] ) ;
    }
    for( int i = 0 ; i < bone->children.size() ; i++ )
        setup_animations( bone->children[i], animations, target ) ;
}

void AnimationComputer::blend_animations( std::vector<int> animations, int target, int base )
{
    int active_animation, start_animation ;
    for( int i = 0 ; i < animations.size() ; i++ ){
        active_animation = animations[i] ;
        start_animation = (i==0)? base: animations[i-1] ;
        num_keyframes[target] += num_keyframes[active_animation] ;
        for( float keyframe = 0.0f ; keyframe < num_keyframes[active_animation] ; keyframe++ )
            apply_animations( root_bone, keyframe, active_animation, start_animation, num_keyframes[active_animation], target ) ;
    }
}

void AnimationComputer::merge_animations( Bone * bone, std::vector<int> animations, int target)
{
    float global_keyframe = 0 ;
    for( int i = 0 ; i < animations.size() ; i++ ){
        int animation_index = animations[i] ;
        for( float local_keyframe = 0.0f ; local_keyframe < num_keyframes[animation_index] ; local_keyframe++ ){
            bone->precomputed_animations[target][global_keyframe] = bone->precomputed_animations[animation_index][local_keyframe] ;
            global_keyframe++ ;
        }
    }
    for( int i = 0 ; i < bone->children.size() ; i++ )
        merge_animations( bone->children[i], animations, target ) ;
}

void AnimationComputer::apply_animations( Bone * bone, float keyframe, int active_animation, int start_animation, float num_keyframes, int target )
{
    if( bone->flag[active_animation] ){
        bone->flag[target] = true ;
        bone->precomputed_animations[active_animation][keyframe] = recompose( interpolate( decompose( bone->animations[start_animation] ), decompose( bone->animations[active_animation] ), easeInOut(keyframe/num_keyframes)) ) ;
    }
    for( int i = 0 ; i < bone->children.size() ; i++ )
        apply_animations( bone->children[i], keyframe, active_animation, start_animation, num_keyframes, target ) ;
}

DecomposedTransformation AnimationComputer::interpolate( DecomposedTransformation dt1, DecomposedTransformation dt2, float factor )
{
    DecomposedTransformation result ;
    
    result.translate = glm::mix( dt1.translate, dt2.translate, factor);
    result.rotate = glm::slerp( dt1.rotate, dt2.rotate, factor ) ;
    result.scale = glm::mix( dt1.scale, dt2.scale, factor ) ;
    
    return result;
}

DecomposedTransformation AnimationComputer::decompose( glm::mat4 transformation )
{
    DecomposedTransformation dt ;
    
    dt.translate = glm::vec3( transformation[3] ) ;
    dt.scale = glm::vec3( glm::length(transformation[0]), glm::length(transformation[1]), glm::length(transformation[2]) ) ;
    dt.rotate = glm::quat_cast( glm::mat3(glm::normalize(transformation[0]), glm::normalize(transformation[1]), glm::normalize(transformation[2])) ) ;
    
    return dt ;
}

glm::mat4 AnimationComputer::recompose( DecomposedTransformation dt )
{
    return glm::translate(glm::mat4(1.0f), dt.translate) * glm::toMat4(dt.rotate) * glm::scale(glm::mat4(1.0f), dt.scale) ;
}

float AnimationComputer::easeInOut( float t )
{
    return t * t * (3.0f - 2.0f * t) ;
}

std::vector<float> AnimationComputer::get_num_keyframes()
{
    return num_keyframes ; 
}

AnimationComputer::~AnimationComputer(){}
