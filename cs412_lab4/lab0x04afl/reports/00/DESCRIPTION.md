#### Name
Code not consistent with library return value

#### Description

The return value of `load_png` was not understood by the writer of `size.c`.

#### Affected Lines
In `size.c:16`

#### Expected vs Observed
We expect main to return 1 when `load_png` fails, i.e. when `load_png` returns 1. We observed that main returned 1 when `load_png` succeded, i.e. when `load_png` returned 0.

#### Steps to Reproduce

##### Command

```
./size poc00
```
##### Proof-of-Concept Input (if needed)
(attached: poc00)

#### Suggested Fix Description
Replace ```!load_png(input_name, &img)``` by ```load_png(input_name, &img)```.
