#pragma once

#include "headerless.h"

struct downloader;
struct updater
{
  Awesomium::WebView *view;
  downloader *dl;
  updater(Awesomium::WebView *_view) : view(_view) {};

  bool Bind();
};
