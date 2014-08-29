#include "browser.h"
#include <map>

bool browser::RegisterClass(string name, WNDPROC proc)
{
  // Thread unsafe
  static map<string, bool> registered;

  if (registered.find(name) != registered.end())
    return true;

  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = proc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = instance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = name.c_str();
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
 
  if (!RegisterClassEx(&wc))
    return false;
  registered.insert({ name, true });
  return true;
}

HWND browser::OpenWindow(string clas, string title)
{
  HWND hwnd_ = ::CreateWindow(clas.c_str(),
    title.c_str(),
    WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    default_width,
    default_height,
    NULL,
    NULL,
    instance,
    NULL);

  if (!hwnd_)
    return hwnd_;

  ShowWindow(hwnd_, SW_SHOWNORMAL);
  UpdateWindow(hwnd_);
  SetTimer(hwnd_, 0, 15, NULL);
  return hwnd_;
}

#include <Awesomium\WebCore.h>

bool browser::Update()
{
  MSG msg;

  if (!GetMessage(&msg, NULL, 0, 0))
    return false;
  core->Update();
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  return true;
}