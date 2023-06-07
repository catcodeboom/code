ALL:server client
.PHONY: server client clean
server:server.cc message.pb.cc
	g++ $^ -o $@ -std=c++20 -lpthread -lprotobuf
client:client.cc message.pb.cc
	g++ $^ -o $@ -std=c++20 -lpthread -lprotobuf
clean:
	rm server client