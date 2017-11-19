#include <algorithm>
#include <cxxopts.hpp>
#include "http/server.hpp"

int main(int argc, char *argv[]) {
  cxxopts::Options options(argv[0], "White renderer server");
  options.add_options()
    ("h,help", "Show help")
    ("p,port", "Port that the server will listen to", cxxopts::value<int>())
    ;

  const auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help({""}) << std::endl;
    exit(0);
  }
  if (!result.count("port")) {
    std::cout << "-p --port is required, use --help\n";
    exit(0);
  }

  const auto port = result["port"].as<int>();
  white::http::Server server(port);

  server.init();
  server.start();

  server.shutdown();
}
