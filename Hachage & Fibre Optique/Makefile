CFLAGS  =	-Wall -Wextra -Werror

CC      =	gcc

# EXEC    =	projet
EXEC1    =	ReconstitueReseau
EXEC2    =	ChaineMain
EXEC3    =	ReseauMain
EXEC4    =	speedtest6_1
EXEC5    =	speedtest6_3

all     :	$(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)


OBJS	=	${SRCS:.c=.o}

SRCS	=	gestionChaine.c gestionReseau.c gestionGraphe.c\
			Chaine.c        Reseau.c\
			mesureChaine.c  mesureReseau.c\
			SVGwriter.c\
			Hachage.c\
			ArbreQuat.c gestionArbreQuat.c\
			Graphe.c\
			Struct_File.c Struct_Liste.c\
			testFunction.c 
			# ReconstitueReseau.c
			# ChaineMain.c
			# ReseauMain.c
			# speedtest6_1.c
			# speedtest6_3.c

# projet :	$(OBJS)
# 			$(CC) -o $@ $(CFLAGS) $^ -lm 

	
$(EXEC1) :	$(OBJS) ReconstitueReseau.c
			$(CC) -o $@ $(CFLAGS) $^ -lm 

$(EXEC2) :	$(OBJS) ChaineMain.c
			$(CC) -o $@ $(CFLAGS) $^ -lm 

$(EXEC3) :	$(OBJS) ReseauMain.c
			$(CC) -o $@ $(CFLAGS) $^ -lm 

$(EXEC4) :	$(OBJS) speedtest6_1.c
			$(CC) -o $@ $(CFLAGS) $^ -lm 

$(EXEC5) :	$(OBJS) speedtest6_3.c
			$(CC) -o $@ $(CFLAGS) $^ -lm 

%.o		:	%.c %.h
			$(CC)  $(GCC_FLAGS) -c  $< 

clean	:
			rm -f *.o

fclean	:	clean
			rm $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

re		:	clean all

.PHONY  :   all clean
