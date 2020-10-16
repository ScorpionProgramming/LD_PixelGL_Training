#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include <string.h>

#include <GLFW/glfw3.h>

class Color
{
private:
    /* data */
    u_char r;
    u_char g;
    u_char b;
    u_char a;
public:
    Color();
    Color(u_char& r, u_char& g, u_char& b, u_char& a);
    Color(uint r, uint g, uint b, uint a);

    u_char get_r() const;
    u_char get_g() const;
    u_char get_b() const;
    u_char get_a() const;

    ~Color();
};

Color::Color(){
    this->r = 0x00;
    this->g = 0x00;
    this->b = 0x00;
    this->a = 0xff;
}

Color::Color(u_char& r, u_char& g, u_char& b, u_char& a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(uint r, uint g, uint b, uint a){
    this->r = (u_char)r;
    this->g = (u_char)g;
    this->b = (u_char)b;
    this->a = (u_char)a;
}

u_char Color::get_r() const {
    return this->r;
}

u_char Color::get_g() const{
    return this->g;
}

u_char Color::get_b() const{
    return this->b;
}

u_char Color::get_a() const{
    return this->a;
}

Color::~Color(){
}

class Image
{
typedef struct {
    short int index;
    short int length;
    char entry_size;
}COLOR_MAP_SPECIFICATION;

typedef struct{
    short int x_origin;
    short int y_origin;
    short int width;
    short int height;
    char pixel_depth;
    char descriptor; 
}IMAGE_SPECIFICATION;

typedef struct{
    char id_length;
    char color_map_type;
    char image_type;
    COLOR_MAP_SPECIFICATION color_map_specification;
    IMAGE_SPECIFICATION image_specification;
}TGA_HEAD;

typedef struct{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
}COLOR_RGBA;

private:
    /* data */
    unsigned char* pixel_data_;
    uint width_;
    uint height_;

public:
    Image(std::string path);
    Image();
    void load_tga(std::string path);
    unsigned char* get_full_image();
    Color get_pixel(uint x, uint y);
    uint get_width() const;
    uint get_height() const;

    ~Image();
};

Image::Image(){

}

Image::Image(std::string path){
    std::ifstream file(path);

    std::string line;

    std::string check;
    uint width;
    uint height;
    std::string color;

    std::string word;

    std::vector<unsigned char> data;
    
    unsigned int number;

    std::istringstream iss;

    if(file.is_open()){
        int i = 0;
        while(!file.eof()){
            getline(file, line);

            if(line[0] != '#' && line.length() != 0){
                switch (i)
                {
                case 0:
                    check = line;
                    break;
                case 1:
                    /* split string later create an new method for it */ 
                    iss.str(line);

                    iss >> width;
                    iss >> height;
                    break;
                case 2:
                    color = line;
                    break;
                default:
                    if(check.compare("P6") == 0){
                        line.erase(line.length()-1);
                        for(unsigned int i = 0; i < line.length(); i++){
                            data.push_back(line.at(i));
                        }
                    }else if (check.compare("P3") == 0){
                        number = stoi(line);
                        //std::cout << number << "->";
                        data.push_back((unsigned char)number);
                        //std::cout << data.back() << " "; 
                    }
                    break;
                }
                i++;
            }
            //std::cout << line << std::endl;
        }

    }
    file.close();
    
    std::cout << "Check: " << check << std::endl;
    std::cout << width << " | " << height << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "Data Size: " << data.size() << std::endl;

    //std::cout << data << std::endl;

    this->width_  = width;
    this->height_ = height; 

    if(data.size() != 0){
        pixel_data_ = new unsigned char[data.size()];
        
        for(unsigned int i = 0; i < data.size(); i++){
            //std::cout << (int)data.at(i) << " " << std::endl;
            pixel_data_[i] = data.at(i); 
        }
    }
}

u_char* Image::get_full_image(){
    return this->pixel_data_;
}

void Image::load_tga(std::string path){
    TGA_HEAD* head = new TGA_HEAD;
    size_t data_size;

    COLOR_RGBA* color_image; 

    std::ifstream file(path, std::ifstream::binary);
    
    if(!file.is_open()){
        std::cerr << "Unable to load: " << path << std::endl;
        exit;
    }else {
        std::cout << "Opend: " << path << std::endl;
    }

    file.seekg(0, file.end);
    data_size = file.tellg();
    file.seekg(0, file.beg);

    char* data = new char[data_size]; 
    std::cout << "File size: " << data_size << std::endl;
    
    file.read(data, data_size);
    if (file)
      std::cout << "all characters read successfully." << std::endl;
    else
      std::cout << "error: only " << file.gcount() << " could be read" << std::endl;
    file.close();


    unsigned int i = 0;
    for(int i = 0; i < data_size; i++){
        std::cout << std::hex << (int)data[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "Headsize: " << sizeof(&head) << std::endl;
    std::cout << "Data Size: " << strlen(data) << std::endl;

    size_t offset = 0; 
    memcpy(&(head->id_length), data + offset, sizeof(head->id_length)); offset += sizeof(head->id_length);
    memcpy(&(head->color_map_type), data + offset, sizeof(head->color_map_type)); offset += sizeof(head->color_map_type);
    memcpy(&(head->image_type), data + offset, sizeof(head->image_type)); offset += sizeof(head->image_type);
    memcpy(&(head->color_map_specification.index), data + offset, sizeof(head->color_map_specification.index)); offset += sizeof(head->color_map_specification.index);
    memcpy(&(head->color_map_specification.length), data + offset, sizeof(head->color_map_specification.length)); offset += sizeof(head->color_map_specification.length);
    memcpy(&(head->color_map_specification.entry_size), data + offset, sizeof(head->color_map_specification.entry_size)); offset += sizeof(head->color_map_specification.entry_size);
    memcpy(&(head->image_specification.x_origin), data + offset, sizeof(head->image_specification.x_origin)); offset += sizeof(head->image_specification.x_origin);
    memcpy(&(head->image_specification.y_origin), data + offset, sizeof(head->image_specification.y_origin)); offset += sizeof(head->image_specification.y_origin);
    memcpy(&(head->image_specification.width), data + offset, sizeof(head->image_specification.width)); offset += sizeof(head->image_specification.width);
    memcpy(&(head->image_specification.height), data + offset, sizeof(head->image_specification.height)); offset += sizeof(head->image_specification.height);
    memcpy(&(head->image_specification.pixel_depth), data + offset, sizeof(head->image_specification.pixel_depth)); offset += sizeof(head->image_specification.pixel_depth);
    memcpy(&(head->image_specification.descriptor), data + offset, sizeof(head->image_specification.descriptor)); offset += sizeof(head->image_specification.descriptor);

    std::cout << "Offset: " << (int)offset << std::endl;

    std::cout << "Filename: " << path <<std::endl;  
    std::cout << (int)head->id_length << std::endl;
    std::cout << (int)head->color_map_type << std::endl;
    std::cout << (int)head->image_type << std::endl; std::cout << std::endl;

    std::cout << (int)head->color_map_specification.index << std::endl; 
    std::cout << (int)head->color_map_specification.length << std::endl;
    std::cout << (int)head->color_map_specification.entry_size << std::endl; std::cout << std::endl;

    std::cout << (int)head->image_specification.x_origin << std::endl;
    std::cout << (int)head->image_specification.y_origin << std::endl;
    std::cout << (int)head->image_specification.width << std::endl;
    std::cout << (int)head->image_specification.height << std::endl;
    std::cout << (int)head->image_specification.pixel_depth << std::endl;
    std::cout << (int)head->image_specification.descriptor << std::endl;

    width_  = head->image_specification.width;
    height_ = head->image_specification.height;
    

    //color_image = new COLOR_RGBA[width_ * height_];

    pixel_data_ = new unsigned char[width_ * height_ * 4];

    //memcpy(&pixel_data_, data + offset, sizeof(unsigned char) + (width_ * height_ * 4));
    //std::cout << "Memcopy is durch" << std::endl;

    //memcpy(pixel_data_, data + offset, sizeof(char) * width_ * height_ * 4);
    // for(unsigned int i = 0; i < width_ * height_; i++){
    //     offset += 4;
    // }
    for(unsigned int i = 0; i < width_ * height_; i++){
        pixel_data_[i * 4 + 2] = data[offset + 0]; 
        pixel_data_[i * 4 + 1] = data[offset + 1]; 
        pixel_data_[i * 4 + 0] = data[offset + 2]; 
        pixel_data_[i * 4 + 3] = data[offset + 3]; 
        offset += 4;
    }


    for(unsigned int i = 0; i < width_ * height_; i++){
        std::cout << "R:" << (int)pixel_data_[i*4+0] << " | ";
        std::cout << "G:" << (int)pixel_data_[i*4+1] << " | ";
        std::cout << "B:" << (int)pixel_data_[i*4+2] << " | ";
        std::cout << "A:" << (int)pixel_data_[i*4+3] ;
        std::cout << std::endl;
    }

    //read color data
    // for(unsigned int i = 0; i < width_ * height_; i++){
    //     COLOR_RGBA color;
    //     memcpy(&color.R, data + offset + 0, sizeof(color.R));
    //     memcpy(&color.G, data + offset + 1, sizeof(color.G));
    //     memcpy(&color.B, data + offset + 2, sizeof(color.B));
    //     memcpy(&color.A, data + offset + 3, sizeof(color.A));
    //     color_image[i] = color;
    //     offset += 4;
    // }

    // for(unsigned int i = 0; i < head->image_specification.width * head->image_specification.height; i++){
    //     std::cout << "R:" << (int)color_image[i].R << " | ";
    //     std::cout << "G:" << (int)color_image[i].G << " | ";
    //     std::cout << "B:" << (int)color_image[i].B << " | ";
    //     std::cout << "A:" << (int)color_image[i].A ;
    //     std::cout << std::endl;
    // }
}

Color Image::get_pixel(uint x, uint y){
    int index = (x + (y * width_));
    u_char r = pixel_data_[index * 4 + 0];
    u_char g = pixel_data_[index * 4 + 1];
    u_char b = pixel_data_[index * 4 + 2];
    u_char a = pixel_data_[index * 4 + 3];    

    // std::cout << "Index: " << index << " x-> " << x << " y-> " << y << ": ";
    // std::cout << (int)r << ", "
    //           << (int)g << ", "
    //           << (int)b << ", "
    //           << std::endl;
    return Color(r, g, b, a);
}

uint Image::get_width() const{
    return this->width_;
}
uint Image::get_height() const{
    return this->height_;
}

Image::~Image(){
    delete pixel_data_;
}


class Graphics
{
private:
    /* data */
    u_char* pixel_on_screen;
    uint width_;
    uint height_;

    //check if x and y are in boundry
    void check_x(uint& x);
    void check_y(uint& y);

public:
    Graphics(uint width, uint height);
    Graphics(uint width, uint height, Color c);

    u_char* get_pixels_on_screen() const;
    void draw_pixel(uint x, uint y, Color c);
    void draw_pixel(uint x, uint y, u_char r, u_char g, u_char b, u_char a);
    void draw_line(int x1, int y1, int x2, int y2, Color c);
    void draw_quad(uint x, uint y, uint width, uint height, Color c);
    void draw_quad_filled(uint x, uint y, uint width, uint height, Color c);
    void draw_image(uint x, uint y, uint width, uint height, Image& img);
    
    ~Graphics();
};

Graphics::Graphics(uint width, uint height){
    this->width_    = width;
    this->height_   = height;

    uint array_size = (width * height); 
    pixel_on_screen = new u_char[array_size * 4];
    uint i;
    for (i = 0; i < array_size; i++){
        pixel_on_screen[i * 4 + 0] = 0x00;
        pixel_on_screen[i * 4 + 1] = 0x00;
        pixel_on_screen[i * 4 + 2] = 0x00;
        pixel_on_screen[i * 4 + 3] = 0xff;
    }
}

Graphics::Graphics(uint width, uint height, Color c){
    this->width_    = width;
    this->height_   = height;

    uint array_size = (width * height); 
    pixel_on_screen = new u_char[array_size * 4];
    uint i;
    for (i = 0; i < array_size; i++){
        pixel_on_screen[i * 4 + 0] = c.get_r();
        pixel_on_screen[i * 4 + 1] = c.get_g();
        pixel_on_screen[i * 4 + 2] = c.get_b();
        pixel_on_screen[i * 4 + 3] = c.get_b();
    }
}

u_char* Graphics::get_pixels_on_screen() const{
    return this->pixel_on_screen;
}

void Graphics::draw_pixel(uint x, uint y, Color c){
    // if(x < width_ && y < height_){
        uint coord = (x + (y * width_));
        pixel_on_screen[coord * 4 + 0] = c.get_r();
        pixel_on_screen[coord * 4 + 1] = c.get_g();
        pixel_on_screen[coord * 4 + 2] = c.get_b();
        pixel_on_screen[coord * 4 + 3] = c.get_a();
    // }
}

void Graphics::draw_pixel(uint x, uint y, u_char r, u_char g, u_char b, u_char a){
    uint coord = (x + (y * width_));
    pixel_on_screen[coord * 4 + 0] = r;
    pixel_on_screen[coord * 4 + 1] = g;
    pixel_on_screen[coord * 4 + 2] = b;
    pixel_on_screen[coord * 4 + 3] = a;
}


void Graphics::draw_line(int x1, int y1, int x2, int y2, Color c){
    // c1 = b1 - a1;
    // c2 = b2 - a2; 

    // float length = sqrt(c1 * c1 + c2 * c2);

    // float cn1 = ((float)c1 / length);
    // float cn2 = ((float)c2 / length);

    // float drawV1 = a1;
    // float drawV2 = a2;

    // while((int)drawV1 != b1 || (int)drawV2 != b2){
    //     g.draw_pixel(drawV1, drawV2, red);
    //     drawV1 += cn1;
    //     drawV2 += cn2;
    // }

    
    //vector
    int cx = x2 - x1;
    int cy = y2 - y1; 

    float length = sqrt(cx * cx + cy * cy);
    // std::cout << "Length: " << length << std::endl;


    float c_norm_x = ((float)cx / length);
    float c_norm_y = ((float)cy / length);

    // std::cout << c_norm_x << ", " << c_norm_y << std::endl; 

    float draw_vec_x = x1;
    float draw_vec_y = y1;

    while((int)draw_vec_x != x2 || (int)draw_vec_y != y2){
        draw_pixel(draw_vec_x, draw_vec_y, c);
        // std::cout << "DRAW: " << draw_vec_x << ", " << draw_vec_y << std::endl; 
        draw_vec_x += c_norm_x;
        draw_vec_y += c_norm_y;
    }
    draw_pixel(x2, y2, c); 
    
    /* swap - perinio */
    // if(x1 >= x2){
    //     int tmp;
    //     tmp = x1; 
    //     x1 = x2; 
    //     x2 = tmp;

    //     tmp = y1; 
    //     y1 = y2; 
    //     y2 = tmp;
    // }

    // float delta_x = (x2 - x1);
    // float delta_y = (y2 - y1);

    // float x = x1; 
    // float y = y1; 
    // if(delta_x == 0){
    //     while(y != y2){
    //         this->draw_pixel((int)x, (int)y, c);
    //         if(y < y2){
    //             y++;
    //         }else if(y > y2) {
    //             y--;
    //         }
    //     }
    // }else if(delta_y == 0){
    //     while(x != x2){
    //         x++;
    //         this->draw_pixel((int)x, (int)y, c);
    //     }
    // }else{
    //     while(x != x2 && y != y2){
    //         float m = ((float)delta_y / (float)delta_x);
    //         if(m < 1){
    //             x += 1;
    //             y += m;
    //         }else if(m > 1){
    //             y += 1;
    //             x += 1/m;
    //         }else if(m == 1){
    //             y++;
    //             x++;
    //         }
    //         this->draw_pixel((int)x, (int)y, c);
    //     }
    // }
}

void Graphics::draw_quad(uint x, uint y, uint width, uint height, Color c){
    draw_line(x , y, x + width, y, c);
    draw_line(x + width, y, x + width, y + height, c);
    draw_line(x + width, y + height, x, y + height, c);
    draw_line(x, y + height, x, y, c);
}

void Graphics::draw_quad_filled(uint x, uint y, uint width, uint height, Color c){
    for(uint i = 0; i < height; i++){
        draw_line(x, y + i, x + width, y + i, c);
    }
}

void Graphics::draw_image(uint x, uint y, uint width, uint height, Image& img){
    /* every vertical line */
    for(int u = 0; u < img.get_width(); u++){
        for(int v = 0; v < img.get_height(); v++){
            if(img.get_pixel(u, v).get_a() != 0)
                this->draw_pixel(x+u, y+v, img.get_pixel(u, v));
        }
    }
}

Graphics::~Graphics(){
    delete pixel_on_screen;
}


//Updates positions and stuff
void update(double& deltaTime){

}

Color red       = Color(255,   0,   0, 255);
Color green     = Color(  0, 255,   0, 255);
Color blue      = Color(  0,   0, 255, 255);
Color yellow    = Color(255, 255,   0, 255);
// Image img1      = Image("Test1.ppm");
// Image img1      = Image("CheckThisFormat.ppm");
// Image img1      = Image("Test_ASCII.ppm");
// Image img1      = Image("Test_raw.ppm");
Image img         = Image();

//all the draw calls come in here
void draw(Graphics& g){

    // g.draw_pixel(0, 0, red);

    // g.draw_line(0, 0, 320, 200, red);
    
    // g.draw_line(320, 20, 20, 20, yellow);

    //g.draw_image(0, 0, 50, 50, img);

    // g.draw_quad(0, 0, 50, 50, blue);

    // g.draw_quad_filled(100, 100, 60, 40, Color(0, 0, 0));
    
    //------------------------------------------------------------------------
    
    g.draw_line(100, 100, 100, 0, red);

    //------------------------------------------------------------------------

    int b1 = 0 , b2 = 0, a1 = 384, a2 = 216, c1 = 0, c2 = 0;

    // g.draw_line(0, 0, 384,216, red);
    // g.draw_line(0, 216, 384, 0, red);

    //------------------------------------------------------------------------

    // for (unsigned int v = 0; v < 216; v++){
    //     for (unsigned int u = 0; u < 384; u++){
    //         g.draw_pixel(u, v, rand() % 256, rand()% 256, rand()% 256);
    //     }
    // }
}

int main(void)
{
    //Image img = Image("CheckThisFormat.ppm");

    // img.load_tga("TestImage_BOT_NoRLE.tga");
    // load_tga("TestImage_BOT_RLE.tga");
    //img.load_tga("TestImage_TOP_NoRLE.tga");
    // load_tga("TestImage_TOP_RLE.tga");
    // img.load_tga("TGA_Test_new.tga");
    //img.load_tga("Color_Combi_Alpha.tga");

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
    if (!window)
    {
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