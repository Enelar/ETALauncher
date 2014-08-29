#include "browser.h"
#include <future>

#include <Awesomium\WebCore.h>

#include "updater.h"

string GetPWD()
{
  static string str = []() -> string
  {
    const int size = 1000;
    char str[size];
    GetCurrentDirectory(size, str);
    return{ str };
  }() + "/";
  return str;
}


int __stdcall WinMain(HINSTANCE i, HINSTANCE, char *, int)
{
  GetPWD();

  using namespace Awesomium;
  WebCore* core = WebCore::Initialize(WebConfig());
  browser b(core, i);
  b.Open("http://eta-mc.ru/launch");

  updater u(b.view);
  u.Bind();

  while (b.Update())
    this_thread::sleep_for(5ms);
  WebCore::Shutdown();
  return 0;
}