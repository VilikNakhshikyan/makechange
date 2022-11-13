#encoder
run : main
	@LD_LIBRARY_PATH=`pwd`/lib/encoder:`pwd`/lib/decoder:`pwd`/lib/test ./bin/main.exe

obj/encoder:
	mkdir -p obj/encoder/

encoder.o : obj/encoder
	g++ -c src/encoder/encoder.cpp -I inc/ -o obj/encoder/encoder.o

lib/encoder:
	mkdir -p lib/encoder

encoder.so : lib/encoder encoder.o
	g++ -shared -fPIC obj/encoder/encoder.o -o lib/encoder/libencoder.so


#decoder
obj/decoder:
	mkdir -p obj/decoder/

decoder.o : obj/decoder
	g++ -c src/decoder/decoder.cpp -I inc/ -o obj/decoder/decoder.o

lib/decoder:
	mkdir -p lib/decoder

decoder.so : lib/decoder decoder.o
	g++ -shared -fPIC obj/decoder/decoder.o -o lib/decoder/libdecoder.so

#main
bin :
	mkdir bin
main.o:
	g++ -c src/main.cpp -I inc/ -o obj/main.o

main: bin encoder.so decoder.so main.o test.a 
	g++ obj/main.o -I ./inc -L ./lib/decoder -L ./lib/encoder -L ./lib/test -lencoder -ldecoder -ltest -o bin/main.exe

#test
obj/test:
	mkdir -p obj/test/

test.o : obj/test
	g++ -c src/test/test.cpp -I inc/ -o obj/test/test.o

lib/test:
	mkdir -p lib/test

test.a : lib/test test.o
	ar cvq lib/test/libtest.a obj/test/test.o


#end
clean:
	rm -R obj lib bin 
