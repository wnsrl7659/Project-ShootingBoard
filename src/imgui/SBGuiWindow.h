#pragma once

#include <string>
#include <vector>
#include "SBGuiWidgets.h"

class SBGuiWidgets;

class SBGuiWindow {
public:
  SBGuiWindow(std::string windowTitle);
  ~SBGuiWindow();

  virtual void Update();

  // the window will delete the memory when it is destroyed
  void AddWidget(SBGuiWidgets* widget);

private:
  std::string title_;
  std::vector<SBGuiWidgets*> widgets_;
};

class SBGuiTestWindow : public SBGuiWindow {
public:
  SBGuiTestWindow();
  ~SBGuiTestWindow();

private:
  bool testCheckBoxBool_ = false;
  int  sliderint_ = 0;
  int  dragint_ = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  bool yes = true;
};


class SBGuiFPSWindow : public SBGuiWindow {
public:
  SBGuiFPSWindow();
  ~SBGuiFPSWindow();

private:
};

class SBGuiTimeWindow : public SBGuiWindow {
public:
  SBGuiTimeWindow();
  ~SBGuiTimeWindow();

private:
};

class SBGuiHPWindow : public SBGuiWindow {
public:
  SBGuiHPWindow();
  ~SBGuiHPWindow();

private:
};



extern SBGuiTreeNode* tn_object;
