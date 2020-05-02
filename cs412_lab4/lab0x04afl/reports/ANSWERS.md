1. If the CRC chunk is invalid the program exits. Since we don't want to build a valid CRC for each input because it would be tedious, we say that the CRC will be valid for every input.

2. Since we consider two ways (two structures) for building images (palette and rgba) we have to feed the fuzzer the two ways to make images.

3. Since the goal is to take as many paths as possible, afl-gcc will put (instrument) informations about jumps in the binary to help the fuzzer, this way we don't to do blackbox fuzzing.

4. About 4 millions crashes. 50 unique crashes.

5. If a program hangs, it will terminate after a long time or not at all, since this not the attended behavior, this is a bug. We could use the hangs to mount a DOS attack for example.

6. Everything that is used by ```store_png``` will not be tested.

7. No, the fuzzer will only try to crash the program through the content of the images, it won't give bad input names.

8. I ran it for about 20min. No, because the bugs will be harder and harder to find and the function number of bugs per unit of time is not linear.
