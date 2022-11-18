/**********************************************************************
 * Copyright (c) 2022
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
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <string.h>

#include "types.h"
#include "list_head.h"
#include "parser.h"
#include "malloc.h"

#define MAX_TABLE_SIZE 4096
#define usage() fprintf(stderr, "Usage: %s {first, best}\n", argv[0]);

static int table_idx = 0;
static void *memory_table[MAX_TABLE_SIZE] = { '\0' };

int realloc_memory(int se_id, size_t n_bytes)
{
  char *ptr;
  if (se_id > table_idx) {
    fprintf(stderr, "[Error] Out of memory table index\n");
    return -1;
  }

  ptr = my_realloc(memory_table[se_id], n_bytes);

  memory_table[se_id] = ptr;
  return 0;
}

static int add_memory(const int n_bytes)
{
  char *ptr = (char *)my_malloc(n_bytes);

  if (table_idx > MAX_TABLE_SIZE) {
    fprintf(stderr, "[Error] The memory_table has not enough space to add memory\n");
    return -1;
  }

  memory_table[table_idx++] = ptr;
  return 0;
}

static int remove_memory(int se_id)
{
  if (table_idx < se_id) {
    fprintf(stderr, "[Error] Out of memory_table index\n");
    return -1;
  }

  my_free(memory_table[se_id]);
  return 0;
}

static int run_request(int nr_tokens, char *tokens[])
{
  if (strcmp(tokens[0], "exit") == 0) {
    return 0;
  }
  else if (strcmp(tokens[0], "a") == 0) {
    if (nr_tokens != 2)
      goto err_request;

    size_t n_bytes = strtoul(tokens[1], NULL, 10);

    if (errno == EINVAL)
      goto err_request;

    add_memory(n_bytes);
    goto success;
  }
  else if (strcmp(tokens[0], "r") == 0) {
    if (nr_tokens != 3)
      goto err_request;

    int se_id = (int)strtoul(tokens[1], NULL, 10);
    size_t n_bytes = strtoul(tokens[2], NULL, 10);

    if (errno == EINVAL)
      goto err_request;

    realloc_memory(se_id, n_bytes);
    goto success;
  }
  else if (strcmp(tokens[0], "f") == 0) {
    if (nr_tokens != 2)
      goto err_request;

    int se_id = (int)strtoul(tokens[1], NULL, 10);

    if (errno == EINVAL)
      goto err_request;

    remove_memory(se_id);
    goto success;
  }

err_request:
  fprintf(stderr, "Unable to execute %s\n", tokens[0]);
  return -EINVAL;

success:
  print_memory_layout();
  return 1;
}

static int __process_request(char * request)
{
  char *tokens[MAX_N_TOKENS] = { NULL };
  int nr_tokens = 0;

  if (!parse_request(request, &nr_tokens, tokens)) {
    fprintf(stderr, "The input should be one more tokens\n");
    return 1;
  }

  return run_request(nr_tokens, tokens);
}

int main(int argc, char * const argv[])
{
  char request[MAX_REQUEST_LEN] = { '\0' };
  int ret = 0;
  bool initialized = false;
  algo_t algo;

  if (argc != 2) {
    usage();
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "first") == 0) {
    algo = FIRST_FIT;
  }
  else if (strcmp(argv[1], "best") == 0) {
    algo = BEST_FIT;
  }
  else {
    usage();
    return EXIT_FAILURE;
  }

  while (1) {
    if (!fgets(request, sizeof(request), stdin)) break;
    printf("Request: %s", request);

    if (!initialized) {
      mem_init(algo);
      initialized = true;
    }
    ret = __process_request(request);
    if (!ret) break;
  }

  mem_deinit();

  return EXIT_SUCCESS;
}
