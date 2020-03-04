
### Name
Command injection

### Description

Parameter given to `system()` is not sanitized and we can inject shell commands.

### Affected Lines
In `solid.c:121-122`

### Expected vs Observed
We expected that the user is not able to do anything else than generating an image. We observed that the user is able to execute shell code through the program.

### Steps to Reproduce

#### Command

```
./solid solid.png"&pwd" 3 3 7ad5f9
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Stop the program if `output_name` contains any potentially dangerous character, i.e. stop the program if `output_name` contains anything else than alphanumeric characters, '.', '-' or '_' .