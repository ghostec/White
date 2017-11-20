docker-build:
	@docker build -t white .

server:
	@target=server port=9080 make which
worker:
	@target=worker port=9081 server=9080 make which
which:
	@docker run -it --rm -v "${PWD}":"/app" -p ${port}:${port} \
		-w /app white	sh -c \
		"port=${port} server=${server} target=$(target) make run"

run-server:
	@cd build/server; ./White --port ${port}
run-worker:
	@cd build/worker; ./White --port ${port} --server ${server}
run:
	@mkdir -p build/${target}; cd build/${target}; \
		cmake -Dtarget:STRING=${target} ../..; make; \
		cd ../..;
		port=${port} server=${server} make run-${target};
