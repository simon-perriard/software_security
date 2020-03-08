
### Name
Division problem


### Description
If `height/square_width` or `width/square_width` is not an integer > 0, the program crashes because the bounds of the for loops are too tight and thus some of the pixel are not initialized. This causes a segfault.

### Affected Lines
In `checkerboard.c:99-100`

### Expected vs Observed
We expect to be able to draw fractions of squares. We observed that the program crashed and raised a segfault when the square_width did not divide height or width.

### Steps to Reproduce

#### Command

```
./checkerboard checkerboard.png 50 50 4 6a5e33 8ea7f0
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Adapt the bounds to draw fractions of squares.