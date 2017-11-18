build:
	@docker build -t white .

server:
	@target=server make which
worker:
	@target=worker make which
which:
	@docker run -it --rm -v "$(PWD)":"/app" -p 9080:9080 -w /app white \
		sh -c "target=$(target) make run"

run:
	@rm -rf build;	mkdir build; cd build; \
		cmake -Dtarget:STRING=$(target) ..; make; \
		./White --port 9080
