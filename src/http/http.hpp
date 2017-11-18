#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

namespace white::http {

class Http {
  public:
    Http(Pistache::Address addr)
      : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr)) {}

    void init(size_t thr = 2) {
      auto opts =
        Pistache::Http::Endpoint::options()
        .threads(thr)
        .flags(Pistache::Tcp::Options::InstallSignalHandler);
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

  protected:
    virtual void setupRoutes() = 0;
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;
};

}
