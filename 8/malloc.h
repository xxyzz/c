#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__
typedef long Align; /* for alignment to long boundary */

union header { /* block header: */
  struct {
    union header *ptr; /* next block if on free list */
    unsigned size;     /* size of this block */
  } s;
  Align x; /* force alignment of blocks */
};

typedef union header Header;

#define NALLOC 1024 /* minimum units to request */

void *my_malloc(unsigned);
void *my_calloc(unsigned, unsigned);
void my_free(void *);
#endif
