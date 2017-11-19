#include <iostream>
#include <rapidjson/document.h>
#include "server.hpp"

namespace white::http {

Server::Server(const int port) : white::http::Http(port) {}

void Server::setup_routes() {
  Pistache::Rest::Routes::Post(
    router,
    "/workers",
    Pistache::Rest::Routes::bind(&Server::post_workers, this)
  );

  Pistache::Rest::Routes::Post(
    router,
    "/jobs",
    Pistache::Rest::Routes::bind(&Server::post_jobs, this)
  );
}

void Server::post_workers(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
  rapidjson::Document body;
  body.Parse(request.body().c_str());
  std::cout << body["port"].GetInt() << std::endl;
  response.send(Pistache::Http::Code::Ok, "POST /workers\n");
}

void Server::post_jobs(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Ok, "POST /jobs\n");
}

}
