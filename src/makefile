NOME = teste_automatizado
NOME2 = interface

CODIGO1 = leitura.c
CODIGOT1 = TesteAutomatizado.c
CODIGO2 = funcoes.c
CODIGOT2 = main.c

ARQUIVOS = $(CODIGO1) $(CODIGOT1) $(CODIGO2)
ARQUIVOS2 = $(CODIGO1) $(CODIGOT2) $(CODIGO2)

OBJETOS = leitura.o TesteAutomatizado.o funcoes.o 
OBJETOS2 = main.o leitura.o funcoes.o 

DIRINCLUDE = -I ../include
DIRLIB = -L ../lib
DIROBJ = ../src/obj
DIRGCNO = ../src/gcda_gcno
DIRGCOV = ../src/gcov
PARLIB = -lgtest -lgtest_main -lpthread -lm -lcurses
FLAGS = -fprofile-arcs -ftest-coverage

COMPILADOR = g++

all:	link link1 compile compile1 executar2 executar GCOV organizar CPPCHECK

link:	$(ARQUIVOS2)
	@clear
	@clear
	@echo "\n ** LINKANDO TESTE DA INTERFACE GRAFICA **\n"	
	@$(COMPILADOR) -c $(ARQUIVOS2) $(DIRINCLUDE) $(FLAGS)

compile: $(ARQUIVOS2)
	@echo "\n ** COMPILANDO TESTE AUTOMATIZADO **\n"
	@$(COMPILADOR) $(OBJETOS2) $(DIRINCLUDE) $(DIRLIB) $(PARLIB) $(FLAGS) -o $(NOME2)

link1: $(ARQUIVOS)
	@echo "\n ** LINKANDO TESTE AUTOMATIZADO **\n"	
	@$(COMPILADOR) -c $(ARQUIVOS) $(DIRINCLUDE) $(FLAGS)

compile1: $(ARQUIVOS)
	@echo "\n ** COMPILANDO TESTE AUTOMATIZADO **\n"
	@$(COMPILADOR) $(OBJETOS) $(DIRINCLUDE) $(DIRLIB) $(PARLIB) $(FLAGS) -o $(NOME)

organizar: $(DIROBJ)
	@echo "\n ** ORGANIZANDO ARQUIVOS **\n"
	@mv *.o $(DIROBJ)
	@mv *.gcda $(DIRGCNO)
	@mv *.gcno $(DIRGCNO)
	@mv *.gcov $(DIRGCOV)

executar: $(NOME)
	@echo "\n\n ******** TESTE AUTOMATIZADO ********\n\n" 
	@./$(NOME)

executar2: $(NOME2)
	@echo "\n\n ******** TESTE DA INTERFACE GRAFICA ********\n\n" 
	@./$(NOME2)

GCOV: $(CODIGO1) $(CODIGOT1) $(CODIGO2) $(CODIGOT2)
	@echo "\n\n ************************************************** \n"
	@echo " **************** RESULTADO GCOV ***************** \n"
	@echo " ************************************************** \n"
	@echo "\n\n ******** leitura.c ******** \n\n"
	@gcov $(CODIGO1)
	@echo "\n\n ******** main.c ******** \n\n"
	@gcov $(CODIGOT1)
	@echo "\n\n ******** funcoes.c ******** \n\n"
	@gcov $(CODIGO2)

clean:
	@echo "\n ** LIMPANDO PASTAS **\n"
	@rm -f $(DIRGCNO)/*.gcda 
	@rm -f $(DIRGCNO)/*.gcno 
	@rm -f $(DIRGCOV)/*.gcov  
	@rm -f $(DIROBJ)/*.o

CPPCHECK:
	@echo "\n\n ******** CPPCHECK DO TESTE AUTOMATIZADO ******** \n\n"
	cppcheck $(ARQUIVOS)
	@echo "\n ~~~~~~~~~~~~~FIM MAKEFILE~~~~~~~~~~~~~ \n\n"

