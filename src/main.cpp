#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>

void drawPixel(unsigned char* data, unsigned int i, unsigned char r, unsigned char g, unsigned char b ){
    data[i * 3 + 0] = r;
    data[i * 3 + 1] = g;
    data[i * 3 + 2] = b;
}

void drawPixelWithRandomColor(unsigned char* data, unsigned int i){
    data[i * 3 + 0] = (char)(rand() % 256);
    data[i * 3 + 1] = (char)(rand() % 256);
    data[i * 3 + 2] = (char)(rand() % 256);
}


void update(unsigned char* data, unsigned int& width, unsigned int& height){
    unsigned int i;
    for(i = 0; i < width * height; i++){
        drawPixelWithRandomColor(data, i);
    }
}

void drawQuad(unsigned char* data, unsigned int x, unsigned int y, unsigned int width, unsigned height){
    unsigned char r = (char)(rand() % 256);
    unsigned char g = (char)(rand() % 256);
    unsigned char b = (char)(rand() % 256);
    for (int _y = y; _y < (y + height); _y++){
        for (unsigned int _x = x;_x < (x + width); _x++){
            int pos = _x + (_y * 640);
            drawPixel(data, pos, r, g, b);
        }
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
    window = glfwCreateWindow(width, height, "PixelGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //If everything works generate data
    unsigned char* data = new unsigned char[width * height * 3];
    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    unsigned int pixelsize = 4;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        update(data, width, height);
        
        for(int j = 0; j < height/pixelsize; j++){
            for(int i = 0; i < width/pixelsize; i++){
                drawQuad(data, i*pixelsize, j*pixelsize, pixelsize, pixelsize);   
            } 
        }
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}