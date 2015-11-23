NOME2 = interface

CODIGO1 = leitura.c
CODIGOT1 = TesteAutomatizado.c
CODIGO2 = funcoes.c

ARQUIVOS = $(CODIGO1) $(CODIGOT1) $(CODIGO2)

OBJETOS = leitura.o TesteAutomatizado.o funcoes.o  

DIRINCLUDE = -I ../include
DIRLIB = -L ../lib
DIROBJ = ../src/obj
DIRGCNO = ../src/gcda_gcno
DIRGCOV = ../src/gcov
PARLIB = -lgtest -lgtest_main -lpthread -lm -lcurses
FLAGS = -fprofile-arcs -ftest-coverage

COMPILADOR = g++

all:	link link1 compile1 executar GCOV organizar CPPCHECK

link:	$(ARQUIVOS)
	@clear
	@clear
	@echo "\n ** LINKANDO TESTE DA INTERFACE GRAFICA **\n"	
	@$(COMPILADOR) -c $(ARQUIVOS) $(DIRINCLUDE) $(FLAGS)

link1: $(ARQUIVOS)
	@echo "\n ** LINKANDO TESTE AUTOMATIZADO **\n"	
	@$(COMPILADOR) -c $(ARQUIVOS) $(DIRINCLUDE) $(FLAGS)

compile1: $(ARQUIVOS)
	@echo "\n ** COMPILANDO TESTE AUTOMATIZADO **\n"
	@$(COMPILADOR) $(OBJETOS) $(DIRINCLUDE) $(DIRLIB) $(PARLIB) $(FLAGS) -o $(NOME2)

organizar: $(DIROBJ)
	@echo "\n ** ORGANIZANDO ARQUIVOS **\n"
	@mv *.o $(DIROBJ)
	@mv *.gcda $(DIRGCNO)
	@mv *.gcno $(DIRGCNO)
	@mv *.gcov $(DIRGCOV)

executar: $(NOME2)
	@echo "\n\n ******** TESTE AUTOMATIZADO ********\n\n" 
	@./$(NOME2)

GCOV: $(CODIGO1) $(CODIGOT1) $(CODIGO2) $(CODIGOT2)
	@echo "\n\n ************************************************** \n"
	@echo " **************** RESULTADO GCOV ***************** \n"
	@echo " ************************************************** \n"
	@echo "\n\n ******** leitura.c ******** \n\n"
	@gcov $(CODIGO1)
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

