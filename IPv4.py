import Utils

PATHREFERENCES = "./referances/"
with open(PATHREFERENCES+"ipProtocoles.txt", "r")as typeProto:
    typeProto.readline()
    types = []
    for line in typeProto:
        split = line.split(" ",1)
        types.append((split[0], split[1].rstrip()))
typeProto.close()

TYPES = dict(types)

class IPv4:
	def __init__(self,data):
		self.ip=data
		self.erronee=False
		self.version=self.ip[0:1]
		self.ihl=self.ip[1:2]
		if Utils.hexToDec(self.ihl)*4>=20 and  Utils.hexToDec(self.ihl)*4<=len(self.ip):
			self.tos=self.ip[2:4]
			self.totalLength=self.ip[4:8]
			self.identification=self.ip[8:12]
			self.flagsAndFragOffset=self.ip[12:16]

			binaire=Utils.hexToBin(self.flagsAndFragOffset)
			binaire=binaire.zfill(16)

			self.R=binaire[0]
			self.DF=binaire[1]
			self.MF=binaire[2]
			self.fragOffset=Utils.binToDec(binaire[3:16])*8


			self.ttl=self.ip[16:18]
			self.protocol=self.ip[18:20]
			self.headerChecksum=self.ip[20:24]
			self.sourceAdress=self.ip[24:32]
			self.destinationAdress=self.ip[32:40]
			#SI on a pas d'option 
			if(int(self.ihl,base=16)==5):
				self.options=""
				#self.padding=""
				self.data=self.ip[40:]
			#40 octets d'options
			else:
				self.options=self.ip[40:int(self.ihl,16)*4*2]#todo padding combien
				#self.padding=self.ip[118:120]
				self.data=self.ip[int(self.ihl,16)*4*2:]
		else:
			self.erronee=True
			



	def analyseOptions(self):
		OPTIONS = {"0":"End of Options List(EOOL)","1":"No Operation(NOP)","7":"Record Route (RR)", "68":"Time Stamp (TS)","131":"Loose Source Route (LSR)","137":"Strict Source Route (SSR)"}
		result="\tOptions contenues: \n"
		offset=0
		try:
			while(offset+2<=len(self.options)):
				option=int(self.options[offset:offset+2],16)

				s=str(option) 
				value = OPTIONS.get(s)
				if(s=="0" or s=="1"):
					result+="\t\t{}: {} \n".format(option,OPTIONS[s])
					offset+=2

				elif value :
					result+="\t\t{}: {} \n".format(option,OPTIONS[s])
					offset+=int(self.options[offset+2:offset+4],16)*2
				else:
					break
		except:
			result+="\t\tType d'option non traité  (Supporté : EOOL,NOP,RR,TS,LSR,SSR)"
			
		if len(result)>len("\tOptions contenues: \n"):
			result=result[:-1]
		else:
				result+="\t\t(Aucune)"
		return result

	def toString(self):
		info="\nInternet Protocol:"
		if not self.erronee:
			info+="\n\tVersion: {}\n\tHeader Length: {} bytes ({})\n".format(
				self.version,Utils.hexToDec(self.ihl)*4,Utils.hexToDec(self.ihl))
			info+="\tDifferentiated Services Filed: {}\n".format("0x"+self.tos)
			info+="\tTotal Length: {}\n".format(Utils.hexToDec(self.totalLength))
			info+="\tIdentification: {} ({})\n".format("0x"+self.identification,Utils.hexToDec(self.identification))
			info+="\tFlags: {} \n \t\tReserved bit: {}\n\t\tDon't fragment: {}\n\t\tMore fragments: {}\n\tFragment offset: {}\n".format("0x"+self.flagsAndFragOffset,self.R,self.DF,self.MF,self.fragOffset)
			info+="\tTime to live: {}\n".format(Utils.hexToDec(self.ttl))
			info+="\tProtocol: {} ({})\n".format(TYPES[self.protocol],Utils.hexToDec(self.protocol))
			info+="\tHeader checksum: {}\n".format("0x"+self.headerChecksum)
			info+="\tSource: {}\n".format(Utils.formatIPAdress(self.sourceAdress))
			info+="\tDestination: {}\n".format(Utils.formatIPAdress(self.destinationAdress))
			info+=self.analyseOptions()
		else:
			info+="Taille annoncée par l'ihl plus grande que la taille du datagrame ! "
		return info
	
	def getMessage(self):
		return "Protocol IPv4,({})".format(TYPES[self.protocol])


"""
ip=IPv4("4500007c3f860000fb0149afc0219f0684e33d0507272884e33c20c02c4112c0464705c0219f02c0219f06c0464706c02c411a84e33c1e84e33d87000000aa562f00000029368c410003862b08090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f3031323334353637")
print(ip.toString())
"""












