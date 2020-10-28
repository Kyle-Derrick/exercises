CFLAGS=-Iinclude
LIBS=-Llib -ltools
src=$(wildcard src/*.c)
obj=$(patsubst src/%.c, obj/%.o, $(src))
app=bin/app

$(app):$(obj)
	$(CC) $^ $(LIBS) -o $@
obj/%.o:src/%.c
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	rm $(obj) $(app) -f