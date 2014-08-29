#include "updater.h"
#include <Awesomium\WebView.h>
#include <Awesomium\WebViewListener.h>
#include <Awesomium/STLHelpers.h>

using namespace Awesomium;

#include <sstream>
#include <string>
#include <chrono>

struct loader : WebViewListener::Load
{
  updater &u;

  loader(updater &_u) : u(_u) {}
  void OnBeginLoadingFrame(Awesomium::WebView* caller,
    int64 frame_id,
    bool is_main_frame,
    const Awesomium::WebURL& url,
    bool is_error_page)
  {
  }

  void OnFailLoadingFrame(Awesomium::WebView* caller,
    int64 frame_id,
    bool is_main_frame,
    const Awesomium::WebURL& url,
    int error_code,
    const Awesomium::WebString& error_desc)
  {
  }

  void OnFinishLoadingFrame(Awesomium::WebView* caller,
    int64 frame_id,
    bool is_main_frame,
    const Awesomium::WebURL& url)
  {
  }

  void OnDocumentReady(Awesomium::WebView* caller,
    const Awesomium::WebURL& url)
  {
    std::stringstream ss;
    ss << url.spec();
    std::string s = ss.str();

    if (s.find("success.php") != s.npos)
    {
      DownloadUpdate();

      std::string roaming = getenv("APPDATA");
      std::string we = roaming + "/.eta-mc.ru/";

      auto res = caller->ExecuteJavascriptWithResult(WSLit("$('#username').html()"), WSLit(""));
      ss.swap(std::stringstream());
      ss << "\"" << res.ToString() << "\"";
      auto username = ss.str();

      ShellExecute(NULL, NULL, (we + "start.bat").c_str(), username.c_str(), we.c_str(), SW_HIDE);
      exit(0);
    }
  }

  void DownloadUpdate()
  {
    char *roaming = getenv("APPDATA");

    auto start = std::chrono::system_clock::now();
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "C:/documents/com/etamc/wget.exe";
    ShExecInfo.lpParameters = "-c http://eta-mc.ru/minecraft.7z";
    ShExecInfo.lpDirectory = roaming;
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
    auto end = std::chrono::system_clock::now();

    if (end - start < std::chrono::seconds(10))
      return;

    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "C:/documents/com/etamc/7zr.exe";
    ShExecInfo.lpParameters = "x -y minecraft.7z";
    ShExecInfo.lpDirectory = roaming;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
  }
};

bool updater::Bind()
{
  auto result = view->CreateGlobalJavascriptObject(WSLit("eta"));
  if (result.IsObject())
  {
    auto &obj = result.ToObject();
    obj.SetCustomMethod(WSLit("update"), false);
  }

  dl = new loader(*this);
  view->set_load_listener(dl);
  return true;
}