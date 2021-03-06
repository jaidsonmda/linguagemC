#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HALT "0"
#define OUT "1"
#define IN "2"
#define LOAD "3"
#define STORE "4"
#define ADD "5"
#define SUB "6"
#define JMP "7"
#define CMP "8"
#define JZ "9"
#define JS "10"
#define CMPI "11"
#define ADDI "12"
#define SUBI "13"
#define LOADI "14"
typedef
  struct dado{
    char comp[1024];
    int pos;
  }sdado;

typedef 
 struct elo{//typedef define um novo nome para declarar um tipo de dado
	sdado dado;
	struct elo *prox;
	struct elo *ant;
} elo;
int entrar(sdado dado, int *quant, elo **listaP, elo **listaU, int pos){
	elo *novo=(elo*)malloc(sizeof(elo));
	novo->dado=dado;
	novo->prox=NULL;
	novo->ant=NULL;
	if(*quant==0){
		(*listaP)=novo;//se quant for zero
		//(*listaP)->prox=(*listaP);
	}
	else
	if(*quant==1){//se quant for igual a um
		(*listaP)->prox=novo;//a listaP aponta o ponteiro prox para novo
		novo->prox=(*listaP);
		novo->ant=(*listaP);//novo aponta o ponteirio ant pra listaP
		(*listaP)->ant=novo;
		(*listaU)=novo;//
		
		
	}
	else{
		(*listaU)->prox=novo;
		novo->ant=(*listaU);
		novo->prox=(*listaP);
		(*listaP)->ant=novo;
		(*listaU)=novo;
	}
	(*quant)++;
	return 1;
}
sdado sair(int *quant, elo **listaP, elo **listaU){
	sdado dado;
	dado.comp[0]='\0';
	if(*quant==0){
		return dado;
	}
	else 
	if(*quant==1){
		elo *tira=(*listaP);
		dado=(*listaP)->dado;
		(*listaU)=NULL;
		(*listaP)=NULL;
		free(tira);
		(*quant)--;
	}
	else{
		elo *tira=(*listaP);
		dado=tira->dado;
		(*listaP)=(*listaP)->prox;
		(*listaP)->ant=(*listaU);
		(*listaU)->prox=(*listaP);
		free(tira);
		(*quant)--;	
	}
	return dado;
	
}
int incluir(sdado dado, int *quant, elo **listaP, elo **listaU, int pos){
	int temp;
	elo *aux;
	elo *aux2;
	elo *novo=(elo *)malloc(sizeof(elo));
	novo->dado=dado;
	novo->prox=NULL;
	novo->ant=NULL;
	if(pos==1){
		novo->prox=(*listaP);
		(*listaP)->ant=novo;
		novo->ant=(*listaU);
		(*listaU)->prox=novo;
		(*listaP)=novo;	
	}
	else{	
		aux=(*listaP);
		for(temp=1;temp<pos;temp++){
			aux2=aux;
			aux=aux->prox;
		}
		novo->prox=aux;
		aux2->prox=novo;
		novo->ant=aux2;
		aux->ant=novo;
	}
	(*quant)++;
}
sdado excluir(int *quant, elo **listaP, elo **listaU, int pos){
	int temp;
	sdado dado;
  	dado.comp[0]='\0';
	elo *aux;
	elo *aux2;
	elo *aux3;
	elo *aux4;
	if(*quant==0 || *quant < pos){
		return dado;
	}
	else 
	if(*quant==1){
		elo *tira=(*listaP);
		dado=(*listaP)->dado;
		(*listaU)=NULL;
		(*listaP)=NULL;
		free(tira);
		(*quant)--;
	}
	else{
		if(pos==1){
			aux=(*listaP);
			(*listaP)=aux->prox;
			(*listaP)->ant=(*listaU);
			(*listaU)->prox=(*listaP);
			dado=aux->dado;
			free(aux);
			(*quant)--;
		}
		else{
			aux=(*listaP);
			for(temp=1;temp<pos;temp++){
				aux3=aux;
				aux=aux->prox;
			}
			if(*quant==pos){
				(*listaU)=aux3;	
				(*listaU)->prox=(*listaP);
				(*listaP)->ant=(*listaU);
				dado=aux->dado;
				free(aux);
				(*quant)--;
			}
			else{
				aux4=aux->prox;
				aux3->prox=aux4;
				aux4->ant=aux3;
				dado=aux->dado;
				free(aux);
				(*quant)--;
			}
		}
	}
	return dado;
	
}
void mostrar( elo *listaP, int quant){
	elo *aux=listaP;
	int temp;
	char nome[100];
	for(temp=1;temp<=quant;temp++){
		strcpy(nome, aux->dado.comp);
		printf("\033[34m%s pos %d\n", nome, aux->dado.pos);
		aux=aux->prox;
	}	
}
sdado retorna( elo **listaP, int *quant, int pos){
	elo *aux=(*listaP);
	int temp;
	sdado dado;
	char nome[100];
	for(temp=1;temp<=*quant;temp++){
		if(temp==pos)
			return aux->dado;	
		aux=aux->prox;
	}	
}
int ver(sdado dado, int *Qtd_var, elo **listavarP){
	elo *aux=(*listavarP);
	int temp;
	if(*Qtd_var==0)
		return 1;
	for(temp=1;temp<=*Qtd_var;temp++){
		if(strcmp(aux->dado.comp, dado.comp)==0)
			return 0;
		else
			aux=aux->prox;
	}
	return 1;
}
void analisar(int *Qtd_lin_arq, elo **listaarqP, elo **listaarqU, int *Qtd_var, elo **listavarP, elo **listavarU){
	elo *aux=(*listaarqU);
	int i=0, temp, pos, aux2=*Qtd_lin_arq;
	char pos2[100];
	sdado dado;
	char nome[100];
	//printf("aux2 %d\n",aux2);
	for(temp=*Qtd_lin_arq;temp!=0;){
		pos=temp--;
		strcpy(nome, aux->dado.comp);
		if(strcmp(nome, "HALT")==0){
				strcpy(aux->dado.comp, HALT);
		}
		else
		if(strcmp(nome, "OUT")==0){
				strcpy(aux->dado.comp, OUT);
		}
		else
		if(strcmp(nome, "IN")==0){
				strcpy(aux->dado.comp, IN);
		}
		else
		if(strcmp(nome, "LOAD")==0){
				strcpy(aux->dado.comp, LOAD);
		}
		else
		if(strcmp(nome, "STORE")==0){
				strcpy(aux->dado.comp, STORE);
		}
		else
		if(strcmp(nome, "ADD")==0){
				strcpy(aux->dado.comp, ADD);
		}
		else
		if(strcmp(nome, "SUB")==0){
				strcpy(aux->dado.comp, SUB);
		}
		else
		if(strcmp(nome, "JMP")==0){
				strcpy(aux->dado.comp, JMP);
		}
		else
		if(strcmp(nome, "CMP")==0){
				strcpy(aux->dado.comp, CMP);
		}
		else
		if(strcmp(nome, "JZ")==0){
				strcpy(aux->dado.comp, JZ);
		}
		else
		if(strcmp(nome, "JS")==0){
				strcpy(aux->dado.comp, JS);
		}
		else
		if(strcmp(nome, "CMPI")==0){
				strcpy(aux->dado.comp, CMPI);
		}
		else
		if(strcmp(nome, "ADDI")==0){
				strcpy(aux->dado.comp, ADDI);
		}
		else
		if(strcmp(nome, "SUBI")==0){
				strcpy(aux->dado.comp, SUBI);
		}
		else
		if(strcmp(nome, "LOADI")==0){
				strcpy(aux->dado.comp, LOADI);
		}
		else
		if(strcmp(nome, "INICIO:")==0){
				strcpy(aux->dado.comp, "0");
		}
		else
		if(nome[0]<58){
			
		}
		else{
			strcpy(dado.comp, nome);
			//printf("\033[34m %s foi excluido\n", dado.comp);//testar
			if(ver(dado, Qtd_var, listavarP)){
				dado.pos=pos;
				//printf("con %d\n", pos);
				entrar(dado, Qtd_var, listavarP, listavarU, pos);
			}
		}
		aux=aux->ant;
		
	}
}
int proce_var(int *Qtd_var, elo **listavarP, elo **listavarU, int *Qtd_lin_arq, elo **listaarqP, elo **listaarqU){
	elo *aux=(*listaarqP);
	int pos, temp,temp2;
	int cont=0;
	sdado dado;
	for(temp=*Qtd_var;temp!=0;){
		dado=retorna(listavarP, Qtd_var, temp--);
		//pos=dado.pos;
		pos=dado.pos-cont;
		cont++;
		excluir(Qtd_lin_arq, listaarqP, listaarqU, pos);
		for(temp2=1;temp2<=*Qtd_lin_arq;temp2++){
			if(strcmp(dado.comp, aux->dado.comp)==0)
				aux->dado.pos=pos-1;
			aux=aux->prox;
		}
	}
}
int main(int argc, char **argv){
	elo *listaarqP=NULL;
  	elo *listaarqU=NULL;
	elo *listavarP=NULL;
  	elo *listavarU=NULL;
  	int Qtd_lin_arq=0, Qtd_var=0;
	sdado dado;	
	char x,  num[100];
	int i=0, aux, pos=0;
	FILE *ja, *el;
	if(argv[1]==NULL){
		printf("\033[31mFalta o codigo fonte!\n");
		printf("\033[0m");
		exit(0);
	}
	if(ja=fopen(argv[1], "r")){
		
		//printf("%s\n", argv[1]);
		x=fgetc(ja);
		while(x!=EOF)//enq n??o final do arq!
		{
			while(x!=' ' && x!='\n' && x!='=' && x!='\t' && x>47){
				if(x==';'){
					while(x!='\n'){
						x=fgetc(ja);
					}
					//printf("Saiu\n");
					x=fgetc(ja);			
				}
				else{
					num[i]=x;
					i++;
					x=fgetc(ja);
				}
							
			}
			num[i]='\0';//'\0' final de strings
			if(num[0]!='\0'){
				strcpy(dado.comp, num);
				entrar(dado, &Qtd_lin_arq, &listaarqP, &listaarqU, pos);
			}
			x=fgetc(ja);
			i=0;
		}
		fclose(ja);
	}
	else{
		printf("\033[31mCodigo fonte n??o existe\n");
		printf("\033[0m");
		exit(0);	
	}
	//strcpy(dado.comp, "\n");
	//entrar(dado, &Qtd_lin_arq, &listaarqP, &listaarqU, pos);
	printf("_______________________________________ lista de leitura___________________________________________\n");
	mostrar(listaarqP, Qtd_lin_arq);
	analisar(&Qtd_lin_arq, &listaarqP, &listaarqU, &Qtd_var, &listavarP, &listavarU);
	printf("_______________________________________ lista de vari??veis_________________________________________\n");
	mostrar(listavarP, Qtd_var);
	printf("_______________________________________ lista de leitura analisada_________________________________\n");
	mostrar(listaarqP, Qtd_lin_arq);
	proce_var(&Qtd_var, &listavarP, &listavarU, &Qtd_lin_arq, &listaarqP, &listaarqU);
	printf("_______________________________________ lista de leitura pronta pra ser salva______________________\n");
	mostrar(listaarqP, Qtd_lin_arq);
	if(argv[2]==NULL){
		printf("\033[31mFalta o nome de sa??da!\n");
		printf("\033[0m");
		exit(0);
	}
	//printf("%s\n", argv[2]);
	if(el=fopen(argv[2], "wt")){
		while(Qtd_lin_arq>0){
			dado=sair(&Qtd_lin_arq, &listaarqP, &listaarqU);
			if(dado.comp[i]<58)
				fprintf(el,"%s\n", dado.comp);
			else
				fprintf(el,"%d\n", dado.pos);
		}
		fclose(el);
	}
	else{
		printf("\033[31mErro ao gerar execut??vel\n");
		printf("\033[0m");
		exit(0);
	}
	while(Qtd_var!=0){
		sair(&Qtd_var, &listavarP, &listavarU);
	}
}
