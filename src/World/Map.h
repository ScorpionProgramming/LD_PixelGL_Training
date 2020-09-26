class Map
{
private:
    char* name;
    unsigned int m_width;
    unsigned int m_height;
    char* m_map;
public:
    Map(unsigned int width, unsigned int height, char* map);
    ~Map();

    char* getName() const;
    void setName(char* name);

    unsigned int getHeight() const;
    void setHeight(unsigned int height);
    unsigned int getWidth() const;
    void setWidth(unsigned int width); 

    char getCell(unsigned int x_Pos, unsigned int y_Pos) const;
};