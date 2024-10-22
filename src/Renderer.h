#include "Camera.h"




class Renderer{
    
private:
    
    Man * man ;
    Skybox * skybox ;
    Camera * camera ;
    GLFWwindow * window ;
    int fps, frameNumber ;
    float fps_time, time ;

public:
    
    Renderer( GLFWwindow * window_ ) ;
    void set() ;
    void start_game_loop() ;
    void write_frame() ; 
    void handle_events() ;
    void update_view() ;
    void calculate_fps() ;
    void generate_error( std::string error_msg ) ;
    ~Renderer() ;
} ;
