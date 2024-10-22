#include "Renderer.h"
#include "../external/include/stb_image_write.h"



Renderer::Renderer( GLFWwindow * window_): fps(0), fps_time(0), window(window_), frameNumber(0)
{
    camera = new Camera() ;
    man = new Man( camera->get_view(), camera->get_projection(), camera->get_camera_position() ) ;
    skybox = new Skybox( camera->get_view(), camera->get_projection(), camera->get_camera_position()) ;
}



void Renderer::set()
{
    man->set(skybox) ;
}



void Renderer::start_game_loop()
{
    time = glfwGetTime() ;
    update_view() ;
    while( !glfwWindowShouldClose(window) ){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        glClearColor(0.0f, 0.0f, 0.0f,1.0f) ;
        skybox->activate() ;
        skybox->render() ;
        man->render() ;
        glfwSwapBuffers(window) ;
        handle_events() ;
        calculate_fps() ;
    }
}

void Renderer::handle_events()
{
    glfwPollEvents() ;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        camera->look_around(false,false,true,false) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        camera->look_around(false,false,false,true) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        camera->look_around(true,false,false,false) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        camera->look_around(false,true,false,false) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){
        camera->move() ;
        update_view() ;
    }
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ){
        man->set_animation( WALK_ANIMATION, 0.0f ) ;
        update_view() ;
    }
    if( glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS ){
        man->set_animation( RUN_ANIMATION, 0.0f ) ;
        update_view() ;
    }
    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){
        man->set_animation( WALK_ANIMATION, TURN_RIGHT ) ;
        update_view() ;
    }
    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){
        man->set_animation( WALK_ANIMATION, TURN_LEFT ) ;
        update_view() ;
    }
    if( glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS ){
        man->set_animation( STAND_ANIMATION ) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
        man->set_animation( SIT_ANIMATION ) ;
        update_view() ;
    }
    if( glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS ){
        man->set_animation( BREATH ) ;
        update_view() ;
    }
    if( glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS ){
        man->set_animation( BLINK ) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        man->set_animation( GRIN ) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){
        man->set_animation( MAKE_FIST ) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS){
        man->set_animation( CHECK_WATCH ) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){
        man->set_animation( LOOK_AROUND ) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS){
        man->set_animation( SAY_HI ) ;
        update_view() ;
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS){
        man->set_animation( SCRATCH_HEAD ) ;
        update_view() ;
    }
}



void Renderer::update_view()
{
    man->update_view( camera->get_camera_position(), camera->get_view() ) ;
    skybox->update_view( camera->get_view(), camera->get_camera_position() ) ;
}



void Renderer::calculate_fps()
{
    fps++ ;
    if( glfwGetTime() - static_cast<float>(fps_time) >= 1.0 ){
        std::cout << "FPS: \033[1;31m" << fps << "\033[0m" << '\r' << std::flush ;
        fps = 0 ;
        fps_time += 1.0 ;
    }
}



void Renderer::generate_error( std::string error_msg )
{
    std::cout << "\033[1;31m" << error_msg << "\033[0m" << std::endl;
    exit(1) ;
}



Renderer::~Renderer()
{
    delete man ;
    man = NULL ;
    delete camera ;
    camera = NULL ;
    delete skybox ;
    skybox = NULL ;
}
