#### Name
Double free

#### Description

The program was freeing a pointer that was already freed but not put at NULL.

#### Affected Lines
In `pngparser.c:301`, `pngparser.c:721`

#### Expected vs Observed
We expect the program to put at NULL a pointer that could be reused later on so we are able to check whether it was already freed or not. We observed that the freed pointer was not put at NULL and a double free was attempted.

#### Steps to Reproduce

##### Command

```
./fuzzer_load_png -detect_leaks=0 crash-d763581c0cd02ca1547a74b25aff5b327f6f9071
```
##### Proof-of-Concept Input (if needed)
(attached: crash-d763581c0cd02ca1547a74b25aff5b327f6f9071)

#### Suggested Fix Description
Assign NULL to pointer before returning.
```
if (chunk->chunk_data) {
    free(chunk->chunk_data);
    chunk->chunk_data = NULL;
}
```