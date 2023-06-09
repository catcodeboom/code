ALL:server client 
.PHONY:server client clean
server:server.cc
	g++ $^ -o $@ -std=c++20 -lpthread
client:client.cc
	g++ $^ -o $@ -std=c++20 -lpthread
clean:
	rm server client