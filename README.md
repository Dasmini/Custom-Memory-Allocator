## What's this project

A from-scratch reimplementation of malloc() / free() built on top of a fixed-size static memory pool. No OS heap calls, no sbrk/mmap. Every byte of "heap" is a static array managed entirely by hand. Metadata headers, a free list, block splitting, coalescing, and alignment, all implemented from first principles.

## Why this project

I'm transitioning from IT operations into Embedded Systems / Firmware Engineering. Most embedded targets have no OS-backed heap. Firmware allocators manage a fixed RAM region exactly like this project does. I built this to genuinely understand what malloc() is doing underneath, rather than just knowing how to call it: how metadata is tracked, how a free list is threaded through memory using pointers, why alignment matters, and what fragmentation actually looks like in practice.

## Features

- A malloc() / free() style allocation over a static byte pool
- First-fit allocation with a singly-linked free list threaded through the pool itself (no extra memory used for bookkeeping)
- Block splitting : large free blocks are cut down to size, with the remainder reinserted as a new free block
- Coalescing : adjacent free blocks are automatically merged, reducing fragmentation
- Alignment : all returned pointers are aligned to an 8-byte boundary.
- Error handling : zero-size requests, allocation failure, double-free protection, and safe NULL frees
- dump_heap() : prints every block in address order (address, size, used/free)
- heap_stats() : pool size, total used/free, block count, largest free block
- A file-driven test harness(test_allocator.c) that reads simple text commands and drives the allocator end to end
- Full Doxygen-style documentation on every public function

## Project Structure
```
├── allocator.h        # Function prototypes + Block struct
├── allocator.c         # heap_init, my_malloc, my_free, coalesce, dump_heap, heap_stats
├── main.c                # Entry point
├── test_allocator.c    # Command-driven test harness
├── test.txt             # Example command file
├── Makefile
└── README.md
```
## Building and running

```
git clone https://github.com/Dasmini/Custom-Memory-Allocator
make
./allocator < test.txt
```
*make clean* removes all build artifacts (.o files and the allocator executable) if you want to rebuild from scratch.
## Usage Example

### test.txt
```
init
alloc a 100
alloc b 200
alloc c 50
free b
alloc d 150
dump
stats
free a
free c
free d
dump
stats
```
### Running ./allocator < test.txt produces

```
my_malloc(100) called
my_malloc(200) called
my_malloc(50) called
b freed
my_malloc(150) called
=============HEAP DUMP=============

[1] 0x5ff736b2f060 Size = 104    USED
[2] 0x5ff736b2f0d8 Size = 152    USED
[3] 0x5ff736b2f180 Size = 32     FREE
[4] 0x5ff736b2f1b0 Size = 56     USED
[5] 0x5ff736b2f1f8 Size = 600    FREE

===================================

Pool size             : 1024
Total used            : 312
Total free            : 632
Block count           : 5
Largest free block    : 600
a freed
c freed
d freed
=============HEAP DUMP=============

[1] 0x5ff736b2f060 Size = 1008   FREE

===================================

Pool size             : 1024
Total used            : 0
Total free            : 1008
Block count           : 1
Largest free block    : 1008
```
## What I learned

Building this forced me past "I know what malloc does" into genuinely reasoning about memory.

- Why every allocator needs hidden metadata attached to each block, and how free(ptr) finds that metadata from nothing but a bare pointer (stepping backward by sizeof(header))
- How a free list can be threaded through memory itself, using pointers inside the free blocks, with zero extra storage
- What fragmentation actually looks like: having enough total free memory without having enough contiguous free memory
- Why "adjacent in the free list" and "adjacent in physical memory" are two completely different relationships. And the bugs that come from confusing them (this took several iterations to get right during coalescing).

## Deliberately out of scope

Thread safety, mmap/sbrk, multiple arenas, garbage collection, calloc/realloc, and production-grade corruption detection were left out on purpose. This project targets understanding the core allocator mechanics, not building a production-grade library.

## Tools used

- gcc -Wall -Wextra for compile-time warnings.
- manual address/state tracing via dump_heap()/heap_stats() throughout development.
- Printing real addresses and sizes at each step and verifying them by hand against expected behavior, especially while debugging the free-list and coalescing logic.

## Author

Dasmini D ❤️

### Links
[Github](https://github.com/Dasmini) | [Linkedin](https://www.linkedin.com/in/dasmini-d-265b3920b/)