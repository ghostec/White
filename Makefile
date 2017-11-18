docker-build:
	@docker build -t white .

docker-run:
	@docker run -it --rm -v "$(PWD)":"/app" -p 9080:9080 -w /app white sh -c "make run"

run:
	@rm -rf build;	mkdir build; cd build; \
		cmake ..; make; \
		./White --port 9080

