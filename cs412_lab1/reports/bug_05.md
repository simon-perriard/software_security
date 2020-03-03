
### Name
Wrong variable used

### Description

The variable `width` is used in a context where `new_width` should be used. Since those are array sizes, we could end up with a segfault.

### Affected Lines
In `resize.c:55`

### Expected vs Observed
We expect to assign a array of length X to an other array of length X. We observed that an array of length X was assigned to an array of length Y.

### Steps to Reproduce

Hasn't been able to trigger the bug...

#### Command

```
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Use `new_width` instead of `width`