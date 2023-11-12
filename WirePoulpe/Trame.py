
import Ethernet
import IPv4
import Tcp
import Http
from Utils import hexToDec
class Trame:
	id=1
	def __init__(self, ligne):
		self.trame=ligne.upper()
		self.erronee=False
		self.id = Trame.id
		self.ethernet=None
		self.ipv4=None
		self.tcp=None
		self.http=None
		Trame.id += 1



	def analyse(self):
		resuletatString=""
		if(self.id!=1):
			resuletatString+="\n\n\n"

		resuletatString+="********************Trame numero {}********************\n".format(self.id)
		suite=""
		if (len(self.trame)>=28):

			self.ethernet=Ethernet.Ethernet(self.trame)
			suite+=self.ethernet.toString()
			if( not self.ethernet.erronee and self.ethernet.type["Hexadecimal"]=="0800"):
				if(len(self.ethernet.data)>=40):
					self.ipv4=IPv4.IPv4(self.ethernet.data)
					suite+=self.ipv4.toString()

					if  not self.ipv4.erronee:
						if hexToDec(self.ipv4.protocol)==6 :
							if len(self.ipv4.data)>=40:
								self.tcp=Tcp.Tcp(self.ipv4.data)
								suite+=self.tcp.toString()


								if(not self.tcp.erronee and ((hexToDec(self.tcp.dstPort)==80 or hexToDec(self.tcp.srcPort)==80 )or (hexToDec(self.tcp.dstPort)==80 or hexToDec(self.tcp.srcPort)==80))and len(self.tcp.data)>0): #Remplacer 80

									self.http =Http.Http(self.tcp.data)
									suite+=self.http.toString()

									if self.http.erronee:
										self.http=None
									


								elif self.tcp.erronee:
									self.erronee=True
								
							else:
								self.erronee=True
						else:
							#self.erronee=True
							suite+="\nProtocole encapsulé dans le paquest ip non traité ---->( Pas d'analyse au niveau de la COUCHE 4)"
					else:
						self.erronee=True
				else:	
					self.erronee=True
					suite+="\nLa taille du paquet ip est trop petite ---->( Pas d'analyse au niveau de la COUCHE 3)"
			else:
				if self.ethernet.erronee:
					self.erronee=True
				else:
					suite+="\nProtocole encapsulé  dans la trame ethernet non traité ---->( Pas d'analyse au niveau de la COUCHE 3)"
		else:
			self.erronee=True
			suite+="\n Trame de longeur insuffisante ---->( Pas d'analyse au niveau de la COUCHE2 )"

		resuletatString+=suite
		return (resuletatString)

	def toString(self):
		result="Trame numero {}:\n".format(self.id)
		if Ethernet!=None:
			result+=self.ethernet.toString()
			result+="\n"
			if self.ipv4!=None:
				result+=self.ipv4.toString()
				result+="\n"
				if self.tcp!=None:
					result+=self.tcp.toString()
					result+="\n"
				if self.http!=None:
					result+=self.http.toString()

		result=result[:-1]
		return result


	def getMsgGraphe(self):
		message=""
		if not self.erronee:
			if self.http!=None:
				message=self.http.getMessage()
			elif self.tcp!=None:
				message=self.tcp.getMessage()
		return message

	def getMsgTerminal(self,proto):
		message=[]
		if (proto=="" or proto=="HTTP") and self.http!=None and not self.http.erronee:
			message.append("HTTP")
			message.append(self.ipv4.sourceAdress)
			message.append(self.tcp.srcPort)
			message.append(self.http.getMessage())
			message.append(self.ipv4.destinationAdress)
			message.append(self.tcp.dstPort)
		elif (proto=="" or proto=="TCP") and  self.tcp!=None and not self.tcp.erronee:
			message.append("TCP")
			message.append(self.ipv4.sourceAdress)
			message.append(self.tcp.srcPort)
			message.append(self.tcp.getMessage())
			message.append(self.ipv4.destinationAdress)
			message.append(self.tcp.dstPort)
			
		elif (proto=="" or proto=="IPV4") and self.ipv4!=None and not self.ipv4.erronee:
			message.append("IPV4")
			message.append(self.ipv4.sourceAdress)
			message.append(self.ipv4.getMessage())
			message.append(self.ipv4.destinationAdress)
			if self.tcp==None:
				if self.erronee:
					message.append("(Trame erronée au niveau TCP)")
				else:
					message.append("(Protocol non supporté)")
			else:
				message.append("")
		elif (proto=="" or proto=="ETHERNET")  and self.ethernet!=None and not self.ethernet.erronee:
			message.append("ETHERNET")
			message.append(self.ethernet.adresseSource)
			message.append(self.ethernet.getMessage())
			message.append(self.ethernet.adresseDest)
			if self.ipv4==None:
				if self.erronee:
					message.append("(Trame erronée au niveau IP)")
				else:
					message.append("(Protocol non supporté)")
			else:
				message.append("")
			
		return message
		
