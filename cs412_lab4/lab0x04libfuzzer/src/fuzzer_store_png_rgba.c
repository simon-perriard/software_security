#include "pngparser.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  if (Size < 1000) {
    return 0;
  }
  
  struct image img;
  img.size_x = (Data[18] << 8) + Data[19];
  img.size_y = (Data[22] << 8) + Data[23];
  img.px = &Data[41];
  
  store_png("testinput.png", &img, NULL, 0);

  // Always return 0
  return 0;
}
