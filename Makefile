LEAP_LIBRARY := lib/libLeap.so -Wl,-rpath,/lib #leap library
INCLUDE = -I../include #prj include dirs

main: main.cpp #Build with opencv config
	g++ main.cpp -o main $(INCLUDE) $(LEAP_LIBRARY) `pkg-config --cflags --libs opencv`

clean:
	rm -rf main 
