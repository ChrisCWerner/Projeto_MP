//Arquivo de funcoes para funcoes principais

#include "funcoes.h"
#include <math.h>


Record *Inicializa_Record(void){
	Record *rec = (Record *) malloc(sizeof(Record));
	rec->numero_de_falhas = 0;
	rec->tempo_de_falha = 0;
	rec->custo_total = 0;
	rec->tempo_total = 0;
	rec->total_geradores = 0;
	rec->total_cidades = 0;
	rec->energia_total_geradores = 0;
	rec->energia_gasta_cidades = 0;
	rec->tamanho_interc = 0;
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
	
	Examina_Cidades(inicio);
	
	rec->tempo_total++;
}

void Examina_Cidades(Listas *inicio){
	
	Record *rec = inicio->p_record;
	Cidade *city = inicio->p_cidade;
	
//	int segundocontado = 0, segundocontado30 = 0;

	while(city != NULL){
		
		if(city->fluxo < city->recurso_necessario){
//			if(segundocontado == 0){
				rec->tempo_cidades_sem_recurso++;
//				segundocontado = 1;
//			}
			if(city->sem_rec == 0){
				city->sem_rec = 1;
				rec->cidades_sem_recurso++;
			}
		}
		if(city->fluxo < 0.3*city->recurso_necessario){
//			if(segundocontado30 == 0){
				rec->tempo_sem_30porcento++;
//				segundocontado30 = 1;
//			}
	
			if(city->sem_rec < 2){
				city->sem_rec = 2;
				rec->cidades_sem_30porcento++;
			}
		}
		city = city->prox;
	}
}

void Total_Elementos(Listas *inicio){
	
	Record *rec = inicio->p_record;
	Gerador *gerad = inicio->p_gerador;
	Cidade *city = inicio->p_cidade;
	
	while(gerad != NULL){
		rec->total_geradores++;
		gerad = gerad->prox;
	}
	
	while(city != NULL){
		rec->total_cidades++;
		city = city->prox;
	}
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
	arq = fopen("Relatorio.txt","w");
	
	rec->tamanho_interc = Tamanho_Interc(path);
	Total_Elementos(inicio);
	
	fprintf(arq, "Tempo total de simulacao: %d segundos.\n", rec->tempo_total);
	fprintf(arq, "Custo total da simulacao: %d\n", rec->custo_total);
	fprintf(arq, "Total de geradores: %d\n", rec->total_geradores);
	fprintf(arq, "Energia total gerada: %d\n", rec->energia_total_geradores);
	
	fprintf(arq, "Total de cidades: %d\n", rec->total_cidades);
	fprintf(arq, "Energia total gasta pelas cidades: %d\n", rec->energia_gasta_cidades);
	
	fprintf(arq, "Tamanho total das interconexoes: %.2f\n", rec->tamanho_interc);
	fprintf(arq, "Numero de falhas nas interconexoes: %d\n", rec->numero_de_falhas);
	fprintf(arq, "Numero de cidades que ficaram sem recurso necessario: %d\n", rec->cidades_sem_recurso);
	fprintf(arq, "Tempo que ficaram sem recurso: %d segundos.\n",rec->tempo_cidades_sem_recurso);
	fprintf(arq, "Numero de cidades que ficaram com menos de 30%% dos recursos: %d\n", rec->cidades_sem_30porcento);
	fprintf(arq, "Tempo que ficaram com menos de 30%% de recurso: %d segundos.\n",rec->tempo_sem_30porcento);
	
	fclose(arq);
}


void putpixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    int offset = y * surface->w + x;
    Uint32 color = SDL_MapRGB(surface->format, r, g, b);

    if(surface->format->BytesPerPixel == 1)
        *( ((Uint8*)surface->pixels) + offset) = color;
    else if(surface->format->BytesPerPixel == 2)
        *( ((Uint16*)surface->pixels) + offset) = color;
    else
        *( ((Uint32*)surface->pixels) + offset) = color;
}

void cria_linha_vertical(int xi, int yc, int xf, SDL_Surface*tela, int condicao) {
	int i;
	if (xi < xf) {
		for (i = xi; i <= xf; i++){
			if (condicao == 1) putpixel(tela, i, yc, 0, 255, 0);
			else putpixel(tela, i, yc, 255, 0, 0);  
			SDL_UpdateRect(tela, i, yc, 1, 1); 
		}
	}
	else {
		for (i = xf; i <= xi; i--) {
			if (condicao == 1) putpixel(tela, i, yc, 0, 255, 0);
			else putpixel(tela, i, yc, 255, 0, 0);
			SDL_UpdateRect(tela, i, yc, 1, 1); 
		}  
	}	
}
	
void cria_linha_horizontal(int xc, int yi, int yf,SDL_Surface*tela, int condicao) {
	int i;
	if (yi < yf) {
		for (i = yi; i <= yf; i++){
			if (condicao == 1) putpixel(tela, xc, i, 0, 255, 0);
			else putpixel(tela, xc, i, 255, 0, 0); 
			SDL_UpdateRect(tela, xc, i, 1, 1); 
		} 
	}
	else {
		for (i = yf; i <= yi; i--){
			if (condicao == 1) putpixel(tela, xc, i, 0, 255, 0);
			else putpixel(tela, xc, i, 255, 0, 0);
			SDL_UpdateRect(tela, xc, i, 1, 1);
		}   
	}
}

void cria_linha_diagonal(int xi, int xf, int yi, int yf, SDL_Surface*tela, int condicao) {
	int i = 0, j = 0;
	if (xi < xf && yi < yf){
		i = xi; j = yi;
		while (i < xf || j < yf){
			if (i < xf && j < yf) {
				i++; j++;
				if (condicao == 1) putpixel(tela, i, j, 0, 255, 0);
				else putpixel(tela, i, j, 255, 0, 0);
				SDL_UpdateRect(tela, i, j, 1, 1);   
			}else if (i == xf && j < yf){
				cria_linha_horizontal(i, j, yf,tela, condicao);
				return;
			}else if (j == yf && i < xf){
				cria_linha_vertical(i,j,xf,tela, condicao);
				return;
			}
		}
		return;
	}else if(xi > xf && yi > yf){
		i = xf; j = yf;
		while (i < xi || j < yi){
			if (i < xi && j < yi) {
				i++; j++;
				if (condicao == 1) putpixel(tela, i, j, 0, 255, 0);
				else putpixel(tela, i, j, 255, 0, 0);
				SDL_UpdateRect(tela, i, j, 1, 1);   
			}else if (i == xi && j < yi){
				cria_linha_horizontal(i, j, yi,tela, condicao);
				return;
			}else if (j == yi && i < xi){
				cria_linha_vertical(i,j,xi,tela, condicao);
				return;
			}
		}
		return;
	}else if(xi < xf && yi > yf){
		i = xi; j = yf;
		while (i < xf || j < yi){
			if (i < xf && j < yi) {
				i++; j++;
				if (condicao == 1) putpixel(tela, i, j, 0, 255, 0);
				else putpixel(tela, i, j, 255, 0, 0);
				SDL_UpdateRect(tela, i, j, 1, 1);   
			}else if (i == xf && j < yi){
				cria_linha_horizontal(i, j, yi,tela, condicao);
				return;
			}else if (j == yi && i < xf){
				cria_linha_vertical(i,j,xf,tela, condicao);
				return;
			}
		}
		return;
	}else if(xi > xf && yi < yf){
		i = xf; j = yi;
		while (i < xi || j < yf){
			if (i < xi && j < yf) {
				i++; j++;
				if (condicao == 1) putpixel(tela, i, j, 0, 255, 0);
				else putpixel(tela, i, j, 255, 0, 0);
				SDL_UpdateRect(tela, i, j, 1, 1);   
			}else if (i == xi && j < yf){
				cria_linha_horizontal(i, j, yf,tela, condicao);
				return;
			}else if (j == yf && i < xi){
				cria_linha_vertical(i,j,xi,tela, condicao);
				return;
			}
		}
		return;
	}
}

/*******************************************************************************************************************************
* Nome da função: Interface_Grafica;
* Descrição: Responsável por criar a janela da interface gráfica da simulação;
* Assertivas de Entrada:
*			Listas != NULL;
* Assertivas de saída: Nenhuma;
*********************************************************************************************************************************/
void Interface_Grafica(Listas* inicio){	
	assert(inicio != NULL);
	assert(inicio->p_cidade != NULL);
	assert(inicio->p_gerador != NULL);
	assert(inicio->p_interc != NULL);
	assert(inicio->p_adapter != NULL);
	int i = 1, j = 0, condicao, q = 0;
	Cidade *aux1 = NULL;
	Gerador *aux2 = NULL;
	Interc *aux3 = NULL;
	Adapter *aux4 = NULL;
	//ponteiro para a tela do SDL:
	SDL_Surface *tela;
	//Inicializando a SDL:
	SDL_Init( SDL_INIT_EVERYTHING ); 
	//atribuindo um nome a janela:
	SDL_WM_SetCaption("Interface da simulação", NULL); 
	//Definindo as propriedades da tela:
	tela = SDL_SetVideoMode(1280,1280,16, SDL_SWSURFACE); 
	if(SDL_MUSTLOCK(tela)) SDL_LockSurface(tela);
	aux3 = inicio->p_interc;

	while (aux3 != NULL){ 
		if (aux3->vemc == 'G'){
			aux2 = (Gerador*) aux3->vem;
			SDL_Rect drect = {aux2->pos_x, aux2->pos_y, 12, 12};
			Uint32 color = SDL_MapRGB(tela->format, 255, 127, 0);
			SDL_FillRect(tela, &drect, color);
			SDL_UpdateRect(tela, aux2->pos_x, aux2->pos_y, 12, 12);  
		}else if (aux3->vemc == 'A'){
			aux4 = (Adapter*)aux3->vem;
			SDL_Rect drect = {aux4->pos_x, aux4->pos_y, 12, 12};
			Uint32 color = SDL_MapRGB(tela->format, 168, 168, 168);
			SDL_FillRect(tela, &drect, color);
			SDL_UpdateRect(tela, aux4->pos_x, aux4->pos_y, 12, 12); 
		}
		if (aux3->vaic == 'A'){
			aux4 = (Adapter*)aux3->vai;
			SDL_Rect drect = {aux4->pos_x, aux4->pos_y, 12, 12};
			Uint32 color = SDL_MapRGB(tela->format, 168, 168, 168);
			SDL_FillRect(tela, &drect, color);
			SDL_UpdateRect(tela, aux4->pos_x, aux4->pos_y, 12, 12); 
		}else if (aux3->vaic == 'C'){
			Uint32 color;
			aux1 = (Cidade*) aux3->vai;
			SDL_Rect drect = {aux1->pos_x, aux1->pos_y, 12, 12};
			if(aux1->fluxo >= aux1->recurso_necessario)		
				color = SDL_MapRGB(tela->format, 0, 255, 0);
			else if(aux1->fluxo <= aux1->recurso_necessario && aux1->fluxo > 0.3*aux1->recurso_necessario)		
				color = SDL_MapRGB(tela->format, 255, 200, 0);
			else if(aux1->fluxo <= 0.3*aux1->recurso_necessario)			
				color = SDL_MapRGB(tela->format, 255, 0, 0);

			
			SDL_FillRect(tela, &drect, color);
			SDL_UpdateRect(tela, aux1->pos_x, aux1->pos_y, 12, 12);  
		}		
		if (aux3->funciona == 1) condicao = 1;
		else condicao = 0;
	
		if (aux3->pos_inic_x == aux3->pos_final_x){
			cria_linha_horizontal(aux3->pos_inic_x, aux3->pos_inic_y, aux3->pos_final_y,tela, condicao);
		}else if (aux3->pos_inic_y == aux3->pos_final_y){
			cria_linha_vertical(aux3->pos_inic_x, aux3->pos_inic_y, aux3->pos_final_x,tela, condicao);
		}
		if (aux3->pos_inic_x != aux3->pos_final_x || aux3->pos_inic_y != aux3->pos_final_y)
			cria_linha_diagonal(aux3->pos_inic_x, aux3->pos_final_x, aux3->pos_inic_y, aux3->pos_final_y,tela, condicao);
	
		aux3 = aux3->prox;
	} 	
	//pausar a tela:
	SDL_Delay(2500);
	if(SDL_MUSTLOCK(tela)) SDL_UnlockSurface(tela);  
	//finalizar o uso da SDL:
	SDL_Quit(); 	
}

