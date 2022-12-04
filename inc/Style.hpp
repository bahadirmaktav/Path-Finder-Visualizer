#ifndef STYLE_HPP_
#define STYLE_HPP_

#include "GL/glew.h"

struct Style {
    enum Pen {
        PEN_OBSTACLE = 0,
        PEN_START,
        PEN_FINAL,
        PEN_MAX
    };
    enum Color{
        COLOR_EMPTY = 0,     // Empty Cells
        COLOR_OBSTACLE,      // Obstacle Cells
        COLOR_START,         // Start Cell
        COLOR_FINAL          // Final Cell
    };
    Style() {}
    static void SetColor(int color) {
        switch(color) {
        case Style::Color::COLOR_EMPTY:
            glColor3f(1, 1, 1);
            break;
        case Style::Color::COLOR_OBSTACLE:
            glColor3f(0.7f, 0.7f, 0.7f);
            break;
        case Style::Color::COLOR_START:
            glColor3f(0, 1, 1);
            break;
        case Style::Color::COLOR_FINAL:
            glColor3f(1, 1, 0);
            break;
        default:
            break;
        }
    }
};

#endif // STYLE_HPP_