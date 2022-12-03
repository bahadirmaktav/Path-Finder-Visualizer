#ifndef GRID_PARAMETERS_H_
#define GRID_PARAMETERS_H_

constexpr int WINDOW_WIDTH = 1206;
constexpr int WINDOW_HEIGHT = 806;
constexpr int CELL_SPACE_PIXEL = 3;

constexpr double CELL_SPACE_RLT_W = (CELL_SPACE_PIXEL / ((double)WINDOW_WIDTH / 2));
constexpr double CELL_SPACE_RLT_H = (CELL_SPACE_PIXEL / ((double)WINDOW_HEIGHT / 2));

#endif // GRID_PARAMETERS_H_