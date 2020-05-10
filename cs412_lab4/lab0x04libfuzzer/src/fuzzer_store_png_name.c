#include "pngparser.h"
#include <stdio.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  if (Size < 1000) { //otherwise bug in fopen
    return 0;
  }

  struct image *test_img;
  load_png("../seeds/rgba.png", &test_img);
  
  store_png(Data, &test_img, NULL, 0);
  
  if (test_img && test_img->px) {
    free(test_img->px);
  }

  // Always return 0
  return 0;
}
