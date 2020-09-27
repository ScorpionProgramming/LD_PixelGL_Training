#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <ctime> //for deltatime calc 
#include <sstream>

#include "World/Map.h"

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

void moveUp(){
    std::cout << "UP" << std::endl;
}

void moveDown(){
    std::cout << "DOWN" << std::endl;
}

void moveLeft(){
    std::cout << "LEFT" << std::endl;
}

void moveRight(){
    std::cout << "RIGHT" << std::endl;
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveUp();
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveLeft();
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveDown();
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveRight();
}

int main(void)
{
    char map[] = "aaaaaabbbaabbbaabbbaaaaaa"; 

    Map* m = new Map(5, 5, map);

    std::cout << m->getCell(0,0) << " " << m->getCell(4,4) << " " << m->getCell(0,1) << std::endl;

    for(int i = 0; i < 5 * 5; i++){
        if(i % 5 == 0 && i != 0){
            std::cout << std::endl;
        }
        std::cout << m->getCell(i % 5, i / 5) << " ";
    }
    std::cout << std::endl;

    std::cout << 0x61 << " " << 0x67 << std::endl;


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

    unsigned int pixelsize = 8;
    //update(data, width, height);
    for(int j = 0; j < height/pixelsize; j++){
        for(int i = 0; i < width/pixelsize; i++){
            drawQuad(data, i*pixelsize, j*pixelsize, pixelsize, pixelsize);   
        } 
    }

    int xPos = 0, yPos = 0;
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        const clock_t begin_time = clock();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        drawQuad(data, xPos, yPos, 30, 80);
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
        std::stringstream ss; 
        int fps = (1/(float( clock () - begin_time ) /  CLOCKS_PER_SEC));
        ss << "PixelGL \t" << fps << " fps";
        glfwSetWindowTitle(window, ss.str().c_str());
    }

    glfwTerminate();
    return 0;
}
