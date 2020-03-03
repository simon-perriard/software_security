
### Name
Type confusion

### Description

Comparing `unsigned` with `double` does not make sense and may lead to unexpected behavior because.

### Affected Lines
In `resize.c:54-55`

### Expected vs Observed
We expect to compare comparable types. We observed a comparison between a signed type value (double) and an unsigned type value (unsigned). It may cause to go too far in memory because of how the `round` result is interpret in `unsigned` type when the comparison is done. It caused a segfault at line 66.

### Steps to Reproduce

#### Command

```
./resize_image checkerboard.png resize.png 40000000000000
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
replace `round(factor*img->size_y)` by `new_height`
replace `round(factor*img->size_x)` by `new_width`