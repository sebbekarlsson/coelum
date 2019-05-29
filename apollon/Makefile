exec = apollon.out
sources = $(wildcard src/*.c)
sources += $(wildcard ../GL/src/*.c)
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
