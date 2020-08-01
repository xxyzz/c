CC = clang
CFLAGS = -Weverything
CHAPTER := 1
EXERCISES := 24
TARGETS := $(foreach i,$(shell seq $(EXERCISES)),$(CHAPTER)-$i.out)

all: $(TARGETS)

%.out: %.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f ./*.out
