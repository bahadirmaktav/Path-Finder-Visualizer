#ifndef VECTOR_2D_HPP_
#define VECTOR_2D_HPP_

struct Vector2D {
    double x;
    double y;
    Vector2D(double iX, double iY) 
    : x(iX)
    , y(iY) 
    {}
    Vector2D() : Vector2D(0, 0) {}
    Vector2D operator + (Vector2D & pos) {
        Vector2D res(pos.x + x, pos.y + y);
        return res;
    }
    void operator = (Vector2D & pos) {
        x = pos.x;
        y = pos.y; 
    }
};

#endif // VECTOR_2D_HPP_