exec = leto.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -lcoelum -lhermes -I../GL/include -lglfw -ldl -lcglm -lm -lopenal -lpthread -laudio


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
