#include <GLFW/glfw3.h>
#include <stdlib.h>

void update(unsigned char* data, unsigned int& width, unsigned int& height){
    unsigned int i;
    for(i = 0; i < width * height; i++){
        data[i * 3 + 0] = (char)(rand() % 256);
        data[i * 3 + 1] = (char)(rand() % 256);
        data[i * 3 + 2] = (char)(rand() % 256);
    }
}

int main(void)
{
    GLFWwindow* window;

    unsigned int width  = 640;
    unsigned int height = 480; 
    //^^^ for later generate width and height with number of pixels and pixels size

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //If everything works generate data
    unsigned char* data = new unsigned char[width * height * 3];
    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        update(data, width, height);
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}