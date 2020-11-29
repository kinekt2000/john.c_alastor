// variant 4;
// shapes: Circle, Five pointed star, six pointed 

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>


#define PI std::atan(1)*4


float round(float val, int dec_places)
{   
    auto ret_val = std::round(val * (10.f * dec_places))/(10.f * dec_places);
    if(ret_val == -0) ret_val = 0;
    return ret_val;
}

struct Point{
    float x = 0;
    float y = 0;
    

    friend Point operator+(const Point& a, const Point& b)
    {
        auto x = a.x + b.x;
        auto y = a.y + b.y;
        return Point{x, y};
    }

    friend Point operator-(const Point& a, const Point& b)
    {
        auto x = a.x - b.x;
        auto y = a.y - b.y;
        return Point{x, y};
    }

    friend Point operator*(const Point& a, const Point& b)
    {
        auto x = a.x * b.x;
        auto y = a.y * b.y;
        return Point{x, y};
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "(" << round(p.x, 6) << ", " << round(p.y, 6) << ")"; 
    }
};


Point rotateVector(const Point& vector, float angle_rad)
{
    float x = double(vector.x) * std::cos(double(angle_rad)) - double(vector.y) * std::sin(double(angle_rad));
    float y = double(vector.x) * std::sin(double(angle_rad)) + double(vector.y) * std::cos(double(angle_rad));
    return Point{x, y};
}


struct Color{
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
};


// all shapes have origin in center 

class Shape
{
    inline static unsigned int count = 0;
    unsigned int ID;
    Color color;

protected:
    virtual void print(std::ostream &os) const = 0;

public:
    Shape(){
        count++;
        ID = count;
    }
    ~Shape(){}

    void setColor(const Color& c)
    { color = c; }

    void setColor(uint8_t r, uint8_t g, uint8_t b)
    { color = Color{r, g, b}; }

    const Color& getColor() const
    { return color; }

    unsigned int getID() const
    { return ID; }

    virtual void setPosition(const Point& p) = 0;
    virtual void setRotation(float angle_rad) = 0;
    virtual void setScale(float x, float y) = 0;

    virtual const Point& getPosition() const = 0;
    virtual float getRotation() const = 0;
    virtual const Point& getScale() const = 0;
    
    friend std::ostream& operator<<(std::ostream &os, const Shape& sh)
    {
        sh.print(os);
        return os;
    }
};


class Circle: public Shape
{
    Point pos;
    float radius;
    Point scale;

protected:
    void print(std::ostream &os) const
    {
        os << "Shape number " << getID() << std::endl;
        os << "Circle with center in " << pos << std::endl;
        os << "Radius is " << radius*scale.x << std::endl;
        os << "Shape scale is " << scale.x << std::endl;
        os << "Color: " << int(getColor().r) << ", "
                        << int(getColor().g) << ", "
                        << int(getColor().b) << std::endl; 
    }
    
public:
    Circle(const Point& pos, float radius):
        pos(pos), radius(radius), scale{1, 1}
    {}


    void setPosition(const Point& p)
    {
        pos = p;
    }

    void setRotation(float)
    {
        // circle don't have rotation
        return;
    }

    void setScale(float x, float y)
    {
        auto scale = std::max(x, y);
        this->scale = Point{scale, scale};
    }


    const Point& getPosition() const
    {
        return pos;
    }


    float getRotation() const
    {
        return 0.f;
    }


    const Point& getScale() const
    {
        return scale;
    }
};


class FivePStar: public Shape
{
    Point pos; // center
    float radius;
    std::vector<Point*> ends;

    Point scale;
    float rotation;

protected:
    void print(std::ostream& os) const
    {
        os << "Shape number " << getID() << std::endl;
        os << "Five pointed star with points:" << std::endl;
        for(auto p: ends)
        { 
            os << (pos + rotateVector((*p)*scale, rotation)) << std::endl;
        }
        os << "With center in " << pos << std::endl;
        os << "Radius is " << radius << std::endl;
        os << "Shape rotated by " << rotation << " rads" << std::endl;
        os << "Shape scaled by " << scale << std::endl;
        os << "Color: " << int(getColor().r) << ", "
                        << int(getColor().g) << ", "
                        << int(getColor().b) << std::endl;
    }

public:
    ~FivePStar()
    {
        for(auto p: ends)
            delete p;
    }


    FivePStar(const Point& pos, float radius):
        pos(pos), radius(radius), scale{1, 1}, rotation(0)
    {
        for(int k = 0; k < 5; k++)
        {
            float m = 2*PI/5;
            float phase = PI/2;
            auto end = new Point{radius * std::cos(float(k*2)*m + phase),
                                 radius * std::sin(float(k*2)*m + phase)};

            ends.push_back(end);
        }
    }

    void setPosition(const Point& p)
    {
        pos = p;
    }


    void setRotation(float angle_rad)
    {
        rotation = angle_rad;
    }


    void setScale(float x, float y)
    {
        scale = Point{x, y};
    }


    const Point& getPosition() const
    {
        return pos;
    }


    float getRotation() const
    {
        return rotation;
    }


    const Point& getScale() const
    {
        return scale;
    }
};


class SixPStar: public Shape
{
    Point pos;
    float radius;

    // six pointed star is a pair of triangles
    // which overlap each other
    std::vector<Point*> f_tri; // first triangle
    std::vector<Point*> s_tri; // second triangle

    Point scale;
    float rotation;

protected:
    void print(std::ostream &os) const
    {
        os << "Shape number " << getID() << std::endl;
        os << "Six pointed star with points" << std::endl;
        os << "of \"first\" triangle:" << std::endl;
        for(auto p: f_tri)
        { 
            os << (pos + rotateVector((*p), rotation)) << std::endl;
        }

        os << "and of \"second\" triangle" << std::endl;
        for(auto p: s_tri)
        {
            os << (pos + rotateVector((*p), rotation)) << std::endl;
        }

        os << "With center in " << pos << std::endl;
        os << "Radius is " << radius << std::endl;
        os << "Shape rotated by " << rotation << " rads" << std::endl;
        os << "Shape scaled by " << scale << std::endl;
        os << "Color: " << int(getColor().r) << ", "
                        << int(getColor().g) << ", "
                        << int(getColor().b) << std::endl;
    }

public:
    ~SixPStar()
    {
        for(auto p: f_tri)
            delete p;

        for(auto p: s_tri)
            delete p;
    }


    SixPStar(const Point& p, float radius):
        pos(pos), radius(radius), scale{1, 1}, rotation(0)
    {
        for(int k = 0; k < 3; k++)
        {
            float m = 2*PI/3;
            float phase = PI/2;

            auto x = radius * std::cos(float(k*2)*m + phase);
            auto y = radius * std::sin(float(k*2)*m + phase);

            auto end = new Point{x, y};

            f_tri.push_back(end);
        }

        for(int k = 0; k < 3; k++)
        {
            float m = 2*PI/3;
            float phase = 3*PI/2;

            auto x = radius * std::cos(float(k*2)*m + phase);
            auto y = radius * std::sin(float(k*2)*m + phase);

            auto end = new Point{x, y};

            s_tri.push_back(end);
        }
    }
        

    void setPosition(const Point& p)
    {
        pos = p;
    }


    void setRotation(float angle_rad)
    {
        rotation = angle_rad;
    }


    void setScale(float x, float y)
    {
        scale = Point{x, y};
    }


    const Point& getPosition() const
    {
        return pos;
    }


    float getRotation() const
    {
        return rotation;
    }


    const Point& getScale() const
    {
        return scale;
    }

};

int main(){

    std::vector<Shape*> shapes;

    auto circle = new Circle(Point{1, 5}, 5);
    circle->setRotation(PI/4); // it will do nothing, you can't rotate a circle
    circle->setScale(2, 0.5f); // it gonna take maximum of scale values. Circle will double
    circle->setColor(168, 122, 0);

    shapes.push_back(circle);

    auto fps = new FivePStar(Point{-1, -1}, 8);
    fps->setRotation(PI/8);  // will rotate PI/8 radians counter-clockwise
    fps->setScale(0.5f, -1); // will be halved along the x-axis and flipped along y-axis
    fps->setColor(0, 0, 0);

    shapes.push_back(fps);

    auto sps = new SixPStar(Point{0, 0}, 3);
    sps->setRotation(-PI/7);
    //left deafult scale and color

    shapes.push_back(sps); 

    for(auto shape: shapes)
        std::cout << *shape << std::endl;

    return 0;
}
