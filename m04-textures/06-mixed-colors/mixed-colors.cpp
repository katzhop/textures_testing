


#include "GLM/gtc/type_ptr.hpp"
#include <glad/gl.h>

#include "learnopengl/shader.h"

#include "cs4722/artifact.h"
#include "cs4722/view.h"
#include "cs4722/texture_utilities.h"
#include "../callbacks.h"


static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::artifact*> artifact_list;

const static auto b_position = 1;
const static auto b_texture_coords = 2;
const static auto b_color = 3;

static GLint u_transform = 1;
static GLint u_sampler = 2;
static GLint u_surface_effect = 3;
static GLint u_diffuse_color = 4;

void init() {

    the_view = new cs4722::view();
    the_view->set_flup(glm::vec3(0.202971, -0.227978, -0.952277),
                       glm::vec3(-0.978031, 0, -0.20846),
                       glm::vec3(0.0475242, 0.973667, -0.222969),
                       glm::vec3(-0.146291, 0.6f, 1.3214));


    Shader shader("vertex_shader06.glsl", "fragment_shader06.glsl");
    program = shader.ID;
    glUseProgram(program);

    glEnable(GL_DEPTH_TEST);



    /*
     *  Create two textures, one from a file and one procedurally generated
        Note the different texture units assigned.
     */
    cs4722::init_texture_from_file("../media/leaves.jpg", 2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    cs4722::init_texture_from_file("../media/tree_bark.jpg", 3);
    cs4722::init_texture_from_file("../media/ground.jpg", 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    cs4722::shape *b = new cs4722::sphere(15, 50);
    b->color_set_ = std::vector<cs4722::color>({cs4722::x11::pink, cs4722::x11::light_sea_green});
    cs4722::shape *b1 = new cs4722::block();
    b1->color_set_ = std::vector<cs4722::color>({cs4722::x11::purple, cs4722::x11::sienna});
    cs4722::shape *b2 = new cs4722::cylinder();
    b2->color_set_ = std::vector<cs4722::color>({cs4722::x11::purple, cs4722::x11::sienna});
    cs4722::shape *b3 = new cs4722::torus();
    b3->color_set_ = std::vector<cs4722::color>({cs4722::x11::purple, cs4722::x11::light_blue});



    auto *artf1 = new cs4722::artifact_rotating();
    auto *artf = new cs4722::artifact_rotating();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(rand()%5, .3f, rand()%5));
    artf->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    artf->rotation_rate = (M_PI / 3);
    artf->world_transform.scale = (glm::vec3(.3f, .3f, .3f));
    artf->animation_transform.rotation_center =
            artf->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    artf->texture_unit = 1;
    artf->surface_material.diffuse_color = cs4722::x11::dark_green;
    artf->surface_effect = 3;
    artifact_list.push_back(artf);

    artf = new cs4722::artifact_rotating();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(rand()%5, .3f, rand()%5));
    artf->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    artf->rotation_rate = (M_PI / 3);
    artf->world_transform.scale = (glm::vec3(.3f, .3f, .3f));
    artf->animation_transform.rotation_center =
            artf->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    artf->texture_unit = 1;
    artf->surface_material.diffuse_color = cs4722::x11::medium_violet_red;
    artf->surface_effect = 2;
    artifact_list.push_back(artf);

    artf1 = new cs4722::artifact_rotating();
    artf1->the_shape = (b3);
    artf1->world_transform.translate = (glm::vec3(5, .5f, 6));
    artf1->world_transform.scale = (glm::vec3(.4f, 1.0f, .4f));
    artf1->texture_unit = 3;
    artf1->surface_material.diffuse_color = cs4722::x11::green;
    artf1->surface_effect = 2;
    artifact_list.push_back(artf1);

    artf1 = new cs4722::artifact_rotating();
    artf1->the_shape = (b3);
    artf1->world_transform.translate = (glm::vec3(6, .5f, 5));
    artf1->world_transform.scale = (glm::vec3(.4f, 1.0f, .4f));
    artf1->texture_unit = 3;
    artf1->surface_material.diffuse_color = cs4722::x11::brown;
    artf1->surface_effect = 3;
    artifact_list.push_back(artf1);


    //trees
    for (auto t = 0; t < 10; t++) {
        float x = rand()%24 / 4.5 + .5;
        float z = rand()%24 / 4.5 + .5;

        artf1 = new cs4722::artifact_rotating();
        artf1->the_shape = (b1);
        artf1->world_transform.translate = (glm::vec3(x, .5f, z));
        artf1->world_transform.scale = (glm::vec3(.4f, 1.0f, .4f));
        artf1->texture_unit = 3;
        artf1->surface_material.diffuse_color = cs4722::x11::brown;
        artf1->surface_effect = 0;
        artifact_list.push_back(artf1);

        artf1 = new cs4722::artifact_rotating();
        artf1->the_shape = (b2);
        artf1->world_transform.translate = (glm::vec3(x, 1.2f, z));
        artf1->animation_transform.rotation_axis = (glm::vec3(0, 1, 0));
        artf1->rotation_rate = (M_PI / 3);
        artf1->world_transform.scale = (glm::vec3(.5f, .4f, .5f));
        artf1->animation_transform.rotation_center =
                artf1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
        artf1->texture_unit = 2;
        artf1->surface_material.diffuse_color = cs4722::x11::dark_green;
        artf1->surface_effect = 0;
        artifact_list.push_back(artf1);
    }



    //ground
    b1 = new cs4722::block();
    artf1 = new cs4722::artifact_rotating();
    artf1->the_shape = b1;
    artf1->world_transform.scale = glm::vec3(6, .01, 6);
    artf1->world_transform.translate = glm::vec3(6 / 2, 0, 6 / 2);
    artf1->surface_material.diffuse_color = cs4722::x11::lawn_green;
    artf1->texture_unit = 1;
    artf1->surface_effect = 1;
    artifact_list.push_back(artf1);


    auto total_vertex_count = 0;
    for(auto *artf : artifact_list) {
        if(artf->the_shape->buffer_size == 0) {
            artf->the_shape->buffer_start = total_vertex_count;
            artf->the_shape->buffer_size = artf->the_shape->get_size();
            total_vertex_count += artf->the_shape->get_size();
        } else {
            artf->shape_is_shared = true;
        }
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    const int number_of_buffers = 3;
    GLuint  buffers[number_of_buffers];
    glGenBuffers(number_of_buffers, buffers);


    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 4 * total_vertex_count, NULL,  GL_STATIC_DRAW);
    glVertexAttribPointer(b_position, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(b_position);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * total_vertex_count, NULL,  GL_STATIC_DRAW);
    glVertexAttribPointer(b_texture_coords, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(b_texture_coords);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, 1 * 4 * total_vertex_count, NULL,  GL_STATIC_DRAW);
    glVertexAttribPointer(b_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(b_color);

    for (auto artf : artifact_list) {
        if(!artf->shape_is_shared) {
            auto pos = artf->the_shape->positions();
            glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
            glBufferSubData(GL_ARRAY_BUFFER,
                            4 * 4 * artf->the_shape->buffer_start,
                            4 * 4 * artf->the_shape->buffer_size,
                            pos->data());
            delete pos;

            auto texture_coords = artf->the_shape->texture_coordinates();
            glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
            glBufferSubData(GL_ARRAY_BUFFER,
                            2 * 4 * artf->the_shape->buffer_start,
                            2 * 4 * artf->the_shape->buffer_size,
                            texture_coords->data());
            delete texture_coords;

            auto colors = artf->the_shape->colors();
            glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
            glBufferSubData(GL_ARRAY_BUFFER,
                            1 * 4 * artf->the_shape->buffer_start,
                            1 * 4 * artf->the_shape->buffer_size,
                            colors->data());
            delete colors;

        }
    }

}


void render()
{

    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect, the_view->perspective_near);
    auto vp_transform = projection_transform * view_transform;


    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;


    for (auto artf : artifact_list) {

        artf->animate(time, delta_time);

        auto model_transform = artf->animation_transform.matrix() * artf->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(transform));
        /*
         * Set the texture unit to use for this artf
         */
        glUniform1i(u_sampler, artf->texture_unit);

        glUniform1i(u_surface_effect, artf->surface_effect);
        glUniform4fv(u_diffuse_color, 1, artf->surface_material.diffuse_color.as_float().get());

        glDrawArrays(GL_TRIANGLES, artf->the_shape->buffer_start, artf->the_shape->buffer_size);
    }
}


int
main(int argc, char** argv)
{
    glfwInit();

    // set the OpenGL version to use: 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    auto aspect_ratio = 16.0f/9.0f;
    float ratio = 0.9f;             // ratio of window size to screen size
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    int xpos, ypos, width, height;
    glfwGetMonitorWorkarea(primary, &xpos, &ypos, &width, &height);
    //std::cout << xpos << " " << ypos << " " << width << " " << height << std::endl;
    int w_width = glm::min(ratio * width, aspect_ratio * ratio * height);
    int w_height = w_width / aspect_ratio;
    GLFWwindow* window = glfwCreateWindow(w_width, w_height, "Multiple Textures", NULL, NULL);
    int w_x = (width - w_width) / 2;
    int w_y = (height - w_height) / 2;
    glfwSetWindowPos(window, w_x, w_y);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);
//    cs4722::setup_debug_callbacks();

    init();
    the_view->perspective_aspect = aspect_ratio;

    glfwSetWindowUserPointer(window, the_view);
    glfwSetKeyCallback(window, general_key_callback);
    glfwSetCursorPosCallback(window, move_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    glfwSetWindowUserPointer(window, the_view);
	
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float().get());
        glClear(GL_DEPTH_BUFFER_BIT);

        render();
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
