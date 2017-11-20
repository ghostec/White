#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <chrono>
#include <thread>

namespace white::http {

class Http {
 public:
  Http(const int port) {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));
    m_endpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
  }

  void start() {
    m_endpoint->setHandler(router.handler());
    m_endpoint->serveThreaded();

    while (!should_shutdown) {
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    m_endpoint->shutdown();
  }

 protected:
  virtual void setup_routes() = 0;

  void init(const size_t thr = 2) {
    auto opts = Pistache::Http::Endpoint::options().threads(thr).flags(
        Pistache::Tcp::Options::InstallSignalHandler);
    m_endpoint->init(opts);
    Pistache::Rest::Routes::Post(
        router, "/shutdown",
        Pistache::Rest::Routes::bind(&Http::post_shutdown, this));
    setup_routes();
  }

  std::shared_ptr<Pistache::Http::Endpoint> m_endpoint;
  Pistache::Rest::Router router;

 private:
  void post_shutdown(const Pistache::Rest::Request& request,
                     Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok);
    should_shutdown = true;
  }

  bool should_shutdown = false;
};

}  // namespace white::http
