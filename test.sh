#!/bin/bash
# usage: ./test.sh tests/c5.c

set -e

make test
cc -Wall -Wextra -Werror -g3 -I include "$1" minirt.a -o test
./test
rm test
