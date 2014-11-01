test_:
	g++ -c test.cpp
	g++ -o test test.o
clean_old:
	rm -f -r test.o
	rm -f -r test
	rm -f -r test1_l.o
	rm -f -r test1_w.o
	rm -f -r test1
clean:
	rm -f -r test1_l.o
	rm -f -r test1_w.o
	rm -f -r msp_l
	rm -f -r msp_w
test1:
	g++ -c test1.cpp
	g++ -o test1 test1.o -lncurses
memespew_linux:
	g++ -g -c test1.cpp -o test1_l.o
	g++ -g -o msp_l test1_l.o -lncurses
memespew_windows:
	sudo /usr/bin/i586-mingw32msvc-g++ -g -c test1.cpp -o test1_w.o
	sudo /usr/bin/i586-mingw32msvc-g++ -g -o msp_w.exe test1_w.o -lpdcurses
memespew_all:
	make clean
	make memespew_windows
	make memespew_linux
