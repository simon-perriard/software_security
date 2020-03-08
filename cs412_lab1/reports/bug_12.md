
### Name
Unverified memory allocation

### Description
The success of the allocation of struct palette is never checked. On a system with very low memory, we would have a segfault when accessing palette if the malloc failed.

### Affected Lines
In `solid.c:16``

### Expected vs Observed
We expect the program to handle memory allocation, whether it succeed or not. We observed that memory allocation in the case it failed is not well handled.


### Steps to Reproduce

#### Command

```
./solid block.png 50 50 00ff00
```
On a machine with very low memory.

#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Check that malloc succeeded, exit the program otherwise.