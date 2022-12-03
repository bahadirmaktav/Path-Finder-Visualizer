#ifndef POSITION_2D_HPP_
#define POSITION_2D_HPP_

struct Position2D {
    double x;
    double y;
    Position2D(double iX, double iY) 
    : x(iX)
    , y(iY) 
    {}
    Position2D() : Position2D(0, 0) {}
    Position2D operator + (Position2D & pos) {
        Position2D res(pos.x + x, pos.y + y);
        return res;
    }
    void operator = (Position2D & pos) {
        x = pos.x;
        y = pos.y; 
    }
};

#endif // POSITION_2D_HPP_