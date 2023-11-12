Cynthia Hached 	- 	3702042

Racha Nadine Djeghali	-	21200169

# Projet Visualisateur des flux de trafic réseau  

## Plan

**I.	Analyse de paquet**

		1.	Qu'attend-on de nous ?
		2.	Comment allons-nous nous y prendre ?

**II.	Accès aux données et vérification du contenu**

		*1. Parsing*
		*2. Vérification*

**III.	Analyse de paquet**

		*1. Trame & Couche 2 : Ethernet*
		*2. Couche 3 : IPv4*
		*3. Couche 4 : TCP*
		*4. Couche 7 : HTTP*
		*5. Choix appliqués*

**IV.	Interface graphique**

**V. 	Extension**




# Présentation du projet

# I.	Analyse de paquet

### 1. Objectif
Le but de ce projet est de programmer un visualiseur des flux de trafic réseau, c'est-à-dire l'échange de trames dans le cadre d'un protocole exécuté à l'initiative de deux machines, chacune identifiée par une adresse MAC, une adresse IP et éventuellement par un numéro de port.

### 2. Façon de procéder
Le visualiseur prendra en entrée un fichier trace au format texte contenant les octets capturés préalablement sur un réseau Ethernet (éventuellement accompagné de commentaires). Nous nous sommes appuyés sur les enseignements vus en cours ainsi que [cet article sur le fonctionnement d'internet](https://spathis.medium.com/comprendre-internet-et-son-fonctionnement-9b2f63a07430)

# II.	Accès aux données et vérification du contenu

### 1. Accès aux données
La classe cleanTrame contient la méthode tramesValides() qui récupère dans un fichier l’ensemble de trames à analyser (Celle qui respectent le format indiqué sur le sujet) et les enregiste dans le fichier texte: cleanTrames.txt présent dans le dossier OutPuts.
Afin d'analyser notre trame nous avions besoin de récupérer les données nécessaires en supprimant les éléments indésirables comme :

- Les chaînes de caractères en fin de ligne (commentaires) ou entre trames,
- offset invalide (dans ce cas nous avons décidé de ne pas considérer la trame invalide car il est très probable que le reste soit corrompu ou incomplet)


### 2. Vérification

-Si une des contraires a été rencontré, on a choisi d'afficher les champs déjà analysés correspondants à cette trame puis de passer à la trame suivante.
-Nous avons pris la décision de considérer comme erronée toute trame encapsulant le bon protocole mais ayant une taille trop courte par exemple(chose qui pourrait poser problème a notre découpage)
-Si par contre la trame encapsule un autre protocole que ceux supporté on passe pas au niveau supérieure lors de l’analyse)

# III.	Analyse de paquet

### 	Trame
C'est une classe qui contient 4 attributs principaux de type Ethernet,IPv4,Tcp et Http ainsi qu'un boolean erronée qui est mis a True lorsque l'on estime que la trame est erronée.

### 1. Ethernet

Plusieurs trames peuvent être contenues dans un fichier. La fonction de parsing renverra une trame par ligne. Cette classe va récupérer l’entête avec les champs Ethernet ; adresse MAC Destination et Source, le type de protocole(Capable d'identifier tout les protocoles Ethernet) ainsi que le reste de la trame qui sera passée a la couche superieur si le protocole encapsulé est IPV4. Les protocoles qu'on utilise dans cette UE sont stockés dans le fichier typeEthernet, mais seul le protocole IPV4 est pris en charge dans cette version.

### 2.	IPv4
La classe Paquet récupèrera l'entete IP ; sa version, et le reste des informations pertinentes. Nous avons fait l'analyse des options ; End of Options List (EOOL), No Operation (NOP), Record Route (RR), Time Stamp (TS), Loose Source Route (LSR) ainsi que Strict Source Route (SSR). Tous les protocoles que l'ont trouve sont stockés dans le fichier ipProtocoles, mais seul le protocole TCP est pris en charge dans notre analyseur et est mis dans Tcp.

### 3. Tcp
TCP est un des principaux protocoles de télécommunication utilisés par internet. TCP segmente les données générées par l'application émettrice et ajoute à chaque segment un entête, c'est ce qu'on appelle Tcp. La classe Segment récupère l'entete TCP. Nous avons également traité toutes les options TCP possibles. Toutes les options qui existent sont dans le fichier tcpOptions.csv.

### 4.	HTTP
Le protocole HTTP(HyperText Transfer Protocol) est le protocole qui permet le téléchargement des pages Web. La classe HTTP récupérera le message HTTP en différenciant les requêtes des réponses.Http est aussi en mesure d’analyser toutes les lignes d’entête présentes dans ce dernier, afin d'extraire les champs et valeur différents.

### 5. Choix appliqués
Notre analyseur est en mesure de :

- Éviter tout fichier n'ayant aucun octet ; c'est-à-dire qui est vide.(Vous ne verrez donc aucun affichage sur l’interface dans ce cas la)
- Extraire le maximum de champs pour une trame ; celui-ci est capable de récupérer la trame jusqu'à croiser un champ erroné puis arrête son analyse.
- Éviter tout caractère non hexadécimal et les traite en fonction des cas ;

		-> Caractère non hexadécimal dans une trame : analyse jusqu'à rencontrer le caractère puis le saut.
		-> Caractère non hexadécimal entre deux trames : cherche le prochain octet correspondant à une nouvelle trame ou a la suite de la trame présélectionnée .

### 6. Test
Nous avons mis a votre disposition le dossier Tests qui contient un ensemble de traces contenant des trames commentées ou pas.

# IV. 	Interface graphique
### 1. Envoi du fichier au serveur
Après avoir sélectionné le fichier que vous voulez visualiser, celui-ci est envoyé au serveur, qui sera alors affiché dans une seconde fenêtre où on retrouvera la barre de recherche filtre comme dans WireShark. Nous avons la partie affichant les échanges de flux et une autre pour les commentaires correspondant à chacun des flux.

# V.	Extension
Nous avons également inclus la version terminal ; notre programme peut s'exécuter dans une fenetre de commande de type terminal en plus de l'affichage dans notre interface graphique.

Pour la Version terminal :
			-> Nous avons donné la possibilité ç l'utilisateur de spécifier a quelle niveau il veut visualiser des connexions données , par exemple si une trame encapsule le protocole HTTP mais que l’utilisateur veuille voir les adresses mac des machines impliquées il peut limiter le niveau de l'analyse en spécifiant dans sa recherche --porotocol=ETHERNET :
				*->python3 main.py --terminal "cheminverslefichieràpartirdudossierWirePoupe" --protocol=ETHERNET
