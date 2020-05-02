#### Name
Double free

#### Description

`chunk_data` was already freed in `error` in `read_png_chunk`.

#### Affected Lines
In `pngparser.c:300`

#### Expected vs Observed
We expect the program to free the memory without error, to have a beautiful memory management. We observed a double free.

#### Steps to Reproduce

##### Command

```
./size poc01
```
##### Proof-of-Concept Input (if needed)
(attached: poc01)

#### Suggested Fix Description
Add `chunk->chunk_data = NULL` so we cannot reuse `chunk_data`.

