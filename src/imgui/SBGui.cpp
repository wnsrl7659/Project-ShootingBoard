#include "SBGui.h"
#include "SBGuiWindow.h"
#include "SBGuiWidgets.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../system/Window.h"

bool pressGUI = false;
bool uiGUI = false;


SBGui::SBGui(){

}

SBGui::~SBGui(){
}

void SBGui::Init() {
  GLFWwindow* pWindow = GetWindow();
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
  ImGui_ImplOpenGL3_Init("#version 130");

  // test window
  guiWindows.push_back(new SBGuiTestWindow());
  guiWindows.push_back(new SBGuiFPSWindow());

  uiWindows.push_back(new SBGuiTimeWindow());
  uiWindows.push_back(new SBGuiHPWindow());
}

void SBGui::Update() {

  // Start the Dear ImGui frame
  if (pressGUI || uiGUI)
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGuiIO& io = ImGui::GetIO();

    /*********************************************************/
    int width, height;
    glfwGetWindowSize(GetWindow(), &width, &height);
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    int W = desktop.right;
    int H = desktop.bottom;

    io.MousePos.x = io.MousePos.x * (width / io.DisplaySize.x);
    io.MousePos.y = io.MousePos.y * (height / io.DisplaySize.y);

    io.DisplaySize = ImVec2(width, height);
    io.DisplayFramebufferScale = ImVec2(1, 1);

    /*********************************************************/

    ImGui::NewFrame();

    if (pressGUI)
    {
      for (SBGuiWindow* window : guiWindows) {
        window->Update();
      }
    }
    if (uiGUI)
    {
      for (SBGuiWindow* window : uiWindows) {
        window->Update();
      }
    }
  }
}

void SBGui::Render(){
    if (pressGUI || uiGUI)
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void SBGui::Shutdown(){
  for (SBGuiWindow* window : guiWindows) {
    delete window;
  }
  for (SBGuiWindow* window : uiWindows) {
    delete window;
  }
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
