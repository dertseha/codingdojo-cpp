# CodingDojo template - C++

This is a template for a coding dojo. The language is C++.

## Setup
The repository contains the [Google Mock](https://github.com/google/googletest) framework.

To build the project, you need either
* [Boost.Build](http://www.boost.org/build/index.html) or
* [CMake](http://www.cmake.org/)

### Using Boost.Build
Simply call ```b2``` in the project root directory. Unit-tests are built and automatically executed.

### Using CMake
Generate your project files with
```
mkdir build
cd build
cmake ..
```
Then run your build tool with the generated files. The unit-tests need to be run manually.

## License

[![License][license-image]][license-url]

This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).

[license-url]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[license-image]: https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png
