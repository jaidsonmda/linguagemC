#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FALSE	0
#define TRUE	!0


int memoria[256], pilha[100];
int acm, pc,sp=100, reg_instrucao, parametro;
int parada = FALSE;
int trace = TRUE;
int eh_negativo, guarda_pc;
int eh_zero;
int reg_aux;

#define instrS "soma.txt"
#define instrD "subtrair.txt"
#define HALT 0
#define OUT 1
#define IN 2
#define LOAD 3
#define STORE 4
#define ADD 5
#define SUB 6
#define JMP 7
#define CMP 8
#define JZ 9
#define JS 10
#define CMPI 11
#define ADDI 12
#define SUBI 13
#define LOADI 14
#define PUSH 15
#define POP 16
#define PUSHI 17
#define RET 18
#define CALL 19

void busca()
{
	reg_instrucao=memoria[pc];
	pc++;
}

void busca_parametro()
{
	parametro=memoria[pc];
	pc++;
}

void carregar()
{
  int i;
  for(i=0;i<256;i++)
  {
    printf("Entre com memoria[%d]: ",i);
    scanf("%d",&(memoria[i]));
    if(memoria[i]>127 || memoria[i]<-128)
    {
      memoria[i]=0;
      break;
    }
  }
  while(getchar()!='\n');
}

void exibir()
{
  int i;
  char opc;
  for(i=0;i<256;i++)
  {
    printf("Memoria[%d]: %d\n",i,memoria[i]);
    if(i%16==15)
    {
      //while(getchar()!='\n');
      printf("Digite <Entrer> para continuar...ou <p> para parar...");
      opc=getchar();
      if(opc=='p')
	break;
    }
  }
  
}


void execucao() 
{
	switch (reg_instrucao) {
		case HALT:
			parada = TRUE;
			break;
		case OUT:
			printf("Saida=%d\n", acm );
			break;		
		case IN:
			printf("Entre com um valor:" );
			scanf("%d", &acm );
			break;
		case LOAD:
			busca_parametro();
			acm = memoria[parametro];
			break;
		case STORE:
			busca_parametro();
			memoria[parametro] = acm;
			break;
		case ADD:
			busca_parametro();
			acm = acm + memoria[parametro];
			if( acm == 0 )
				eh_zero = TRUE;
			else
				eh_zero = FALSE;
			if( acm < 0 )
				eh_negativo = TRUE;
			else
				eh_negativo = FALSE;
			break;
		case SUB:
			busca_parametro();
			acm = acm - memoria[parametro];
			if( acm == 0 )
				eh_zero = TRUE;
			else
				eh_zero = FALSE;
			if( acm < 0 )
				eh_negativo = TRUE;
			else
				eh_negativo = FALSE;
			break;
		case JMP:
			busca_parametro();
			pc = parametro;
			break;
		case CMP:
			busca_parametro();
			reg_aux = acm - memoria[parametro];
			if( reg_aux == 0 )
				eh_zero = TRUE;
			else
				eh_zero = FALSE;
			if( reg_aux < 0 )
				eh_negativo = TRUE;
			else
				eh_negativo = FALSE;
			break;
		case JZ:
			if( eh_zero ) {
				busca_parametro();
				pc = parametro;
			}
			break;
		case JS:
			if( eh_negativo ) {
				busca_parametro();
				pc = parametro;
			}
			break;
		case CMPI:
			busca_parametro();
			reg_aux= acm-parametro;
			eh_zero=(reg_aux==0);
			eh_negativo=(reg_aux<0);
			break;
		case LOADI:
			busca_parametro();
			acm=parametro;
			break;
		case SUBI:
			busca_parametro();
			acm=parametro;
			eh_zero=(acm==0);
			eh_negativo=(acm<0);
			break;
		case ADDI:
			busca_parametro();
			acm=parametro;
			eh_zero=(acm==0);
			eh_negativo=(acm<0);
			break;
		case PUSH:
			sp++;
			pilha[sp]=guarda_pc;
			break;
		case POP:
			acm=pilha[sp];
			sp--;
			break;
		case RET:
			pc=pilha[sp];
			break;
		case PUSHI:
			busca_parametro();
			pilha[sp]=parametro;
			sp--;
			break;
		case CALL:
			busca_parametro();
			pc = parametro;
			guarda_pc=pc+1;
			break;
			
	}

}

void mostrar_regs()
{
    if(trace)
    {
    	printf( "PC=%d\tRI=%d\tParam=%d\tA=%d\n", pc, reg_instrucao, parametro, acm );
    }
}

void rodar()
{
  pc = 0; // volta para a instrução inicial
  while(1)
  {
    mostrar_regs();
    
    busca();
    execucao();
    if(parada)
      break;
  }
  mostrar_regs();
}
void instruc(char *lista){
	char x, num[10];
	int i=0, j=0, aux;
	FILE *ja;
	ja=fopen(lista, "r");
	x=fgetc(ja);
	while(x!=EOF)
	{
		while(x!='\n'){
			num[i]=x;
			i++;
			x=fgetc(ja);			
		}
		num[i]='\0';
		aux=atof(num);
		memoria[j]=aux;
		x=fgetc(ja);
		j++;
		i=0;
	}
	fclose(ja);
	rodar();
}
int main()
{
  char opc, instru[20];
  while(1)
  {
    printf("|<----MENU PRINCIPAL---->|\n");
    printf("|<c> Carregar------------|\n");
    printf("|<e> Exibir--------------|\n");
    printf("|<r> Rodar---------------|\n");
    printf("|<S> somar-------------->|\n");
    printf("|<D> subtrair----------->|\n");
    printf("|<s> Sair----------------|\n");
    printf("|<o> Outra operação----->|\n");
		printf("|<---------------------->|\n");
    opc=getchar();
    while(getchar()!='\n');
    switch(opc)
    {
      case 'c':
	carregar();
	break;
      case 'e':
	exibir();
	break;
      case 'r':
	rodar();
	break;
      case 's':
	exit(0);
	break;
      case 'S':
	instruc(instrS);
	break;
      case 'D':
	instruc(instrD);
	break;
	    case 'o':
      printf("Digite o nome do arquivo:");
      scanf(" %[^\n]", instru);
      getchar();
      instruc(instru);
  break;
    }
  }
  return 0;
}
