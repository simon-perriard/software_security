#include "pngparser.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  struct image test_img;
  
  if(Size < 400){ // at least 400 bytes
    return 0;
  }
  
  test_img.size_x = 10;
  test_img.size_y = 10;
  test_img.px = Data; // 10*10*4 bytes
  
  store_png("testinput.png", &test_img, NULL, 0);

  // Always return 0
  return 0;
}
