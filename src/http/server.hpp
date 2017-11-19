#include "http.hpp"

namespace white::http {

class Server : public Http {
  public:
    Server(const int port);

  private:
    void setupRoutes();
    void registerWorker(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response
    );
};

}
