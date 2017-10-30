#ifndef __WHITE_SERVER_SERVERHPP__
#define __WHITE_SERVER_SERVERHPP__

#include <iostream>
#include <map>
#include <exception>
#include <asio.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> ws_server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace white::server {
  class Server {
    public:
      Server() {
        m_server.init_asio();

        m_server.set_message_handler(bind(&Server::on_message, this, ::_1, ::_2));
      }

      void on_gui_message(connection_hdl hdl, ws_server::message_ptr msg) {
        std::cout << "gui message received\n";
      }

      void on_worker_message(connection_hdl hdl, ws_server::message_ptr msg) {
        std::cout << "worker message received\n";
      }

      void on_message(connection_hdl hdl, ws_server::message_ptr msg) {
        const auto payload = msg->get_payload();

        if (payload.compare("register_gui") == 0) {
          const auto con_ptr = m_server.get_con_from_hdl(hdl);
          con_ptr->set_message_handler(bind(&Server::on_gui_message, this, ::_1, ::_2));
        } else if (payload.compare("register_worker") == 0) {
          const auto con_ptr = m_server.get_con_from_hdl(hdl);
          con_ptr->set_message_handler(bind(&Server::on_worker_message, this, ::_1, ::_2));
        }
      }

      void run(uint16_t port) {
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
      }

    private:
      ws_server m_server;
  };
}

#endif
