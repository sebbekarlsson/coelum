sources = $(wildcard src/*.c)
sources += $(wildcard GL/src/*.c)
objects = $(sources:.c=.o)
flags = -g -IGL/include -lglfw -ldl -lcglm -lm -lspr -ljson -lopenal -lpthread -laudio -std=c99


libcoelum.a: $(objects)
	ar rcs $@ $^

%.o: %.c ../include/glad/%.h
	gcc -c $(flags) $< -o $@ -fPIC

%.o: %.c ../include/%.h
	gcc -c $(flags) $< -o $@ -fPIC

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./coelum.pc /usr/share/pkgconfig/.
	cp ./libcoelum.a /usr/local/lib/.
	mkdir -p /usr/local/include/coelum
	cp -r ./src/include/* /usr/local/include/coelum	
	mkdir -p /usr/local/share/coelum/res
	cp -r ./res/* /usr/local/share/coelum/res

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.c src/include/*.h  -- -IGL/include
