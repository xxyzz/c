CC = clang
CFLAGS = -Weverything -D $(shell uname -s)
CHAPTER := 8
EXERCISES := 3
TARGETS := $(foreach i,$(shell seq $(EXERCISES)),$(CHAPTER)-$i.out)
TARGETS += 8-1-clib.out 8-2-fields.out

all: $(TARGETS)

8-2.out: 8-2.c 8-2-syscalls.h

8-2-fields.out: 8-2-fields.c 8-2-syscalls-fields.h

8-3.out: 8-3.c 8-3-syscalls.h

%.out: %.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -rf ./*.out ./*.dSYM
