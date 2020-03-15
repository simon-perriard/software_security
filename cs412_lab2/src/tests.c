#include <sys/types.h>
#include <assert.h>
#include <check.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include "filter.h"

struct image generate_rand_img() {
  struct image img;
  do{  img.size_x = rand() % 256; } while(img.size_x == 0);
  do{  img.size_y = rand() % 256; } while(img.size_y == 0);
  img.px = malloc(img.size_x * img.size_y * sizeof(struct pixel));
  if(img.px == NULL)
    assert(0 && "Rerun test, malloc failed");
  for(long i = 0; i < img.size_y * img.size_x; i++) {
    img.px[i].red = rand();
    img.px[i].green = rand();
    img.px[i].blue = rand();
    img.px[i].alpha = rand();
  }

  return img;
}
struct image duplicate_img(struct image img) {
  struct image img_dup;

  img_dup.size_x = img.size_x;
  img_dup.size_y = img.size_y;
  img_dup.px = malloc(img.size_x * img.size_y * sizeof(struct pixel));
  if(img_dup.px == NULL)
    assert(0 && "Rerun test, malloc failed");
  for(long i = 0; i < img.size_y * img.size_x; i++) {
    img_dup.px[i].red = img.px[i].red;
    img_dup.px[i].green = img.px[i].green;
    img_dup.px[i].blue = img.px[i].blue;
    img_dup.px[i].alpha = img.px[i].alpha;
  }

  return img_dup;
}

/* Grayscale function should not crash when the weights are 
 * at the limits of the double data size */
START_TEST(grayscale_double_limit) {
  srand(time(NULL) ^ getpid());

  /* Generate random png image */
  struct image img = generate_rand_img();

  /* Limiting cases of double */
  double weight_limits[] = {DBL_MIN, DBL_TRUE_MIN, DBL_MAX, DBL_EPSILON, DBL_MIN_EXP};
  int n_limits = sizeof(weight_limits)/sizeof(weight_limits[0]);

  /* grayscale requires array of 3 weights */
  for(unsigned i0 = 0; i0 < n_limits; i0++)
    for(unsigned i1 = 0; i1 < n_limits; i1++)
      for(unsigned i2 = 0; i2 < n_limits; i2++) {
        double weights[3] = {weight_limits[i0], weight_limits[i1], weight_limits[i2]};
        /* Merely checking that the function does not crash */
        filter_grayscale(&img, weights);
      }

  /* Not strictly necessary unless using CK_FORK=no */
  free(img.px);
}
END_TEST

START_TEST(grayscale_functionality) {
  srand(time(NULL) ^ getpid());

  /* Generate random png image */
  struct image img = generate_rand_img();
  uint8_t rand_alpha = rand();
  double weights[] = {0, 0, 0};
  uint16_t sz_x = img.size_x, sz_y = img.size_y;
  for(long i = 0; i < sz_y; i++)
    for(long j = 0; j < sz_x; j++)
      img.px[i * sz_x + j].alpha = rand_alpha;


  filter_grayscale(&img, weights);

  ck_assert_uint_eq(img.size_x, sz_x);
  ck_assert_uint_eq(img.size_y, sz_y);
  ck_assert_ptr_ne(img.px, NULL);
  for(long i = 0; i < sz_y; i++)
    for(long j = 0; j < sz_x; j++){
      long idx = i * sz_x + j;
      ck_assert_uint_eq(img.px[idx].red, 0);
      ck_assert_uint_eq(img.px[idx].green, 0);
      ck_assert_uint_eq(img.px[idx].blue, 0);
      ck_assert_uint_eq(img.px[idx].alpha, rand_alpha);
    }

  free(img.px);
}
END_TEST

START_TEST(sepia_limits0) {
  struct image img;
  img.size_x = 0;
  img.size_y = 0;
  img.px = NULL;

  uint8_t depth = 0;
  /* Should not crash */
  filter_sepia(&img, &depth);
}
END_TEST

START_TEST(sepia_limits_depth) {
  srand(time(NULL) ^ getpid());
  struct image img;
  struct pixel pxl;

  img.size_x = 1;
  img.size_y = 1;
  img.px = &pxl;
  pxl.red = pxl.green = pxl.blue = 0;
  pxl.alpha = 255;

  uint8_t depth = 255;
  filter_sepia(&img, &depth); 
  ck_assert_uint_eq(pxl.red, 255);
  ck_assert_uint_eq(pxl.green, 255);
  ck_assert_uint_eq(pxl.blue, 0);
  ck_assert_uint_eq(pxl.alpha, 255);

  depth = 128;
  pxl.red = pxl.green = pxl.blue = 0;
  filter_sepia(&img, &depth); 
  ck_assert_uint_eq(pxl.red, 255);
  ck_assert_uint_eq(pxl.green, 128);
  ck_assert_uint_eq(pxl.blue, 0);
  ck_assert_uint_eq(pxl.alpha, 255);

  depth = 0;
  uint8_t rand8 = pxl.red = pxl.green = pxl.blue = rand();
  filter_sepia(&img, &depth); 
  ck_assert_uint_eq(pxl.red, rand8);
  ck_assert_uint_eq(pxl.green, rand8);
  ck_assert_uint_eq(pxl.blue, rand8);
  ck_assert_uint_eq(pxl.alpha, 255);
}
END_TEST

char *sepia_summers[] = {
  "test_imgs/summer_sepia_0.png",
  "test_imgs/summer_sepia_10.png",
  "test_imgs/summer_sepia_20.png",
  "test_imgs/summer_sepia_30.png",
  "test_imgs/summer_sepia_42.png"
};
uint8_t sepia_depths[] = {
  0x0, 0x10, 0x20, 0x30, 0x42
};

START_TEST(sepia_example_image) {
  struct image *img, *img_sepia, img_dup;

  ck_assert_int_eq(load_png("test_imgs/summer.png", &img), 0);
  img_dup = duplicate_img(*img);
  filter_sepia(img, &sepia_depths[_i]);

  /* Compare to known good image */
  ck_assert_int_eq(load_png(sepia_summers[_i], &img_sepia), 0);

  ck_assert_uint_eq(img_sepia->size_x, img->size_x);
  ck_assert_uint_eq(img_sepia->size_y, img->size_y);
  for(long j = 0; j < img->size_x * img->size_y; j++) {
    ck_assert_uint_eq(img_sepia->px[j].red, img->px[j].red);
    ck_assert_uint_eq(img_sepia->px[j].green, img->px[j].green);
    ck_assert_uint_eq(img_sepia->px[j].blue, img->px[j].blue);
    ck_assert_uint_eq(img_dup.px[j].alpha, img->px[j].alpha);
  }
  free(img_dup.px);
  free(img_sepia->px);
  free(img->px);
  free(img_sepia);
  free(img);
}
END_TEST


START_TEST(bw_limits0) {
  struct image img;
  img.size_x = 0;
  img.size_y = 0;
  img.px = NULL;

  uint8_t threshold = 0;
  /* Should not crash */
  filter_bw(&img, &threshold);
}
END_TEST

START_TEST(bw_threshold) {
  srand(time(NULL) ^ getpid());
  
  struct pixel img_pxl, img_dup_pxl;
  struct image img = generate_rand_img();
  struct image img_dup = duplicate_img(img);

  uint8_t threshold = 0;
  filter_bw(&img, &threshold);
  ck_assert_uint_eq(img.size_x, img_dup.size_x);
  ck_assert_uint_eq(img.size_y, img_dup.size_y);
  for(long j = 0; j < img.size_x * img.size_y; j++) {
    img_pxl = img.px[j];
    img_dup_pxl = img_dup.px[j];

    /* Check all pixels are equal */
    ck_assert_uint_eq(img_pxl.red, img_pxl.green);
    ck_assert_uint_eq(img_pxl.red, img_pxl.blue);

    /* Check that alpha is unaffected */
    ck_assert_uint_eq(img_pxl.alpha, img_dup_pxl.alpha);

    if(img_pxl.red == 0) {
      ck_assert_uint_lt(img_pxl.red, 3);
      ck_assert_uint_lt(img_pxl.green, 3);
      ck_assert_uint_lt(img_pxl.blue, 3);
      uint8_t total = img_pxl.red + img_pxl.green + img_pxl.blue;
      ck_assert_uint_lt(total, 3);
    } else {
      ck_assert_uint_eq(img_pxl.red, 255);
      ck_assert_uint_eq(img_pxl.green, 255);
      ck_assert_uint_eq(img_pxl.blue, 255);
    }
  }

  threshold = 255;
  memcpy(img.px, img_dup.px, img.size_x * img.size_y * sizeof(struct pixel));
  filter_bw(&img, &threshold);
  ck_assert_uint_eq(img.size_x, img_dup.size_x);
  ck_assert_uint_eq(img.size_y, img_dup.size_y);
  for(long j = 0; j < img.size_x * img.size_y; j++) {
    img_pxl = img.px[j];
    img_dup_pxl = img_dup.px[j];

    /* Check all pixels are equal */
    ck_assert_uint_eq(img_pxl.red, img_pxl.green);
    ck_assert_uint_eq(img_pxl.red, img_pxl.blue);

    /* Check that alpha is unaffected */
    ck_assert_uint_eq(img_pxl.alpha, img_dup_pxl.alpha);

    /* Cannot exceed threshold */
    ck_assert_uint_eq(img_pxl.red, 0);
    ck_assert_uint_eq(img_pxl.green, 0);
    ck_assert_uint_eq(img_pxl.blue, 0);
  }
}
END_TEST

char *bw_summers[] = {
  "test_imgs/summer_bw_40.png",
  "test_imgs/summer_bw_80.png",
};
uint8_t bw_thresholds[] = {
  0x40, 0x80
};

START_TEST(bw_example_image) {
  struct image *img, *img_bw, img_dup;

  ck_assert_int_eq(load_png("test_imgs/summer.png", &img), 0);
  img_dup = duplicate_img(*img);
  filter_bw(img, &bw_thresholds[_i]);

  /* Compare to known good image */
  ck_assert_int_eq(load_png(bw_summers[_i], &img_bw), 0);

  ck_assert_uint_eq(img_bw->size_x, img->size_x);
  ck_assert_uint_eq(img_bw->size_y, img->size_y);
  for(long j = 0; j < img->size_x * img->size_y; j++) {
    ck_assert_uint_eq(img_bw->px[j].red, img->px[j].red);
    ck_assert_uint_eq(img_bw->px[j].green, img->px[j].green);
    ck_assert_uint_eq(img_bw->px[j].blue, img->px[j].blue);
    ck_assert_uint_eq(img_dup.px[j].alpha, img->px[j].alpha);
  }
  free(img_dup.px);
  free(img_bw->px);
  free(img->px);
  free(img_bw);
  free(img);

}
END_TEST

START_TEST(bw_simple) {
  struct image img;
  struct pixel pxl;

  img.size_x = img.size_y = 1;
  img.px = &pxl;

  for(uint8_t i = 3; i < 5; i++) {
    pxl.red = pxl.green = pxl.blue = i; 
    pxl.alpha = 128;  

    uint8_t threshold = 4;  
    filter_bw(&img, &threshold);  
    ck_assert_uint_eq(pxl.alpha, 128);
    ck_assert_uint_eq(pxl.red, pxl.green);
    ck_assert_uint_eq(pxl.red, pxl.blue);
    ck_assert_uint_eq(pxl.red, (i > 4)? 255:0);
  }
}
END_TEST

START_TEST(edge_threshold) {
  struct image img;
  struct pixel pxl;
  uint8_t threshold;

  img.size_x = img.size_y = 1;
  img.px = &pxl;
  
  /* These calls should not crash */
  threshold = 0;
  filter_bw(&img, &threshold);  
  threshold = 255;
  filter_bw(&img, &threshold);  
}
END_TEST

char *edge_deserts[] = {
  "test_imgs/desert_edge_40.png",
  "test_imgs/desert_edge_80.png",
  "test_imgs/desert_edge_c0.png",
  "test_imgs/desert_edge_e0.png"
};
uint8_t edge_thresholds[] = {
  0x40, 0x80, 0xc0, 0xe0
};

START_TEST(edge_example_image) {
  struct image *img, *img_edge, img_dup;

  ck_assert_int_eq(load_png("test_imgs/desert.png", &img), 0);
  img_dup = duplicate_img(*img);
  filter_edge_detect(img, &edge_thresholds[_i]);

  /* Compare to known good image */
  ck_assert_int_eq(load_png(edge_deserts[_i], &img_edge), 0);

  ck_assert_uint_eq(img_edge->size_x, img->size_x);
  ck_assert_uint_eq(img_edge->size_y, img->size_y);
  for(long j = 0; j < img->size_x * img->size_y; j++) {
    ck_assert_uint_eq(img_edge->px[j].red, img->px[j].red);
    ck_assert_uint_eq(img_edge->px[j].green, img->px[j].green);
    ck_assert_uint_eq(img_edge->px[j].blue, img->px[j].blue);
    ck_assert_uint_eq(img_dup.px[j].alpha, img->px[j].alpha);
  }
  free(img_dup.px);
  free(img_edge->px);
  free(img->px);
  free(img_edge);
  free(img);

}
END_TEST

START_TEST(edge_checkerboard) {
  struct image *img, *img_edge, img_dup;

  ck_assert_int_eq(load_png("test_imgs/ck.png", &img), 0);
  uint8_t threshold = 0x10;
  img_dup = duplicate_img(*img);
  filter_edge_detect(img, &threshold);

  /* Compare to known good image */
  ck_assert_int_eq(load_png("test_imgs/ck_edge.png", &img_edge), 0);

  ck_assert_uint_eq(img_edge->size_x, img->size_x);
  ck_assert_uint_eq(img_edge->size_y, img->size_y);
  for(long j = 0; j < img->size_x * img->size_y; j++) {
    ck_assert_uint_eq(img_edge->px[j].red, img->px[j].red);
    ck_assert_uint_eq(img_edge->px[j].green, img->px[j].green);
    ck_assert_uint_eq(img_edge->px[j].blue, img->px[j].blue);
    ck_assert_uint_eq(img_dup.px[j].alpha, img->px[j].alpha);
  }
  free(img_dup.px);
  free(img_edge->px);
  free(img->px);
  free(img_edge);
  free(img);

}
END_TEST

START_TEST(keying_limits) {
  srand(time(NULL) ^ getpid());

  struct pixel key, pxls[9], pxl;
  struct image img;

  /* All pixels equal one randomly generated pixel */
  do { pxl.red = rand();  } while(pxl.red == 0);
  do { pxl.green = rand();  } while(pxl.green == 0);
  do { pxl.blue = rand(); } while(pxl.blue == 0);
  do { pxl.alpha = rand();  } while(pxl.alpha == 0);
  for(unsigned i = 0; i < 9; i++) {
    pxls[i].red = pxl.red;
    pxls[i].green = pxl.green;
    pxls[i].blue = pxl.blue;
    pxls[i].alpha = pxl.alpha;
  }
  img.size_x = 3;
  img.size_y = 3;
  img.px = pxls;

  /* Case 1: No pixels match, so shouldn't be changed */
  key.red = 0;
  key.green = 0;
  key.blue = 0;
  filter_keying(&img, &key);
  for(unsigned i = 0; i < 9; i++) {
    ck_assert_uint_eq(pxls[i].red, pxl.red);
    ck_assert_uint_eq(pxls[i].green, pxl.green);
    ck_assert_uint_eq(pxls[i].blue, pxl.blue);
    ck_assert_uint_eq(pxls[i].alpha, pxl.alpha);
  }
  
  /* Case 2: All pixels match, so should all be transparent */
  key = pxl;
  filter_keying(&img, &key);
  for(unsigned i = 0; i < 9; i++) {
    ck_assert_uint_eq(pxls[i].alpha, 0);
  }
}
END_TEST

START_TEST(keying_functionality) {
  srand(time(NULL) ^ getpid());

  struct image img = generate_rand_img();
  struct image img_dup = duplicate_img(img);
  struct pixel key;

  key = img.px[rand() % (img.size_x * img.size_y)];
  filter_keying(&img, &key);
  long count_matches = 0;
  for(long i = 0; i < img.size_x * img.size_y; i++) {
    struct pixel pxl = img.px[i], dup_pxl = img_dup.px[i];
    if((dup_pxl.red == key.red) && (dup_pxl.green == key.green) &&
       (dup_pxl.blue == key.blue)) {
      ck_assert_uint_eq(pxl.alpha, 0);
      count_matches++;
    }   
  }
  ck_assert_int_gt(count_matches, 0);
}
END_TEST

char *grayscale_sources[] = {
  "test_imgs/desert.png",
  "test_imgs/summer.png"
};
char *grayscale_output[] = {
  "test_imgs/desert_gray.png",
  "test_imgs/summer_gray.png"
};
START_TEST(grayscale_examples) {
  double weights[] = {0.2125, 0.7154, 0.0721};
  /* TODO: Implement */
}
END_TEST

/* Verify that the black image is inverted properly to a white image.
 * Then invert the result again and verify that you get a black image back
 * The alpha channel needs to be intact in both cases */
START_TEST(negative_functionality) {
  /* TODO: Implement */
}
END_TEST

/* Check if the filter doesn't crash when we pass a 0x0 image */
START_TEST(negative_zero_size) {
  /* TODO: Implement */
}
END_TEST

/* Check for the simple, non-uniform, 3x3 test image that the blur filter
 * gives the correct output for different values of the radius (0, 1, 2, 3) */
START_TEST(blur_functionality) {
  struct pixel black = {0, 0, 0, 255};
  struct pixel white = {252, 252, 252, 255};
  struct pixel px[3][3] = {{black, black, black}, {black, white, black}, {black, black, black}};
  struct image img = {3, 3, &px};

  /* TODO: Implement */
}
END_TEST

/* Verify that the filter doesn't crash when we provide extreme values
 * for the radius (INT_MIN, INT_MAX, 0, image_width, image_height, all of the previous values divided by 2,
 * all of the previous values +- 1) */
START_TEST(blur_radius_edge_cases) {
  /* TODO: Implement */
}
END_TEST

/* Verify for a random image that the transparency filter works properly */
START_TEST(transparency_functionality) {
  /* TODO: Implement */
}
END_TEST

/* Check if the function crashes when we pass nullptr as the argument */
START_TEST(transparency_edge_case) {
  /* TODO: Implement */

}
END_TEST

int main() {
  Suite* s = suite_create("lib-Y0l0 tests");
  TCase *tc1 = tcase_create("edge case tests"); 
  suite_add_tcase(s, tc1);
  TCase *tc2 = tcase_create("basic functionality tests"); 
  suite_add_tcase(s, tc2);

  /* TODO: Add more tests here */
  /* Add tests for input limits, and general functionality tests */

  /* Tests for limits*/
  tcase_add_test(tc1, grayscale_double_limit);
  tcase_add_test(tc1, negative_zero_size);
  tcase_add_test(tc1, blur_radius_edge_cases);
  tcase_add_test(tc1, sepia_limits0);
  tcase_add_test(tc1, sepia_limits_depth);
  tcase_add_test(tc1, bw_limits0);
  tcase_add_test(tc1, bw_threshold);
  tcase_add_test(tc1, edge_threshold);
  tcase_add_test(tc1, transparency_edge_case);
  tcase_add_test(tc1, keying_limits);

  /* Tests for functionality */
  tcase_add_test(tc2, grayscale_functionality);
  /* TODO: Add looped test case for grayscale_examples */
  tcase_add_test(tc2, negative_functionality);
  tcase_add_test(tc2, blur_functionality);
  tcase_add_test(tc2, transparency_functionality);
  tcase_add_loop_test(tc2, sepia_example_image, 0, sizeof(sepia_depths) / sizeof(sepia_depths[0]));
  tcase_add_loop_test(tc2, bw_example_image, 0, sizeof(bw_summers) / sizeof(bw_summers[0]));
  tcase_add_test(tc2, bw_simple);
  tcase_add_loop_test(tc2, edge_example_image, 0, sizeof(edge_deserts) / sizeof(edge_deserts[0]));
  tcase_add_test(tc2, edge_checkerboard);
  tcase_add_test(tc2, keying_functionality);

  SRunner *sr = srunner_create(s); 
  srunner_run_all(sr, CK_VERBOSE); 

  int number_failed = srunner_ntests_failed(sr); 
  srunner_free(sr); 

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE; 
}