
from Trace import *

cleanTrameFile="./OutPuts/cleanTrames.txt"

def enHexa(test):
	try:
		int("0x"+test,base=16)
		return True
	except:
		return False

def nouvelleTrame(byte):
	try:
		x=int("0x"+byte,base=16)
	except:
		return False
	return x==0


def offsetValide(byte,ancienOffset,byteLu):
	try:
		dec=int("0X"+byte,base=16)
	except:
		return False
	return dec== ancienOffset+byteLu


def outPut (data,fileName):
	with open(fileName,"w") as output: 
		output.write(data)
	output.close()


def getTrace(FileName,resultatAnalyseTrame):
	
	try:
		trameValide=tramesValides(FileName)
		outPut(trameValide,cleanTrameFile) #On ecrit enregistre l'ensemble de nos bonnes trames dans un fichiers cleanTrames
	except:
		print("Veuillez selectionner un fichier existant !")
		return None

	#Aprés avoir enregistrées les trames à traiter, on les récupére du bon fichier(cleanTrames), et on commence :

	#Premiere chose separer les trames en les recuperant sous forme de liste!
	listeDeTrame=[]
	try:
		with open(cleanTrameFile,"r") as fichier:
			contenu=fichier.readlines()

			for line in contenu:
				line=line.rstrip("\n")
				listeDeTrame.append(line)
		fichier.close()
	except:
		print("Etes vous sur d avoir tout creer pour le lancement du programme(fichier cleanTrames.txt manquant :(")
		return None

	#Deuxieme chose on crée notre trace qui contiendra toutes les trames parsées (sous forme de chaines de caracteres)
	#ainsi que la vraie structure trame appropiée à chaqu'un des messages capturés (C'est là qu'on delimite tous les champs)
	trace=None
	if len(listeDeTrame)!=0:   # On verifie qu'il existe bien des trames respectant le format attendu dans le fichier trace lu
		trace=Trace(listeDeTrame)
		resultat=trace.analyse()  #La fonction analyse permet d'initialiser les champs de la trame(champ ethernet, ipv4,tcp et http)
		outPut(resultat,resultatAnalyseTrame)
	return trace	





########################################################################################################
def tramesValides(nameFile):
	trames=""
	trame=""
	numLigne=0
	byteLu=0
	ancienOffset=0
	with open(nameFile,"r") as fichier:
		
		lignes=fichier.readlines()

		for ligne in lignes:
			if(len(ligne)>0):
				ligne=ligne.rstrip("\n")
				ligne=ligne.rstrip(" ")
				ligne=ligne.lstrip(" ")
				

				if(len(ligne)>0):
					trouveEspace=False
					numLigne+=1
					isOffset=True
					erreurDetectee=False#Pour sauter toutes les lignes de trame comportant une erreur!
					splitted=ligne.split(" ")
					#print(splitted)

					#print(splitted)
					for byte in range(len(splitted)):
						#print("{}{}".format(enHexa(splitted[byte]),splitted[byte]))

						if len(splitted[byte])>0 and  not enHexa(splitted[byte]): #on recotre un char diff de 0-9 et de a-f on arrete la selection
							break
						if isOffset:
							isOffset=False
							if(nouvelleTrame(splitted[byte])):
								if(len(trame)>0 and not erreurDetectee):#Si la trame a au la taille min requise(14 octets pour une trame ethernet sans)
									if trames!="":
										trames+="\n"
									trames+=trame
								byteLu=0
								ancienOffset=0
								erreurDetectee=False
								trame=""
							elif erreurDetectee:
								break
							elif offsetValide(splitted[byte],ancienOffset,byteLu) :
								ancienOffset+=byteLu
								byteLu=0
							else:
								if(len(trame)>0 ):
									if(len(trames)!=0):
										trames+="\n"
									trames+=trame
								erreurDetectee=True

								trame=""
								break

						elif byte==1 or byte==2 :#pour les 3 espaces de l'offset
							if splitted[byte]!="":
								erreurDetectee=True
								break
							else:
								continue

						elif splitted[byte]=="":
								break
						elif not erreurDetectee :
							if(len(splitted[byte])==2 and enHexa(splitted[byte])):
								byteLu+=1
								trame+=splitted[byte]
						else:
							break
						
	if(len(trame)>0 and not erreurDetectee):#Si la trame a au la taille min requise
		if trames!="":
			trames+="\n"
		trames+=trame


	fichier.close()


	return trames
