#### Name
Trying to write to missing file

#### Description

The program was trying to write to a missing file.

#### Affected Lines
In `pngparser.c:1028`, `pngparser.c:736`

#### Expected vs Observed
We expect the program to handle missing files and exit gracefully. We observed a segfault.

#### Steps to Reproduce

##### Command

```
./fuzzer_store_png_name crash-bd904a8f5b461f5f06a14860de0e27c315ba121a
```
##### Proof-of-Concept Input (if needed)
(attached: crash-d763581c0cd02ca1547a74b25aff5b327f6f9071)

#### Suggested Fix Description
Check whether fopen succeded and return 1 if not.
```
if (!output) {
    return 1;
}
```
