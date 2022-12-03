#include "PathFinderApp.hpp"

int main(int, char**) {
    try {
        PathFinderApp::Instance().Init();
        PathFinderApp::Instance().Run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
