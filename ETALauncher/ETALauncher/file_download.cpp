#include "file_download.h"
#include <boost\asio.hpp>
#include <iterator>
#include <sstream>
#include <array>

string Download(string url, function<void(string, float)> cb)
{
  boost::asio::io_service io;
  boost::asio::ip::tcp::socket socket(io);
  boost::asio::ip::tcp::resolver resolver(io);
  connect(socket, resolver.resolve({ "eta-mc.ru", "80" }));

  string request[] =
  {
    "GET /minecraft.7z HTTP/1.1",
    "Host: eta-mc.ru"
  };
  
  stringstream o;

  for each (auto &row in request)
    o << row << "\r\n";

  boost::asio::write(socket, boost::asio::buffer(o.str(), o.str().size()));
  return "";
}