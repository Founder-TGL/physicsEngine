#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 


int main()
{   
    //initializes glfw so everything can be used
    glfwInit();

    //informs glfw of the version we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //tells glfw to only use the modern functions, so nothing outdated or old 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //creates a window object
    GLFWwindow* window = glfwCreateWindow(800,800, "test Window", NULL , NULL);
    //error checks to ensure the window popped up
    if(window == NULL){
        cout<< "failed to create GLFW window";
        glfwTerminate();
        return -1;
    }

    //brings the window to the current context so it may be edited (i beleive)
    glfwMakeContextCurrent(window);

    //loads glad so it may configure GL
    gladLoadGL();

    //specify the viewport of OpenGL in the window
    glViewport(0,0,800,800);

    //specify the color of the background 
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //cleans the back buffer and assigns it a color
    glClear(GL_COLOR_BUFFER_BIT);
    //swaps the back and front buffer
    glfwSwapBuffers(window);

    //while the window is opened it polls events (deals with all GLFW events)
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }
    
    //ends program
    glfwTerminate();
    return 0;
}
