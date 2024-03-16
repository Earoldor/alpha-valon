CECI FONCTIONNE UNIQUEMENT POUR LINUX.
VOUS POUVEZ TENTER DE L'EXECUTER SUR MAC, MAIS SUCCES NON GARANRTI

//////////////////////////::::NOTICE D'UTILISATION DU STANDALONE::::////////////////////////////



!--!--!--!--! POUR EXECUTER LE MODE DEBOGAGE DU STANDALONE.C !--!--!--!--!

=> Nettoyer au préalable tous les fichiers parasites en utilisant le makefile global (se situant dans le répertoire cmj2023): 
    -> make clean

=> Compiler en utilisant le makefile global (se situant dans le répertoire cmj2023) en utilisant la commande suivant :
    -> make debug

=> Pour exécuter, suivre la commande suivante depuis le répertoire /cmj2023/build/ :
    LIBRAIRIE DYNAMIQUE : Exécuter 'source dyn.sh' situé dans le répertoire cmj2023/build/ puis après la commande ci-dessous : 
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

    ATTENTION : si vous changez le chemin d'accès au fichier en dehors de 'web/data', il faut aussi le modifier dans le fichier HTML 'avalam-refresh.HTML'.

    Les chemins peuvent être de la forme suivante :
        -> "fichier.js"
        -> "./rep1/rep2/rep3/repN/fichier.js"
        -> 'fichier.js'
        -> './rep1/rep2/rep3/repN/fichier.js'
        -> 'mon fichier.js'
        -> "mon fichier.js"

=> Il vous sera demandé en premier lieu de rentrer à tour de rôle bonus et malus des jaunes et des rouges
    -> Attention !!! : Une mauvaise position sera détectée.

=> Il vous sera ensuite demandé de jouer un coup. Pour cela, vous devez renseigner une position de départ et une position d'arrivée.
    -> Attention !!! : Un coup impossible sera détectée.




//////////////////////////::::FIN NOTICE D'UTILISATION DU STANDALONE::::////////////////////////////


#######################################################################################################################################################################################


//////////////////////////::::NOTICE D'UTILISATION DU DIAG::::////////////////////////////




!--!--!--!--! POUR EXECUTER LE MODE DEBOGAGE DU DIAG.C !--!--!--!--!

=> Nettoyer au préalable tous les fichiers parasites en utilisant le makefile global (se situant dans le répertoire cmj2023): 
    -> make clean

=> Compiler en utilisant le makefile global (se situant dans le répertoire cmj2023) en utilisant la commande suivant :
    -> make debug

=> Pour exécuter, suivre la commande suivante depuis le répertoire /cmj2023/build/ :
    LIBRAIRIE DYNAMIQUE : Exécuter 'source dyn.sh' situé dans le répertoire cmj2023/build/ puis après la commande ci-dessous : 
                        -> ./diag.exe numDiag chaineFEN
                    OU  -> ./diag.exe numDiag chaineFEN < 'chemin_de_la_redirection'

    LIBRAIRIE STATIQUE : Exécuter la commande ci-dessous :
                        -> ./diag.static numDiag chaineFEN
                    OU  -> ./diag.static numDiag chaineFEN < 'chemin_de_la_redirection'

=> Utilité du mode debogage :
    -> permet de repérer les différents endroits où le programme pourrait éventuellement planter,notamment grâce aux 'printf0'et aux 'fprintf(stderr,"message")'.
    -> permet de voir le bon fonctionnement du traitement de la chaine FEN notamment son critère d'arrêt.




!--!--!--!--! POUR EXECUTER LE MODE CLASSIQUE DU DIAG.C !--!--!--!--!

=> Nettoyer au préalable tous les fichiers parasites en utilisant le makefile global (se situant dans le répertoire cmj2023): 
    -> make clean

=> Compiler en utilisant le makefile global (se situant dans le répertoire cmj2023) en utilisant la commande suivant :
    -> make all
ou  -> make

=> Pour exécuter, suivre la commande suivante depuis le répertoire /cmj2023/build/ :
    LIBRAIRIE DYNAMIQUE : Exécuter 'source dyn.sh' situé dans le répertoire cmj2023/build/ puis après la commande ci-dessous : 
                        -> ./diag.exe <numDiag> <chaineFEN>
                    OU  -> ./diag.exe <numDiag> <chaineFEN> < 'chemin_de_la_redirection'

    LIBRAIRIE STATIQUE : Exécuter la commande ci-dessous :
                        -> ./diag.static <numDiag> <chaineFEN>
                    OU  -> ./diag.static <numDiag> <chaineFEN> < 'chemin_de_la_redirection'




!--!--!--!--! PRISE EN MAIN DU PROGRAMME (valable pour les deux modes) !--!--!--!--!

=> Vous avez l'opportunité de lancer le DIAG.C de deux manières :

    -> via une commmande classique : ./diag.exe(ou static) <numéro du diagramme> <chaineFEN>
    -> via une commande avec une redirection : ./diage.exe(ou static) <numéro du diagramme> <chaineFEN> < 'chemin_de_la_redirection'

    ATTENTION : Si vous utilisez une redirection, le fichier redirigé doit être rédigé comme tel :

                1ere ligne : <chemin du fichier>
                2eme ligne : <description du diagramme>


    Dans le cas où vous n'utilisez pas de redirection, il vous sera demandé d'abord d'entrer un chemin vers un fichier.
    Si vous voulez utiliser le chemin par défaut, appuyez seulement sur la touche entrée.
    Si vous voulez modifier le chemin, saisissez le chemin et appuyez sur entrée.

    Il vous sera ensuite demandé une description. Vous avez la fonctionnalité d'entrer la description sur plusieurs sauts de lignes.
    Cependant, veuillez bien veiller à finir une ligne par un espace.
    
    Lorsque vous avez fini d'entrer votre description, revenez à la ligne et appuyez sur CTRL + D pour arrêter la saisie.

    Le programme s'arrêtera alors et affichera les différentes caractéristiques du diagramme.

    ATTENTION : si vous changez le chemin d'accès au fichier en dehors de 'web/data', il faut aussi le modifier dans le fichier HTML 'avalam-diag.HTML'.




!--!--!--!--! ROBUSTESSE DE LA CHAINE FEN !--!--!--!--!

=> Lorsque vous entrez une chaine FEN en paramètre, merci de faire attention à respecter son écriture et à ce qu'elle soit correcte.

=> Si vous ne respectez pas son écriture, le programme saura reconnaitre les erreurs et dans certains cas vous forcera à la corriger.


//////////////////////////::::FIN NOTICE D'UTILISATION DU STANDALONE::::////////////////////////////
