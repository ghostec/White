#include <algorithm>
#include <cxxopts.hpp>
#include <pistache/endpoint.h>
#include "http/server.hpp"

int main(int argc, char *argv[]) {
  cxxopts::Options options(argv[0], "White renderer server");
  options.add_options()
    ("h,help", "Show help")
    ("p,port", "Port that the server will listen to", cxxopts::value<int>())
    ;

  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help({""}) << std::endl;
    exit(0);
  }
  if (!result.count("port")) {
    std::cout << "-p --port is required, use --help\n";
    exit(0);
  }

  Pistache::Port port(result["port"].as<int>());
  Pistache::Address addr(Pistache::Ipv4::any(), port);
  white::http::Server server(addr);

  server.init();
  server.start();

  server.shutdown();
}
