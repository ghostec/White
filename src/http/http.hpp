#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

namespace white::http {

class Http {
  public:
    Http(const int port) {
      Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));
      m_endpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
    }

    void init(const size_t thr = 2) {
      auto opts =
        Pistache::Http::Endpoint::options()
        .threads(thr)
        .flags(Pistache::Tcp::Options::InstallSignalHandler);
      m_endpoint->init(opts);
      setupRoutes();
    }

    void start() {
      m_endpoint->setHandler(router.handler());
      m_endpoint->serve();
    }

    void shutdown() {
      m_endpoint->shutdown();
    }

  protected:
    virtual void setupRoutes() = 0;
    std::shared_ptr<Pistache::Http::Endpoint> m_endpoint;
    Pistache::Rest::Router router;
};

}
