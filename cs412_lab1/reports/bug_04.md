
### Name
Unverified malloc result

### Description

There is no check whether malloc succeeded or not. If malloc failed and the pointer is used later there will be a segfault.

### Affected Lines
In `resize.c:47`

### Expected vs Observed
We expect that if malloc fails to allocate memory the program stops without segfault. What was observed was that when no memory was available, the program went through and crashed later on.

### Steps to Reproduce

#### Command

```
./resize_image checkerboard.png resize.png 40000
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Check malloc result:

if (!new_img->px) {
    goto error_memory_img;
}