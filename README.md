# how2bss
After being inspired by [Shellphish](https://github.com/shellphish)'s [how2heap](https://github.com/shellphish/how2heap), I decided to start my own little repo of bss and data segment exploitation techniques.

Unlike the stack and the heap, the bss and data segments don't have many of the same protections on them. There are no canaries between variables, bss and data addresses are unaffected by ASLR (Provided PIE is not enabled), and (with a special case) bss overflows can even be used to overwrite Global Offset Table entries.

| File | Technique | Tested on | GCC Version |
| - | - | - | - |
| [stat.c](stat.c) | Static variable overflow. | Ubuntu 18 (amd64) | 7.4.0 |
| [globalstatic.c](globalstatic.c) | Static and global variable alterations with overflows. | Ubuntu 18 (amd64) | 7.4.0 |
| [backwardgot.c](backwardgot.c) | Overwriting Global Offset Table entries with a backwards overflow. | Ubuntu 16 (amd64) | 7.4.0 |
| [aslrusage.c](aslrusage.c) | Introduces a useful property of the BSS and data segments. | Ubuntu 18 (amd64) | 7.4.0 |
| [overwritefp.c](overwritefp.c) | Shows how global function pointers can be manipulated with overflows. (Suggested by [@poppushpop](https://twitter.com/poppushpop)) | Ubuntu 18 (amd64) | 7.4.0 |
