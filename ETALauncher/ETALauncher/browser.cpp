#pragma comment(lib, "awesomium.lib")

#include "browser.h"

#include <Awesomium\WebCore.h>
#include <Awesomium/STLHelpers.h>

using namespace Awesomium;

WebView* view = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

static const char szWindowClass[] = "DEFCLASS";
static const char szTitle[] = "ÝÒÀ ËÀÓÍ×ÅÐ";

void browser::Open(string url)
{
  view = core->CreateWebView(default_width, default_height, 0, kWebViewType_Window);
  if (!RegisterClass(szWindowClass, WndProc))
    exit(-1);
  hwnd = OpenWindow(szWindowClass, szTitle);
  if (!hwnd)
    exit(-1);
  view->set_parent_window(hwnd);

  auto s = WSLit(url.c_str());
  view->LoadURL(WebURL(s));

  while (view->IsLoading())
    core->Update();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_COMMAND:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  case WM_TIMER:
    break;
  case WM_SIZE:
    if (view)
      view->Resize(LOWORD(lParam), HIWORD(lParam));
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_QUIT:
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}