#include "malloc.h"
#include <limits.h>
#include <stdio.h>  // NULL
#include <string.h> // memset
#include <unistd.h> // sbrk

// xv6 uses this code:
// https://github.com/mit-pdos/xv6-public/blob/master/umalloc.c

static Header base;          /* empty list to get started */
static Header *freep = NULL; /* start of free list */

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu) {
  char *cp;
  Header *up;

  if (nu < NALLOC)
    nu = NALLOC;
  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1) /* no space at all */
    return NULL;
  up = (Header *)cp;
  up->s.size = nu;
  my_free((void *)(up + 1));
  return freep;
}

/* my_malloc: general-purpose storage allocator */
void *my_malloc(unsigned nbytes) {
  Header *p, *prevp;
  unsigned nunits;

  if (nbytes <= 0 || nbytes > UINT_MAX - sizeof(Header) + 1)
    return NULL;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL) { /* no free list yet */
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) { /* big enough */
      if (p->s.size == nunits) /* exactly */
        prevp->s.ptr = p->s.ptr;
      else { /* allocate tail end */
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep) /* wrapped around free list */
      if ((p = morecore(nunits)) == NULL)
        return NULL; /* none left */
  }
}

/* my_free: put block ap in free list
 *   p       bp       p->s.ptr
 * -------------------------------->
 */
void my_free(void *ap) {
  Header *bp, *p;

  if (ap == NULL) {
    fprintf(stderr, "NULL pointer\n");
    return;
  }
  bp = (Header *)ap - 1; /* point to block header */
  if (bp->s.size <= 0 || bp->s.size > UINT_MAX / sizeof(Header) + 1) {
    fprintf(stderr, "weird size\n");
    return;
  }

  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break; /* freed block at start or end of arena */

  if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if (p + p->s.size == bp) { /* join to lower nbr */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}

/* returns a pointer to n objects of size size,
 * with the storage initialized to zero */
void *my_calloc(unsigned n, unsigned size) {
  void *p;
  p = my_malloc(n * size);
  if (p == NULL)
    return NULL;
  return memset(p, 0, n * size);
}
