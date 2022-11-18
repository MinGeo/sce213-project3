/**********************************************************************
 * Copyright (c) 2020
 *  Jinwoo Jeong <jjw8967@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdint.h>

#include "malloc.h"
#include "types.h"
#include "list_head.h"

#define ALIGNMENT 32
#define HDRSIZE sizeof(header_t)

static LIST_HEAD(free_list); // Don't modify this line
static algo_t g_algo;        // Don't modify this line
static void *bp;             // Don't modify thie line

/***********************************************************************
 * extend_heap()
 *
 * DESCRIPTION
 *   allocate size of bytes of memory and returns a pointer to the
 *   allocated memory.
 *
 * RETURN VALUE
 *   Return a pointer to the allocated memory.
 */
void *my_malloc(size_t size)
{
  /* Implement this function */
  header_t *header;
  header_t *temp;
  //header_t *temp2;
  size_t sizediff = 20000;
  size_t bestsize = 0;
  if(g_algo == FIRST_FIT)
  {
    if((size % ALIGNMENT) == 0)
    { 
      
      list_for_each_entry(header, &free_list, list)
      {
        if(header->free == 1)
        {
          
          if(header->size > size){
            
            temp = header + size / 32 + 1;
            //fprintf(stdout, "error?\n");
            temp->size = header->size-size-32;
            
            header->size = header->size-temp->size-32;
            header->free = 0;
            
            temp->free = 1;
            
            list_add(&temp->list, &header->list);
            
            //bp = (void *)header;
            return header + HDRSIZE;
          }
          else if(header->size == size)
          {
            header->free = 0;
            //.bp = (void *)header;
            return header + HDRSIZE;
          }
        }
      }
      header = list_last_entry(&free_list, header_t, list);
      //temp = list_prev_entry(header, list);
      if(header->free == 1)
      {
        header->size = size + header->size + 32;
        temp = header + size/32 + 1;
        temp->size = header->size-size-32;
        header->size = header->size-temp->size-32;
        header->free = 0;
        temp->free = 1;
        list_add(&temp->list, &header->list);
        temp = sbrk(size + HDRSIZE);
        return header + HDRSIZE;
      }
      else {
        header = sbrk(size+HDRSIZE);
        header->size = size;
        header->free = 0;
        INIT_LIST_HEAD(&header->list);
        list_add_tail(&header->list, &free_list);
          //bp = (void *)header;
        return header + HDRSIZE;
      }
    }
    else {
      size = size + (ALIGNMENT - (size % ALIGNMENT));
      list_for_each_entry(header, &free_list, list)
      {
        if(header->free == 1)
        {
          if(header->size > size){
            temp = header + size / 32 + 1;
            temp->size = header->size-size-32;
            temp->free = 1;
            header->size = header->size-temp->size-32;
            header->free = 0;
            list_add(&temp->list, &header->list);
            return header + HDRSIZE;
          }
          else if(header->size == size)
          {
            header->free = 0;
            return header + HDRSIZE;
          }
        }
      }      
      header = list_last_entry(&free_list, header_t, list);
      if(header->free == 1)
      {
        header->size = size + header->size + 32;
        temp = header + size/32 + 1;
        temp->size = header->size-size-32;
        header->size = header->size-temp->size-32;
        header->free = 0;
        temp->free = 1;
        list_add(&temp->list, &header->list);
        temp = sbrk(size+HDRSIZE);
        return header + HDRSIZE;



      }
      else {
        header = sbrk(size+HDRSIZE);
        header->size = size;
        header->free = 0;
        INIT_LIST_HEAD(&header->list);
        list_add_tail(&header->list, &free_list);
        return header + HDRSIZE;
      }
      
      
    }
  }
  else if(g_algo == BEST_FIT)
  {
    if((size % ALIGNMENT) == 0)
    {
      list_for_each_entry(header, &free_list, list)
      {
        if(header->free == 1)
        {
          if(header->size == size)
          {
            header->free = 0;
            return header + HDRSIZE;
          }
          else if(header->size > size)
          {
            if(sizediff > (header->size-size))
            {
              sizediff = header->size-size;
              bestsize = header->size;
            }
          }
        }
      }
      list_for_each_entry(header, &free_list, list)
      {
        if(header->size == bestsize && header->free == 1)
        {
            temp = header + size / 32 + 1;
            temp->size = header->size-size-32;
            header->size = header->size-temp->size-32;
            temp->free = 1;
            header->free = 0;
            list_add(&temp->list, &header->list);
            return header + HDRSIZE;
        }
      }      
      header = list_last_entry(&free_list, header_t, list);
      //temp = list_prev_entry(header, list);
      if(header->free == 1)
      {
        header->size = size + header->size + 32;
        temp = header + size/32 + 1;
        temp->size = header->size-size-32;
        header->size = header->size-temp->size-32;
        header->free = 0;
        temp->free = 1;
        list_add(&temp->list, &header->list);
        temp = sbrk(size + HDRSIZE);
        return header + HDRSIZE;
      }
      else {
        header = sbrk(size+HDRSIZE);
        header->size = size;
        header->free = 0;
        INIT_LIST_HEAD(&header->list);
        list_add_tail(&header->list, &free_list);
          //bp = (void *)header;
        return header + HDRSIZE;
      }
    }
    else {
      size = size + (ALIGNMENT - (size % ALIGNMENT));
      list_for_each_entry(header, &free_list, list)
      {
        if(header->free == 1)
        {
          if(header->size == size)
          {
            header->free = 0;
            return header + HDRSIZE;
          }
          if(header->size > size)
          {
            if(sizediff > (header->size-size))
            {
              sizediff = header->size-size;
              bestsize = header->size;
            }
          }
        }
      }
      list_for_each_entry(header, &free_list, list)
      {
        if(header->size == bestsize && header->free == 1)
        {
            temp = header + size / 32 + 1;
            temp->size = header->size-size-32;
            header->size = header->size-temp->size-32;
            temp->free = 1;
            header->free = 0;
            list_add(&temp->list, &header->list);
            //bp = (void *)header;
            return header + HDRSIZE;
        }
      }      
      header = list_last_entry(&free_list, header_t, list);
      //temp = list_prev_entry(header, list);
      if(header->free == 1)
      {
        header->size = size + header->size + 32;
        temp = header + size/32 + 1;
        temp->size = header->size-size-32;
        header->size = header->size-temp->size-32;
        header->free = 0;
        temp->free = 1;
        list_add(&temp->list, &header->list);
        temp = sbrk(size + HDRSIZE);
        return header + HDRSIZE;
      }
      else {
        header = sbrk(size+HDRSIZE);
        header->size = size;
        header->free = 0;
        INIT_LIST_HEAD(&header->list);
        list_add_tail(&header->list, &free_list);
        return header + HDRSIZE;
      }
    }
  }
  return NULL;
}

/***********************************************************************
 * my_realloc()
 *
 * DESCRIPTION
 *   tries to change the size of the allocation pointed to by ptr to
 *   size, and returns ptr. If there is not enough memory block,
 *   my_realloc() creates a new allocation, copies as much of the old
 *   data pointed to by ptr as will fit to the new allocation, frees
 *   the old allocation.
 *
 * RETURN VALUE
 *   Return a pointer to the reallocated memory
 */
void *my_realloc(void *ptr, size_t size)
{
  /* Implement this function */
  header_t *header = (header_t*)ptr - HDRSIZE;
  header_t *temp;
  if(header->size < size)
  {
    temp = my_malloc(size);
    my_free(ptr);
  }
  else {
    my_free(ptr);
    temp = my_malloc(size);
  }
  return temp;

  
  
 
}

/***********************************************************************
 * my_realloc()
 *
 * DESCRIPTION
 *   deallocates the memory allocation pointed to by ptr.
 */
void my_free(void *ptr)
{
  /* Implement this function */
  header_t *header;
  header_t *prev;
  header_t *next;
  header = (header_t*)ptr - HDRSIZE;
  header->free = 1;
  prev = list_prev_entry(header, list);
  next = list_next_entry(header,list);
  if(prev->free == 1)
  {
    if(next->free == 1)
    {
      prev->size = header->size + prev->size + next->size + 64;
      list_del(&header->list);
      list_del(&next->list);
      return;
    }
    else{
      prev->size = header->size + prev->size + 32;
      list_del(&header->list);
      return;
    }
  }
  else if(next->free == 1)
  {
    header->size = header->size + next->size +32;
    list_del(&next->list);
    return;
  }
  return;
}

/*====================================================================*/
/*          ****** DO NOT MODIFY ANYTHING BELOW THIS LINE ******      */
/*          ****** BUT YOU MAY CALL SOME IF YOU WANT TO.. ******      */
/*          ****** EXCEPT TO mem_init() AND mem_deinit(). ******      */
void mem_init(const algo_t algo)
{
  g_algo = algo;
  bp = sbrk(0);
}

void mem_deinit()
{
  header_t *header;
  size_t size = 0;
  list_for_each_entry(header, &free_list, list) {
    size += HDRSIZE + header->size;
  }
  sbrk(-size);

  if (bp != sbrk(0)) {
    fprintf(stderr, "[Error] There is memory leak\n");
  }
}

void print_memory_layout()
{
  header_t *header;
  int cnt = 0;

  printf("===========================\n");
  list_for_each_entry(header, &free_list, list) {
    cnt++;
    printf("%c %ld\n", (header->free) ? 'F' : 'M', header->size);
  }

  printf("Number of block: %d\n", cnt);
  printf("===========================\n");
  return;
}
