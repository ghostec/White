# Requires: git, ninja, cmake

deps: common-deps; make -j2 clone-deps; make websocketpp

common-deps:
	@rm -rf thirdparty
	@mkdir thirdparty

clone-deps: clone-websocketpp clone-asio
clone-websocketpp:
	@cd thirdparty; git clone https://github.com/zaphoyd/websocketpp
clone-asio:
	@cd thirdparty; git clone https://github.com/chriskohlhoff/asio.git

websocketpp:
	@cd thirdparty/websocketpp; mkdir build; cd build; \
		cmake -DCMAKE_INSTALL_PREFIX=./ ..; make install
