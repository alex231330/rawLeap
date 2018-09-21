LEAP_LIBRARY := lib/libLeap.so -Wl,-rpath,/lib

main: main.cpp
	$(CXX) -Wall -g -I../include main.cpp -o main $(LEAP_LIBRARY)

clean:
	rm -rf main 