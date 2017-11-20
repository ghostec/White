#ifndef __WHITE_HTTP_WORKER__
#define __WHITE_HTTP_WORKER__

#include <vector>
#include "http.hpp"

namespace white::http {

class Worker : public Http {
 public:
  Worker(const int port, const int sport);

 private:
  void setup_routes();
  void post_jobs(const Pistache::Rest::Request& request,
                 Pistache::Http::ResponseWriter response);

  // renderer::Renderer m_renderer;
};

}  // namespace white::http

#endif
