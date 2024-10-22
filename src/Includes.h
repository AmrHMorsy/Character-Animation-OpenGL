#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include <map>
#include <chrono>
#include <string>
#include <stdio.h>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdlib.h>
#include <queue>
#include <unistd.h>
#include <algorithm>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
#include <OpenGL/OpenGL.h>
#pragma clang diagnostic pop

using namespace std ;







// Animations
// --------------------------------------------------------------------------------------------

// Number of Animations
#define NUM_ANIMATIONS 43

// Stand Animation Index
#define STAND_ANIMATION 0
    #define NUM_KEYFRAMES_STAND 50.0f

// Sit Animation Index
#define SIT_ANIMATION 1
    #define NUM_KEYFRAMES_SIT 30.0f

// Walk Animation Indices
#define WALK_ANIMATION 2            // --> Press W to Walk
    #define LEFT_STRIDE 3
    #define NUM_KEYFRAMES_LEFT_STRIDE 20.0f
    #define JOIN_RIGHT 4
    #define NUM_KEYFRAMES_JOIN_RIGHT 20.0f
    #define RIGHT_STRIDE 5
    #define NUM_KEYFRAMES_RIGHT_STRIDE 20.0f
    #define JOIN_LEFT 6
    #define NUM_KEYFRAMES_JOIN_LEFT 20.0f

// Run Animation Indices
#define RUN_ANIMATION 7
    #define LEFT_SPRINT 8
    #define NUM_KEYFRAMES_LEFT_SPRINT 20.0f
    #define MERGE_RIGHT 9
    #define NUM_KEYFRAMES_MERGE_RIGHT 20.0f
    #define RIGHT_SPRINT 10
    #define NUM_KEYFRAMES_RIGHT_SPRINT 20.0f
    #define MERGE_LEFT 11
    #define NUM_KEYFRAMES_MERGE_LEFT 20.0f

#define IDLE_ANIMATIONS_STARTING_INDEX 12
// Breath Animation Indices
#define BREATH 12                    // --> Press 1 to Breath
    #define INHALE 13
    #define NUM_KEYFRAMES_INHALE 100.0f
    #define EXHALE 14
    #define NUM_KEYFRAMES_EXHALE 100.0f

// Blink Animation Indices
#define BLINK 15                    // --> Press 2 to Blink
    #define OPEN_EYE 16
    #define NUM_KEYFRAMES_OPEN_EYE 50.0f
    #define CLOSE_EYE 17
    #define NUM_KEYFRAMES_CLOSE_EYE 50.0f

// Grin Animation Indices
#define GRIN 18                    // --> Press 3 to Grin
    #define SMILE 19
    #define NUM_KEYFRAMES_SMILE 100.0f
    #define FROWN 20
    #define NUM_KEYFRAMES_FROWN 50.0f


// Make Fist Animation Indices
#define MAKE_FIST 21                // --> Press 4 to Make Fist
    #define CLENCH_FIST 22
    #define NUM_KEYFRAMES_CLENCH_FIST 100.0f
    #define UNCLENCH_FIST 23
    #define NUM_KEYFRAMES_UNCLENCH_FIST 100.0f

// Check Watch Animation Indices
#define CHECK_WATCH 24              // --> Press 5 to Check Watch
    #define CHECK_WRIST 25
    #define NUM_KEYFRAMES_CHECK_WRIST 50.0f
    #define RESET_ARM 26
    #define NUM_KEYFRAMES_RESET_ARM 50.0f

// Look Around Animation Indices
#define LOOK_AROUND 27             // --> Press 6 to Look Around
    #define RIGHT_HEAD_ANIMATION 28
    #define NUM_KEYFRAMES_RIGHT_HEAD_ANIMATION 100.0f
    #define LEFT_HEAD_ANIMATION 29
    #define NUM_KEYFRAMES_LEFT_HEAD_ANIMATION 100.0f
    #define UP_HEAD_ANIMATION 30
    #define NUM_KEYFRAMES_UP_HEAD_ANIMATION 100.0f
    #define DOWN_HEAD_ANIMATION 31
    #define NUM_KEYFRAMES_DOWN_HEAD_ANIMATION 100.0f
    #define RESET_HEAD 32
    #define NUM_KEYFRAMES_RESET_HEAD 100.0f

// Say Hi Animation Indices
#define SAY_HI 33                   // --> Press 7 to Say Hi
    #define RAISE_HAND 34
    #define NUM_KEYFRAMES_RAISE_HAND 50.0f
    #define WAVE_HAND_LEFT 35
    #define NUM_KEYFRAMES_WAVE_HAND_LEFT 50.0f
    #define WAVE_HAND_RIGHT 36
    #define NUM_KEYFRAMES_WAVE_HAND_RIGHT 50.0f
    #define LOWER_HAND 37
    #define NUM_KEYFRAMES_LOWER_HAND 50.0f

// Scratch Head Animation Indices
#define SCRATCH_HEAD 38             // --> Press 8 to Scratch Head
    #define PUT_HAND_ON_HEAD 39
    #define NUM_KEYFRAMES_PUT_HAND_ON_HEAD 30.0f
    #define SCRATCH_INWARDS 40
    #define NUM_KEYFRAMES_SCRATCH_INWARDS 30.0f
    #define SCRATCH_OUTWARDS 41
    #define NUM_KEYFRAMES_SCRATCH_OUTWARDS 30.0f
    #define RESET_HANDS 42
    #define NUM_KEYFRAMES_RESET_HANDS 30.0f

// --------------------------------------------------------------------------------------------



// Directions
// --------------------------------------------------------------------------------------------

#define TURN_RIGHT -2.0f
#define TURN_LEFT 2.0f

// --------------------------------------------------------------------------------------------



// Bones
// --------------------------------------------------------------------------------------------
// These are the names given to the bones of the 3D character model.
#define LEFT_ARM "DEF-upper_arm.L"
#define RIGHT_ARM "DEF-upper_arm.R"
#define LEFT_FOREARM "DEF-forearm.L"
#define RIGHT_FOREARM "DEF-forearm.R"
#define LEFT_THIGH "DEF-thigh.L"
#define RIGHT_THIGH "DEF-thigh.R"
#define LEFT_SHIN "DEF-shin.L"
#define RIGHT_SHIN "DEF-shin.R"
#define LEFT_SHIN2 "DEF-shin.L.001"
#define RIGHT_SHIN2 "DEF-shin.R.001"
#define HEAD "ORG-spine.005"
#define HEAD2 "DEF-spine.005"
#define LEFT_THUMB1 "DEF-thumb.01.L"
#define LEFT_THUMB2 "DEF-thumb.02.L"
#define LEFT_THUMB3 "DEF-thumb.03.L"
#define RIGHT_THUMB1 "DEF-thumb.01.R"
#define RIGHT_THUMB2 "DEF-thumb.02.R"
#define RIGHT_THUMB3 "DEF-thumb.03.R"
#define RIGHT_INDEX1 "DEF-f_index.01.R"
#define RIGHT_INDEX2 "DEF-f_index.02.R"
#define RIGHT_INDEX3 "DEF-f_index.03.R"
#define RIGHT_MIDDLE1 "DEF-f_middle.01.R"
#define RIGHT_MIDDLE2 "DEF-f_middle.02.R"
#define RIGHT_MIDDLE3 "DEF-f_middle.03.R"
#define RIGHT_RING1 "DEF-f_ring.01.R"
#define RIGHT_RING2 "DEF-f_ring.02.R"
#define RIGHT_RING3 "DEF-f_ring.03.R"
#define RIGHT_PINKY1 "DEF-f_pinky.01.R"
#define RIGHT_PINKY2 "DEF-f_pinky.02.R"
#define RIGHT_PINKY3 "DEF-f_pinky.03.R"
#define LEFT_INDEX1 "DEF-f_index.01.L"
#define LEFT_INDEX2 "DEF-f_index.02.L"
#define LEFT_INDEX3 "DEF-f_index.03.L"
#define LEFT_MIDDLE1 "DEF-f_middle.01.L"
#define LEFT_MIDDLE2 "DEF-f_middle.02.L"
#define LEFT_MIDDLE3 "DEF-f_middle.03.L"
#define LEFT_RING1 "DEF-f_ring.01.L"
#define LEFT_RING2 "DEF-f_ring.02.L"
#define LEFT_RING3 "DEF-f_ring.03.L"
#define LEFT_PINKY1 "DEF-f_pinky.01.L"
#define LEFT_PINKY2 "DEF-f_pinky.02.L"
#define LEFT_PINKY3 "DEF-f_pinky.03.L"
#define DIAPHRAM "ORG-spine.003"
#define LOWER_LIP_RIGHT1 "DEF-lip.B.R"
#define LOWER_LIP_LEFT1 "DEF-lip.B.L"
#define UPPER_LIP_RIGHT1 "DEF-lip.T.R"
#define UPPER_LIP_LEFT1 "DEF-lip.T.L"
#define LOWER_LIP_RIGHT2 "DEF-lip.B.R.001"
#define LOWER_LIP_LEFT2 "DEF-lip.B.L.001"
#define UPPER_LIP_RIGHT2 "DEF-lip.T.R.001"
#define UPPER_LIP_LEFT2 "DEF-lip.T.L.001"
#define RIGHT_HAND "DEF-hand.R"
#define LEFT_HAND "DEF-hand.L"
#define RIGHT_EYEBROW "DEF-brow.B.R"
#define LEFT_EYEBROW "DEF-brow.B.L"
#define RIGHT_EYELID_TOP1 "DEF-lid.T.R.001"
#define RIGHT_EYELID_TOP2 "DEF-lid.T.R.002"
#define RIGHT_EYELID_TOP3 "DEF-lid.T.R.003"
#define LEFT_EYELID_TOP1 "DEF-lid.T.L.001"
#define LEFT_EYELID_TOP2 "DEF-lid.T.L.002"
#define LEFT_EYELID_TOP3 "DEF-lid.T.L.003"
#define LOWER_BODY "ORG-spine"
#define LEFT_FOOT "DEF-foot.L"
#define RIGHT_FOOT "DEF-foot.R"
#define SPINE "spine_fk"
#define SPINE1 "spine_fk.001"
#define SPINE2 "spine_fk.002"
#define UPPER_BODY "DEF-spine"
#define UPPER_BODY1 "DEF-spine.001"
#define UPPER_BODY2 "DEF-spine.002"

// --------------------------------------------------------------------------------------------








// Structures
// --------------------------------------------------------------------------------------------

struct Bone {
    Bone * parent ;
    std::string name ;
    std::vector<bool> flag ;
    std::vector<Bone*> children ;
    std::vector<glm::mat4> animations ;
    std::vector< std::vector<unsigned int> > affected_vertices ;
    std::vector< std::vector<glm::mat4> > precomputed_animations ;
    glm::mat4 offset, inverse_offset, transformation, local_transformation ;
} ;


struct Mesh {
    glm::vec3 albedo ;
    float metallic, roughness ;
    int num_vertices ;
    float * vertices ;
    int num_indices ;
    unsigned int * indices ;
    float * original_vertices ;
    std::vector<std::vector<Bone*>> bones ;
    std::vector<std::vector<float>> weights ;
} ;

struct MinMesh{
    glm::vec3 albedo ;
    float metallic, roughness ;
    int num_vertices ;
    float * vertices ;
    int num_indices ;
    unsigned int * indices ;
    float * original_vertices ;
} ;


struct DecomposedTransformation{
    glm::quat rotate ;
    glm::vec3 translate, scale ;
} ;


// --------------------------------------------------------------------------------------------
