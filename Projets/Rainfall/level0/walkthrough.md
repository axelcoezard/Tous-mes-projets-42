# LEVEL 0 

## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level1`. 

1. Une fois connecté à la VM sur le `level0`, l'on retrouve un fichier `level0` situé à la racine du dossier utilisateur. Ce dernier s'avère être un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

    ```sh
    > scp -P 4242 level0@127.0.0.1:level0 /path/on/machine/host
    ```

3. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage suivant (refactoriser) :

    ```sh
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>

	int main(int argc, char** argv) 
    {
        int		iVarl;
        char*	local_20;
        int		local_1c;
        uid_t	local_18;
        gid_t	local_14;

        iVarl = atoi(argv[1]);
        if (iVarl == 423) {
            local_20 = strdup("/bin/sh");
            local_1c = 0;
            local_14 = getegid();
            local_18 = geteuid();
            setresgid(local_14, local_14, local_14);
            setresuid(local_18, local_18, local_18);
            execv("/bin/sh", &local_20);
        } else {
            fwrite("No !\n", 1, 5, stderr);
        }
        return 0;
    }
	```

    À partir de ce code source, on peut déduire que le programme contient une fonction `main` qui prend deux paramètres : `argc`et `argv`. Elle convertit la valeur pointée par `argv[1]` en entier et la stocke dans la variable `iVar1`. Si `iVar1` est égal à `423` (`0x1a7` en hexadécimal), le programme effectue les actions suivantes :


    - Alloue de la mémoire pour une chaîne de caractères et la stocke dans `local_20`, soit `/bin/sh` ;
    - Initialise `local_1c` à `0` ;
    - Récupère l'identifiant de groupe effectif (EGID) dans `local_14` avec la fonction `getegid` ;
    - Récupère l'identifiant d'utilisateur effectif (EUID) dans `local_18` avec la fonction `geteuid` ;
    - Modifie l'EGID et l'EUID en utilisant les fonctions `setresgid` et `setresuid` ;
    - Exécute le programme `/bin/sh` avec la fonction `execv` et l'addresse de la variable `local_20` comme arguments, ce qui démarre un shell interactif sur la machine.

    En revanche, si `iVar1` n'est pas égal à `423`, le programme écrit `No !\n` sur la sortie d'erreur standard (`stderr`).

    Ce programme semble être conçu pour exécuter un shell interactif (`/bin/sh`) avec des privilèges élevés (EGID et EUID modifiés) uniquement si la valeur de `argv[1]` est égale à `423`. Sinon, il affiche simplement `No !` sur la sortie d'erreur.

4. De retour sur la VM, on en déduit qu'il suffit d'exécuter `level0` avec le nombre `423` en paramètre afin que le script change l'utilisateur pour `level1`. Pour s'assurer de cela, on lance ensuite la commande `whoami` dans le shell interactif qu'à lancer le script `level0`.

    ```sh
    > ./level0 423
    > whoami
    level1
    ```

5. Enfin, il ne reste plus qu'a `cat` le fichier `/home/user/level1/.pass` pour obtenir le mot de passe qui nous permettra d'accéder au niveau suivant :
    ```sh
    > cat /home/user/level1/.pass
    1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
    ```

6. On peut à présent passer au niveau supérieur en exécutant la commande `su level1` et en y spécifiant le mot de passe qui vient d'être trouvée. 
    ```sh
    > su level1
    Password :
    > 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
    ```
