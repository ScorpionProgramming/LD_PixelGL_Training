#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <ctime> //for deltatime calc 
#include <sstream>

#include "World/Map.h"
#include "Math/Math.h"

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
    // for(int j = 0; j < height/pixelsize; j++){
    //     for(int i = 0; i < width/pixelsize; i++){
    //         drawQuad(data, i*pixelsize, j*pixelsize, pixelsize, pixelsize);   
    //     } 
    // }

    int xPos = 100, yPos = 100;
    
    int _ii;

    unsigned int buffer;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_2D, buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        const clock_t begin_time = clock();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //update(data, width, height);
        
        
        for(int j = 0; j < height/pixelsize; j++){
            for(int i = 0; i < width/pixelsize; i++){
                drawQuad(data, i*pixelsize, j*pixelsize, pixelsize, pixelsize);   
            } 
        }


        //drawQuad(data, xPos, yPos, 30, 80);
        
        //------------Draw with standard method--------
        //glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);


        //--------------Draw with newer method--------
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f, 0.0f);
            glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f,  1.0f, 0.0f);
            glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f,  1.0f, 0.0f);
            glTexCoord2f(1.0, 1.0); glVertex3f( 1.0f, -1.0f, 0.0f);        
        glEnd();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
        _ii++;

        if(_ii == 20){
            _ii = 0;
            std::stringstream ss; 
            int fps = (1/(float( clock () - begin_time ) /  CLOCKS_PER_SEC));
            ss << "PixelGL \t" << fps << " fps";
            glfwSetWindowTitle(window, ss.str().c_str());
        }
    }

    glfwTerminate();
    return 0;
}
