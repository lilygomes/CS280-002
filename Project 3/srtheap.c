/*
 * Lily Gomes
 * CS 280-002
 * Project 2: Recursive Descent Parsing
 * 11 June 2026
 */

/*
 *  after splitting this file into the five source files:
 *	srt.h, main.c, srtbubb.c, srtinsr.c, srtmerg.c
 *  compile using the command:
 *	gcc -std=c99 -DRAND -DPRNT -DTYPE=(float | double) -D(BUBB | HEAP | INSR | MERG) *.c
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "srt.h"

// iterates through heap to make root node the largest value
void buildheap(void *hptr, size_t nelem, int inode, size_t size, int (*compar)(const void *, const void *)) {
  // compare values of child nodes to root node
  size_t imax = inode;
  size_t ileft = 2 * inode + 1;
  size_t iright = 2 * inode + 2;
  // if child node greater, change index of largest item on node
  if (ileft < nelem && compar(hptr + size * inode, hptr + size * ileft))
    imax = ileft;
  if (iright < nelem && compar(hptr + size * inode, hptr + size * iright))
    imax = iright;
  // if root of node is not largest, swap 'em
  if (imax != inode)
    swap(hptr + size * inode, hptr + size * imax, size);
}

void srtheap(void* base, size_t nelem, size_t size, int (*compar)(const void *, const void *)) {
  // create new void* for heap
  void* heap = calloc(nelem, size);
  memcpy(heap, base, size * nelem);
  // work backwards through heap nodes to sort into max-heap
  for (int i = 0; i < nelem; i++)
    buildheap(heap, nelem, i, size, compar);

  // TODO figure out a better way to do this
  memcpy(base, heap, size * nelem);
}

// Returns index of parent node for a given index in the heap
int iparent(size_t inode) {
  return floor((inode - 1) / 2);
}
