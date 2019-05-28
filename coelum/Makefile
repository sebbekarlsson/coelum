sources = $(wildcard src/*.c)
sources += $(wildcard ../GL/src/*.c)
objects = $(sources:.c=.o)
flags = -g -I../GL/include -lglfw -ldl -lcglm -lm -lopenal -lpthread


libcoelum.a: $(objects)
	ar rcs $@ $^

%.o: %.c ../../include/glad/%.h
	gcc -c $(flags) $< -o $@ -fPIC

%.o: %.c ../include/%.h
	gcc -c $(flags) $< -o $@ -fPIC

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
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
