
### Name
Double free

### Description

`img->px` is freed twice, that could lead to unexpected behaviour.

### Affected Lines
In `resize.c:87`

### Expected vs Observed
We expect to free a pointer only once. We observed a `double free or corruption (out)` error.

### Steps to Reproduce

#### Command

```
./resize_image checkerboard.png resize.png 400000
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
free img instead of free img->px the second time