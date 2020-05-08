#include "pngparser.h"
#include <stdio.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  if (Size < 1000) {
    return 0;
  }

  struct image *test_img;
  
  load_png(Data, &test_img);

  // Always return 0
  return 0;
}
