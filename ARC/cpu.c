#include<stdio.h>
#include<stdlib.h>
#define FALSE	0
#define TRUE	!0


int memoria[256];
int acm, pc, reg_instrucao, parametro;
int parada = FALSE;
int trace = TRUE;


#define HALT 0
#define OUT 1
#define IN 2
#define LOAD 3
#define STORE 4
#define ADD 5
#define SUB 6

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
			break;
		case SUB:
			busca_parametro();
			acm = acm - memoria[parametro];
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
void SUB{
	memoria[0]=2;
	memoria[1]=4;
	memoria[2]=100;
}
int main()
{
  char opc;
  while(1)
  {
    printf("|<----MENU PRINCIPAL---->|\n");
    printf("|<c> Carregar------------|\n");
    printf("|<e> Exibir--------------|\n");
    printf("|<r> Rodar---------------|\n");
    printf("|<s> Sair----------------|\n");
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
    }
  }
  return 0;
}
