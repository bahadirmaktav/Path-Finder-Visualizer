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
    , gridSizeMode_(2)
    , selectedAlgoritmType_(0)
    , penTypeNames_{"Obstacle", "Start", "Final"} 
    , algorithmTypeNames_{"BFS", "DFS", "Dijkstra", "A*"} {
        changeGridSizeFn_ = [](int gridSizeMode) {};
        setActivePenFn_ = [](int activePen) {};
        clearCellMatrixFn_ = []() {};
        setActiveAlgorithmFn_ = [](int activeAlgorithm) {};
        startSimulationFn_ = []() {};
        stopSimulationFn_ = []() {};
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
    ImGuiIO * GetGuiIO() {
        return io_;
    }
    void SetSelectedPenType(int selectedPenType) {
        selectedPenType_ = selectedPenType;
    }
    void SetChangeGridSizeFn(std::function<void(int)> changeGridSizeCb) {
        changeGridSizeFn_ = changeGridSizeCb;
    }
    void SetActivePenFn(std::function<void(int)> setActivePenCb) {
        setActivePenFn_ = setActivePenCb;
    }
    void SetClearCellMatrixFn(std::function<void()> clearCellMatrixCb) {
        clearCellMatrixFn_ = clearCellMatrixCb;
    }
    void SetActiveAlgorithmFn(std::function<void(int)> setActiveAlgorithmCb) {
        setActiveAlgorithmFn_ = setActiveAlgorithmCb;
    }
    void SetStartSimulationFn(std::function<void()> startSimulationCb) {
        startSimulationFn_ = startSimulationCb;
    }
    void SetStopSimulationFn(std::function<void()> stopSimulationCb) {
        stopSimulationFn_ = stopSimulationCb;
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

        HelpWindow();
        SettingsWindow();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
private:
    void SettingsWindow() {
        ImGui::Begin("Settings");
            if(ImGui::Combo("Active Pen", &selectedPenType_, penTypeNames_, IM_ARRAYSIZE(penTypeNames_))) {
                setActivePenFn_(selectedPenType_);
            }
            if(ImGui::SliderInt("Grid Size Mode", &gridSizeMode_, 1, 3)) {
            }
            if(ImGui::Button("Change Grid Size")) {
                changeGridSizeFn_(gridSizeMode_);
            }
            ImGui::SameLine();
            if(ImGui::Button("Clear Cell Matrix")) {
                clearCellMatrixFn_();
            }
            if(ImGui::Combo("Active Algorithm", &selectedAlgoritmType_, algorithmTypeNames_, IM_ARRAYSIZE(algorithmTypeNames_))) {
                setActiveAlgorithmFn_(selectedAlgoritmType_);
            }
            if(ImGui::Button("Start Simulation")) {
                startSimulationFn_();
            }
            ImGui::SameLine();
            if(ImGui::Button("Stop Simulation")) {
                stopSimulationFn_();
            }
        ImGui::End();
    }
    void HelpWindow() {
        ImGui::Begin("Help");
            ImGui::Text("S           : Switch between pens. (Obstacle - Start - Final)");
            ImGui::Text("C           : Clear cell matrix.");
            ImGui::Text("P           : Start simulation.");
            ImGui::Text("Left Mouse  : Paint cell with active pen.");
            ImGui::Text("Right Mouse : Clear cell when active pen is obstacle.");
        ImGui::End();
    }
private:
    ImGuiIO * io_;
    int gridSizeMode_;
    int selectedPenType_;
    int selectedAlgoritmType_;
    const char * penTypeNames_[3];
    const char * algorithmTypeNames_[4];
    std::function<void(int)> changeGridSizeFn_;
    std::function<void(int)> setActivePenFn_;
    std::function<void()> clearCellMatrixFn_;
    std::function<void(int)> setActiveAlgorithmFn_;
    std::function<void()> startSimulationFn_;
    std::function<void()> stopSimulationFn_;
};

#endif // GUI_MANAGER_HPP_