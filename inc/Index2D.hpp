#ifndef INDEX_2D_HPP_
#define INDEX_2D_HPP_

struct Index2D {
    int i;
    int j;
    Index2D(int iI, int iJ) 
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