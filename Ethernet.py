import Utils
import IPv4
PATHREFERENCES = "./referances/"
OUTPUTPATH = "./output/"

with open(PATHREFERENCES+"typeEthernet.txt", "r")as typeEthe:
    typeEthe.readline()
    types = []
    for line in typeEthe:
        split = line.split(" ",1)
        types.append((split[0], split[1].rstrip()))
typeEthe.close()
TYPES = dict(types)


class Ethernet:
	def __init__(self,trame):
		self.erronee=False
		if(len(trame)>=28):
			self.ethernet = trame.upper()
			self.entete = self.ethernet[0:28]
			self.adresseDest = self.ethernet[0:12]
			self.adresseSource = self.ethernet[12:24]
			s= TYPES.get(self.entete[24:28])
			if s!=None:
				self.type = { "Hexadecimal": self.entete[24:28], "Definition": TYPES[self.entete[24:28]]}
				self.data = self.ethernet[28:]
			else:
				self.erronee=True
		else:
			self.erronee=True

			
		

	def toString(self):
		res="Ethernet:"
		if not self.erronee:
			res+="\n\tAdresse MAC Destination: {}\n\tAdresse MAC Source: {}\n\tType (Ox{}): {}".format( 
				Utils.formatMACAdress(self.adresseDest), Utils.formatMACAdress(self.adresseSource), self.type["Hexadecimal"], self.type["Definition"])
		else:
			res+= "Erreur le protocole encapsulé n'existe pas"
		return res

	def getMessage(self):
		return "Ethernet,({})".format(self.type["Definition"])

