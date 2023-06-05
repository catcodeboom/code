src=$(wildcard *.cc)
dynamic_o=$(patsubst %.cc,%_d.o,$(src))
static_o=$(patsubst %.cc,%_s.o,$(src))
ALL:boost
boost:libboost.so libboost.a
	mkdir -p Boostlib/include
	mkdir -p Boostlib/lib
	mv $^ Boostlib/lib
	rm -rf *.o
	cp *.h Boostlib/include
libboost.so:$(dynamic_o)
	g++ -shared $^ -o $@
libboost.a:$(static_o)
	ar -rc -o $@ $^
$(dynamic_o):%_d.o:%.cc
	g++ -fPIC -c $< -o $@
$(static_o):%_s.o:%.cc
	g++ -c $< -o $@
.PHONY:clean
clean:
	rm -rf Boostlib
