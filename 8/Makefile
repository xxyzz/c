CC = clang
CFLAGS = -Wall -Wextra -D $(shell uname -s)
CHAPTER := 8
EXERCISES := 8
TARGETS := $(foreach i,$(shell seq $(EXERCISES)),$(CHAPTER)-$i.out)
TARGETS += 8-1-clib.out 8-2-fields.out

all: $(TARGETS)

8-2.out: 8-2.c 8-2-syscalls.h

8-2-fields.out: 8-2-fields.c 8-2-syscalls-fields.h

8-3.out: 8-3.c 8-3-syscalls.h

8-4.out: 8-4.c 8-3-syscalls.h

8-5.out: 8-5.c dirent.c dirent.h fsize.c fsize.h
	$(CC) 8-5.c dirent.c fsize.c -o $@ $(CFLAGS)

8-6.out: 8-6.c malloc.c malloc.h
	$(CC) 8-6.c malloc.c -o $@ $(CFLAGS)

8-7.out: 8-7.c malloc.c malloc.h
	$(CC) 8-7.c malloc.c -o $@ $(CFLAGS)

8-8.out: 8-8.c malloc.c malloc.h
	$(CC) 8-8.c malloc.c -o $@ $(CFLAGS)

%.out: %.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -rf ./*.out ./*.dSYM
