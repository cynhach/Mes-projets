from Utils import * 
import Trame
class Trace:
	def __init__(self,data):
		self.listeDeTrames=[]#Liste d'objets trame , ayant tous les champs initialisés
		for trame in data:
			self.listeDeTrames.append(Trame.Trame(trame))

	def analyse(self):
		resuletat=""
		for trame in self.listeDeTrames:
			resuletat+=trame.analyse()
			resuletat+="\n"
		resuletat=resuletat[:-1]
		return resuletat

	def filtre(self,protocol,adressM1,adressM2):
		listeTramProto=[]
		for trame in self.listeDeTrames:
			if not trame.erronee:
				if(protocol=="TCP" and trame.tcp!=None and not trame.tcp.erronee):
					listeTramProto.append(trame)
				elif(protocol=="HTTP" and trame.http!=None and not trame.http.erronee):
					listeTramProto.append(trame)
				elif(protocol=="ETHERNET" and trame.ethernet!=None and not trame.ethernet.erronee):
					listeTramProto.append(trame)
				elif(protocol=="IPV4" and trame.ipv4!=None and not trame.ipv4.erronee):
					listeTramProto.append(trame)

		listeTramAdress=[]
		for trame in self.listeDeTrames:
			if not trame.erronee:
				if trame.ipv4!= None and ((formatIPAdress(trame.ipv4.sourceAdress)==adressM1 and formatIPAdress(trame.ipv4.destinationAdress)==adressM2) or
				(formatIPAdress(trame.ipv4.sourceAdress)==adressM2 and formatIPAdress(trame.ipv4.destinationAdress)==adressM1) ):
					listeTramAdress.append(trame)
		
		result=[]
		if(len(protocol)!=0 and len(adressM1)!=0 and  len(adressM2)!=0):
			result = [trame for trame in listeTramProto if trame in listeTramAdress]
		elif  len(adressM1)==0 and  len(adressM2)==0:
			result=listeTramProto
		elif len(protocol)==0:
			result=listeTramAdress
		
		return result

	def listeTrameTCPetHTTP(self):
		liste=[]
		for trame in self.listeDeTrames:
			if not trame.erronee and (trame.tcp!=None or trame.http!=None):
				liste.append(trame)
		return liste
				