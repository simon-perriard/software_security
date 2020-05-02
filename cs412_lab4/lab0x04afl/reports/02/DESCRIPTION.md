#### Name
Type confusion and malloc not checked

#### Description
The types of `size_x` and `size_y` of the `struct image` were consistent with the library specifications, they should be on 4 bytes.

The `malloc` return values are not check for `NULL`.

#### Affected Lines
In `46-47 pngparser.h`, `418 and 421 pngparser.c`

#### Expected vs Observed
We expect the code to be consistent with the library specifications. We observed that the spec were not respected, i.e. `size_x` and `size_y` are on 2 bytes instead of 4 bytes.

We expect the `malloc` return value to be checked for `NULL`. We observed that no check was done.

#### Steps to Reproduce

##### Command

```
./size poc02
```
##### Proof-of-Concept Input (if needed)
(attached: poc02)

#### Suggested Fix Description
Modify the types of `size_x` and `size_y` to `uint32_t` in the definition of the `struct image`.

Verify the malloc by adding checks just after each of the two `malloc` and add an `error` procedure (goto error).
```
if (!img) {
        goto error;
    }
```

```
if (!img->px) {
        goto error;
    }
```

```
error:
        if (img) {
            if (img->px) {
                free(img->px);
            }
            free(img);
        }

        return NULL;
```