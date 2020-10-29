CFLAGS=-Iinclude
src=$(wildcard src/*.c)
obj=$(patsubst src/%.c, obj/%.o, $(src))
app=lib/libtools.a

$(app):$(obj)
	ar rcs $@ $^
obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(obj) $(app) -f