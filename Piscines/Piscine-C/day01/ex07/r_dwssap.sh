#!/bin/sh
cat /etc/passwd | sed '/^#/d' | awk 'NR%2==0' | sed 's/:.*//g' | rev | sort -r | awk "NR>=$FT_LINE1 && NR<=$FT_LINE2" | awk 1 ORS=', ' | sed 's/\(.*\), /\1./g' | tr -d "\n"
