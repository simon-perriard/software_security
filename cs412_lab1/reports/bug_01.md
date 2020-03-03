### Name
Unverified input size

### Description

The elements of argv[i] are copied into char arrays of size 256 but the size of each argv[i] is not checked.

### Affected Lines
In `filter.c:177-179` and `filter.c:183`

### Expected vs Observed
We expect that whatever the input, the command should either succeed or exit, but never terminate with a `core dumped` error.

### Steps to Reproduce

#### Command

```
./filter checkerboard.png checkerboard2.png blurrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr 3
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Check that the size of each input is smaller or equal to the size of the arrays we want to put them in later.