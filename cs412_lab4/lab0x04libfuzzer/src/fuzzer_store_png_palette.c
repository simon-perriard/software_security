#include "pngparser.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// LibFuzzer stub

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    struct image *test_img;

    if(Size < 5){
        return 0;
    }

    //cut Data to fill required inputs
    struct pixel * palette = malloc(sizeof(struct pixel));
    palette->red = Data[Size-2];
    palette->blue = Data[Size-3];
    palette->green = Data[Size-4];
    palette->alpha = Data[Size-5];

    uint8_t *Data_image = malloc((Size -5) * sizeof(uint8_t));
    memcpy(Data_image, Data, (Size -5));

    uint8_t size_palette = Data[Size-1];


    store_png("test.png", Data_image, palette, size_palette);

    // Always return 0
    return 0;
} 
