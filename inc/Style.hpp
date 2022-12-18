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
        COLOR_EMPTY = 0,     // Empty Cell
        COLOR_OBSTACLE,      // Obstacle Cell
        COLOR_START,         // Start Cell
        COLOR_FINAL,         // Final Cell
        COLOR_OPENED,        // Opened Cell
        COLOR_CLOSED,        // Closed Cell
        COLOR_SEARCH_PATH    // Search Path Cell
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
        case Style::Color::COLOR_OPENED:
            glColor3f(0, 1, 0);
            break;
        case Style::Color::COLOR_CLOSED:
            glColor3f(1, 0, 0);
            break;
        case Style::Color::COLOR_SEARCH_PATH:
            glColor3f(0, 0, 0.8f);
            break;
        default:
            break;
        }
    }
};

#endif // STYLE_HPP_