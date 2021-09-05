#pragma once

#include <string> // text, checkbox, headers
#include <vector> // collapsing header
#include <queue>  // FPS
#include "../graphic/Sprite.h"

class SBGuiWidgets {
public:
    SBGuiWidgets() {}
    virtual ~SBGuiWidgets() {}
    virtual void update() = 0;
};

class SBGuiText : public SBGuiWidgets {
public:
    SBGuiText(std::string text);
    ~SBGuiText();

    void update();
private:
    std::string text_;
};

class SBGuiCheckBox : public SBGuiWidgets {
public:
    SBGuiCheckBox(std::string name, bool* target);
    ~SBGuiCheckBox();

    void update();
private:
    std::string name_;
    bool* target_;
};

class SBGuiButton : public SBGuiWidgets {
public:
    SBGuiButton(std::string name, void (*pfun)(), int width = 0, int height = 0);
    ~SBGuiButton();

    void update();
private:
    std::string name_;
    int width_, height_;
    void (*fun_ptr)();
};

class SBGuiSlider : public SBGuiWidgets {
public:
    SBGuiSlider(std::string name, int* target, int min, int max);
    ~SBGuiSlider();

    void update();
private:
    std::string name_;
    int* target_;
    int min_;
    int max_;
};

class SBGuiDragInt : public SBGuiWidgets {
public:
    SBGuiDragInt(std::string name, int* target);
    ~SBGuiDragInt();

    void update();
private:
    std::string name_;
    int* target_;
};

class SBGuiCollapsingHeader : public SBGuiWidgets {
public:
  SBGuiCollapsingHeader(std::string name);
  ~SBGuiCollapsingHeader();

  void update();

  void AddWidget(SBGuiWidgets* widget);
private:
  std::string name_;
  std::vector<SBGuiWidgets*> widgets_;
};

class SBGuiTreeNode : public SBGuiWidgets {
public:
  SBGuiTreeNode(std::string name);
  ~SBGuiTreeNode();

  void update();

  void AddWidget(SBGuiWidgets* widget);
  void DeleteWidget(int oid);
private:
  std::string name_;
  std::vector<SBGuiWidgets*> widgets_;
};

class SBGuiObject : public SBGuiWidgets {
public:
  SBGuiObject(std::string name, Sprite* sprite);
  ~SBGuiObject();

  void update();
  int oid;
private:
  std::string name_;
  Sprite* pSp;
};

class SBGuiFPS : public SBGuiWidgets {
public:
    SBGuiFPS(std::string name);
    ~SBGuiFPS();

    void update();
private:
    std::string name_;
    std::queue<float> FPSqueue;
};

class SBGuiTimer : public SBGuiWidgets {
public:
  SBGuiTimer();
  ~SBGuiTimer();

  void update();
private:
};

class SBGuiHP : public SBGuiWidgets {
public:
  SBGuiHP();
  ~SBGuiHP();

  void update();
private:
};

void resetGameTime();