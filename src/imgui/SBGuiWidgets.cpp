#include "SBGuiWidgets.h"
#include "imgui.h"
#include "../system/Window.h"
#include "../scene/SceneTest.h"

//////////////////////////////////////////
// Text
SBGuiText::SBGuiText(std::string text)
  : text_(text) {
}

SBGuiText::~SBGuiText(){
}

void SBGuiText::update() {
    ImGui::Text(text_.c_str());
}
// End Text
///////////////////////////////////////////

///////////////////////////////////////////
// CheckBox
SBGuiCheckBox::SBGuiCheckBox(std::string name, bool* target)
    : name_(name), target_(target) {
}

SBGuiCheckBox::~SBGuiCheckBox() {
}

void SBGuiCheckBox::update() {
    ImGui::Checkbox(name_.c_str(), target_);
}
//End CheckBox
///////////////////////////////////////////

///////////////////////////////////////////
// Button
SBGuiButton::SBGuiButton(std::string name, void (*pfun)(), int width, int height)
    : name_(name), fun_ptr(pfun), width_(width), height_(height) {
}

SBGuiButton::~SBGuiButton() {
}

void SBGuiButton::update() {
    if (ImGui::Button(name_.c_str(), ImVec2(width_, height_)))
    {
        (*fun_ptr)();
    }
}
//End Button
///////////////////////////////////////////

///////////////////////////////////////////
// Slider
SBGuiSlider::SBGuiSlider(std::string name, int* target, int min, int max)
    : name_(name), target_(target), min_(min), max_(max) {
}

SBGuiSlider::~SBGuiSlider() {
}

void SBGuiSlider::update() {
    ImGui::SliderInt(name_.c_str(), target_, min_, max_);
}
//End Slider
///////////////////////////////////////////

///////////////////////////////////////////
// DragInt
SBGuiDragInt::SBGuiDragInt(std::string name, int* target)
    : name_(name), target_(target) {
}

SBGuiDragInt::~SBGuiDragInt() {
}

void SBGuiDragInt::update() {
    ImGui::DragInt(name_.c_str(), target_);
}
//End DragInt
///////////////////////////////////////////

///////////////////////////////////////////
// Collapsing Header

SBGuiCollapsingHeader::SBGuiCollapsingHeader(std::string name)
  : name_(name) {
}

SBGuiCollapsingHeader::~SBGuiCollapsingHeader() {
    for (SBGuiWidgets* w : widgets_) {
        delete w;
    }
}

void SBGuiCollapsingHeader::update() {
    if (ImGui::CollapsingHeader(name_.c_str())) {
        for (SBGuiWidgets* w : widgets_) {
            w->update();
        }
    }
}

void SBGuiCollapsingHeader::AddWidget(SBGuiWidgets* widget) {
    widgets_.push_back(widget);
}

// Collapsing Header
///////////////////////////////////////////

///////////////////////////////////////////
// TreeNode

SBGuiTreeNode::SBGuiTreeNode(std::string name)
    : name_(name) {
}

SBGuiTreeNode::~SBGuiTreeNode() {
    for (SBGuiWidgets* w : widgets_) {
        delete w;
    }
}

void SBGuiTreeNode::update() {
    if (ImGui::TreeNode(name_.c_str())) {
        for (SBGuiWidgets* w : widgets_) {
            w->update();
            //change
        }
        ImGui::TreePop();
    }
}

void SBGuiTreeNode::AddWidget(SBGuiWidgets* widget) {
    widgets_.push_back(widget);
}
void SBGuiTreeNode::DeleteWidget(int oid)
{
  int i = 0;
  for (SBGuiWidgets* w : widgets_) {
    SBGuiObject* temp = reinterpret_cast<SBGuiObject*>(w);
    if (temp->oid == oid)
    {
      delete w;
      widgets_.erase(widgets_.begin() + i);
    }
    i++;
  }
}

// TreeNode
///////////////////////////////////////////

SBGuiObject::SBGuiObject(std::string name, Sprite* sprite)
  : name_(name), pSp(sprite){
}

SBGuiObject::~SBGuiObject() {
}

void SBGuiObject::update() {
  if (ImGui::TreeNode(name_.c_str()))
  {
    glm::vec2 pPos = pSp->GetPosition();

    ImGui::DragFloat("Xpos", &pPos.x);
    ImGui::DragFloat("Ypos", &pPos.y);

    pSp->SetPosition(pPos.x, pPos.y);

    ImGui::TreePop();
  }
}

SBGuiFPS::SBGuiFPS(std::string name)
    : name_(name){
}

SBGuiFPS::~SBGuiFPS() {
}

void SBGuiFPS::update() {

    float fps = ImGui::GetIO().Framerate;

    FPSqueue.push(fps);

    int extraSpace = FPSqueue.size() - 120;
    for (int i = 0; i < extraSpace; i++)
        FPSqueue.pop();

    std::queue<float> duplicate = FPSqueue;

    float values[121];
    values[0] = 0;
    int queueSize = duplicate.size();
    for (int i = 0; i < queueSize; i++)
    {
        values[i + 1] = duplicate.front();
        duplicate.pop();
    }

    ImGui::PlotLines("Graph", values, queueSize, 1);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}


static double game_time = 0.0f;

SBGuiTimer::SBGuiTimer()
{
}

SBGuiTimer::~SBGuiTimer() {
}

void SBGuiTimer::update()
{
  //700 500
  int width, height;
  glfwGetWindowSize(GetWindow(), &width, &height);

  game_time++;

  ImGui::SetWindowFontScale(width * 2 / 700);

  int time = game_time;
  int timei = time / 60.0f;
  float timef = time / 60.0f;
  int timeMin = timei / 60;
  int timeSec = timei - 60 * timeMin;

  ImGui::Dummy(ImVec2(width * 0.5 / 700, 0));
  ImGui::SameLine();
  if (timeSec > 9)
  {
    ImGui::Text(" %d:%d", timeMin, timeSec);
  }
  else
  {
    ImGui::Text(" %d:0%d", timeMin, timeSec);
  }
}

void resetGameTime()
{
  game_time = 0.0f;
}

SBGuiHP::SBGuiHP()
{
}

SBGuiHP::~SBGuiHP() {
}

void SBGuiHP::update()
{
  //700 500
  int width, height;
  glfwGetWindowSize(GetWindow(), &width, &height);

  ImGui::SetWindowFontScale(width * 2 / 700);

  float HP = getHP();

  ImGui::Dummy(ImVec2(width * 0.5 / 700, 0));
  ImGui::SameLine();
  ImGui::Text(" %.2f", HP);
  
}
