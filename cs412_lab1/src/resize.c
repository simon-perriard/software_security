#include <string.h>
#include <math.h>
#include "pngparser.h"


int main(int argc, char *argv[])
{
    struct image *img = NULL;
    struct image *new_img = NULL;

    /* Check if the argument count is correct */
    if (argc != 4) {
        goto error_usage;
    }

    /* Rename the arguments for easier reference */
    char *input = argv[1];
    char *output = argv[2];

    double factor = atof(argv[3]);

    /* Resizing and image to 0 isn't allowed */
    if (factor <= 0) {
        goto error_usage;
    }

    if (load_png(input, &img)) {
        return 1;
    }

    unsigned height = img->size_y;
    unsigned width = img->size_x;

    unsigned new_height = (unsigned) (img->size_y * factor);
    unsigned new_width = (unsigned) (img->size_x * factor);

    /* Allocate memory for the resized image */
    new_img = malloc(sizeof(struct image));

    if (!new_img) {
        goto error_memory;
    }

    new_img->size_x = new_width;
    new_img->size_y = new_height;

    new_img->px = malloc(new_width * new_height * sizeof(struct pixel));

    if (!new_img->px) {
        goto error_memory_img;
    }

    {
        struct pixel (*image_data)[width] = (struct pixel (*)[width])img->px;
        struct pixel (*image_data_new)[new_width] = (struct pixel (*)[new_width])new_img->px;

        /* Iterate over all pixels in the new image and fill them with the nearest neighbor in the old one */
        for (unsigned y = 0; y < new_height; y++) {
            for (unsigned x = 0; x < new_width; x++) {

                /* Calculate the location of the pixel in the old image */
                unsigned nearest_x = x / factor;
                unsigned nearest_y = y / factor;

                /* Store the pixel */
                image_data_new[y][x] = image_data[nearest_y][nearest_x];
            }
        }
    }

    store_png(output, new_img, NULL, 0);
    free(img->px);
    free(img);

    free(new_img->px);
    free(new_img);
    return 0;

error_usage:
    printf("Usage: %s input_image output_image resize_factor\n", argv[0]);
    return 1;

error_memory_img:
    free(new_img);
error_memory:
    free(img->px);
    free(img);
    printf("Memory error!");
    return 1;
}