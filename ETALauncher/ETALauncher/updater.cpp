#include "updater.h"
#include <Awesomium\WebView.h>
#include <Awesomium\WebViewListener.h>
#include <Awesomium/STLHelpers.h>

using namespace Awesomium;

#include <sstream>

struct downloader : WebViewListener::Download
{
  void OnRequestDownload(Awesomium::WebView* caller,
    int download_id,
    const Awesomium::WebURL& url,
    const Awesomium::WebString& suggested_filename,
    const Awesomium::WebString& mime_type)
  {
  }

  void OnUpdateDownload(Awesomium::WebView* caller,
    int download_id,
    int64 total_bytes,
    int64 received_bytes,
    int64 current_speed)
  {
    float p = 100.0 * received_bytes / total_bytes;
    std::stringstream ss;

    ss << "$('#progress').html('" << p << "% " << current_speed / 1024 << "kbit/s" << "')";
    caller->ExecuteJavascript(WSLit(ss.str().c_str()), WSLit(""));
  }

  void OnFinishDownload(Awesomium::WebView* caller,
    int download_id,
    const Awesomium::WebURL& url,
    const Awesomium::WebString& saved_path)
  {
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

  dl = new downloader();
  view->set_download_listener(dl);
  return true;
}