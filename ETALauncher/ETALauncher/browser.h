#pragma once

#include <Windows.h>
#include <string>

using namespace std;

namespace Awesomium
{
  class WebCore;
}

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
  Awesomium::WebCore *core;
};
