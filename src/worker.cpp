#include "http/worker.hpp"
#include <algorithm>
#include <cxxopts.hpp>

int main(int argc, char *argv[]) {
  cxxopts::Options options(argv[0], "White renderer worker");
  options.add_options()("h,help", "Show help")(
      "p,port", "Port that the worker will listen to", cxxopts::value<int>())(
      "s,server", "Port that the server is listening to",
      cxxopts::value<int>());

  const auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help({""}) << std::endl;
    exit(0);
  }
  if (!result.count("port")) {
    std::cout << "-p --port is required, use --help\n";
    exit(0);
  }
  if (!result.count("server")) {
    std::cout << "-s --server is required, use --help\n";
    exit(0);
  }

  const auto port = result["port"].as<int>();
  const auto server = result["server"].as<int>();
  white::http::Worker worker(port, server);
  worker.start();
}
