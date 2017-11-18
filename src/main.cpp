#include <algorithm>
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <cxxopts.hpp>

using namespace Pistache;

class Server {
  public:
    Server(Address addr)
      : httpEndpoint(std::make_shared<Http::Endpoint>(addr)) {}

    void init(size_t thr = 2) {
      auto opts =
        Http::Endpoint::options()
        .threads(thr)
        .flags(Tcp::Options::InstallSignalHandler);
      httpEndpoint->init(opts);
      setupRoutes();
    }

    void start() {
      httpEndpoint->setHandler(router.handler());
      httpEndpoint->serve();
    }

    void shutdown() {
      httpEndpoint->shutdown();
    }

  private:
    void setupRoutes() {
      using namespace Rest;
      Routes::Post(router, "/workers", Routes::bind(&Server::registerWorker, this));
    }

    void registerWorker(const Rest::Request& request, Http::ResponseWriter response) {
      response.send(Http::Code::Ok, "Isso ae!\n");
    }

    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
};

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

  Port port(result["port"].as<int>());

  Address addr(Ipv4::any(), port);
  Server server(addr);

  server.init();
  server.start();

  server.shutdown();
}
