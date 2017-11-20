#include "worker.hpp"
#include <rapidjson/document.h>
#include <iostream>

namespace white::http {

Worker::Worker(const int port, const int server) : white::http::Http(port) {
  init();
}

void Worker::setup_routes() {
  Pistache::Rest::Routes::Post(
      router, "/jobs", Pistache::Rest::Routes::bind(&Worker::post_jobs, this));
}

void Worker::post_jobs(const Pistache::Rest::Request& request,
                       Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Ok, "POST /jobs\n");
}

}  // namespace white::http
