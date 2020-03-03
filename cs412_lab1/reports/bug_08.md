
### Name
Free after jump

### Description

Free is used after a `goto`, so the palette is never freed and we have a memory leak

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
free palette and then goto error