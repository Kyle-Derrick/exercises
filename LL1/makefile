CPPFLAGS=-Iinclude
src=$(wildcard src/*.c)
obj=$(patsubst src/%.c, obj/%.o, $(src))
app=bin/app

$(app):$(obj)
	$(CC) $^ -o $@
obj/%.o:src/%.c
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm $(obj) $(app) -f