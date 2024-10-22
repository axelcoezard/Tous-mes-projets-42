#!/bin/sh

# Compile les fichiers sources en objets.
gcc -Wall -Wextra -Werror -c *.c

# Archive les objets dans une bibliotheque.
ar -r libft.a *.o

# Index et stocke le contenu pour
# supporter les liaison entre objets,
ranlib libft.a

# Supprime les fichiers objets
rm -f *.o

