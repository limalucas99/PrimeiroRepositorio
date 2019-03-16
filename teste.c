#include <stdio.h>
#include <stdlib.h>

struct vetor {
	int * v;
	int capacidade;
	int ocupacao;
};

struct vetor * cria_vetor (int aux) {
	struct vetor * ponteiro = (struct vetor *) malloc (sizeof(struct vetor));
	if (ponteiro == NULL) {
		return NULL;
	}
	ponteiro->v = (int *) malloc (aux * sizeof(int));
	if (ponteiro->v == NULL) {
		return NULL;
	}
	ponteiro->capacidade = aux;
	ponteiro->ocupacao = 0;
	return ponteiro;
}

struct vetor * libera_vetor (struct vetor * sv) {
	free(sv->v);
	free(sv);
	return NULL;
}

int vetor_cheio (struct vetor * sv) {
	return (sv->ocupacao == sv->capacidade);
}
int vetor_vazio (struct vetor * sv) {
	return !sv->ocupacao;
}
int insere_elemento_vetor (int e, struct vetor * sv) {
	int * aux_v;
	int i;
	
	// REUSAVEL
	if (vetor_cheio(sv)) {  // precisa aumentar o vetor
		aux_v = (int *) malloc (2*sv->capacidade*sizeof(int));
		if (aux_v != NULL) {
			for (i=0; i<sv->ocupacao; i++) { // analise amortizada . Escalabilidade de alg ex Gangn-2 a 31 a 2 a 31-1.
				aux_v[i] = sv->v[i];
			}
			free(sv->v);
			sv->v = aux_v;
			sv->capacidade = 2 * sv->capacidade;
		}
		else {
			return 0;
		}
	}
	sv->v[sv->ocupacao++] = e;
	return 1;
}
// AULA 04 - diminuir o vetor

	/*// sobreposição -> ocupação(memoria livre). Seja ela memoria persistente ou volatil, só será realmente liberada pelo S.O
	*e = sv->v [--sv->ocupacao];
	if (sv->ocupacao<= sv->capacidade/4) { //precisa diminuir
	 aux_v = (int *) malloc (sv->capacidade/2 * sizeof(int));
	if(aux_v != NULL){
		for(i=0; i<sv->ocupacao; i++){
			aux_v[i]=sv->v[i];
		}
	}
	free(sv->v);
	sv->v=aux_v;
	sv->capacidade = sv->capacidade/2;
}
else {
			return 0;
		}
	}
*/

int remove_elemento(int *e, struct vetor *sv){
	int *aux_v;
	int i;
	if(vetor_vazio(sv)){
		return 0;
	}
	// sobreposição -> ocupação(memoria livre). Seja ela memoria persistente ou volatil, só será realmente liberada pelo S.O
	*e = sv->v [--sv->ocupacao];
	if (sv->ocupacao<= sv->capacidade/4) { //precisa diminuir
	 //aux_v = (int *) malloc (sv->capacidade/2 * sizeof(int));
	if(aux_v != NULL){
		for(i=0; i<sv->ocupacao; i++){
			aux_v[i]=sv->v[i];
		}
	}
	free(sv->v);
	sv->v=aux_v;
	sv->capacidade = sv->capacidade/2;
}
else {
			return 0;
		}
	}
void exibe_vetor (struct vetor * sv) {
	int i;
	printf ("\ncapacidade atual: %d\n", sv->capacidade);
	if (vetor_vazio(sv)) {
		printf ("vetor vazio\n");
	}
	else {
		for (i=0; i<sv->ocupacao; i++) {
			printf (" %d", sv->v[i]);
		}
	}
}
/*
// PARAMETRIZANDO
int redimensiona (int nova_capacidade, struct vetor *sv){
	int * aux_v;
	int i;
	
	aux_v = (int *) malloc (nova_capacidade*sizeof(int));
		if (aux_v != NULL) {
			for (i=0; i<sv->ocupacao; i++) { // analise amortizada . Escalabilidade de alg ex Gangn-2 a 31 a 2 a 31-1.
				aux_v[i] = sv->v[i];
			}
			free(sv->v);
			sv->v = aux_v;
			sv->capacidade = nova_capacidade;
			return 1;
		}
		else {
			return 0;
		}
	}
	   
	
}
*/
int main () {
	int aux;
	struct vetor * ponteiro_estrutura;
	printf ("\ndigite o tamanho inicial do vetor: ");
	scanf ("%d", &aux);
	ponteiro_estrutura = cria_vetor(aux);
	if (ponteiro_estrutura == NULL) {
		printf ("\nfalha na criacao do vetor\n");
		return 0;
	}
	/*if (insere_elemento (15, ponteiro_estrutura)) {
		printf ("\nelemento inserido com sucesso\n");
	}
	else {
		printf ("\nvetor ta cheio\n");
	}*/
	for (aux = 1; aux<=42; aux++) {
		if (insere_elemento_vetor(aux, ponteiro_estrutura)) {
			exibe_vetor (ponteiro_estrutura);
		}
	}
	
	while(remove_elemento(&aux, ponteiro_estrutura)){
		printf ("\n %d removido", aux);
		exibe_vetor (ponteiro_estrutura);
	}
	
	
	
	libera_vetor(ponteiro_estrutura);		
	return 0;
	
//	remove_elemento(*e,*sv);
}




