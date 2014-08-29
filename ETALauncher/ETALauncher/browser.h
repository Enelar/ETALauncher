#pragma once

#include <Windows.h>
#include <string>

using namespace std;

#include "headerless.h"

struct browser
{
  browser(Awesomium::WebCore *c, HINSTANCE i)
    : core(c), instance(i) {}
  void Open(string url);
  bool Update();

  const static int
    default_width = 800,
    default_height = 400;
private:
  HWND OpenWindow(string clas, string title);
  bool RegisterClass(string name, WNDPROC proc);
  HWND hwnd;
  HINSTANCE instance;
public:
  Awesomium::WebCore *core;
  Awesomium::WebView *view;
};
