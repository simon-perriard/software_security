
### Name

### Description


### Affected Lines
In `checkerboard.c:99-100`

### Expected vs Observed
We expect the program to handle corner cases in a way or an other without crashing.


### Steps to Reproduce

#### Command

```
./checkerboard.png 50 50 80 6a5e33 8ea7f0
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Exit the program if `height/square_width` or `width/square_width` is not an integer > 0.