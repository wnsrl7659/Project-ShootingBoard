#include "SBGuiWindow.h"
#include "imgui.h"
#include "../system/Window.h"


SBGuiTreeNode* tn_object;

SBGuiWindow::SBGuiWindow(std::string windowTitle)
  : title_(windowTitle) {
}

SBGuiWindow::~SBGuiWindow() {
  for (SBGuiWidgets* w : widgets_) {
    delete w;
  }
}

void SBGuiWindow::Update() {
  int width, height;
  glfwGetWindowSize(GetWindow(), &width, &height);

  if (title_ == "test")
  {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::Begin(title_.c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
  }
  else if (title_ == "Time")
  {
    int neww = width * 120 / 700;
    int newh = height * 60 / 500;
    ImGui::SetNextWindowPos(ImVec2(width * 0 / 700, height * 35 / 500));
    ImGui::SetNextWindowSize(ImVec2(neww, newh));
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin(title_.c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
  }
  else if (title_ == "HP")
  {
    int neww = width * 120 / 700;
    int newh = height * 60 / 500;
    ImGui::SetNextWindowPos(ImVec2(width * 0 / 700, height * 185 / 500));
    ImGui::SetNextWindowSize(ImVec2(neww, newh));
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin(title_.c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
  }
  else
  {
    ImGui::Begin(title_.c_str());
  }

  for (SBGuiWidgets* w : widgets_) {
      w->update();
  }
  ImGui::End();
}

void SBGuiWindow::AddWidget(SBGuiWidgets* widget) {
  widgets_.push_back(widget);
}

SBGuiTestWindow::SBGuiTestWindow()
  : SBGuiWindow("TestTitle") {

  SBGuiCollapsingHeader* buttonHeader = new SBGuiCollapsingHeader("SCENE HEADER");

  SBGuiTreeNode* tn_Scene = new SBGuiTreeNode("Scene Manager");
  tn_Scene->AddWidget(new SBGuiText("Scence Button"));
  buttonHeader->AddWidget(tn_Scene);

  AddWidget(buttonHeader);


  SBGuiCollapsingHeader* objectHeader = new SBGuiCollapsingHeader("OBJECT HEADER");

  tn_object = new SBGuiTreeNode("Object Manager");
  objectHeader->AddWidget(tn_object);

  AddWidget(objectHeader);


}

SBGuiTestWindow::~SBGuiTestWindow(){
}


SBGuiFPSWindow::SBGuiFPSWindow()
  : SBGuiWindow("FPS Window")
{
  AddWidget(new SBGuiFPS("FPS"));
}

SBGuiFPSWindow::~SBGuiFPSWindow() {
}


SBGuiTimeWindow::SBGuiTimeWindow()
  : SBGuiWindow("Time")
{
  AddWidget(new SBGuiTimer());
}

SBGuiTimeWindow::~SBGuiTimeWindow() {
}


SBGuiHPWindow::SBGuiHPWindow()
  : SBGuiWindow("HP")
{
  AddWidget(new SBGuiHP());
}

SBGuiHPWindow::~SBGuiHPWindow() {
}

