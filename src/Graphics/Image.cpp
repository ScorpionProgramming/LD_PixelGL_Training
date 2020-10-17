#include "Image.h"

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

Image::Image(){

}
