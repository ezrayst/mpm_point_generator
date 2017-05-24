# mpm_point_generator
Generation of Material Points

1. Run `mkdir build && cd build && cmake ..`
2. Run `make clean && make -jN` (where N is the number of cores)
3. Run lem `./mpm_point_generator`

Note to Developers

1. Format using clang-format: `clang-format -i ./src/*`, `clang-format -i ./include/*` and `clang-format -i ./tests/*`