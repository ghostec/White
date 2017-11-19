#include "http.hpp"

namespace white::http {

class Server : public Http {
  public:
    Server(const int port);

  private:
    void setup_routes();
    void post_workers(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response
    );
    void post_jobs(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response
    );
};

}
