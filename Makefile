# compilador C
CC = gcc

# arquivos de cabeçalho
INC = -I./include

# biblioteca estática bidimensional (.a)
LIB_2D = ./lib/libcg2d.a

# biblioteca estática tridimensional (.a)
LIB_3D = ./lib/libcg3d.a

# bibliotecas dinâmicas (.so)
# utilizadas para conversar com o X-Window e biblioteca matemática
LIBS = -lm -lX11 

# Códigos objeto, adicione -g para depuração e
# retire as flags de otimização
# Opções para otimizar o código: -O2 -O3 ou -Ofast 
#CFLAGS = -g -c
CFLAGS = -Ofast -c

# Códigos executáveis, adicione -g para depuração e
# retire as flags de otimização 
# Opções para otimizar o código: -O2 -O3 ou -Ofast
#OFLAGS = -g -o
OFLAGS = -Ofast -o

# define o arquivo objeto que contém os códigos dos exercícios
EFLAG = exercicios.o

all:
	# gera os arquivos objetos (códigos realocáveis)
	#$(CC) $(INC) $(CFLAGS) ./sources/cg2d.c
	#$(CC) $(INC) $(CFLAGS) ./sources/cg3d.c	
	$(CC) $(INC) $(CFLAGS) ./exercicios/exercicios.c
	
	# gera as bibliotecas (estáticas)
	#ar rcs libcg2d.a cg2d.o
	#ar rcs libcg3d.a cg3d.o
	
	# remove os códigos objetos realocáveis
	#rm cg2d.o
	#rm cg3d.o
	
	# move as bibliotecas para a pasta de referência
	#mv libcg2d.a ./lib
	#mv libcg3d.a ./lib	

	# exemplos de códigos utilizando a biblioteca 2D
	$(CC) $(INC) ./examples/bezier.c $(OFLAGS) bezier $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/bolinhas1.c $(OFLAGS) bolinhas1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/bolinhas2.c $(OFLAGS) bolinhas2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)			
	$(CC) $(INC) ./examples/bolinhas3.c $(OFLAGS) bolinhas3 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/bolinhas4.c $(OFLAGS) bolinhas4 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/bolinhas5.c $(OFLAGS) bolinhas5 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)			
	$(CC) $(INC) ./examples/colormaps.c $(OFLAGS) colormaps $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/espiral1.c $(OFLAGS) espiral1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/espiral2.c $(OFLAGS) espiral2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/lemniscatas.c $(OFLAGS) lemniscatas $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)	
	$(CC) $(INC) ./examples/limacons.c $(OFLAGS) limacons $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/poligonos1.c $(OFLAGS) poligonos1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/poligonos2.c $(OFLAGS) poligonos2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)	
	$(CC) $(INC) ./examples/rainbow.c $(OFLAGS) rainbow $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/rosaceas.c $(OFLAGS) rosaceas $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/circulos.c $(OFLAGS) circulos $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/letrinhas.c $(OFLAGS) letrinhas $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/poligonos3.c $(OFLAGS) poligonos3 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/circulo.c $(OFLAGS) circulo $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/elipse.c $(OFLAGS) elipse $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)			

	# exemplos de códigos utilizando a biblioteca 3D		
	$(CC) $(INC) ./examples/prisma1.c $(OFLAGS) prisma1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/prisma2.c $(OFLAGS) prisma2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)	
	$(CC) $(INC) ./examples/prisma3.c $(OFLAGS) prisma3 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/prisma4.c $(OFLAGS) prisma4 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/prisma5.c $(OFLAGS) prisma5 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)	
	$(CC) $(INC) ./examples/prisma6.c $(OFLAGS) prisma6 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/toro1.c $(OFLAGS) toro1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/toro2.c $(OFLAGS) toro2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)	
	$(CC) $(INC) ./examples/esfera.c $(OFLAGS) esfera $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/cone.c $(OFLAGS) cone $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/elipsoide1.c $(OFLAGS) elipsoide1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/elipsoide2.c $(OFLAGS) elipsoide2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/elipsoide3.c $(OFLAGS) elipsoide3 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/elipsoide4.c $(OFLAGS) elipsoide4 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)											
	$(CC) $(INC) ./examples/teapot1.c $(OFLAGS) teapot1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teapot2.c $(OFLAGS) teapot2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teapot3.c $(OFLAGS) teapot3 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teapot4.c $(OFLAGS) teapot4 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teapot5.c $(OFLAGS) teapot5 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teapot6.c $(OFLAGS) teapot6 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teapot7.c $(OFLAGS) teapot7 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)			
	$(CC) $(INC) ./examples/bunny1.c $(OFLAGS) bunny1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/bunny2.c $(OFLAGS) bunny2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)	
	$(CC) $(INC) ./examples/teddy1.c $(OFLAGS) teddy1 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teddy2.c $(OFLAGS) teddy2 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)
	$(CC) $(INC) ./examples/teddy3.c $(OFLAGS) teddy3 $(EFLAG) $(LIB_2D) $(LIB_3D) $(LIBS)					
								
	# remove os arquivos objetos
	rm *.o		

	# move os executáveis dos exemplos para a pasta adequada
	# para executá-los, digite (utilizando o executável bezier como exemplo):
	# cd bin
	# ./bezier
	mv bezier ./bin
	mv bolinhas1 ./bin
	mv bolinhas2 ./bin	
	mv bolinhas3 ./bin
	mv bolinhas4 ./bin
	mv bolinhas5 ./bin			
	mv colormaps ./bin
	mv espiral1 ./bin
	mv espiral2 ./bin
	mv lemniscatas ./bin	
	mv limacons ./bin
	mv poligonos1 ./bin
	mv poligonos2 ./bin
	mv poligonos3 ./bin	
	mv rainbow ./bin
	mv rosaceas ./bin
	mv circulos ./bin
	mv letrinhas ./bin
	mv circulo ./bin
	mv elipse ./bin
	mv prisma1 ./bin
	mv prisma2 ./bin
	mv prisma3 ./bin
	mv prisma4 ./bin
	mv prisma5 ./bin	
	mv prisma6 ./bin
	mv toro1 ./bin
	mv toro2 ./bin	
	mv esfera ./bin
	mv cone ./bin
	mv elipsoide1 ./bin
	mv elipsoide2 ./bin
	mv elipsoide3 ./bin
	mv elipsoide4 ./bin		
	mv teapot1 ./bin
	mv teapot2 ./bin
	mv teapot3 ./bin
	mv teapot4 ./bin
	mv teapot5 ./bin
	mv teapot6 ./bin
	mv teapot7 ./bin			
	mv bunny1 ./bin	
	mv bunny2 ./bin		
	mv teddy1 ./bin	
	mv teddy2 ./bin	
	mv teddy3 ./bin						
		
# depuração da memória alocada
# necessária a flag -g no processo de compilação (retire as flags de otimização)

debug:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./bin/"nome do executavel a ser depurado"

# gdb => https://www.ic.unicamp.br/~rafael/materiais/gdb.html


