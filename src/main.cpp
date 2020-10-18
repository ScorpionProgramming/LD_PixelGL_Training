#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include <string.h>

#include <GLFW/glfw3.h>

#include "Graphics/Color.h"
#include "Graphics/Image.h"
#include "Graphics/Graphics.h"

//Updates positions and stuff
void update(double& deltaTime){

}

Color red       = Color(255,   0,   0, 255);
Color green     = Color(  0, 255,   0, 255);
Color blue      = Color(  0,   0, 255, 255);
Color yellow    = Color(255, 255,   0, 255);


//all the draw calls come in here
void draw(Graphics& g){

    // g.draw_pixel(0, 0, red);

    // g.draw_line(0, 0, 320, 200, red);
    
    // g.draw_line(320, 20, 20, 20, yellow);

    // g.draw_image(0, 0, 50, 50, img);
    // g.draw_image(100, 100, 50, 50, img2);

    // g.draw_quad(0, 0, 50, 50, blue);

    // g.draw_quad_filled(100, 100, 60, 40, red);
    
    //------------------------------------------------------------------------
    
    // g.draw_line(100, 100, 100, 0, red);

    //------------------------------------------------------------------------

    int b1 = 0 , b2 = 0, a1 = 384, a2 = 216, c1 = 0, c2 = 0;

    // g.draw_line(0, 0, 384,216, red);
    // g.draw_line(0, 216, 384, 0, red);

    //------------------------------------------------------------------------

    for (unsigned int v = 0; v < 216; v++){
        for (unsigned int u = 0; u < 384; u++){
            g.draw_pixel(u, v, rand() % 256, rand()% 256, rand()% 256, 255);
        }
    }
    
}

int main(void){
    uint            screen_width_   = 384;//1920; //320;
    uint            screen_height_  = 216;//1080;//200;
    uint            pixel_width_    = 4;
    uint            pixel_height_   = 4;
    std::string     title_          = "Scorpions Loop Stucker";

    GLFWwindow*     window;
    
    double          deltaTime_      = 0;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow((screen_width_ * pixel_width_), (screen_height_ * pixel_height_), title_.c_str(), NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* create graphics object */
    Graphics graphics = Graphics(screen_width_, screen_height_, Color(0x00, 0x88, 0x88, 0x00));

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    uint buffer;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_2D, buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screen_width_, screen_height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, (char*)graphics.get_pixels_on_screen());

    static int i = 0;
    static double fps = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        const clock_t begin_time = clock();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        update(deltaTime_);
        draw(graphics);

        /* For debug is quite nice because it works! */
        //glDrawPixels(screen_width_ , screen_height_, GL_RGB, GL_UNSIGNED_BYTE, graphics.get_pixels_on_screen());

        /* Draw pixels on the screen */
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, screen_width_ , screen_height_, GL_RGBA, GL_UNSIGNED_BYTE, (char*)graphics.get_pixels_on_screen());
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        deltaTime_ = (float( clock () - begin_time ) /  CLOCKS_PER_SEC);
        
        if(i > 50){
            std::cout << fps/i << " fps" << std::endl;
            i = 0;  
            fps = 0;
        }else{
            fps = fps + (1/deltaTime_);
            i++;
        }
    }

    glfwTerminate();
    return 0;
}