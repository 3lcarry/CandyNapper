#ifndef POINT_H
#define POINT_H

class Point{
private:
    float x;
    float y;

public:
    Point();
    ~Point();
    void setX(float x);
    void setY(float y);
    float getX();
    float getY();
};

#endif // POINT_H
