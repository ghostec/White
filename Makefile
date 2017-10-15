# Requires: git, ninja, cmake

deps: common-deps; make -j2 clone-deps; make paho-mqtt-c; make paho-mqtt-cpp

common-deps:
	@rm -rf thirdparty
	@mkdir thirdparty

clone-deps: clone-paho-mqtt-c clone-paho-mqtt-cpp
clone-paho-mqtt-c:
	@cd thirdparty; git clone https://github.com/eclipse/paho.mqtt.c
clone-paho-mqtt-cpp:
	@cd thirdparty; git clone https://github.com/eclipse/paho.mqtt.cpp

paho-mqtt-c:
	@cd thirdparty/paho.mqtt.c; mkdir build; cd build; \
		cmake -GNinja -DPAHO_BUILD_STATIC=true \
		-DCMAKE_INSTALL_PREFIX=/tmp/paho -DPAHO_WITH_SSL=TRUE ..; \
		ninja;
	@mkdir -p thirdparty/paho.mqtt.c/build/include
	@mkdir -p thirdparty/paho.mqtt.c/build/lib
	@find thirdparty/paho.mqtt.c/src -iname \*.h -exec cp {} \
		thirdparty/paho.mqtt.c/build/include/ \;
	@find thirdparty/paho.mqtt.c/build/src -iname \*.dylib -exec cp {} \
		thirdparty/paho.mqtt.c/build/lib/ \;

paho-mqtt-cpp:
	@cd thirdparty/paho.mqtt.cpp; mkdir build; cd build; \
		cmake -DPAHO_BUILD_STATIC=true \
		-DPAHO_MQTT_C_PATH=../../paho.mqtt.c/build \
		-DCMAKE_INSTALL_PREFIX=./ ..; make install
