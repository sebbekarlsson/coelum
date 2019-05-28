exec = test.out
sources = $(wildcard src/*.c)
sources += $(wildcard ../src/*.c)
objects = $(sources:.c=.o)
flags = -g -lcoelum -I ../../cmocka/include -I../GL/include -lglfw -ldl -lcglm -lm -lopenal -lpthread -lcmocka


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
