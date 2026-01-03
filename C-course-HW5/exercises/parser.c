#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define FIELDS_LEN(flags) (int)(sizeof(flags) / sizeof(flags_t))

#define FIELDS_MIN 0
#define VERSION_MAX 7
#define LENGTH_MAX 15
#define PACKET_TYPE_MAX 31
#define NODE_MAX 127
#define PRIORITY_MAX 2
#define ENCRYPTED 1

typedef struct {
  const char *short_name;
  const char *long_name;
  const char *description;
  unsigned int min;
  unsigned int max;
} flags_t;

static const flags_t flags[] = {
    {HELP_FLAG, "Help", "Print this description", FIELDS_MIN, FIELDS_MIN},
    {"-v", "Version", "Protocol version", FIELDS_MIN, VERSION_MAX},
    {"-l", "Packet Length", "Packet length in 4 bytes units", FIELDS_MIN,
     LENGTH_MAX},
    {"-t", "Packet Type", "Packet type", FIELDS_MIN, PACKET_TYPE_MAX},
    {"-s", "Source Node", "Sender address", FIELDS_MIN, NODE_MAX},
    {"-d", "Destination Node", "Receiver address", FIELDS_MIN, NODE_MAX},
    {"-p", "Priority", "Priority class (0 = low … 2 = high)", FIELDS_MIN,
     PRIORITY_MAX},
    {"-e", "Encrypted", "1 if the packet is encrypted", FIELDS_MIN, ENCRYPTED}};

void print_help() {
  printf("Usage:\n");
  for (int i = 0; i < FIELDS_LEN(flags); i++) {
    printf("%*s%*s [%u-%u]:\t%s,\n", 4, flags[i].short_name, 17,
           flags[i].long_name, flags[i].min, flags[i].max,
           flags[i].description);
  }
  printf("Please try again.\n");
}

err_t parse_args(int argc, const char *argv[], header_t *p_hdr) {
  if (argv == NULL || p_hdr == NULL) {
    return ERR_PARAMS;
  }

  int expected_args = 1 + ((int)FIELDS_LEN(flags) - 1) * 2;
  if (argc != expected_args) {

    printf("Error: number of given arguements %d is different than expected\n",
           argc);
    return ERR_NUM_ARGS;
  }

  for (int i = 1; i < argc; i += 2) {
    const char *flag = argv[i];
    int fidx = -1;
    for (int j = 1; j < (int)FIELDS_LEN(flags); j++) {
      if (strcmp(flag, flags[j].short_name) == 0) {
        fidx = j;
        break;
      }
    }
    if (fidx < 0) {
      printf("Error: Unknown flag: \"%s\"\n", flag);
      return ERR_UNKNOWN_FLAG;
    }

    if (i + 1 >= argc || argv[i + 1][0] == '-') {
      printf("Error: Missing argument for flag \"%s\"\n", flag);
      return ERR_MISSING_ARG;
    }
    char *endptr = NULL;
    long value = strtol(argv[i + 1], &endptr, 10);
    if (endptr == argv[i + 1] || *endptr != '\0') {
      printf("Error: value %s for flag \"%s\" (%s) is out of range [%u-%u]\n",
             argv[i + 1], flags[fidx].short_name, flags[fidx].long_name,
             flags[fidx].min, flags[fidx].max);
      return ERR_INVALID_VALUE;
    }

    if (value < (long)flags[fidx].min || value > (long)flags[fidx].max) {
      printf("Error: value %ld for flag \"%s\" (%s) is out of range [%u-%u]\n",
             value, flags[fidx].short_name, flags[fidx].long_name,
             flags[fidx].min, flags[fidx].max);
      return ERR_INVALID_VALUE;
    }

    unsigned char uc_val = (unsigned char)value;
    switch (fidx) {
    case 1: 
      p_hdr->version = uc_val;
      break;
    case 2: 
      p_hdr->length = uc_val;
      break;
    case 3: 
      p_hdr->type = uc_val;
      break;
    case 4: 
      p_hdr->src_node = uc_val;
      break;
    case 5: 
      p_hdr->dst_node = uc_val;
      break;
    case 6: 
      p_hdr->priority = uc_val;
      break;
    case 7: 
      p_hdr->encrypted = (value != 0);
      break;
    default:
      break;
    }
  }
  return OK;
}
