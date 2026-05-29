# So, why does this exist?

Mostly as a toy project to reuse in the future as a skeleton
for much larger Meson-driven C++ codebases using the Google Test
framework.

## Using it

```shell
$ git clone https://github.com/rjhansen/toast
$ cd toast
$ meson setup buildDir
$ cd buildDir
$ ninja && ninja test
```
