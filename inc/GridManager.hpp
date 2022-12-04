#ifndef GRID_MANAGER_HPP_
#define GRID_MANAGER_HPP_

#include "GridParameters.h"
#include "Cell.hpp"
#include "Index2D.hpp"
#include "WindowManager.hpp"
#include "GuiManager.hpp"

// INFO : Grid Size Modes
Vector2D GRID_SIZE_MODE_1(15, 10);
Vector2D GRID_SIZE_MODE_2(30, 20);
Vector2D GRID_SIZE_MODE_3(60, 40);

// INFO : Positions
// Center   (0,0) | Right (1,0) | Left (-1,0) | Up (1,0) | Down (-1,0)  --> RelativePos
// Top Left (0,0) | Bottom Right (WINDOW_WIDTH,WINDOW_HEIGHT)           --> ResolutionPos
// Top Left (0,0) | Bottom Right (ROW_NUMBER-1,COLUMN_NUMBER-1)         --> IndexPos

#define GRID GridManager::Instance()

class GridManager {
public:
    GridManager() 
    : cells_(nullptr)
    , totalCell_(0)
    , columnNum_(0)
    , cellSize_(0)
    , activePen_(Style::Pen::PEN_OBSTACLE)
    , startNodeInd_(0, 0)
    , finalNodeInd_(0, 1)
    , mousePos_(0, 0)
    , mouseAction_(0)
    , mouseButton_(0)
    {}
    ~GridManager() {
        DeleteCells();
    }
    static GridManager & Instance() {
        static GridManager gridManager;
        return gridManager;
    }
    GridManager(const GridManager &) = delete;
    GridManager & operator = (const GridManager &) = delete;
    void Init() {
        WINDOW.SetMousePosCallbackFn(std::bind(&GridManager::MousePosHandler, this, std::placeholders::_1, std::placeholders::_2));
        WINDOW.SetMouseButtonCallbackFn(std::bind(&GridManager::MouseButtonHandler, this, std::placeholders::_1, std::placeholders::_2));
        WINDOW.SetKeyCallbackFn(std::bind(&GridManager::KeyHandler, this, std::placeholders::_1, std::placeholders::_2));
        GUI.SetChangeGridSizeFn(std::bind(&GridManager::ChangeGridSize, this, std::placeholders::_1));
        GUI.SetActivePenFn(std::bind(&GridManager::SetActivePen, this, std::placeholders::_1));
        GUI.SetClearCellMatrixFn(std::bind(&GridManager::ClearCellMatrix, this));
        SetGridCells(GRID_SIZE_MODE_2.x, GRID_SIZE_MODE_2.y);
    }
    void SetGridCells(const int & wCount, const int & hCount) {
        columnNum_ = wCount;
        cellSize_ = (((WINDOW_WIDTH - CELL_SPACE_PIXEL * 2) / wCount) - CELL_SPACE_PIXEL); // INFO : Or (((WINDOW_HEIGHT - CELL_SPACE_PIXEL * 2) / hCount) - CELL_SPACE_PIXEL) 
        double cellSizeRltW = (cellSize_ / ((double)WINDOW_WIDTH / 2));
        double cellSizeRltH = (cellSize_ / ((double)WINDOW_HEIGHT / 2));
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
    void SetActivePen(int activePen) {
        activePen_ = activePen;
    }
    void ClearCellMatrix() {
        for(int i = 0; i < totalCell_; i++) {
            cells_[i].color = Style::Color::COLOR_EMPTY;
        }
    }
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
    void KeyHandler(int key, int action) {
        if(action == GLFW_PRESS) {
            if(key == GLFW_KEY_S) {
                activePen_ += 1;
                if(activePen_ == Style::Pen::PEN_MAX) {
                    activePen_ = 0;
                }
            }
        }
    }
    void MousePosHandler(double xpos, double ypos) {
        mousePos_.x = xpos;
        mousePos_.y = ypos;
        MouseButtonCalc();
    }
    void MouseButtonHandler(int button, int action) {
        mouseAction_ = action;
        mouseButton_ = button;
        MouseButtonCalc();
    }
    void MouseButtonCalc() {
        if(mouseAction_ == GLFW_PRESS) {
            Index2D indexPos = ResolutionToIndexPos(mousePos_);
            int i = indexPos.i * columnNum_ + indexPos.j;
            if(activePen_ == Style::Pen::PEN_OBSTACLE) {
                if(mouseButton_ == GLFW_MOUSE_BUTTON_LEFT) {
                    cells_[i].color = Style::Color::COLOR_OBSTACLE;
                } else if(mouseButton_ == GLFW_MOUSE_BUTTON_RIGHT) {
                    cells_[i].color = Style::Color::COLOR_EMPTY;
                }
            } else if(activePen_ == Style::Pen::PEN_START) {
                if(mouseButton_ == GLFW_MOUSE_BUTTON_LEFT) {
                    int oldi = startNodeInd_.i * columnNum_ + startNodeInd_.j;
                    cells_[oldi].color = Style::Color::COLOR_EMPTY;
                    cells_[i].color = Style::Color::COLOR_START;
                    startNodeInd_ = indexPos;
                }
            } else if(activePen_ == Style::Pen::PEN_FINAL) {
                if(mouseButton_ == GLFW_MOUSE_BUTTON_LEFT) {
                    int oldi = finalNodeInd_.i * columnNum_ + finalNodeInd_.j;
                    cells_[oldi].color = Style::Color::COLOR_EMPTY;
                    cells_[i].color = Style::Color::COLOR_FINAL;
                    finalNodeInd_ = indexPos;
                }
            }
        }
    }

    Index2D ResolutionToIndexPos(Position2D resPos) {
        int columnIndex = resPos.x / (CELL_SPACE_PIXEL + cellSize_);
        int rowIndex = resPos.y / (CELL_SPACE_PIXEL + cellSize_);
        Index2D indexPos(rowIndex, columnIndex);
        return indexPos;
    }
private:
    Cell * cells_;
    int totalCell_;
    int columnNum_;
    int cellSize_;        // Pixel size of cell.
    int activePen_;
    Index2D startNodeInd_;
    Index2D finalNodeInd_;
    Position2D mousePos_; // Resolution position.
    int mouseAction_;
    int mouseButton_;
};

#endif // GRID_MANAGER_HPP_