# Installer et lancer le programme
		Pour décompresser taper cette commande sur votre terminal (Ou effectuez le manuellement ) :
				->  unzip WirePoulpe21200169-3702042.zip

		Placez vous dans le dossier WirePoulpe:
				-> cd WirePoulpe

		Pour lancer l'interface vous pouvez directement saisir :
				-> make interface


Notre programme supporte 2 options :
	1. La version termianl
	2. La version graphique

## Pour la version terminal
**Si vous optez pour une version terminal :**

	Quatre Options s'offrent à vous ! Il faudra imperativement respecter les formats suivants :

		1. Pour une analyse simple:
				-> python3 main.py --terminal [chemin vers le fichier(txt)]

	 	2. Pour présicer un protocol donné:
	 		(Protocoles supportés par le programme : ETHERNET, IPV4, TCP, HTTP )
				-> python3 main.py --terminal [chemin vers le fichier(txt)] --protocol=[nom du protocol]

	 	3. Pour visualiser un flot particulier en selectionnant les adresses IP les 2 machines impliquées :
	 		(Adresse IP respecte le format X.X.X.X ou X est une valeur dans l'intervalle : [0-255])
			-> python3 main.py --terminal [chemin vers le fichier(txt)] --adr1=[Adresse IP] --adr2=[Adresse IP]

	 	4. Pour visualiser un flot particulier en selectionnant les adresses IP de 2 machines impliquées et le protocole :
				-> python3 main.py --terminal [chemin vers le fichier(txt)] --protocol=[nom du protocol]
				--adr1=[Adresse IP] --adr2=[Adresse IP]

## Pour la version interface
Afin de lancer WirePoulpe il suffit d'exécuter la commande suivante à la racine de notre dossier :

    1. python3 main.py --interface
    2. Ensuite il suffit de cliquer sur le bouton Import et sélectionner un fichier .txt de trames à visualiser
