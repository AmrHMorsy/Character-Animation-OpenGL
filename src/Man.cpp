#include "Man.h"
#include "../external/Include/stb_image.h"
#define EPSILON 1.8






Man::Man( glm::mat4 v, glm::mat4 proj, glm::vec3 c ): view(v), projection(proj), camera(c)
{
    initialize_variables() ;
    load_FBXModel() ;
    load_shaders() ;
    generate_buffers() ;
    load_textures() ;
    bind_vertices() ;
    bind_indices() ;
    set_uniform_variables() ;
}

void Man::initialize_variables()
{
    lock = false ;
    current_animation = LEFT_STRIDE ;
    position = 0.0f ;
    step = false ;
    time = 0.0f ;
    elapsed_time = 0.0f ;
    direction = glm::vec3( 0.0f, 0.0f, 1.0f ) ;
    light_position = glm::vec3( -5.0f, 34.0f, 66.0f ) ;
    light_color = glm::vec3( 1000.0f, 1000.0f, 1000.0f ) ;
    model = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, 0.0f) ) * glm::scale( glm::mat4(1.0f), glm::vec3( 0.01f, 0.01f, 0.01f ) ) ;
    file_paths = { "../assets/Man/Albedo.png", "../assets/Man/AO.png", "../assets/Man/Normal.png", "../assets/Man/Roughness.png", "../assets/Man/Displacement.png", "../assets/Man/Metallic.png", "../assets/Man/Opacity.png" } ;
}

void Man::load_FBXModel()
{
    parser = new Parser() ;
    parser->parse_fbx( "../assets/Man/Man.fbx" ) ;
    meshes = parser->get_meshes() ;
    num_meshes = meshes.size() ;
    animator = new Animator( parser->get_root_bone(), meshes, parser->get_num_keyframes(), parser->get_precomputed_animations(), parser->get_animation_computer() ) ;
}

void Man::load_shaders()
{
    shader = new Shader( "../external/Shaders/Object/Object_vs.vs", "../external/Shaders/Object/Object_fs.fs") ;
    shader_program = shader->get_shader_program() ;
    glUseProgram(shader_program) ;
}

void Man::set( Skybox * skybox )
{
    this->skybox = skybox ;
}

void Man::generate_buffers()
{
    num_indices.resize( num_meshes ) ;
    textures.resize( file_paths.size() ) ;
    vao.resize( num_meshes ) ;
    vbo.resize( num_meshes ) ;
    ebo.resize( num_meshes ) ;
    glGenTextures( file_paths.size(), textures.data() ) ;
    glGenVertexArrays( num_meshes, vao.data() ) ;
    glGenBuffers( num_meshes, vbo.data() ) ;
    glGenBuffers( num_meshes, ebo.data() ) ;
}

void Man::bind_vertices()
{
    for( int i = 0 ; i < num_meshes ; i++ ){
        glBindVertexArray( vao[i] ) ;
        glBindBuffer( GL_ARRAY_BUFFER, vbo[i] ) ;
        glBufferData( GL_ARRAY_BUFFER, meshes[i]->num_vertices * sizeof(float), meshes[i]->vertices, GL_STATIC_DRAW ) ;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8*sizeof(float)), (void*)0) ;
        glEnableVertexAttribArray(0) ;
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (8*sizeof(float)), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (8*sizeof(float)), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0) ;
    }
}

void Man::bind_indices()
{
    for( int i = 0 ; i < num_meshes ; i++ ){
        glBindVertexArray( vao[i] ) ;
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[i] ) ;
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, meshes[i]->num_indices*sizeof(int), meshes[i]->indices, GL_DYNAMIC_DRAW ) ;
        glBindVertexArray(0) ;
        num_indices[i] = meshes[i]->num_indices ;
    }
}

void Man::render()
{
    if( animator->animate() ){
        bind_vertices() ;
        model = animator->get_model() ; 
    }
    glUseProgram(shader_program) ;
    update_time() ;
    activate_textures() ;
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, &model[0][0]) ;
    for( int i = 0 ; i < num_meshes ; i++ ){
        glUniform3fv( glGetUniformLocation(shader_program, "alb"), 1, &meshes[i]->albedo[0] ) ;
        glUniform3fv( glGetUniformLocation(shader_program, "met"), 1, &meshes[i]->metallic ) ;
        glUniform3fv( glGetUniformLocation(shader_program, "rough"), 1, &meshes[i]->roughness ) ;
        glBindVertexArray( vao[i] ) ;
        glDrawElements( GL_TRIANGLES, num_indices[i], GL_UNSIGNED_INT, 0 ) ;
        glBindVertexArray( 0 ) ;
    }
}

void Man::update_time()
{
    float deltaTime = glfwGetTime() - time ;
    time += deltaTime ;
    elapsed_time += deltaTime ;
    glUniform1f(glGetUniformLocation(shader_program, "time"), time) ;
}

void Man::load_textures()
{
    GLenum format ;
    int w, h, nc ;
    unsigned char * data ;
    for( int i = 0 ; i < file_paths.size() ; i++ ){
        glBindTexture(GL_TEXTURE_2D, textures[i]) ;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT) ;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT) ;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) ;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;
        stbi_set_flip_vertically_on_load(true) ;
        data = stbi_load(file_paths[i].c_str(), &w, &h, &nc, 0);
        format = (nc==1)? GL_RED : (nc==3)? GL_RGB : (nc==4) ? GL_RGBA : GL_RGB ;
        if (data){
            glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data) ;
            glGenerateMipmap(GL_TEXTURE_2D) ;
        }
        else
            generate_error("Failure To Load Texture") ;
        stbi_image_free(data);
    }
}

void Man::set_uniform_variables()
{
    glUniform1i( glGetUniformLocation(shader_program, "albedo_map"), 0);
    glUniform1i( glGetUniformLocation(shader_program, "ao_map"), 1);
    glUniform1i( glGetUniformLocation(shader_program, "normal_map"), 2);
    glUniform1i( glGetUniformLocation(shader_program, "roughness_map"), 3);
    glUniform1i( glGetUniformLocation(shader_program, "displacement_map"), 4) ;
    glUniform1i( glGetUniformLocation(shader_program, "irradiance_map"), 5) ;
    glUniform1i( glGetUniformLocation(shader_program, "prefilter_map"), 6) ;
    glUniform1i( glGetUniformLocation(shader_program, "brdf_integration_map"), 7) ;
    glUniform1i( glGetUniformLocation(shader_program, "metallic_map"), 8) ;
    glUniform1i( glGetUniformLocation(shader_program, "opacity_map"), 9) ;
    glUniformMatrix4fv( glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, &projection[0][0]) ;
    glUniformMatrix4fv( glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform3fv( glGetUniformLocation(shader_program, "light_color"), 1, &light_color[0] );
    glUniform3fv( glGetUniformLocation(shader_program, "light_position"), 1, &light_position[0] );
    glUniform3fv( glGetUniformLocation(shader_program, "camera"), 1, &camera[0] ) ;
    glUniform1f( glGetUniformLocation(shader_program, "time"), time ) ;
}

void Man::update_view( glm::vec3 camera, glm::mat4 v )
{
    this->camera = camera ;
    glUseProgram(shader_program) ;
    glUniform3fv(glGetUniformLocation(shader_program, "camera"), 1, &camera[0]) ;
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, &v[0][0]) ;
}

void Man::activate_textures()
{
    for( int i = 0 ; i < textures.size()-2 ; i++ ){
        glActiveTexture(GL_TEXTURE0+i) ;
        glBindTexture(GL_TEXTURE_2D, textures[i]) ;
    }
    skybox->activate_irradiance() ;
    glActiveTexture(GL_TEXTURE8) ;
    glBindTexture(GL_TEXTURE_2D, textures[textures.size()-2]) ;
    glActiveTexture(GL_TEXTURE9) ;
    glBindTexture(GL_TEXTURE_2D, textures[textures.size()-1]) ;
}

void Man::set_animation( int animation )
{
    animator->set_animation( animation ) ;
}

void Man::set_animation( int animation, float requested_steer_angle )
{
    animator->set_direction( requested_steer_angle ) ;
    if( requested_steer_angle == 0.0f )
        animator->set_animation( animation ) ;
}

void Man::generate_error( std::string msg )
{
    std::cout << msg << std::endl ;
    exit(1) ;
}

Man::~Man()
{
    delete animator ;
    animator = NULL ;
    delete shader ;
    shader = NULL ;
    glDeleteVertexArrays(num_meshes, vao.data());
    glDeleteBuffers(num_meshes, vbo.data());
    glDeleteBuffers(num_meshes, ebo.data());
    glDeleteBuffers(textures.size(), textures.data());
}
