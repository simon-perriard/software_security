#include "pngparser.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  struct image *test_img;
  
  FILE *input = fopen("testinput","w");
  fwrite(Data, Size, 1, input);
  fclose(input);

  load_png("testinput.png", &test_img);
  
  store_png("testinput.png", &test_img, NULL, 0);

  // Always return 0
  return 0;
}
