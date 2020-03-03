
### Name
Unallocated memory

### Description

In get_pixel, the struct is allocated in the stack, but it should be allocated in the heap since the pointer is returned at the end of the function.

### Affected Lines
In `filter.c:101-102`, because of those lines we can observe a segfault whenever a reference to the struct (neg->red/green/blue/alpha) is done in the for loop of filter_negative.

### Expected vs Observed
We expect that the pointer that is returned doesn't point to NULL (0x0) when the function is called. When a call to get_pixel is done, the memory for the struct is allocated on the stack, but when the function returns, that memory is given back to the OS and the pointer &px that was returned points to nothing.

### Steps to Reproduce

#### Command

```
./filter checkerboard.png neg.png negative
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Do malloc(sizeof(struct pixel)) in get_pixel.