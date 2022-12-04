#ifndef INDEX_2D_HPP_
#define INDEX_2D_HPP_

struct Index2D {
    double i;
    double j;
    Index2D(double iI, double iJ) 
    : i(iI)
    , j(iJ) 
    {}
    Index2D() : Index2D(0, 0) {}
    void operator = (Index2D & ind) {
        i = ind.i;
        j = ind.j; 
    }
};

#endif // INDEX_2D_HPP_