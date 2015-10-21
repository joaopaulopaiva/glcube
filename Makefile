#	Universidade Federal de Sao Joao del Rei - UFSJ
#	Ciência da Computação
#
#	João Paulo de Paiva Silva

COMPILADORC = gcc
EXECNAME = cubegl



all :
	$(COMPILADORC) cubegl.c -lGL -lGLU -lglut -o $(EXECNAME) 
run:
	./$(EXECNAME)
clean:
	rm -rf $(EXECNAME)
