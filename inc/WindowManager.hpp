#ifndef WINDOW_MANAGER_HPP_
#define WINDOW_MANAGER_HPP_

#include <iostream>
#include <functional>
#include <memory>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "GridParameters.h"

#define WINDOW WindowManager::Instance()

class WindowManager {
public:
    WindowManager() 
    : window_(nullptr) {
        keyCallbackFn_ = [](int key, int action) {};
        mousePosCallbackFn_ = [](double xpos, double ypos) {};
        mouseButtonCallbackFn_ = [](int button, int action) {};
    }
    ~WindowManager() {
        glfwTerminate();
    }
    static WindowManager & Instance() {
        static WindowManager windowManager;
        return windowManager;
    }
    WindowManager(const WindowManager &) = delete;
    WindowManager & operator = (const WindowManager &) = delete;
    GLFWwindow * GetGlfwWindow() {
        return window_;
    }
    void SetKeyCallbackFn(std::function<void(int, int)> keyCb) {
        keyCallbackFn_ = keyCb;
    }
    void SetMousePosCallbackFn(std::function<void(double, double)> mousePosCb) {
        mousePosCallbackFn_ = mousePosCb;
    }
    void SetMouseButtonCallbackFn(std::function<void(int, int)> mouseButtonCb) {
        mouseButtonCallbackFn_ = mouseButtonCb;
    }
    void Init() {
        if(!glfwInit()) {
            throw std::runtime_error("Could not initialize GLFW!");
        }
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Path Finder Visualizer", NULL, NULL);
        if(!window_) {
            glfwTerminate();
            throw std::runtime_error("Could not create window!");
        }
        glfwMakeContextCurrent(window_);
        if(glewInit() != GLEW_OK) {
            throw std::runtime_error("Could not initialize GLEW!");
        }
        glfwSetKeyCallback(window_, key_callback);
        glfwSetCursorPosCallback(window_, cursor_position_callback);
        glfwSetMouseButtonCallback(window_, mouse_button_callback);
        glfwSetInputMode(window_, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        keyCallbackFn_(key, action);
    }
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        mousePosCallbackFn_(xpos, ypos);
    }
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        mouseButtonCallbackFn_(button, action);
    }
    void PreRender() {
        if(glfwWindowShouldClose(window_)) {
            throw std::runtime_error("Window is closed!");
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void PostRender() {
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
private:
    GLFWwindow * window_;
    static std::function<void(int, int)> keyCallbackFn_;
    static std::function<void(double, double)> mousePosCallbackFn_;
    static std::function<void(int, int)> mouseButtonCallbackFn_;
};

std::function<void(int, int)> WindowManager::keyCallbackFn_;
std::function<void(double, double)> WindowManager::mousePosCallbackFn_;
std::function<void(int, int)> WindowManager::mouseButtonCallbackFn_;

#endif // WINDOW_MANAGER_HPP_