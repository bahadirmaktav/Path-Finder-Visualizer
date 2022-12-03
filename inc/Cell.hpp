#ifndef CELL_HPP_
#define CELL_HPP_

#include "GL/glew.h"

#include "Position2D.hpp"
#include "Vector2D.hpp"
#include "GridParameters.h"

struct Cell {
    Position2D leftUpperRlt;    // Relative Position
    Vector2D cellSizeRlt;       // Relative Cell Size
    Cell(double luX, double luY, double rltW, double rltH)
    : leftUpperRlt(luX, luY)
    , cellSizeRlt(rltW, rltH)
    {}
    Cell(Position2D luPos, Vector2D rltCellSize) {
        leftUpperRlt = luPos;
        cellSizeRlt = rltCellSize;
    }
    Cell() : Cell(0, 0, 0, 0) {}
    void operator = (Cell & cell) {
        leftUpperRlt = cell.leftUpperRlt;
        cellSizeRlt = cell.cellSizeRlt;
    }
    void Render() {
        glBegin(GL_QUADS);
            glColor3f(1, 1, 1);
            glVertex2d(leftUpperRlt.x, leftUpperRlt.y);
            glVertex2d(leftUpperRlt.x + cellSizeRlt.x, leftUpperRlt.y);
            glVertex2d(leftUpperRlt.x + cellSizeRlt.x, leftUpperRlt.y - cellSizeRlt.y);
            glVertex2d(leftUpperRlt.x, leftUpperRlt.y - cellSizeRlt.y);
        glEnd();
    }
};

#endif // CELL_HPP_