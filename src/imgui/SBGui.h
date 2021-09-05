#pragma once
#include <string>
#include <vector>
#include <d3d11.h>

class SBGuiWindow;
struct GLFWwindow;

class SBGui {
public:
    SBGui();
    ~SBGui();

    void Init();

    void Update();
    void Render();
    void Shutdown();

private:
  std::vector<SBGuiWindow*> guiWindows;
  std::vector<SBGuiWindow*> uiWindows;
};

extern bool pressGUI;
extern bool uiGUI;