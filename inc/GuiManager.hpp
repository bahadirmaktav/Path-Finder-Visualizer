#ifndef GUI_MANAGER_HPP_
#define GUI_MANAGER_HPP_

#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GUI GuiManager::Instance()

class GuiManager {
public:
    GuiManager()
    : io_(nullptr)
    , gridSizeMode_(2) {
        changeGridSizeFn_ = [](int gridSizeMode) {};
    }
    ~GuiManager() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    static GuiManager & Instance() {
        static GuiManager guiManager;
        return guiManager;
    }
    GuiManager(const GuiManager &) = delete;
    GuiManager & operator = (const GuiManager &) = delete;
    void SetChangeGridSizeFn(std::function<void(int)> changeGridSizeCb) {
        changeGridSizeFn_ = changeGridSizeCb;
    }
    void Init(GLFWwindow * window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io_ = &ImGui::GetIO(); (void)*io_;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }
    void Render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        SettingsWindow();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
private:
    void SettingsWindow() {
        ImGui::Begin("Settings");
        if(ImGui::SliderInt("Grid Size Mode", &gridSizeMode_, 1, 3)) {
        }
        if(ImGui::Button("Change Grid Size")) {
            changeGridSizeFn_(gridSizeMode_);
        }
        ImGui::End();
    }
private:
    ImGuiIO * io_;
    int gridSizeMode_;
    std::function<void(int)> changeGridSizeFn_;
};

#endif // GUI_MANAGER_HPP_