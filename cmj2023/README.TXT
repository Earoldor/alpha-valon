//////////////////////////::::NOTICE D'UTILISATION DU STANDALONE::::////////////////////////////

!--!--!--!--! POUR EXECUTER LE MODE DEBOGAGE DU STANDALONE.C !--!--!--!--!

=> Nettoyer au préalable tous les fichiers parasites en utilisant le makefile global (se situant dans le répertoire cmj2023): 
    -> make clean

=> Compiler en utilisant le makefile global (se situant dans le répertoire cmj2023) en utilisant la commande suivant :
    -> make debug

=> Pour exécuter, suivre la commande suivante depuis le répertoire /cmj2023/build/ :
    LIBRAIRIE DYNAMIQUE : Exécuter dyn.sh situé dans le répertoire cmj2023/build/ puis après la commande ci-dessous : 
                        -> ./standalone.exe <precisez ici si chemin à un fichier vous disposez>

    LIBRAIRIE STATIQUE : Exécuter la commande ci-dessous :
                        -> ./standalone.static <precisez ici si chemin à un fichier vous disposez>

=> Utilité du mode debogage :
    -> permet de repérer les différents endroits où le programme pourrait éventuellement planter,notamment grâce aux 'printf0'et aux 'fprintf(stderr,"message")'.

!--!--!--!--! POUR EXECUTER LE MODE CLASSIQUE DU STANDALONE.C !--!--!--!--!

=> Nettoyer au préalable tous les fichiers parasites en utilisant le makefile global (se situant dans le répertoire cmj2023): 
    -> make clean

=> Compiler en utilisant le makefile global (se situant dans le répertoire cmj2023) en utilisant la commande suivant :
    -> make all 
ou  -> make

=> Pour exécuter, suivre la commande suivante depuis le répertoire /cmj2023/build/ :
    LIBRAIRIE DYNAMIQUE : Exécuter 'source dyn.sh' situé dans le répertoire cmj2023/build/ puis après la commande ci-dessous : 
                        -> ./standalone.exe <precisez ici si chemin à un fichier vous disposez>

    LIBRAIRIE STATIQUE : Exécuter la commande ci-dessous :
                        -> ./standalone.static <precisez ici si chemin à un fichier vous disposez>

!--!--!--!--! PRISE EN MAIN DU PROGRAMME (valable pour les deux modes) !--!--!--!--!

=> Vous avez l'opportunité de préciser un chemin vers un fichier. Pour cela, utilisez la commande ci-dessous (dans le répertoire cmj2023/build/ de préférence) :
    -> ./standalone.exe <chemin>
    -> ./standalone.static <chemin>

    Les chemins peuvent être de la forme suivante :
        -> "fichier.js"
        -> "/rep1/rep2/rep3/repN/fichier.js"
        -> 'fichier.js'
        -> '/rep1/rep2/rep3/repN/fichier.js'
        -> 'mon fichier.js'
        -> "mon fichier.js"

=> Il vous sera demandé en premier lieu de rentrer à tour de rôle bonus et malus des jaunes et des rouges
    -> Attention !!! : Une mauvaise position sera détectée.

=> Il vous sera ensuite demandé de jouer un coup. Pour cela, vous devez renseigner une position de départ et une position d'arrivée.
    -> Attention !!! : Un coup impossible sera détectée.

//////////////////////////::::FIN NOTICE D'UTILISATION DU STANDALONE::::////////////////////////////