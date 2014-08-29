#pragma once

#include "headerless.h"

struct loader;
struct updater
{
  Awesomium::WebView *view;
  loader *dl;
  updater(Awesomium::WebView *_view) : view(_view) {};

  bool Bind();
};
