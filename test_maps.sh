#!/bin/bash

for file in maps/valid/*.cub; do
    echo "(valgrind ./cub3D $file)"
    valgrind --leak-check=full ./cub3D "$file"
    echo "-----------------------------------"
done