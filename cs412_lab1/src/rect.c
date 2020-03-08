#include <string.h>
#include "pngparser.h"


int main(int argc, char *argv[])
{
    char input[256];
    char output[256];

    int radius;
    struct image *img;

    /* There isn't any complex error handling in this function, so we use a simple if */
    if (argc != 8) {
        printf("Usage: %s input_image output_image top_left_x top_left_y bottom_right_x bottom_right_y hex_color\n", argv[0]);
        return 1;
    }

    if ((strlen(argv[1]) >= sizeof(input)) ||
        (strlen(argv[2]) >= sizeof(output))) {
        exit(1);
    }

    // Copy the filenames into separate arrays for easier reference
    strcpy(input, argv[1]);
    strcpy(output, argv[2]);

    /* Parse the points. Invalid input will just set the coordinate to 0.
     * The program will still work.
     */

    int top_left_x = atoi(argv[3]);
    int top_left_y = atoi(argv[4]);

    int bottom_right_x = atoi(argv[5]);
    int bottom_right_y = atoi(argv[6]);

    /* Invalid color code will set the color to black.
     * If it worked for Henry Ford, it will work for us.
     */

    long hex_color = strtol(argv[7], NULL, 16);

    if (load_png(input, &img)) {
        return 1;
    }

    unsigned height = img->size_y;
    unsigned width = img->size_x;

    struct pixel (*image_data)[width] = (struct pixel (*)[width])img->px;

    /* We iterate over all pixel in the image and check whether they are in the rectangle
     *
     * The rectangle is defined by the two points:
     * - top-left (TL)
     * - bottom-right (BR)
     * 
     * A pixel is inside the rectangle if it is:
     * - to the right of TL
     * - to the left of BR
     * - below TL
     * - above BR
     */
    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {

            // Check if the pixel is in the rectangle

            if (i >= top_left_y &&
                i <= bottom_right_y &&
                j >= top_left_x &&
                j <= bottom_right_x) {
                
                /* The fancy syntax here is just masking the corresponding bits
                 * If the color is RRGGBB, performing AND with 0xff0000 will isolate
                 * the bytes representing red. We then shift them to the right to bring them
                 * into the correct range
                 */
                image_data[i][j].red = (hex_color & 0xff0000) >> 16;
                image_data[i][j].green = (hex_color & 0x00ff00) >> 8;
                image_data[i][j].blue = (hex_color & 0x0000ff);
                image_data[i][j].alpha = 0xff;
            }
        }
    }

    store_png(output, img, NULL, 0);
    free(img->px);
    free(img);
    return 0;
}