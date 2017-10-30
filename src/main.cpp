#include <iostream>
#include "server/server.hpp"

int main() {
  white::server::Server server;
  server.run(9002);
  return 0;
}
