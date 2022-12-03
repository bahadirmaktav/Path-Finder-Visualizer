#ifndef PATH_FINDER_APP_
#define PATH_FINDER_APP_

#include <iostream>
#include <chrono>
#include <thread>

#include "WindowManager.hpp"

class PathFinderApp {
public:
    PathFinderApp() {}
    ~PathFinderApp() {}
    static PathFinderApp & Instance() {
        static PathFinderApp pathFinderApp;
        return pathFinderApp;
    }
    PathFinderApp(const PathFinderApp &) = delete;
    PathFinderApp & operator = (const PathFinderApp &) = delete;
    void Init() {
        WINDOW.Init();
    }
    void Run() {
        while(true) {
            WINDOW.PreRender();
            WINDOW.RenderGrid();
            WINDOW.PostRender();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

#endif // PATH_FINDER_APP_