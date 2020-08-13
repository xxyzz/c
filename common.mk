CC = clang
CFLAGS = -Weverything
TARGETS = $(foreach i,$(shell seq $(EXERCISES)),$(CHAPTER)-$i.out)

all: $(TARGETS)

%.out: %.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -rf ./*.out ./*.dSYM
