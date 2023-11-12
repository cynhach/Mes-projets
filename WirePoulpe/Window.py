import tkinter as tk
from tkinter import ttk

from tkinter import *
from tkinter.filedialog import *
import os 
from Utils import *
from cleanTrame import *

resultatAnalyseTrame="./OutPuts/outPuts.txt"
ANALYSE=None
FILTRE=False

class Window:
    def __init__(self, master):
        self.master = master
        self.analyse=None
        self.master.geometry("950x600")
        self.master.resizable(height=False , width = False)
        self.master.title("WirePoulpe")
        self.master.config(bg = '#F0F0E6')

        # Créer l'image de fond sur notre fenetre
        self.image = tk.PhotoImage(file = "./Image/DALL·E 2022-12-02 13.12.31 - monster octopus.png")
        self.limg = Label(self.master, i = self.image)
        self.limg.place(x = 0, y = 0, relwidth = 1, relheight = 1)

        self.showWidgets()

    def showWidgets(self):
        # Titre page principale 
        self.title = Label(self.master, text = "Bienvenue sur WirePoulpe", font = ('Courier', 20), width = 50, height = 5, bg = '#2C514C', fg = 'black')
        self.title.pack(pady = 50)

        self.frame = tk.Frame(self.master)
        self.frame.pack()

        
        b=self.createButton(self.master,"Import",10,2, lambda: self.openFile())
        b.place(x = 0, y = 0, relwidth = 1, relheight = 1)
        self.explorer = b

        self.explorer.pack()

        b = self.createButton(self.master,"Quit",10,2, lambda : self.closeWindow())
        b.place(x = 0, y = 0, relwidth = 1, relheight = 1)
        self.quit=b
        self.quit.pack()



    def createButton(self,where, text,width,height, command):
        butt = tk.Button(where, text = text, font = ('Courier', 15), width = width, height = height, bg = '#2C514C', command = command)
        return butt

    # Ouvrir un fichier
    def openFile(self):
        self.file = askopenfilename(initialdir= os.getcwd(), title = "Selectionner un fichier .txt", filetypes=(("text files", "*.txt"), ("all files", "*.*")))
        #self.file = tk.filedialog.askopenfilename(initialdir = "~/", title = "Select a file", filetypes = [("Text files", "*.txt*")])
        global ANALYSE
        ANALYSE= getTrace(self.file,resultatAnalyseTrame)
        if ANALYSE !=None:
            self.newWindow(Win2)
        
        

    def newWindow(self, _class):
        global win2
        try:
            if _class == Win2:
                if win2.state() == "normal":
                    win2.focus()
        except:
            win2 = tk.Toplevel(self.master, bg = '#F0F0E6')
            _class(win2)

    def closeWindow(self):
        self.master.destroy()
    def getAnalyse(self):
        return self.analyse

class Win2(Window):
    def __init__(self, master):
        super().__init__(master)
        self.master.title("Visualisateur du trafic réseau -WirePoulpe-")
        self.trames=[]
    def showWidgets(self):
        self.graheFrame = tk.Frame(self.master, width=700 , height=550,bg="green")
        self.filtreBarre = tk.Frame(self.master, bd=1, bg="pink", relief=SUNKEN)
        self.graheFrame.place(x = 5, y = 55 , width=675 , height=525)
        self.filtreBarre.place(height=50, width=950)


        self.ma_var=StringVar()
        self.user_Entry = Entry(self.filtreBarre, bg = "white",textvariable=self.ma_var,width=30,background="white")
        self.user_Entry.grid(row=0,column=0,padx=10)
        self.user_Entry.insert(0,"--protocol= --adr1= --adr2=")

        self.user = Label(self.filtreBarre, text ="---SYNTAXE---  1)--protocol=TCP/HTTP2)--adr1=a1 --adr2=a2\n 3)--protocol=p --adr1=a1 --adr2=a2 (Sans espaceS autour des '='",background="CadetBlue1",relief=SUNKEN,font=('Courier', 9),width=70)
        self.user.grid(row=0,column=1,padx=10,pady=5)

        self.butt=self.createButton(self.filtreBarre,"Valider",10,2, lambda : self.filtreCommande())
        self.butt.grid(row=0,column=2,padx=10)
       
        #Pour afficher les commentaires:
        self.scrollbarx =Scrollbar(self.master, orient=HORIZONTAL)
        self.scrollbary =Scrollbar(self.master, orient=VERTICAL)

        self.commentsBox = Listbox(self.master, xscrollcommand=self.scrollbarx.set,yscrollcommand=self.scrollbary.set,bg="pink",font=('Courier', 10))

        self.scrollbarx.config(command=self.commentsBox.xview)
        self.scrollbary.config(command=self.commentsBox.yview)

        self.scrollbarx.place(x = 685, y = 580, height=15,  width=250)
        self.scrollbary.place(x = 935, y = 55,  height=525, width=15)

        self.commentsBox.place(x = 685 , y = 55, width=250 , height=525)
    
        
       #Pour la partie Graphe
        grapheCanvas = Canvas(self.graheFrame , width=700 , height=510 )
        grapheCanvas.place(x =0, y = 0, width=675 , height=515)
       
        ScrollbarX = ttk.Scrollbar(self.graheFrame, orient=HORIZONTAL , command=grapheCanvas.xview)
        ScrollbarX.pack(side = BOTTOM , fill = "x")
     

        ScrollbarY = ttk.Scrollbar(self.graheFrame, orient=VERTICAL , command=grapheCanvas.yview)
        ScrollbarY.config(command=grapheCanvas.yview)
        ScrollbarX.config(command=grapheCanvas.xview)

        ScrollbarY.pack(side = RIGHT , fill = "y")

        grapheCanvas.configure(xscrollcommand=ScrollbarX.set,yscrollcommand=ScrollbarY.set)
        grapFrame = Frame(grapheCanvas)
 

        global FILTRE
        self.filtre=FILTRE
        global ANALYSE
        if (ANALYSE!=None and not self.filtre):
            self.trames=ANALYSE.listeTrameTCPetHTTP()
        if len(self.trames)!=0:

            adressIps=adIPDistinctes(self.trames)
            if len(adressIps)!=0:
                cpt=0
                l=50
                L=30
                c=490
                C=250
                for ip in adressIps :
                    Label(grapFrame, text =ip,bg="pink" ,padx=200).grid(row=0,column=cpt)
                    grapheCanvas.create_line(C+cpt*c,L,C+cpt*c,L+len(self.trames)*l, dash = (3, 2))
                    cpt+=1

 
                self.commentsBox.insert(END,"\t       ***Comments***\n")
                self.commentsBox.insert(END,"\n\n")

                for i in range (len(self.trames)):
                    self.commentsBox.insert(END,"\n")
                    message="({}) {}".format(str(i+1),self.trames[i].getMsgGraphe())
                    self.commentsBox.insert(END, message)
                    self.commentsBox.insert(END,"\n\n")
                    
                    trame = self.trames[i]
                    ipsource =adressIps.index(formatIPAdress(trame.ipv4.sourceAdress))
                    ipdest = adressIps.index(formatIPAdress(trame.ipv4.destinationAdress))
                    psrc = int("0x"+trame.tcp.srcPort, 16)
                    pdest =int("0x"+trame.tcp.dstPort, 16)

                    if ipsource>ipdest:
                        grapheCanvas.create_line(C+ipsource*c, L+30 + i*l , C+ipdest*c, L+30 + i*l, fill="orange",arrow=tk.LAST)
                        grapheCanvas.create_text(C+ipsource*c+20,L+30+i*l, text =psrc,fill="red")
                        grapheCanvas.create_text(C+ipdest*c-20,L+30+i*l, text =pdest,fill="red")
                        grapheCanvas.create_text(C+ipdest*c+250,L+30+i*l-20, text =message,width=500,justify=CENTER,fill="DodgerBlue4",font=('Courier', 10))
                    else:
                        grapheCanvas.create_line(C+ipsource*c, L+30 + i*l , C+ipdest*c  , L+30+ i*l, fill="orange",arrow=tk.LAST)
                        grapheCanvas.create_text(C+ipsource*c-20,L+30+i*l, text =psrc,fill="red")
                        grapheCanvas.create_text(C+ipdest*c+20,L+30+i*l, text =pdest,fill="red")
                        grapheCanvas.create_text(C+ipsource*c+250,L+30+i*l-20, text =message,width=500,justify=CENTER,fill="DodgerBlue4",font=('Courier', 10))

                    
             
                grapFrame.update()
                grapheCanvas.create_window((5,5) ,window=grapFrame, anchor = NW)
                grapheCanvas.configure(scrollregion=grapheCanvas.bbox(ALL))#au lieu de grapFrame mettre grapheCanvas
 
    #--protocol= --adr1= --adr2=
    def filtreCommande(self):
        aucun=True
        erreurFormat=False
        p=["TCP","HTTP"]
        splitted=self.ma_var.get().strip().split(" ")
        if len(splitted)<1 or len(splitted)>3:
            erreurFormat=True
            #affichier en rouge!
            #todo
        elif len(splitted)==1:#SI y'avat qu'un filtre protocole: ---protocol
            splittedVal=splitted[0].split("=")
            if(len(splittedVal)!=2):
                erreurFormat=True
            else:
                if(splittedVal[0].rstrip()=="--protocol"):
                    try:
                        pro=splittedVal[1].strip().upper()
                        if pro not in p:
                            erreurFormat=True
                        else:
                            global ANALYSE
                            self.trames=filtre(ANALYSE.listeTrameTCPetHTTP(),pro,"","")
                            global FILTRE
                            FILTRE=True
                            aucun=False
                            self.showWidgets()
                    except:
                        erreurFormat=True
                else:
                    erreurFormat=True
        elif len(splitted)==2:#Si --adr1=a1 --adr2=a2
            splittedVal1=splitted[0].split("=")
            splittedVal2=splitted[1].split("=")
            if(len(splittedVal1)!=2 or len(splittedVal2)!=2 ):
                erreurFormat=True
            else:
                if(splittedVal1[0].strip()=="--adr1" and splittedVal2[0].strip()=="--adr2"):
                    self.trames=filtre(ANALYSE.listeTrameTCPetHTTP(),"",splittedVal1[1].strip(" \n"),splittedVal2[1].strip(" \n"))
                    FILTRE=True
                    aucun=False
                    self.showWidgets()
                else:
                    erreurFormat=True
        elif len(splitted)==3:#Si --protocol=p --adr1=a1 --adr2=a2--protocol=http --adr1=192.168.1.19 --adr2=104.124.109.108 
            splittedVal1=splitted[0].split("=")
            splittedVal2=splitted[1].split("=")
            splittedVal3=splitted[2].split("=")
            if(len(splittedVal1)!=2 or len(splittedVal2)!=2 or len(splittedVal3)!=2 ):
                erreurFormat=True
            #--protocol=http --adr1=96.16.122.53 --adr2=192.168.1.44

            else:
                
                if(splittedVal1[0].strip()=="--protocol" and splittedVal2[0].strip()=="--adr1"and splittedVal3[0].strip()=="--adr2"
                and splittedVal1[1].strip()!="" and splittedVal2[1].strip()!=""and splittedVal3[1].strip()!=""):

                    self.trames=filtre(ANALYSE.listeTrameTCPetHTTP(),splittedVal1[1].strip().upper(),splittedVal2[1].strip(" \n"),splittedVal3[1].strip(" \n"))
                    FILTRE=True
                    aucun=False
                    self.showWidgets()
                else:
                    erreurFormat=True                    
        
        if aucun :# si on a mis tous les filtres a null pour ne pas appliquer de filtre!
            FILTRE=False
            self.showWidgets()
