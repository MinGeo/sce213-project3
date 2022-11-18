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

#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "types.h"
#include "list_head.h"

typedef enum
{
	FIRST_FIT,
	BEST_FIT,
} algo_t;

typedef struct
{
  size_t size;
	bool free;
  struct list_head list;
} header_t;

void mem_init(algo_t algo);

void mem_deinit();

void *my_malloc(size_t size);

void *my_realloc(void *ptr, size_t size);

void my_free(void *ptr);

void print_memory_layout();

#endif
