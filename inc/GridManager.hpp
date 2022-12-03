#ifndef GRID_MANAGER_HPP_
#define GRID_MANAGER_HPP_

#include "GridParameters.h"
#include "Cell.hpp"

// INFO : Testing purposes.
int w1 = 15; int w2 = 30; int w3 = 60;
int h1 = 10; int h2 = 20; int h3 = 40;

class GridManager {
public:
    GridManager() 
    : cells_(nullptr)
    , totalCell_(0)
    {}
    ~GridManager() {
        delete[] cells_;
    }
    void Init() {
        SetGridCells(w2, h2);    // INFO : Testing purposes.
    }
    void SetGridCells(const int & wCount, const int & hCount) {
        double cellSizeRltW = ((((WINDOW_WIDTH - CELL_SPACE_PIXEL * 2) / wCount) - CELL_SPACE_PIXEL) / ((double)WINDOW_WIDTH / 2));
        double cellSizeRltH = ((((WINDOW_HEIGHT - CELL_SPACE_PIXEL * 2) / hCount) - CELL_SPACE_PIXEL) / ((double)WINDOW_HEIGHT / 2));
        Vector2D cellSizeRlt(cellSizeRltW, cellSizeRltH);
        Position2D leftUpperRltBuff(-1 + CELL_SPACE_RLT_W, 1 - CELL_SPACE_RLT_H);
        totalCell_ = wCount * hCount;
        cells_ = new Cell[totalCell_];
        for(int i = 0; i < hCount; i++) {
            for(int j = 0; j < wCount; j++) {
                Cell cell(leftUpperRltBuff, cellSizeRlt);
                leftUpperRltBuff.x += (cellSizeRlt.x + CELL_SPACE_RLT_W);
                cells_[i * wCount + j] = cell;
            }
            leftUpperRltBuff.y -= (cellSizeRlt.y + CELL_SPACE_RLT_H);
            leftUpperRltBuff.x = -1 + CELL_SPACE_RLT_W;
        }
    }
    void Render() {
        for(int i = 0; i < totalCell_; i++) {
            cells_[i].Render();
        }
    }

private:
    Cell * cells_;
    int totalCell_;
};

#endif // GRID_MANAGER_HPP_