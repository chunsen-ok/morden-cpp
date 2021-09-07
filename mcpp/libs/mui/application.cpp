#include "application.hpp"
#include "glad/glad.h"
#include <glfw/glfw3.h>
#include <vector>

class ApplicationPrivate
{
public:
    std::vector<GLFWwindow*> windows;
};

Application::Application(int argc, char *argv[])
    : d(std::make_unique<ApplicationPrivate>())
{

}

Application::~Application()
{
    
}

void Application::set_root(Widget *widget)
{
    
}

int Application::exec()
{
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window, *win2;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    win2 = glfwCreateWindow(640, 480,"Second",NULL,NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}