#include "server.hpp"

namespace white::http {

Server::Server(const int port) : white::http::Http(port) {}

void Server::setupRoutes() {
  Pistache::Rest::Routes::Post(
    router,
    "/workers",
    Pistache::Rest::Routes::bind(&Server::registerWorker, this)
  );
}

void Server::registerWorker(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Ok, "Isso ae!\n");
}

}
