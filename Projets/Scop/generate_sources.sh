#!/bin/bash
find * -name *.cpp -type f -print \
| while IFS= read -r -d $'\n' file; do echo ${file#*/}; done
