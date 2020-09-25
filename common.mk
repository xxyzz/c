CC = clang
CFLAGS = -Wall -Wextra -D $(shell uname -s)
COMMON_TARGETS = $(foreach i,$(shell seq $(EXERCISES)),$(CHAPTER)-$i.out)
ifndef TARGETS
	TARGETS = $(COMMON_TARGETS)
else
	TARGETS += $(COMMON_TARGETS)
endif

all: $(TARGETS)

%.out: %.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -rf ./*.out ./*.dSYM
