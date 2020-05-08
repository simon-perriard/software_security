#### Name
Unfreed pointer

#### Description

A pointer is never freed and leaks memory.

#### Affected Lines
In `pngparser.c:711`, `pngparser.c:730`

#### Expected vs Observed
We expect the program not to leak memory and free all the pointers. We observed that the pointer inflated_buf was never freed in load_png.

#### Steps to Reproduce

##### Command

``
./fuzzer_load_png leak-2d5ff885f157e7321b0f50c06272f3da682963af
```
##### Proof-of-Concept Input (if needed)
(attached: leak-2d5ff885f157e7321b0f50c06272f3da682963af)

#### Suggested Fix Description
Check whether input is NULL and free it if its not before return.

