//Arquivo de funcoes para funcoes principais

#include "funcoes.h"
#include <math.h>
#include <curses.h>

Record *Inicializa_Record(void){
	Record *rec = (Record *) malloc(sizeof(Record));
	rec->custo_total = 0;
	rec->tempo_de_falha = 0;
	rec->total_geradores = 0;
	rec->total_cidades = 0;
	rec->energia_total_geradores = 0;
	rec->energia_gasta_cidades = 0;
	rec->tamanho_interc = 0;
	rec->numerofalhas = 0;
	rec->cidades_sem_recurso = 0;
	rec->tempo_cidades_sem_recurso = 0;
	rec->cidades_sem_30porcento = 0;
	rec->tempo_sem_30porcento = 0;

	return rec;
}

void Localiza_Paths(Listas *inicio){
	
	assert(inicio != NULL);
	
	
	Record *rec;
	Cidade *aux1;
	Gerador *aux2;
	Interc *aux3;
	Adapter *aux4;
	int i;
	
	rec = inicio->p_record;
	
	aux2 = inicio->p_gerador;
	while(aux2 != NULL){
		
		i = 0;
		aux3 = inicio->p_interc;
		while(aux3 != NULL){
			
			rec->total_geradores++;
			
			if((aux3->pos_inic_x == aux2->pos_x) && (aux3->pos_inic_y == aux2->pos_y)){
				aux3->vem = aux2;
				aux3->vemc = 'G';
				i++;
				aux2->prim = Insere_Irmao(aux3, aux2->prim);
			}
			
			aux3 = aux3->prox;
		}
		aux2->saida = i;
		aux2->works = i;
		
		aux2 = aux2->prox;
	}
	
	aux4 = inicio->p_adapter;
	while(aux4 != NULL){
		
		i = 0;
		aux3 = inicio->p_interc;
		while(aux3 != NULL){
			
			if((aux3->pos_inic_x == aux4->pos_x) && (aux3->pos_inic_y == aux4->pos_y)){
				aux3->vem = aux4;
				aux3->vemc = 'A';
				i++;
				aux4->prim = Insere_Irmao(aux3, aux4->prim);
			}
			else if((aux3->pos_final_x == aux4->pos_x) && (aux3->pos_final_y == aux4->pos_y)){
				aux3->vai = aux4;
				aux3->vaic = 'A';
			}
			
			aux3 = aux3->prox;
		}
		aux4->saida = i;
		aux4->works = i;
		
		aux4 = aux4->prox;
	}
	
	aux3 = inicio->p_interc;
	while(aux3 != NULL){
		
		aux1 = inicio->p_cidade;
		while(aux1 != NULL){
			
			rec->total_cidades++;
			
			if((aux3->pos_final_x == aux1->pos_x) && (aux3->pos_final_y == aux1->pos_y)){
				aux3->vai = aux1;
				aux3->vaic = 'C';
			}
			
			aux1 = aux1->prox;
		}
		aux3 = aux3->prox;
	}
}

Interc *Insere_Irmao(Interc *novo_elem, Interc *top){
	
	assert(novo_elem != NULL);
	
	novo_elem->irmao = top;
	top = novo_elem;
	return top;
}

int Calcula_Cap_Total(Interc *inicio){
	
	assert(inicio != NULL);
	
	Interc *aux = inicio;
	int capacidade_total = 0;
	
	while(aux != NULL){
		if(aux->funciona)
			capacidade_total += aux->capacidade_max;
		aux = aux->irmao;
	}
	return capacidade_total;
}

int Calcula_Rel_Flow(Interc *inicio, int total){
	
//	if(total == 0){
//		printf("\n\ntotal != 0 !!!");
//		getchar();
//		return -1;
//	}
	
	Interc *aux = inicio;
	int i = 0;
	
	while(aux != NULL){
		if((!aux->funciona) || (aux->fluxo >= aux->capacidade_max) || (total == 0))
			aux->rel_flow = 0;
		else
			aux->rel_flow = (float) (aux->capacidade_max) / (total);
		
		aux = aux->irmao;
	}
	return i;
}

int Calcula_Fluxo(void *inicio, char id){
	
	assert(inicio != NULL);
	
	Gerador *gerad = NULL;
	Interc *path = NULL;
	Adapter *adapt = NULL;
	int sobra = 0, rec_disp;
	
	if(id == 'G'){
		gerad = (Gerador *) inicio;
		rec_disp = gerad->recurso_produzido;
		gerad->cheio = 0;
		path = gerad->prim;
		sobra += gerad->sobra;
	}
	else if(id == 'A'){
		adapt = (Adapter *) inicio;
		rec_disp = adapt->fluxo;
		adapt->cheio = 0;
		path = adapt->prim;
		sobra += adapt->sobra;
	}
	else {
		printf("\n\n id nao pode ser == '%c'!!\n\n", id);
		return -1;
	}
	
	while(path != NULL){
		if(path->funciona){
			path->fluxo = (int) round( (path->rel_flow) * (rec_disp) );
			
			if(path->fluxo > path->capacidade_max){
				sobra += path->fluxo - path->capacidade_max;
				path->fluxo = path->capacidade_max;
			}
			
			if(path->fluxo == path->capacidade_max){
				if(id == 'G')
					gerad->cheio++;
				else
					adapt->cheio++;
			}
		}
		else {
			sobra += path->fluxo;
			path->fluxo = 0;
		}
		
		path = path->irmao;
	}
	
	return sobra;
}

void Gerencia_Sobra(void *inicio, char id){
	
	Gerador *gerad = NULL;
	Interc *path = NULL, *aux = NULL;
	Adapter *adapt = NULL;
	int sobra, sobra_saida, tudo_cheio, total;
	int total_funciona, total_cheio;
//	int path_ncheio;
	
	if(id == 'G'){
		gerad = (Gerador *) inicio;
		if(gerad->works == 0){
			gerad->sobra = gerad->recurso_produzido;
			return;
		}
		total = gerad->total;
		total_funciona = gerad->works;
		total_cheio = gerad->cheio;
		sobra_saida = gerad->sobra;
		aux = gerad->prim;
	}
	else if(id == 'A'){
		adapt = (Adapter *) inicio;
		if(adapt->works == 0){
			adapt->sobra = adapt->fluxo;
			return;
		}
		total = adapt->total;
		total_funciona = adapt->works;
		total_cheio = adapt->cheio;
		sobra_saida = adapt->sobra;
		aux = adapt->prim;
	}
	else {
		printf("\n\n id nao pode ser == '%c'!!\n\n", id);
		return;
	}
	
	tudo_cheio = total_funciona == total_cheio;
	
	while((!tudo_cheio) && (sobra_saida != 0)){
		
		total = Calcula_Cap_Total(aux);
		Calcula_Rel_Flow(path, total);
		
		path = aux;
		while(path != NULL){
			path->fluxo += (path->rel_flow) * (sobra_saida);
			//pois o rel_flow dos caminhos cheios/quebrados == 0;
			
			path = path->irmao;
		}
		
		sobra = 0;
		
		path = aux;
		while(path != NULL){
			
			if(path->fluxo > path->capacidade_max){
				sobra += path->fluxo - path->capacidade_max;
				path->fluxo = path->capacidade_max;
				
				total_cheio++;
			}
			path = path->irmao;
		}
		
		sobra_saida = sobra;
		tudo_cheio = total_funciona == total_cheio;
	}
	
	if(id == 'G'){
		gerad->sobra = sobra_saida;
		gerad->cheio = total_cheio;
		gerad->total = total;
	}
	else {
		adapt->sobra = sobra_saida;
		adapt->cheio = total_cheio;
		adapt->total = total;
	}
}

void Fluxo_Adapt(Interc *inicio){
	
	assert(inicio->vai != NULL);
	
	Interc *path = NULL;
	Adapter *adapt = NULL;
	
	path = inicio;
	while(path != NULL){
		
		if(path->vaic == 'A'){
			adapt = (Adapter *) path->vai;
			adapt->fluxo += path->fluxo;
		}
		
		path = path->prox;
	}
}

void Fluxo_City(Interc *inicio, Record *rec){
	
	assert(inicio->vai != NULL);
	
	Interc *path = NULL;
	Cidade *city = NULL;
	
	path = inicio;
	while(path != NULL){
		
		if(path->vaic == 'C'){
			city = (Cidade *) path->vai;
			city->fluxo += path->fluxo;
			
			rec->energia_gasta_cidades += city->fluxo;
		}
		
		path = path->prox;
	}
}

void Verifica_Falhas(Interc *inicio, Record *rec){
	
	Interc *path = NULL;
	Gerador *gerad = NULL;
	Adapter *adapt = NULL;
	float num;
	
	path = inicio;
	while(path != NULL){
		
		num = ((float) rand() / RAND_MAX);
		
		if((path->chance_falha > 0) && (path->chance_falha > num) && (path->funciona)){
			path->funciona = 0;
			path->time_wrk = path->tempo_conserto;
			rec->custo_total += path->custo_conserto;
			rec->tempo_de_falha += path->tempo_conserto;
			rec->numero_de_falhas++;
			
			if(path->vemc == 'G'){
				gerad = (Gerador *) path->vem;
				gerad->works--;
			}
			else {
				adapt = (Adapter *) path->vem;
				adapt->works--;
			}
		}
		path = path->prox;
	}
}

void Maneja_Falhas(Interc *inicio){
	
	Interc *path = NULL;
	Gerador *gerad = NULL;
	Adapter *adapt = NULL;
	
	path = inicio;
	while(path != NULL){
		if(!path->funciona){
			
			path->time_wrk--;
			if(path->time_wrk == 0){
				path->funciona = 1;
				if(path->vemc == 'G'){
					gerad = (Gerador *) path->vem;
					gerad->works++;
				}
				else {
					adapt = (Adapter *) path->vem;
					adapt->works++;
				}
			}
		}
		path = path->prox;
	}
}

void Zera_Fluxo(Listas *inicio){
	
	Cidade *city = NULL;
	Adapter *adapt = NULL;
	Interc *path = NULL;
	
	path = inicio->p_interc;
	while(path != NULL){
		
		path->fluxo = 0;
		path = path->prox;
	}
	
	adapt = inicio->p_adapter;
	while(adapt != NULL){
		
		adapt->fluxo = 0;
		adapt->sobra = 0;
		adapt->total = 0;
		adapt = adapt->prox;
	}
	
	city = inicio->p_cidade;
	while(city != NULL){
		
		city->fluxo = 0;
		city = city->prox;
	}
}

void Distribui_Recursos(Listas *inicio){
	
	assert(inicio != NULL);
	assert(inicio->p_gerador->prim != NULL);
	
	
	Record *rec = NULL;
	Gerador *gerad = NULL;
	Adapter *adapt = NULL;
	
	rec = inicio->p_record;
	Zera_Fluxo(inicio);
	
	Maneja_Falhas(inicio->p_interc);
	Verifica_Falhas(inicio->p_interc, rec);
	
	gerad = inicio->p_gerador;
	while(gerad != NULL){
		
		rec->custo_total += gerad->custo_gerador;
		rec->energia_total_geradores += gerad->recurso_produzido;
		
		gerad->total = Calcula_Cap_Total(gerad->prim);
		
		Calcula_Rel_Flow(gerad->prim, gerad->total);
		gerad->sobra = Calcula_Fluxo(gerad, 'G');
		
		if(gerad->sobra > 0)
			Gerencia_Sobra(gerad, 'G');
		
		gerad = gerad->prox;
	}
	
	Fluxo_Adapt(inicio->p_interc);
	
	adapt = inicio->p_adapter;
	while(adapt != NULL){
		
		adapt->total = Calcula_Cap_Total(adapt->prim);
		
		Calcula_Rel_Flow(adapt->prim, adapt->total);
		adapt->sobra = Calcula_Fluxo(adapt, 'A');
		
		if(adapt->sobra > 0)
			Gerencia_Sobra(adapt, 'A');
		
		adapt = adapt->prox;
	}
	
	Fluxo_City(inicio->p_interc, rec);
	
	rec->tempo_total++;
}

float Tamanho_Interc(Interc *inicio){
	
	Interc *path = NULL;
	int x, y;
	float tam = 0;
	
	path = inicio;
	while(path != NULL){
		
		x = path->pos_inic_x - path->pos_final_x;
		y = path->pos_inic_y - path->pos_final_y;
		
		tam += sqrt(pow(x, 2) + pow(y, 2));
		
		path = path->prox;
	}
	
	return tam;
}

void Relatorio(Listas *inicio){
	
	Record *rec = inicio->p_record;
	Interc *path = inicio->p_interc;
	
	FILE* arq;
	arq = fopen("Relatorio.txt","w+");
	
	rec->tamanho_interc = Tamanho_Interc(path);
	
	fprintf(arq, "Tempo total de simulacao: %d\n", rec->tempo_total);
	fprintf(arq, "Custo total da simulacao: %d\n", rec->custo_total);
	fprintf(arq, "Total de geradores: %d\n", rec->total_geradores);
	fprintf(arq, "Energia total gerada: %d\n", rec->energia_total_geradores);

	fprintf(arq, "Total de cidades: %d\n", rec->total_cidades);
	fprintf(arq, "Energia total gasta pelas cidades: %d\n", rec->energia_gasta_cidades);
	
	fprintf(arq, "Tamanho total das interconexoes: %d\n", rec->tamanho_interc);
	fprintf(arq, "Numero de falhas nas interconexoes: %d\n", rec->numero_de_falhas);
	fprintf(arq, "Numero de cidades que ficaram sem recurso necessario: %d\n", rec->cidades_sem_recurso);
	fprintf(arq, "Tempo que ficaram sem recurso: %d\n",rec->tempo_cidades_sem_recurso);
	fprintf(arq, "Numero de cidades que ficaram com menos de 30%% dos recursos: %d\n", rec->cidades_sem_30porcento);
	fprintf(arq, "Tempo que ficaram com menos de 30%% de recurso: %d\n",rec->tempo_sem_30porcento);


	fclose(arq);

}

void Interface_Grafica(Listas* inicio){
	assert(inicio != NULL);
	assert(inicio->p_cidade != NULL);
	assert(inicio->p_gerador != NULL);
	assert(inicio->p_interc != NULL);
	assert(inicio->p_adapter != NULL);
	int i = 1, j = 0, espera = 0;
	Cidade *aux1 = NULL;
	Gerador *aux2 = NULL;
	Interc *aux3 = NULL;
	Adapter *aux4 = NULL;
	initscr();  
	 start_color(); //Esta funcao torna possivel o uso das cores
//Abaixo estamos definindo os pares de cores que serao utilizados no programa
    init_pair(1,COLOR_GREEN,COLOR_BLACK ); //Texto(Branco) | Fundo(Azul)
    init_pair(2,COLOR_RED,COLOR_BLACK );
    init_pair(3,COLOR_YELLOW,COLOR_BLACK );
 bkgd(COLOR_PAIR(1));  /*Aqui nos definiremos que a cor de fundo do nosso
                                      programa sera azul e a cor dos textos sera branca.*/
	move (0,0);
	printw("Os geradores, adapatadores e cidades representados estao todos conectados!Pressione Enter para sair...");
	aux3 = inicio->p_interc;
	while (aux3 != NULL){ 
		if (aux3->vemc == 'G'){
			attroff(COLOR_PAIR(2));
			attroff(COLOR_PAIR(3));
			aux2 = (Gerador*) aux3->vem;
			move(aux2->pos_x,aux2->pos_y);
			printw("G\t", i);
		}else if (aux3->vemc == 'A'){
			aux4 = (Adapter*)aux3->vem;
			if(aux3->funciona == 0 && aux4->saida == 2) attron(COLOR_PAIR(2));
			else attroff(COLOR_PAIR(2));
			move(aux4->pos_x,aux4->pos_y);
			printw("A\t", i);
		}
		if (aux3->vaic == 'A'){
			aux4 = (Adapter*)aux3->vai;
			if(aux3->funciona == 0 && aux4->saida == 2) attron(COLOR_PAIR(2));
			else attroff(COLOR_PAIR(2));
			move(aux4->pos_x,aux4->pos_y);
			printw("A\t", i);
		}else if (aux3->vaic == 'C'){
			aux1 = (Cidade*) aux3->vai;
			if (aux3->vemc == 'A' && aux3->funciona == 0 && aux4->saida == 2) attron(COLOR_PAIR(3));
			else attroff(COLOR_PAIR(3));
			move(aux1->pos_x,aux1->pos_y);
			printw("C\t", i);
		}
		aux3 = aux3->prox;
		i++;
	}  	
	refresh();    //Atualiza a tela
	for ( int c = 1 ; c <= 15000 ; c++ )
       	for (int d = 1 ; d <= 15000 ; d++ )
       	{}
	endwin();	
}

