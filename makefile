O = $(patsubst src/%.cpp,%.o,$(wildcard src/*.cpp))
SO = encoder.so decoder.so
CC = c++
run :clean dir main
	@LD_LIBRARY_PATH=`pwd`/lib ./bin/main.exe

dir:
	echo $(SO)
	mkdir -p obj lib bin 

%.o: src/%.cpp
	$(CC) -c $< -I inc/ -o obj/$@

%.so: *obj/%.o
	$(CC) -shared -fPIC $^ -o lib/lib$@

%.a: *obj/%.o
	ar cvq lib/lib$@ $^

main: $(O) test.a $(SO)
	$(CC) obj/main.o -I ./inc -L ./lib -lencoder -ldecoder -ltest -o bin/main.exe

clean:
	rm -rf obj lib bin
