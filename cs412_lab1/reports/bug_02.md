
### Name
Unverified input size

### Description

The elements of argv[i] are copied into char arrays of size 256 but the size of each argv[i] is not checked.

### Affected Lines
In `rect.c:20-21`

### Expected vs Observed
We expect that whatever the input, the command should either succeed or exit, but never terminate with a `core dumped` error.

### Steps to Reproduce

#### Command

```
./rect aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa  rect.png 0 0 30 30 92a834
```
With this command we can already see in the stack that we went too far, but we would need more characters to trigger a stack smashing error.
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Check that the size of each input is smaller or equal to the size of the arrays we want to put them in later.