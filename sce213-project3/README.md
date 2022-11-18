## Malloc Dynamic Memory Allocator

### *** Due on 11:59 pm, June 27 (Monday) ***

### Introduction
This project is to implement **Malloc Dynamic Memory Allocator**. Typically, in the C programming language, the dynamic memory allocation is performed using standard library functions: `malloc()`, `realloc()`, and `free()`. Those functions are defined in `stdlib.h` library.
Our ultimate goal is to implement such dynamic memory allocation functions: `my_malloc()`, `my_realloc()`, and `my_free()` which are defined in `malloc.c` file.

* `void *my_malloc(size_t size)`: allocates size of bytes of memory and returns a pointer to the allocated memory.
* `void *my_realloc(void *ptr, size_t size)`: tries to change the size of the allocation pointed to by ptr to size, and returns ptr. If there is
not enough memory block, `my_realloc()` creates a new allocation, copies as much of the old data pointed to by ptr as will fit to the new allocation,
frees the old allocation, and returns a pointer to the allocated memory.
* `void my_free(void *ptr)`: deallocates the memory allocation pointed to by ptr.

### Allocation Algorithm
The dynamic memory allocator employs as below memory allocation algorithms to avoid external fragmentation.
* First-Fit: it starts scanning from the beginning of the heap. Traverse each block until we find a free block and the block is large enough to handle the request.

* Best-Fit: it deals with allocating the smallest free block that meets the requirement of the requesting memory. This algorithm first traverses all free blocks and considers the smallest block that is adequate. It then tries to find a free block close to the actual memory size needed.

In this project, you need to implement these memory allocation algorithms into the dynamic memory allocator.

### Problem Specification
* The `pa3` program helps you test whether you have properly implemented the dynamic memory allocator.
* The `pa3` awaits a memory request line input. Each line represent either an allocate [a], reallocate [r], or free [f] request.
* `pa3` has allocation algorithm { first, best } as an argument.
```bash
Usage: ./pa3 {first, best}
```
* The &#60;id&#62; is an integer that uniquely identifies an free or rellocate request and automatic increamented whenever the allocate [a] is requested.
The pointers to the allocated memory blocks are stored  in `memory_table` which is defined in `pa3.c`.

```
a <bytes>       /* memory_table[<id>] = malloc(<bytes>) */ 
r <id> <bytes>  /* realloc(memory_table[<id>], <bytes>) */ 
f <id>          /* free(memory_table[<id>]) */
```
Once the program faces the 'exit' command from users or EOF from the input file, it is terminated. 

  
### Execution Example
Whenever a memory request is entered, `pa3` program will print the current memory layout and number of blocks as follows.
The blocks in the memory layout are output sequentially, and each block is represented in <allocation state|{M, F}> <bytes> format.
If a block is allocated, &#60;allocation state&#62; is **M**. Otherwise, **F**.

```bash
$ ./pa3 first
a 1024 # User Input
Request: a 1024
===========================
M 1024
Number of block: 1
===========================
a 1024 # User Input
Request: a 1024
===========================
M 1024
M 1024
Number of block: 2
===========================
f 1 # User Input
Request: f 1
===========================
M 1024
F 1024
Number of block: 2
===========================
```
### TODO
Implement the functions in `mallo.c` file. You don't need to modify other files.
* `my_alloc()`
* `my_realloc()`
* `my_free()`
  
The functions behave simliarly to the standard functions, such as `malloc()`, `realloc()`, and `free()`.

### Restriction and Hint
* You should only use `sbrk()` to implement `my_malloc()` and `my_realloc()` instead `malloc()` family functions. You will get 0 pts if you use it.
* All allocation sizes are aligned by **32 bytes**.
* The **Dynamic Memory Allocator** should be able to maintain all memory block metadata to manage the blocks.
  The metadata includes allocation status, size of allocated memory, next and previous block pointers that can be implmented as double-linked list.
  You can reference `header_t` structure that is defined in `malloc.c` file.
  Noramlly, the metadata is stored into head of allocated memmory space.
  To this end, you need to allocate additional space equal to size of metadata to contain the metadata at the time of memory allocation.
* All arguments and all returned ptrs of **TODO functions** must point to a memory space that can contain actual data, not meta data.
  You will get 0 pts if the ptrs point to the metadata.
