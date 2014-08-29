#include <Awesomium\WebCore.h>
#include <Windows.h>

#include <Awesomium/STLHelpers.h>
#include <future>

using namespace Awesomium;
using namespace std;

#pragma comment(lib, "awesomium.lib")

const char szWindowClass[] = "ViewWinClass";
const char szTitle[] = "ÝÒÀ ËÀÓÍ×ÅÐ";

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#define WIDTH 800
#define HEIGHT 400

struct window
{
  HWND hwnd_;


  void OpenWindow(HINSTANCE i)
  {
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(0);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szWindowClass;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    if (!RegisterClassEx(&wc)) {
      exit(-1);
    }

    hwnd_ = ::CreateWindow(szWindowClass,
      szTitle,
      WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      WIDTH,
      HEIGHT,
      NULL,
      NULL,
      i,
      NULL);
    if (!hwnd_)
      exit(-1);

    ShowWindow(hwnd_, SW_SHOWNORMAL);
    UpdateWindow(hwnd_);
    SetTimer(hwnd_, 0, 15, NULL);
  }
};

WebView* view;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_COMMAND:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  case WM_TIMER:
    break;
  case WM_SIZE:
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

int __stdcall WinMain(HINSTANCE i, HINSTANCE, char *, int)
{
  WebCore* core = WebCore::Initialize(WebConfig());

  window w;
  view = core->CreateWebView(WIDTH, HEIGHT, 0, kWebViewType_Window);
  w.OpenWindow(i);
  view->set_parent_window(w.hwnd_);
  auto s = WSLit("http://eta-mc.ru/launch");
  view->LoadURL(WebURL(s));

  // finish loading the page
  while (view->IsLoading())
    core->Update();

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    core->Update();
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    this_thread::sleep_for(5ms);
  }
  WebCore::Shutdown();
  return 0;
}