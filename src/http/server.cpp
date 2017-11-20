#include "server.hpp"
#include <rapidjson/document.h>
#include <iostream>

namespace white::http {

Server::Server(const int port) : white::http::Http(port) { init(); }

void Server::setup_routes() {
  Pistache::Rest::Routes::Post(
      router, "/workers",
      Pistache::Rest::Routes::bind(&Server::post_workers, this));

  Pistache::Rest::Routes::Post(
      router, "/jobs", Pistache::Rest::Routes::bind(&Server::post_jobs, this));

  Pistache::Rest::Routes::Post(
      router, "/render",
      Pistache::Rest::Routes::bind(&Server::post_render, this));
}

void Server::post_workers(const Pistache::Rest::Request& request,
                          Pistache::Http::ResponseWriter response) {
  rapidjson::Document body;
  body.Parse(request.body().c_str());
  workers.push_back(body["port"].GetInt());
  response.send(Pistache::Http::Code::Ok);
}

void Server::post_jobs(const Pistache::Rest::Request& request,
                       Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Ok, "POST /jobs\n");
}

void Server::post_render(const Pistache::Rest::Request& request,
                         Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Ok, "POST /render\n");
}

}  // namespace white::http
