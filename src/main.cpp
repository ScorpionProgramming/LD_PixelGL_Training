#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <ctime> //for deltatime calc 
#include <sstream>

#include "World/Map.h"
#include "Math/Math.h"
#include "Player/Player.h"

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

float delta = 0.001f;
const float walkspeed = 2.0f;

//Create Player on Position x y
Player player = Player(new Vector2f(22.0f, 12.0f), new Vector2f(-1.0f, 0.0f));

void moveUp(){
    //std::cout << "UP" << std::endl;
    player.getPos().X += (float)delta * (float)walkspeed;
}

void moveDown(){
    //std::cout << "DOWN" << std::endl;
    player.getPos().X -= walkspeed * (float)delta;
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
    //create map
    char map[] = "111111111111111111111111100000000000000000000001100000000000000000000001100000000000000000000001100000222220000303030001100000200020000000000001100000200020000300030001100000200020000000000001100000220220000303030001100000000000000000000001100000000000000000000001100000000000000000000001100000000000000000000001100000000000000000000001100000000000000000000001100000000000000000000001144444444000000000000001140400004000000000000001140000504000000000000001140400004000000000000001140444444000000000000001140000000000000000000001144444444000000000000001111111111111111111111111";
    Map* m = new Map(24, 24, map);

    //output map
    for(int i = 0; i < 24 * 24; i++){
        if(i % 24 == 0 && i != 0){
            std::cout << std::endl;
        }
        std::cout << m->getCell(i % 24, i / 24) << " ";
    }
    std::cout << std::endl;

    std::cout << 0x61 << " " << 0x67 << std::endl;

    
    
    Vector2f cPlane = Vector2f(0.0f, 0.66f);

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
            drawQuad(data, i * pixelsize, j * pixelsize, pixelsize, pixelsize);   
        } 
    }

    int xPos = 0, yPos = 0;
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        const clock_t begin_time = clock();

        for(int x = 0; x < width; x++){
            Vector2f camera = Vector2f();
            camera.X = 2 * x / (double)width - 1;

            Vector2f rayDir = Vector2f(
                (player.getDir().X + cPlane.X * camera.X),
                (player.getDir().Y + cPlane.Y * camera.X));
            
            int mapX = (int)player.getPos().X;
            int mapY = (int)player.getPos().Y;

            double sideDistX; 
            double sideDistY;

            double deltaDistX = std::abs(1 / rayDir.X);
            double deltaDistY = std::abs(1 / rayDir.Y);

            double perpWallDist; 

            int stepX; 
            int stepY;

            int hit = 0;
            int side;  

            // Alternative code for deltaDist in case division through zero is not supported
            // double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
            // double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));

            if(rayDir.X < 0){
                stepX = -1;
                sideDistX = (player.getPos().X - mapX) * deltaDistX;
            }else{
                stepX = 1;
                sideDistX = (mapX + 1.0 - player.getPos().X) * deltaDistX;
            }

            if(rayDir.Y < 0){
                stepY = -1;
                sideDistY = (player.getPos().Y  - mapY) * deltaDistY;
            }else{
                stepY = 1;
                sideDistY = (mapY + 1.0 - player.getPos().Y) * deltaDistY;
            }

            //Hit Detection
            while(hit == 0){
                if(sideDistX < sideDistY){
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }else{
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }

                if(m->getCell(mapX, mapY) != '0') {
                    hit = 1;
                }
            }
            
            //calc distance
            if(side == 0){
                perpWallDist = (mapX - player.getPos().X + 1 - stepX / 2) / player.getDir().X;
            } else{
                perpWallDist = (mapY - player.getPos().Y + 1 - stepY / 2) / player.getDir().Y;
            }

            int lineHeight = (int) height / perpWallDist;

            int drawStart = -lineHeight / 2 + height / 2;
            if(drawStart < 0 ){
                drawStart = 0;
            }
            int drawEnd = lineHeight / 2 + height / 2;
            if(drawEnd >= height){
                drawEnd = height - 1;
            }
            
            //working on the color part
            drawQuad(data, x, drawStart, 1, drawEnd);
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        drawQuad(data, xPos, yPos, 30, 80);
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
        std::stringstream ss; 
        delta = (float( clock () - begin_time ) /  CLOCKS_PER_SEC);
        int fps = (1/delta);
        ss << "PixelGL \t" << fps << " fps";
        glfwSetWindowTitle(window, ss.str().c_str());
    }

    glfwTerminate();
    return 0;
}
