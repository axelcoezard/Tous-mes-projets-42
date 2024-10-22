#!/bin/bash
find * -name *.h -type f -print \
| while IFS= read -r -d $'\n' file; do dirname "$file"; done \
| uniq -c \
| awk '{$1=$1};1' \
| cut -d' ' -f2 \
| while read file; do echo "-I./$file"; done
