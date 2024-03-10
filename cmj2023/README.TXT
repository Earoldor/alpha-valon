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




!--!--!--!--! COMPLÉMENTARITÉ EXPÉRIMENTALE !--!--!--!--!

=> Dans le code du standalone.c, vous aurez l'occasion de retrouver en commentaire des lignes du type "//fonctionFen(position);"
   Ces lignes sont à disposition de l'utilisateur s'il veut récupérer la position courrante du programme en notation FEN.
   
   CEPENDANT : Cette fonctionnalité est à l'état expérimentale. C'est-à-dire que cette fonctionnalité n'est pas garantie de fonctionner parfaitement dans tous les cas.
               Elle constitue une première complémentarité entre le standalone.c et le diag.c.
 
   Nous ne recommandons donc pas son utilisation autre d'un cas de récupération d'une position SIMPLE.




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

=> Dans le cas où elle n'est pas correcte, le programme saura gérer les chaines FEN de la forme suivante :

        -> Avec trop de bonus/malus, par exemple : tBbdtBMUDmU42 r
        -> Avec des symboles spéciaux du type : tbUmééùdBUU43 r
        -> Avec des nombres à deux chiffres : tdt10UDU32 r
        -> Avec trop de cases : tdtUDU48 r

        -> Par contre, le programme ne saura pas gérer une chaine FEN du type : tbUééùmdBUU43 r, où un bonus se trouve après des caractères spéciaux.


//////////////////////////::::FIN NOTICE D'UTILISATION DU STANDALONE::::////////////////////////////
