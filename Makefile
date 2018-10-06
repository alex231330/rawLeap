LEAP_LIBRARY := lib/libLeap.so -Wl,-rpath,/lib #leap library
INCLUDE = -I../include #prj include dirs
main: main.cpp #Build with opencv config
	g++ main.cpp -o main $(INCLUDE) $(LEAP_LIBRARY) `pkg-config --cflags --libs opencv` -l:/home/xelon/Documents/opencv-3.4.3/build/lib/libopencv_ximgproc.so.3.4

clean:
	rm -rf main 
