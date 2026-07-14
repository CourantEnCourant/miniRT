#!/bin/bash
# Run norminette on all .c/.h files in include/ and lib/,
# excluding anything mlx-related.

find include lib \
	\( -name '*.c' -o -name '*.h' \) \
	-not -name 'mlx*' \
	-not -path '*minilibx*' \
	-print0 | xargs -0 norminette
