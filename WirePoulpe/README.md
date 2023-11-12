**Projet Visualisateur de Flux de Trafic Réseau**

**Plan**

I. **Analyse de paquet**
   1. Objectif et approche

II. **Accès aux données et Vérification du contenu**
   1. Parsing
   2. Vérification

III. **Analyse de paquet**
   1. Trame & Couche 2 : Ethernet
   2. Couche 3 : IPv4
   3. Couche 4 : TCP
   4. Couche 7 : HTTP
   5. Choix appliqués

IV. **Interface Graphique**

V. **Extension**

---

**Présentation du Projet**

I. **Analyse de paquet**
   1. Objectif

Ce projet vise à créer un visualiseur de flux de trafic réseau, analysant l'échange de trames entre deux machines identifiées par adresse MAC, adresse IP, et éventuellement un numéro de port.

   2. Façon de procéder

Le visualiseur prend un fichier trace au format texte avec des octets capturés sur un réseau Ethernet comme entrée. Nous nous référons aux enseignements du cours et à un article sur le fonctionnement d'Internet.

II. **Accès aux données et Vérification du contenu**
   1. Accès aux données

La classe `cleanTrame` utilise la méthode `tramesValides()` pour récupérer et enregistrer les trames à analyser. Les trames invalides sont exclues.

   2. Vérification

Si des contraintes sont rencontrées, les champs analysés jusqu'à ce point sont affichés pour la trame correspondante. Une trame est considérée erronée si elle encapsule le bon protocole mais a une taille inappropriée.

III. **Analyse de paquet**
   - **Trame**

Cette classe contient des attributs Ethernet, IPv4, TCP, HTTP, et un booléen 'erronée'.

   - **Ethernet**

La fonction de parsing renvoie une trame par ligne, récupérant les champs Ethernet. Seul le protocole IPv4 est pris en charge dans cette version.

   - **IPv4**

La classe `Paquet` récupère l'entête IP, analysant également les options possibles.

   - **TCP**

La classe `Segment` récupère l'entête TCP, traitant toutes les options TCP possibles.

   - **HTTP**

La classe `HTTP` analyse les messages HTTP, distinguant les requêtes des réponses et extrayant les champs et valeurs des lignes d'entête.

   - **Choix appliqués**

L'analyseur évite les fichiers vides, extrait le maximum de champs pour une trame jusqu'à rencontrer une erreur, et gère les caractères non hexadécimaux.

IV. **Interface Graphique**
   1. Envoi du fichier au serveur

Sélectionnez le fichier à visualiser, envoyez-le au serveur, et affichez les échanges de flux et les commentaires dans une fenêtre distincte avec une barre de recherche filtre.

V. **Extension**
   - Exécution dans une fenêtre de commande de type terminal en plus de l'interface graphique.
   - Possibilité de limiter le niveau d'analyse en spécifiant les connexions données dans la version terminal.

Pour la version terminal : `python3 main.py --terminal "cheminverslefichieràpartirdudossierWirePoupe" --protocol=ETHERNET`
