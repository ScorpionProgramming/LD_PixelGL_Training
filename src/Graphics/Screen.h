class Screen
{
private:
unsigned int m_width;
unsigned int m_height;

public:
    Screen(unsigned int& width, unsigned int& height);
    ~Screen();

    void setWidth(unsigned int& width);
    void setHeight(unsigned int& height);
    unsigned int getWidth() const;
    unsigned int getHeight() const;
};
