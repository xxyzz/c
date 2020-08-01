CC = clang
CFLAGS = -Weverything
CHAPTER := 2
EXERCISES := 10
TARGETS := $(foreach i,$(shell seq $(EXERCISES)),$(CHAPTER)-$i.out)

all: $(TARGETS)

%.out: %.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f ./*.out
