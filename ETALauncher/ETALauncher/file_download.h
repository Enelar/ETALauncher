#pragma once

#include <functional>
#include <string>

using namespace std;

string Download(string url, function<void(string, float)>);