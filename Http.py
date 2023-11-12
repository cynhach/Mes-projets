
import Utils
import csv
PATHREFERENCES = "./referances/"
OUTPUTPATH = "./output/"


with open(PATHREFERENCES+"methodshttp.csv", "r")as httpOp:
    reader=csv.reader(httpOp, delimiter=',')
    httpMethods = []
    for ligne in reader:
        httpMethods.append(ligne[0])

httpOp.close()
HTTPMETHODS=httpMethods


class Http:
    def __init__(self, data):
        self.data = data.upper()
        self.info1, self.info2, self.info3 = "","",""
        self.erronee=False
        self.message=""
        self.lignesEntete =self.analyse(self.data)
        
    
    def analyse(self,data):
        lignes=data.split("0D0A")

        if len(lignes)==0:
            self.erronee=True
        
        first_line = lignes[0].split("20")
        if len(first_line)==3: 
            self.info1=Utils.asciiToString(first_line[0])
            self.info2=Utils.asciiToString(first_line[1])
            self.info3=Utils.asciiToString(first_line[2])
        elif len(first_line)==2:
            self.info1=Utils.asciiToString(first_line[0])
            self.info2=Utils.asciiToString(first_line[1])
        elif len(first_line)==1: 
            self.info1=first_line[0]
        else:
            self.erronee=True
        
        dict={}

        if not self.erronee: 
            lignes=lignes[1:]
            #if len(lignes)!=0: lignes.pop()
            for i in range(len(lignes)):
                if(len(lignes[i])==0):#pour le message , car si on a un "" c'est qu il "etait entre 2 0a0d successifs
                    if(i+1<len(ligne)-1):
                        str=''.join(lignes[i+1:])
                        self.message=Utils.asciiToString(str)
                else:    
                    ligneSplitted=lignes[i].split("20")
                    if(len(ligneSplitted)%2!=0): #Si on a un nom de champs sans sa valeur en effet les 0x20
                                                # separent chaque champs avec sa valeur donc il doit y'avoir 
                                                #un nombre pair de val(cle,val)
                        #self.erronee=True
                        break
                    else:
                        i=0
                        while(i+1<=len(ligneSplitted)-1):
                            if(len(ligneSplitted[i])>0):
                                key=Utils.asciiToString(ligneSplitted[i])
                                value=Utils.asciiToString(ligneSplitted[i+1])
                                dict[key]=value
                            else:
                                #self.erronee=True
                                break
                            
                            i+=2
        return dict

    def get_method(self):
        return self.info1

    def get_versionRes(self):
        return self.info1
    
    def get_url(self):
        return self.info2
    
    def get_code(self):
        return self.info2

    def get_versionReq(self):
        return self.info3

    def get_message(self):
        return self.info3

    def is_request(self,isReq):
        
        if not  isReq in HTTPMETHODS:
            return False
        return True

    def is_response(self,isRes):
        try:
            return isRes.startswith("HTTP/")
        except:
            return False

    def toString(self):
        res = "\nHTTP:"
        if not self.erronee:
            if(self.is_request(self.info1)):
                res += "\n\tRequest\n\t\t Methode : {}\n\t\t URL : {}\n\t\t Version : {}\n". format(self.info1, self.info2,self.info3)
            elif self.is_response(self.info1):
                res += "\n\tResponse\n\t\t Version : {}\n\t\t Code : {}\n\t\t Message : {}\n".format(self.info1, self.info2,self.info3)
            else: 
                self.erronee=True
            for key in self.lignesEntete.keys():
                res+="\n\t\t{} : {} ".format(key,self.lignesEntete.get(key))
        else:
            res+=" Erreur de format au niveau de la COUCHE7 ----> on arrete l'analyse"
        return res
    
    def getMessage(self):
        return "HTTP: {} {} {} ". format(self.info1, self.info2,self.info3)

