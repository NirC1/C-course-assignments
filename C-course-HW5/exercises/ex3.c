#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned long int cnt_1;
  unsigned long int cnt_0;
  unsigned long int cnt_bytes;
  unsigned char byte_freq;
  unsigned char byte_mdl;
} stats_t;

static void print_stats(stats_t stats) {
  printf("Total bits set to 1: %lu\n", stats.cnt_1);
  printf("Total bits set to 0: %lu\n", stats.cnt_0);
  printf("Total number of bytes: %lu\n", stats.cnt_bytes);
  printf("Most frequent byte value: 0x%X\n", stats.byte_freq);
  printf("Middle byte value: 0x%X\n", stats.byte_mdl);
}

static stats_t compute_stats(FILE *file) {
  stats_t stats = {0};

  if (file == NULL) {
    return stats;
  }
 
  if (fseek(file, 0L, SEEK_END) != 0) {
    return stats;
  }
  long sz = ftell(file);
  if (sz < 0) {
    return stats;
  }
  
  if (fseek(file, 0L, SEEK_SET) != 0) {
    return stats;
  }
  unsigned long bytes = (unsigned long)sz;
  stats.cnt_bytes = bytes;
  if (bytes == 0) {
    return stats;
  }
 
  unsigned char *buffer = (unsigned char *)malloc(bytes);
  if (!buffer) {
    return stats;
  }
  size_t read_bytes = fread(buffer, 1, bytes, file);
  if (read_bytes != bytes) {
    free(buffer);
    return stats;
  }
 
  unsigned long freq[256] = {0};

  for (unsigned long i = 0; i < bytes; i++) {
    unsigned char c = buffer[i];
    unsigned int ones = __builtin_popcount((unsigned int)c);
    stats.cnt_1 += ones;
    stats.cnt_0 += (8u - ones);
    freq[c]++;
  }

  unsigned long max_freq = 0;
  unsigned int max_byte = 0;
  for (unsigned int i = 0; i < 256; i++) {
    if (freq[i] > max_freq || (freq[i] == max_freq && i < max_byte)) {
      max_freq = freq[i];
      max_byte = i;
    }
  }
  stats.byte_freq = (unsigned char)max_byte;

  unsigned long mid_index = bytes / 2;
  if (mid_index < bytes) {
    stats.byte_mdl = buffer[mid_index];
  }
  free(buffer);
  return stats;
}

int main(int argc, char *argv[]) {
  stats_t stats;

  if (argc != 2) {
    printf("Usage: %s <binary_file>\n", argv[0]);
    return 0;
  }

  FILE *file = fopen(argv[1], "rb");
  if (!file) {

    printf("Usage: %s <binary_file>\n", argv[0]);
    return 0;
  }
  
  stats = compute_stats(file);

  fclose(file);

  print_stats(stats);

  return 0;
}
