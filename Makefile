# exec = pong.out
sources := $(wildcard src/*.c)
sources += $(wildcard GL/src/*.c)
objects = $(sources:.c=.o)
flags = -g -IGL/include -lglfw -ldl -lcglm -lm -lopenal -lpthread


# $(exec): $(objects)
#	gcc $(objects) $(flags) -o $(exec)

libcoelum.a: $(objects)
	ar rcs $@ $^

%.o: %.c ../include/glad/%.h
	gcc -c $(flags) $< -o $@ -fPIC


%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@


install:
	make
	cp ./libcoelum.a /usr/local/lib/.
	-rm -rf /usr/local/include/coelum
	mkdir /usr/local/include/coelum
	cp -r ./src/include/* /usr/local/include/coelum
	-rm -rf /usr/local/share/coelum
	mkdir -p /usr/local/share/coelum/res
	cp -r ./res/* /usr/local/share/coelum/res

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
