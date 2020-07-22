CC = clang
CFLAGS = -Weverything
CHAPTER := 1
EXERCISES := 10
TARGETS := $(foreach i, $(shell seq 1 $(EXERCISES)),$(CHAPTER)-$i.out)

all: $(TARGETS)

%.out: %.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f ./*.out
