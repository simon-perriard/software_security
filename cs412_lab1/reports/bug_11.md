
### Name
Circle out of bound

### Description
When a circle is drawn near an edge and the circle radius crosses the edge, the for loops will allow to draw to draw the part of the circle that should not be drawn. In extreme cases it can cause a segfault.

### Affected Lines
In `circle.c:47`, `circle.c:54`, `circle.c:68`, `circle.c:75`

### Expected vs Observed
We expect to see the circle only around its center and with its given radius. We observed that the circle was drawn on the 'other side' of the image when the circle crossed the edge of an image.


### Steps to Reproduce

#### Command

```
./circle block.png cirle.png 0 0 5 00ff00
```
#### Proof-of-Concept Input (if needed)


### Suggested Fix Description
Check whether the pixel to be drawn is valid or not.