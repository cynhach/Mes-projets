#coding:utf8
from Utils import * 
from Trace import * 
import sys
from cleanTrame import *
from Window import *

resultatAnalyseTrame="./OutPuts/outPuts.txt"

PROTOCOLES=["ETHERNET","IPV4","TCP","HTTP"]

#On extrait a partir du fichier d'entrée toutes les trames qui respectent le bon format !
formatOk=False
aucune=False
nameFileErr=False

if len(sys.argv)==2 and sys.argv[1]=="--interface":
	
	root = tk.Tk()
	app = Window(root)
	root.mainloop()

	formatOk=True

elif "--terminal" in sys.argv:

	if len(sys.argv)>=3 and sys.argv[1]=="--terminal":
		fileName=sys.argv[2]
		trames=[]
		trace=None
		i=0		
		if( len(sys.argv)==4 and len(sys.argv[3].split("=")))==2 and sys.argv[3].split("=")[0]=="--protocol":
			trace=getTrace(fileName,resultatAnalyseTrame)
			if sys.argv[3].split("=")[1] in PROTOCOLES:
				formatOk=True
			if(trace!=None):
				trames=filtre(trace.listeDeTrames,sys.argv[3].split("=")[1],"","")
				print("nbr de trames : {}".format(len(trames)))
				i=1
				
		elif len(sys.argv)==5 and len(sys.argv[3].split("="))==2 and sys.argv[3].split("=")[0]=="--adr1" and len(sys.argv[4].split("="))==2 and sys.argv[4].split("=")[0]=="--adr2":
			trace=getTrace(fileName,resultatAnalyseTrame)
			if(trace!=None):
				trames=filtre(trace.listeDeTrames,"",sys.argv[3].split("=")[1],sys.argv[4].split("=")[1])
				print("nbr de trames : {}".format(len(trames)))
			formatOk=True
				
		elif  len(sys.argv)==6 and len(sys.argv[3].split("="))==2 and sys.argv[3].split("=")[0]=="--protocol" and len(sys.argv[4].split("="))==2 and sys.argv[4].split("=")[0]=="--adr1"and len(sys.argv[5].split("="))==2 and sys.argv[5].split("=")[0]=="--adr2":
			trace=getTrace(fileName,resultatAnalyseTrame)
			formatOk=True

			if(trace!=None):
				trames=filtre(trace.listeDeTrames,sys.argv[3].split("=")[1],sys.argv[4].split("=")[1],sys.argv[5].split("=")[1])
				print("nbr de trames : {}".format(len(trames)))
				i=1
				
		elif len(sys.argv)==3:
			trace=getTrace(fileName,resultatAnalyseTrame)
			if(trace!=None):
				trames=trace.listeDeTrames
			formatOk=True
		
		if formatOk and len(trames)!=0:
			for trame in trames:
				if i==1:
					message=trame.getMsgTerminal(sys.argv[3].split("=")[1])
				else:
					message=trame.getMsgTerminal("")
				if(len(message)!=0):
					if message[0]=="HTTP" or message[0]=="TCP":
						print("{} ,{} :-----------{}----------> {}, {}\n".format(colorise(formatIPAdress(message[1]),0),colorise(str(hexToDec(message[2])),1),colorise(message[3],2),colorise(str(hexToDec(message[5])),1),colorise(formatIPAdress(message[4]),0)))
						#a="{} ,{} :--------------{}-------------> {}, {}\n".format(formatIPAdress(message[1]),hexToDec(message[2]),message[3],hexToDec(message[5]),formatIPAdress(message[4]))
						#outPut(a,resultatAnalyseTrame)
					elif message[0]=="IPV4":
						print("{} :-----------{}----------> {} {}\n".format(colorise(formatIPAdress(message[1]),0),colorise(message[2],2),colorise(formatIPAdress(message[3]),0),colorise(message[4],3)))
					elif message[0]=="ETHERNET":
						print("{} :-----------{}----------> {} {}\n".format(colorise(formatMACAdress(message[1]),4),colorise(message[2],2),colorise(formatMACAdress(message[3]),4),colorise(message[4],3)))
		
		if formatOk and (trace==None or(trace!=None and len(trames)==0)):
			aucune=True


			

if not formatOk and not aucune:					
	print(colorise("Veuillez respecter le format suivant : \n\tRajouter ces 2 options à la commande d'execution pour selectionner: \n\t\t 1)La version termianl :"
	"'--terminal'** \n\t\t 2)La version graphique '--interface'",3))
	
	print(colorise("**Si vous optez pour une version terminal : \n\t 3 Options s'offrent à vous ! Il faudra imperativement resepcter les formats suivants :",3))
	print(colorise("\n\t 1)Pour une analyse simple:\n\t\t->python3 main.py --temrinal [chemin vers le fichier(txt)]",1))
	print(colorise("\n\t 2)Pour présicer un protocol donné:\n\t\t->python3 main.py --temrinal [chemin vers le fichier(txt)] --protocol=[nom du protocol]",1))
	print(colorise("\n\t\t\t->Les protocoles supportés par le programme : ETHERNET , IPV4 , TCP , HTTP ",0))
	print(colorise("\n\t 3)Pour visualiser un flot particulier en selectionnant les adresses IP les 2 machines impliquées :"
	"\n\t\tpython3 main.py --temrinal [chemin vers le fichier(txt)] --adr1=[Adresse IP] --adr2=[Adresse IP]\n\t\t\t->'Adresse IP' respecte"
	" le format X.X.X.X ou X est une valeur dans l'intervalle : [0-255]",1))
	print(colorise("\n\t 4)Pour visualiser un flot particulier en selectionnant les adresses IP les 2 machines impliquées ainsi que le protocole :"
	"\n\t\t->python3 main.py --temrinal [chemin vers le fichier(txt)]  --protocol=[nom du protocol] --adr1=[Adresse IP] --adr2=[Adresse IP]",1))
elif aucune:
	print(colorise("Aucune trame n'a été analysée, Verifiez que votre fichier existe bien et qu'il contient des trames qui respectent le format attendu",1))
	