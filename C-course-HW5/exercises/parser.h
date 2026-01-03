#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdbool.h>

#define HELP_FLAG "-h"

typedef enum {
  OK = 0,

  ERR_PARAMS,
  ERR_NUM_ARGS,
  ERR_UNKNOWN_FLAG,
  ERR_MISSING_ARG,
  ERR_INVALID_VALUE,

} err_t;

typedef struct {
  unsigned char version;
  unsigned char length;
  unsigned char type;
  unsigned char src_node;
  unsigned char dst_node;
  unsigned char priority;
  bool encrypted;
} header_t;

err_t parse_args(int argc, const char *argv[], header_t *p_hdr);

void print_help();

#endif 
