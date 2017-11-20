#ifndef __WHITE_HTTP_SERVER__
#define __WHITE_HTTP_SERVER__

#include <vector>
#include "http.hpp"

namespace white::http {

class Server : public Http {
 public:
  Server(const int port);

 private:
  void setup_routes();
  void post_workers(const Pistache::Rest::Request& request,
                    Pistache::Http::ResponseWriter response);
  void post_jobs(const Pistache::Rest::Request& request,
                 Pistache::Http::ResponseWriter response);
  void post_render(const Pistache::Rest::Request& request,
                   Pistache::Http::ResponseWriter response);

  std::vector<int> workers;
};

}  // namespace white::http

#endif
