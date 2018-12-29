#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
//#include<stdout.h>
#include<time.h>
#include<windows.h>
#include <sys/time.h>

struct Buscas
{
    int vet;
};
struct TpInt
{
	int elem;	
};

struct TpArq
{
	int elem;
	char nome[60];
	char endereco[60];
	int status;
};

void Exibir();
//----------------------------------------------- MÉTODOS DE BUSCAS -------------------------------------------
int Busca_Exaustiva(FILE *arq, int arquivo)
{
    TpInt ex;
    int valor, i=0, tempinicio, tempfinal, tempmedio, contador=0, maior=0, menor=99999, medio=0;
    
    if(arquivo==1)
    	arq=fopen("arq1000.dat", "rb");
    else
    	if(arquivo==2)
    		arq=fopen("arq10000.dat", "rb");
    	else
    		if(arquivo==3)
    			arq=fopen("arq100000.dat", "rb");
    
 
    srand(time(NULL));
    tempinicio = GetTickCount();
    while(i<100)
    {
    	contador=0;
    	if(arquivo==1)
    		valor=rand()%2000;
    	else
    		if(arquivo==2)
    			valor=rand()%20000;
    		else
    			if(arquivo==3)
    				valor=rand()%200000;
    	
    	rewind(arq);
    	fread (&ex, sizeof(TpInt), 1, arq);
    	contador++;
	    while (!feof(arq)&& valor!=ex.elem)
	    {
	    	
	        fread (&ex, sizeof(TpInt), 1, arq);
	        contador++;
	    }
	    if(contador>maior)
			maior=contador;
		if(contador<menor)
			menor=contador;
		medio=medio+maior+menor;
		
	    if (valor==ex.elem)
	        printf ("\n Número %d encontrado!", ex.elem);
	    else
	        printf ("\n Número %d nao encontrado!", valor);
	        
		i++;
    	
    }
    
    // finaliza o tempo
	tempfinal = GetTickCount();
	// tempo medio
	tempmedio = tempfinal - tempinicio;
	// resposta:
	printf("\n\n Tempo de execucao: %d milissegundos.",tempmedio);
	printf("\n Quantidade de iteracoes maxima: %d",maior);
	printf("\n Quantidade de iteracoes media: %d",medio/100);
	printf("\n Quantidade de iteracoes minima: %d",menor);
    
    fclose(arq);
}

void BuscaComSentinela (FILE *arq)
{
	TpArq sent;
	FILE *temp;
    int valor, i=0;
    //TpInt sent;
    srand(time(NULL));
    /*printf ("\n Consiste em inserir o elemento a ser encontrado após o último componente válido do arranjo e,");
    printf ("\n de forma sequencia, verificar a posição em que o mesmo se encontra."); getch(); system("cls")*/;
   
    
    while(i<100)
    {
    
    
    	arq=fopen("arq1.dat", "rb+");
    	temp=fopen("temp.dat","wb");
    	rewind(arq);
		rewind(temp);
		
		valor = rand()%2000;
		sent.elem=valor;
	
		fseek(arq,0,2);
		fwrite(&sent,sizeof(TpArq),1,arq);
		rewind(arq);
		fread(&sent,sizeof(TpArq),1,arq);
		while(sent.elem!=valor)
			fread(&sent,sizeof(TpArq),1,arq);
		
		fread(&sent, sizeof(TpArq),1,arq);
		if(!feof(arq))
			printf("\n numero %d encontrado" ,valor);
		else
			printf("\n numero %d nao encontrado" ,valor);
		
		//excluir
		
		
		fseek(arq,-sizeof(TpArq),2);
		sent.elem=-1;
		
		
		fwrite(&sent,sizeof(TpArq),1,arq);
		rewind(temp);
		rewind(arq);
		fread(&sent,sizeof(TpArq),1,arq);
		while(sent.elem!=-1)
		{	
			fwrite(&sent,sizeof(TpArq),1,temp);
			fread(&sent,sizeof(TpArq),1,arq);
		}
		
	
	
		
		fclose(arq);
		fclose(temp);
		
		remove("arq1.dat");
		rename("temp.dat","arq1.dat");
				
		i++;
    }
    
    
    
    
    /*
    printf ("\n Elemento a ser inserido:");
    scanf ("%d", &elem);
    arq=fopen("Buscas.dat", "ab+");
    
    bcs.vet=elem;
    fwrite(&bcs, sizeof(Buscas), 1, arq);
    
    fseek(arq, 0, 0);
    
    fread(&bcs, sizeof(Buscas), 1, arq);
    while(elem!=bcs.vet)
        fread(&bcs, sizeof(Buscas), 1, arq);
    
    if (elem==bcs.vet)
        printf ("\n Elemento foi inserido na últia posição do vetor.");
    else
        printf ("\n Opss! Algum erro ocorreu! ''/ ");
    fclose(arq);*/
    
}

void BuscaSeqIndexada(FILE *arq, int arquivo)
{
    TpInt si; 
	int valor, i=0, tempinicio, tempfinal, tempmedio, contador=0, maior=0, menor=99999, medio=0;;
    
   /* printf ("\n O acesso as informacoes eh realizado de forma sequencial ate se ");
    printf ("encontrar o elemento maior ou identico ao que se busca, ou ainda, todos os elementos do arranjo forem verificados.");
    getch(); system("cls");*/
    
    if(arquivo==1)
    	arq=fopen("arq1000.dat", "rb");
    else
    	if(arquivo==2)
    		arq=fopen("arq10000.dat", "rb");
    	else
    		if(arquivo==3)
    			arq=fopen("arq100000.dat", "rb");
    			
	tempinicio = GetTickCount();
    srand(time(NULL));
    while(i<100)
    {
    	contador=0;
    	if(arquivo==1)
    		valor=rand()%2000;
    	else
    		if(arquivo==2)
    			valor=rand()%20000;
    		else
    			if(arquivo==3)
    				valor=rand()%200000;
    
    	rewind(arq);
    	fread(&si, sizeof(TpInt), 1, arq);
    	contador++;
	    while(!feof(arq) && valor>si.elem)
	    {
	        fread(&si, sizeof(TpInt), 1, arq);
			contador++;
		}
		
	    if(contador>maior)
			maior=contador;
		if(contador<menor)
			menor=contador;
		medio=medio+maior+menor;
	    if (!feof(arq) && valor==si.elem)
	    {
	        printf ("\n Número %d encontrado!", valor);
	    }
	    else
	    {
	    	printf ("\n Número %d nao encontrado.", valor);    
	    }
	    i++;
    }
    // finaliza o tempo
	tempfinal = GetTickCount();
	// tempo medio
	tempmedio = tempfinal - tempinicio;
	// resposta:
	printf("\n\n Tempo de execucao: %d milissegundos.",tempmedio);
	printf("\n Quantidade de iteracoes maxima: %d",maior);
	printf("\n Quantidade de iteracoes media: %d",medio/100);
	printf("\n Quantidade de iteracoes minima: %d",menor);
    
    fclose(arq);
    
}




int BuscaBinaria (FILE *arq, int arquivo)
{
	arquivo=3;
	if(arquivo==1)
	{
		//abre o arquivo 1000
		arq=fopen("arq1000.dat","rb");
	}
	else
	{
		if(arquivo==2)
		{
			//abre o arquivo 10000
			arq=fopen("arq10000.dat","rb");
		}
		else
		{
			if(arquivo==3)
			{
				//abre o arquivo 10000
				arq=fopen("arq100000.dat","rb");
			}
		}
	}
	
	TpInt numero;
	int inicio, fim, meio, i=0, achou=0;
	long int sorteado;
	int t_inicio, t_fim, t_mili;
	int contador=0, contmin=0;
	int maior=0, menor=999, medio=0;
	
	//sorteia um numero
	srand(time(NULL));

	
	//começa a contar o tempo
	t_inicio = GetTickCount();
	//100 repetiçoes N=100
	while(i<100){
		//posiciona o ponteiro no inicio
		rewind(arq);
	//	fread(&numero,sizeof(TpInt),1,arq);
		inicio=0;
		// o fim pode ser 999 para arquivos 1000, 9999 para 10000 e 99999 para 100000
		if(arquivo==1)
			fim=999;
		else
		{
			if(arquivo==2)
				fim=9999;
			else
				if(arquivo==3)
					fim=99999;
		}
		meio=(inicio+fim)/2;
		//contador zera para cada numero procurado
		contador=0;
		//sorteia um numero
		if(arquivo==1)
			sorteado = rand() % 2000;
		else
			if(arquivo==2)
				sorteado=rand()%20000;
			else
				if(arquivo==3)
					sorteado=rand()%2000000;
		
	
		//posiciona o ponteiro no meio e lê
		fseek(arq,sizeof(TpInt)*meio,0);
		fread(&numero,sizeof(TpInt),1,arq);
		contador++;
	
		while(inicio<fim && sorteado!=numero.elem)
		{
			
			if(sorteado>numero.elem)
			{
				inicio=meio+1;
				meio=(inicio+fim)/2;
				fseek(arq,sizeof(TpInt)*meio,0);
				fread(&numero,sizeof(TpInt),1,arq);
				contador++;
			
			}
			else
			{
				fim=meio;
				meio=(inicio+fim)/2;
				fseek(arq,sizeof(TpInt)*meio,0);
			    fread(&numero,sizeof(TpInt),1,arq);
			    contador++;
			   
			}
		
		
		}
		//achou
		if(sorteado==numero.elem)
		{
			printf(" ACHOU! %d\n",numero.elem);
		
		}
		//nao achou
		else
		{
			printf(" NAO ACHOU! %d\n",sorteado);
			
		}
		//calculo da quantidade de leitura meida, maxima e minima
		if(contador>maior)
			maior=contador;
		if(contador<menor)
			menor=contador;
		medio=medio+maior+menor;
		
		i++;
	
	
	}
	
	// finaliza o tempo
	t_fim = GetTickCount();
	// tempo medio
	t_mili = t_fim - t_inicio;
	// resposta:
	printf("\n\n Tempo de execucao: %d milissegundos.",t_mili);
	printf("\n Quantidade de iteracoes maxima: %d",maior);
	printf("\n Quantidade de iteracoes media: %d",medio/100);
	printf("\n Quantidade de iteracoes minima: %d",menor);
	
    fclose(arq);
}

//----------------------------------------------- MÉTODOS DE ORDENAÇÃO -------------------------------------------

void BubbleSort (FILE *arq)
{
	Buscas vi, vj;
	int i, achou=1, j;
	
	arq=fopen("Buscas.dat", "rb+");
	fseek (arq, 0, 2);
	
	for (i=ftell(arq)/sizeof(Buscas)-1; i>=1 && achou; i--)
	{
	   achou=0;
	   for (j=i-1; j>=0; j--)
	   {  
	   	   fseek (arq, sizeof(Buscas)*i, 0); 
 	  	   fread (&vi, sizeof (Buscas), 1, arq);
           fseek (arq, sizeof(Buscas)*j, 0);
           fread (&vj, sizeof (Buscas), 1, arq);
	   	   	   
	       if (vi.vet<vj.vet)
	   	   {
	   	   	   fseek(arq, sizeof(Buscas)*i, 0);
	   	       fwrite (&vj, sizeof(Buscas), 1, arq);
	   	       fseek(arq, sizeof (Buscas)*j, 0);
	   	       fwrite (&vi, sizeof (Buscas), 1, arq);
	   	       achou=1;
	   	   }
       }
	}
	printf ("\n Ordenacao realizada com sucesso!!");
	fclose(arq);
}

void InsercaoDireta (FILE *arq)
{
    Buscas vi, vj;
    int aux, i, j, elem;
    arq=fopen("Buscas.dat", "rb+");
    
    printf ("Elemento que deseja inserir: \n");
    scanf ("%d", &vi.vet);
    fseek(arq, 0, 2);
    fwrite(&vi, sizeof(Buscas), 1, arq);
      
    i=ftell(arq)/sizeof(Buscas)-1;
    j=i-1; 
    fseek(arq, i*sizeof(Buscas), 0);
    fread(&vi, sizeof(Buscas), 1, arq);
    fseek(arq, j*sizeof(Buscas), 0);
    fread(&vj, sizeof(Buscas), 1, arq);
    
    while (i>0 && vi.vet<vj.vet)
    {
        fseek(arq, j*sizeof(Buscas), 0);
        fwrite(&vi, sizeof(Buscas), 1, arq);
        fseek(arq, i*sizeof(Buscas), 0);
        fwrite(&vj, sizeof(Buscas), 1, arq);
        i--; j--;
        
        fseek(arq, i*sizeof(Buscas), 0);
        fread(&vi, sizeof(Buscas), 1, arq);
        fseek(arq, j*sizeof(Buscas), 0);
        fread(&vj, sizeof(Buscas), 1, arq);
    }
    printf ("Elemento inserido corretamente na ordem crescente do vetor.");
    fclose(arq);
}

int PosMaior (FILE *arq, int tl)
{
    Buscas vi;
    int i, j, maior=0, achou=0;          //j=posição maior
    
    arq=fopen("Buscas.dat", "rb");
    
    for(i=0; i<tl; i++)
    {
        fseek(arq, i*sizeof(Buscas), 0);
        fread(&vi, sizeof(Buscas), 1, arq); 
        if(maior<vi.vet)
        {
            maior=vi.vet;
            j=ftell(arq)-sizeof(Buscas);
            achou=1;
        }
    } 
    if (achou==1)
    	return j;
    else
    	return -1;
    
    fclose(arq);
}
void SelecaoDireta (FILE *arq)
{
    Buscas vi, vj;
    int j, i;          //j=posição maior
    arq=fopen("Buscas.dat", "rb+");
    
    fseek (arq, 0, 2);
    i=ftell(arq)/sizeof(Buscas)-1;
    while(i>0)
    {
    	
        j=PosMaior(arq, i);
        fseek(arq, j*sizeof(Buscas), 0);
        fread(&vj, sizeof(Buscas), 1, arq);
        fseek(arq, i*sizeof(Buscas), 0);
        fread(&vi, sizeof(Buscas), 1, arq);
        if (j<i && j!=-1)
        {
        	fseek(arq, i*sizeof(Buscas), 0);
            fwrite(&vj, sizeof(Buscas), 1, arq);
            fseek(arq, j*sizeof(Buscas), 0);
            fwrite(&vi, sizeof(Buscas), 1, arq);
        }
                
        if (j==-1)
            i=0;
        else
			i--;
    }
    fclose(arq);
}

//--------------------------------------------- CADASTRO / EXIBIR / MENU ----------------------------------------------------
void CadastraNumeros (FILE *arq)
{
    int num, i=0;
    Buscas be;
    
    
    printf (" \t\t PARA SAIR DO PROGRAMA DIGITE O NUMERO 9999 \t\tn\n");
    printf ("\n Numero %d:", i);
    scanf ("%d", &num);
    arq=fopen("Buscas.dat", "ab");
    while (num!=9999)
    {
        be.vet=num;
        fwrite(&be, sizeof(Buscas), 1, arq);
        i++;
        printf ("\n Numero %d:", i);
        scanf ("%d", &num);
    }
    fclose(arq);
}

void Exibir ()
{
	
    TpArq b; int i=0;
 	 FILE*arq=fopen("arq1.dat", "rb");
    //FILE*temp=fopen("temp.dat", "rb");
    rewind(arq);
    //rewind(temp);
    
	fread(&b, sizeof(TpArq), 1, arq);
    while(!feof(arq))
    {
        printf("%d %s\n",b.elem,b.endereco);
        fread(&b, sizeof(TpArq), 1, arq);
        i++;
    }
    
    //printf("\n\n\n\n\n");
    
   /* fread(&b, sizeof(Buscas), 1, temp);
    while(!feof (arq))
    {
        printf("Pos[%d], numero: %d \n", i, b.vet);
        fread(&b, sizeof(Buscas), 1, temp);
        i++;
    }*/
    
    fclose(arq);
    //fclose(temp);
}
char Menu(void)
{
    char op;
    
    printf ("-> Opcoes:\n");
    printf ("[1] Cadastrar numeros no vetor\n");
    printf ("---> Metodos de Buscas <---\n\n\n\n");
    printf ("[2] Busca Exaustiva\n");
    printf ("[3] Busca com Sentinela\n");
    printf ("[4] Busca Binaria\n");
    printf ("[5] Busca Sequencial Indexada\n");
    printf ("---> Metodos de Ordenacao <---\n\n\n\n");
    printf ("[6] Bubble Sort\n");
    printf ("[7] Insercao Direta\n");
    printf ("[8] Selecao Direta\n\n");
    
    printf ("[9] Excluir arquivamentos\n");
    printf ("[0] Exibir vetor\n");
    op=getch();
    return op;
}

int main (void)
{
    setlocale(LC_ALL, "Portuguese");
    FILE *arq;
    char op;
    
    do
    {
        op=Menu();
        system("cls");
        switch(op)
        {
            case '1': CadastraNumeros(arq); break;                  
            case '2': Busca_Exaustiva(arq,1); break;            
            case '3': BuscaComSentinela(arq); break;            
            case '4': BuscaBinaria(arq,3); break;            
            case '5': BuscaSeqIndexada(arq,1); break;
            case '6': BubbleSort(arq); break;
            case '7': InsercaoDireta(arq); break;
            case '8': SelecaoDireta(arq); break;
            case '9': remove("Buscas.dat"); 
                      printf ("\n Arquivamento deletado.");
                      break;
            case '0': Exibir (); break;
            default: printf ("\n Opcao invalida!!");
        
        }
        getch(); system("cls");
        
    }while(op!=27);
    
    return 0;
}
