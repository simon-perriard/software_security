#include "pngparser.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct image *test_img;
  
  int id = getpid();
  
  char filename[10];
  snprintf(filename, 10, "%d", id); 

  FILE *input = fopen(filename,"w");
  fwrite(Data, Size, 1, input);
  fclose(input);

  load_png(filename, &test_img);
  
  if (test_img && test_img->px) {
    free(test_img->px);
  }

  // Always return 0
  return 0;
}
