#ifndef GRID_MANAGER_HPP_
#define GRID_MANAGER_HPP_

#include "GridParameters.h"
#include "Cell.hpp"

// INFO : Grid Size Modes
Vector2D GRID_SIZE_MODE_1(15, 10);
Vector2D GRID_SIZE_MODE_2(30, 20);
Vector2D GRID_SIZE_MODE_3(60, 40);

class GridManager {
public:
    GridManager() 
    : cells_(nullptr)
    , totalCell_(0)
    {}
    ~GridManager() {
        DeleteCells();
    }
    void Init() {
        GUI.SetChangeGridSizeFn(std::bind(&ChangeGridSize, this, std::placeholders::_1));
        SetGridCells(GRID_SIZE_MODE_2.x, GRID_SIZE_MODE_2.y);
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
    void DeleteCells() {
        delete[] cells_;
    }
    void ChangeGridSize(int gridSizeMode) {
        switch(gridSizeMode) {
        case 1:
            DeleteCells();
            SetGridCells(GRID_SIZE_MODE_1.x, GRID_SIZE_MODE_1.y);
            break;
        case 2:
            DeleteCells();
            SetGridCells(GRID_SIZE_MODE_2.x, GRID_SIZE_MODE_2.y);
            break;
        case 3:
            DeleteCells();
            SetGridCells(GRID_SIZE_MODE_3.x, GRID_SIZE_MODE_3.y);
            break;
        default:
            break;
        }
    }
private:
    Cell * cells_;
    int totalCell_;
};

#endif // GRID_MANAGER_HPP_