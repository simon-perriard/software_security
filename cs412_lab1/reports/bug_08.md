
### Name
Free after jump and brackets in if block

### Description

If an `if` block is used without bracket, only the first instruction under it will be seen as in the `if` block, so here the `free(palette)` will be executed although it shouldn't and cause a segfault afterwards. Free is used after a `goto`, so the palette is never freed and we have a memory leak.

### Affected Lines
In `solid.c:49`

### Expected vs Observed
We expect to have a clean memory management. We observed that some allocated memory was not freed, leading to memory leak if `height < 0 || *end_ptr`.

### Steps to Reproduce

#### Command

```
./solid solid.png -3 22 7ad5f9
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
put brackets to the if block
goto error and free palette there