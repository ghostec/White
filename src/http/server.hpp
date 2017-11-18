#include "http.hpp"

namespace white::http {

class Server : public Http {
  public:
    Server(Pistache::Address addr) : white::http::Http(addr) {}

  private:
    void setupRoutes() {
      Pistache::Rest::Routes::Post(router, "/workers",
        Pistache::Rest::Routes::bind(&Server::registerWorker, this)
      );
    }

    void registerWorker(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
      response.send(Pistache::Http::Code::Ok, "Isso ae!\n");
    }
};

}
