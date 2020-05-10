#### Name
Closing missing file

#### Description

When the file does not exist, the program still tries to close it.

#### Affected Lines
In `pngparser.c:713`

#### Expected vs Observed
We expect the program not to close an missing file and exit without segfault. We observed a segfault.

#### Steps to Reproduce

##### Command

```
./fuzzer_load_png_name -detect_leaks=0 crash-c4a3ee535e2ae67ced416e1335ae310211e975b3
```
##### Proof-of-Concept Input (if needed)
(attached: crash-c4a3ee535e2ae67ced416e1335ae310211e975b3)

#### Suggested Fix Description
Check whether input is NULL before closing the file.
```
if (input) {
  fclose(input);
}
```
