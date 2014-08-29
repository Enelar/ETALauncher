#include "browser.h"
#include <future>

#include <Awesomium\WebCore.h>

#include "updater.h"

int __stdcall WinMain(HINSTANCE i, HINSTANCE, char *, int)
{
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