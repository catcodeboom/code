src=$(wildcard *.cpp)
dst=$(patsubst %.cpp,%.o,$(src))
ALL:a.out
a.out:$(dst)
	g++ $^ -o $@ -lpthread -g
$(dst):%.o:%.cpp
	g++ -c $< -o $@ -std=c++11 -g
.PHONY:clean
clean:
	rm -rf $(dst) a.out