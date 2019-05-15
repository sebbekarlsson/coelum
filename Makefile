exec = pong.out
sources := $(wildcard src/*.c)
sources += $(wildcard GL/src/*.c)
objects = $(sources:.c=.o)
flags = -g -IGL/include -lglfw -ldl -lcglm -lm -lopenal -lpthread


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)


%.o: %.c ../include/glad/%.h
	gcc -c $(flags) $< -o $@ -fPIC


%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
