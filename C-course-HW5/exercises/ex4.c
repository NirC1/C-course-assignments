#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"

unsigned int cnt_ones(unsigned int n) {
  unsigned int count = 0;
  while (n) {
    count += n & 1u;
    n >>= 1;
  }
  return count;
}

static unsigned int encode_packet_header(header_t hdr) {

  unsigned int packet = 0;
 
  packet |= ((unsigned int)hdr.version & 0x7u) << 29;
  packet |= ((unsigned int)hdr.length & 0xFu) << 25;
  packet |= ((unsigned int)hdr.type & 0x1Fu) << 20;
  packet |= ((unsigned int)hdr.src_node & 0x7Fu) << 13;
  packet |= ((unsigned int)hdr.dst_node & 0x7Fu) << 6;
  packet |= ((unsigned int)hdr.priority & 0x3u) << 4;
  packet |= ((unsigned int)(hdr.encrypted ? 1u : 0u)) << 3;

  unsigned int top29 = packet >> 3;
  unsigned int ones = cnt_ones(top29);
  unsigned int checksum = ones % 8u;
 
  packet |= (checksum & 0x7u);
  return packet;
}


static void print_header(unsigned int hdr_buf) {
  printf("The Encoded Packet Header is: 0x%08X\n", hdr_buf);
}


int main(int argc, const char *argv[]) {
  header_t hdr = {0};
  unsigned int hdr_buf;
  err_t ret;

  if (argc == 1 || (argc == 2 && strcmp(argv[1], HELP_FLAG) == 0)) {
    print_help();
    return 0;
  }

  ret = parse_args(argc, argv, &hdr);
  if (ret != OK) {
    return ret;
  }
  hdr_buf = encode_packet_header(hdr);
  print_header(hdr_buf);
  return OK;
}
