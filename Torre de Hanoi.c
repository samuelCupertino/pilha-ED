#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>

typedef struct DDado{
	int qtdMovento;
	char nome[20];
}jogador;

typedef struct EElemento{
	jogador monge;
	struct EElemento *ant;
}nno;

typedef struct LLista{
	nno *pri;
	nno *ult;
}fila;


typedef struct Dado{
	int size;	
}tam;

typedef struct Elemento{
	tam disco;
	struct Elemento *prox;
}no;

typedef struct Lista{
	int qtdDisco;
	no* top;
}pilha;


fila *Alocar_Fila(){
	
	fila *fila_alocada=(fila*)malloc(sizeof(fila)); // Alocar espaco para pilha 
	
	if(fila_alocada == NULL){  // Se Alocacao falhou finaliza execucao
		printf("Erro de Memória :(");
		exit(1);
	}
	
	fila_alocada->pri=NULL; // Se deu certo a alocacao, iniciaiza as variaveis da fila
	fila_alocada->ult=NULL;
	
	return fila_alocada;
}

void Inserir_Monge(fila *Fila){
	nno *nMonge=(nno*)malloc(sizeof(nno)); // Alocar espaco para um nó de elemento disco 
	int fila_alocada;
	if(nMonge == NULL){  // Se Alocacao falhou finaliza execucao
		printf("Erro de Memória :(");
		exit(1);
	}
	
	printf("Nome do Monge: ");
	fflush(stdin);
	gets(nMonge->monge.nome);
	nMonge->monge.qtdMovento=0;
	
	nMonge->ant=NULL;
	if(Fila->pri == NULL){  // Se nao ha disco na pilha, o novo disco será o 1º
		Fila->pri=nMonge;
		Fila->ult=nMonge;	
	} else{                    // Se ha disco na pilha, o novo disco será o ultimo
		Fila->ult->ant=nMonge;
		Fila->ult=nMonge;
	}
}



pilha *Alocar_Pilha(){
	
	pilha *pilha_alocada=(pilha*)malloc(sizeof(pilha)); // Alocar espaco para pilha 
	
	if(pilha_alocada == NULL){  // Se Alocacao falhou finaliza execucao
		printf("Erro de Memória :(");
		exit(1);
	}
	
	pilha_alocada->top=NULL; // Se deu certo a alocacao, iniciaiza as variaveis da pilha
	pilha_alocada->qtdDisco=0;
	
	return pilha_alocada;
}


void Inserir_Disco(pilha *Pilha, int tamDisco){
	no *nDisco=(no*)malloc(sizeof(no)); // Alocar espaco para um nó de elemento disco 
	
	if(nDisco == NULL){  // Se Alocacao falhou finaliza execucao
		printf("Erro de Memória :(");
		exit(1);
	}
	 
	nDisco->disco.size= tamDisco;  // Preenchimento do dado tamanho do disco
		
	if(Pilha->qtdDisco == 0){  // Se nao ha disco na pilha, o novo disco será o 1º
		nDisco->prox=NULL;
		Pilha->top=nDisco;
		Pilha->qtdDisco=1;
	} else{                    // Se ha disco na pilha, o novo disco será o ultimo
		if(tamDisco < Pilha->top->disco.size){
			nDisco->prox=Pilha->top;
			Pilha->top=nDisco;
			Pilha->qtdDisco++;	
		}
	}			
}

void Mover_Disco(pilha *receptor, pilha *doador){
	no *aux=(no*)malloc(sizeof(no)); // aux de exclusao do disco do doador
		
	Inserir_Disco(receptor, doador->top->disco.size); // inserir no receptor o disco do topo do doador
				
	aux=doador->top;  // É armazenado o indereco do disco do topo do doador 
	doador->top=doador->top->prox;  // O topo passa a ser o penutimo disco
	free(aux);	// É liberado o ex-ultimo disco
	doador->qtdDisco--;  // O doador perde 1 disco

}

void Printar_Torre(char x, char y, pilha *torreA, pilha *torreB, pilha *torreC){
	int i, j, i2, j2, contDisco, linha;
	no *auxA=torreA->top;
	no *auxB=torreB->top;
	no *auxC=torreC->top;
	pilha *receptor, *doador;
	char transp[32];
	char topTor[32]={   "               _                "};
	char pilarTor[32]={ "              | |               "};
	char limpar[32]={   "                                "};
	char disco[7][32]={ "            [][o][]              ",
						"          [][][o][][]           ",
						"        [][][][o][][][]         ",
						"      [][][][][o][][][][]       ",
						"    [][][][][][o][][][][][]     ",
						"  [][][][][][][o][][][][][][]   ",
						"[][][][][][][][o][][][][][][][] "};
	char torres[22][114]={"                                                                                                                 ",
						  "               _                                        _                                        _               ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "              | |                                      | |                                      | |              ",
						  "            .´   `.                                  .´   `.                                  .´   `.            ",
						  "           '-------'                                '-------'                                '-------'           ",
						  "               A                                        B                                        C               "};
	contDisco=7;
	linha=3; // ignorar linhas menores da estring 'torres' pois nesta nao ha locais para discos 
	while (contDisco>0){  // percorrer todos os discos das 3 torres para colocar nas torres printadas discos proporcionais
		if (contDisco <= torreA->qtdDisco){  // 1/3 - se a torre possuir esse numero de discos 
			for(i=0; i<32; i++){
				torres[linha][i]=disco[auxA->disco.size-1][i];  // 1/3 - colocar na string 'torres' o disco representante do elemento do topo da pilha 
			}
			auxA=auxA->prox; // 1/3 - ir para o proximo disco a ser colocado
		}
		if (contDisco <= torreB->qtdDisco){ // 2/3
			for(i=41; i<72; i++){
				torres[linha][i]=disco[auxB->disco.size-1][i-41]; // 2/3
			}
			auxB=auxB->prox;// 2/3
		}
		if (contDisco <= torreC->qtdDisco){ // 3/3
			for(i=82; i<114; i++){
				torres[linha][i]=disco[auxC->disco.size-1][i-82]; // 3/3
			}			
			auxC=auxC->prox; // 3/3
		}
		linha+=2; // pular para a proxima linha para colocar o proximo disco na string (pula de 2 em 2 para da espaco entre os discos)
		contDisco--; // Buscar novo disco abaixo do procurado 
	}
	for (i=0; i<22; i++){  // printar a string 'torres'
		for (j=0; j<114; j++){
			printf("%c", torres[i][j]);
		}
		printf("\n");			
	}
	
	// Verificar se as torres informadas sao validas e definir qual duara e qual recebera
	if(x=='a' || x=='A'){
		doador=torreA;
		if(y=='b' || y=='B')
			receptor=torreB;
		else if(y=='c' || y=='C')
			receptor=torreC;
		else
			return;
	}
	else if(x=='b' || x=='B'){
		doador=torreB;
		if(y=='a' || y=='A')			
			receptor=torreA;
		else if(y=='c' || y=='C')
			receptor=torreC;
		else
			return;
	}
	else if(x=='c' || x=='C'){
		doador=torreC;
		if(y=='a' || y=='A')
			receptor=torreA;
		else if(y=='b' || y=='B')
			receptor=torreB;
		else
			return;
	}
	else{
		return;
	}
	
	if(doador->qtdDisco == 0 || receptor->top!=NULL && receptor->top->disco.size < doador->top->disco.size)
		return;
		
	// Disco saindo da Torre Doadora
	contDisco=7;
	linha=3;
	if(x=='a' || x=='A'){
		while (contDisco > torreA->qtdDisco){  // se o disco em questao nao esta presente na torre (7º- 6º-- 5º--- 4º---- 3º----- 2º------ 1º-------)
			linha+=2;  // vai atualizando as linhas que estaram vazias ate chegar no disco do topo da torre que esta dentro da string
			contDisco--;   // o contador de disco é decrementado ate conter o mesmo numero de disco (e por consequencia indicar a posicao que o disco do topo esta)
		}
		for(i=0; i<=31; i++){ // pegar o disco que esta no topo e colocalo dentro de uma variavel para poder tranportalo
			transp[i]=torres[linha][i];		
		}
		while (linha > 0){  // Subi o disco ate o topo da string 
			Sleep(50);
			system ("CLS");
			for(i=0; i<=31; i++){ 
				torres[linha][i]=pilarTor[i];
				if(linha<1)
					torres[linha][i]=limpar[i];
				if(linha==1)
					torres[linha][i]=topTor[i];
				torres[linha-1][i]=transp[i];
			}
			linha--;			
			for (i=0; i<22; i++){  // printar as torres
				for (j=0; j<114; j++){
					printf("%c", torres[i][j]);
				}
				printf("\n");			
			}
		}	
	}
	if(x=='b' || x=='B'){
		while (contDisco > torreB->qtdDisco){  // se o disco em questao esta presente na torre 
			linha+=2;
			contDisco--;
		}
		for(i=41; i<=72; i++){
			transp[i-41]=torres[linha][i];		
		}
		while (linha > 0){  // Subi o disco ate o topo
			Sleep(50);
			system ("CLS");
			for(i=41; i<=72; i++){ 
				torres[linha][i]=pilarTor[i-41];
				if(linha<1)
					torres[linha][i]=limpar[i-41];
				if(linha==1)
					torres[linha][i]=topTor[i-41];
				torres[linha-1][i]=transp[i-41];
			}
			linha--;			
			for (i=0; i<22; i++){  // printar as torres
				for (j=0; j<114; j++){
					printf("%c", torres[i][j]);
				}
				printf("\n");			
			}
		}		
	}
	if(x=='c' || x=='C'){
		while (contDisco > torreC->qtdDisco){  // se o disco em questao esta presente na torre 
			linha+=2;
			contDisco--;
		}
		for(i=82; i<=113; i++){
			transp[i-82]=torres[linha][i];		
		}
		while (linha > 0){  // Subi o disco ate o topo
			Sleep(50);
			system ("CLS");
			for(i=82; i<=113; i++){ 
				torres[linha][i]=pilarTor[i-82];
				if(linha<1)
					torres[linha][i]=limpar[i-82];
				if(linha==1)
					torres[linha][i]=topTor[i-82];
				torres[linha-1][i]=transp[i-82];
			}
			linha--;			
			for (i=0; i<22; i++){  // printar as torres
				for (j=0; j<114; j++){
					printf("%c", torres[i][j]);
				}
				printf("\n");			
			}
		}
	}
	for(i=0; i<=113; i++){ //limpar ultima linha atualizada (apaga o disco dela para ele sumir da torre doadora e aparecer na receptora)
		torres[0][i]=' ';
	}
	
	// Disco chegando na Torre Receptora
	contDisco=7;
	linha=2;
	if(y=='a' || y=='A'){
		while (contDisco > torreA->qtdDisco){  // se o disco em questao esta presente na torre 
			linha+=2;
			contDisco--;
		}
		for (i=0; i<linha; i++){  // Subi o disco ate o topo
			system("CLS");
			for(j=0; j<=31; j++){	
				if(i==0)
					torres[i][j]=transp[j];
				else if(i>0){
					torres[i][j]=transp[j];
					if(i==1)
					torres[0][j]=limpar[j];
					else if (i==2)
					torres[i-1][j]=topTor[j];
					else					
						torres[i-1][j]=pilarTor[j];
				}
			}		
			for (i2=0; i2<22; i2++){  // printar as torres
				for (j2=0; j2<114; j2++){
					printf("%c", torres[i2][j2]);
				}
				printf("\n");			
			}
			Sleep(50);
		}
	}
	if(y=='b' || y=='B'){
		while (contDisco > torreB->qtdDisco){  // se o disco em questao esta presente na torre 
			linha+=2;
			contDisco--;
		}
		for (i=0; i<linha; i++){  // Subi o disco ate o topo
			system("CLS");
			for(j=41; j<=72; j++){	
				if(i==0)
					torres[i][j]=transp[j-41];
				else if(i>0){
					torres[i][j]=transp[j-41];
					if(i==1)
					torres[0][j]=limpar[j-41];
					else if (i==2)
					torres[i-1][j]=topTor[j-41];
					else					
						torres[i-1][j]=pilarTor[j-41];
				}
			}
			for (i2=0; i2<22; i2++){  // printar as torres
				for (j2=0; j2<114; j2++){
					printf("%c", torres[i2][j2]);
				}
				printf("\n");			
			}
			Sleep(50);
		}
	}
	if(y=='c' || y=='C'){
		while (contDisco > torreC->qtdDisco){  // se o disco em questao esta presente na torre 
			linha+=2;
			contDisco--;
		}
		for (i=0; i<linha; i++){  // Subi o disco ate o topo
			system("CLS");
			for(j=82; j<=113; j++){	
				if(i==0)
					torres[i][j]=transp[j-82];
				else if(i>0){
					torres[i][j]=transp[j-82];
					if(i==1)
					torres[0][j]=limpar[j-82];
					else if (i==2)
					torres[i-1][j]=topTor[j-82];
					else					
						torres[i-1][j]=pilarTor[j-82];
				}
			}		
			for (i2=0; i2<22; i2++){  // printar as torres
				for (j2=0; j2<114; j2++){
					printf("%c", torres[i2][j2]);
				}
				printf("\n");			
			}
			Sleep(50);
		}
	}
	Mover_Disco(receptor, doador);
}

void Torre_qtdDiscos(int qtdDiscos, pilha *torre){
	
	if(qtdDiscos==0){
		torre->qtdDisco=0;
		return;
	}
	while(qtdDiscos>0){
		Inserir_Disco(torre, qtdDiscos);
		qtdDiscos--;
	}
	
}

int Vitoria(pilha *torreB, pilha *torreC){
	
	if(torreB->qtdDisco==7 || torreC->qtdDisco==7)
		return 1;
	else
		return 0;
		
}

int main (void){
	setlocale(LC_ALL, "portuguese");
	fila *jogMonges=Alocar_Fila();
	nno *aux;
	pilha *torreA=Alocar_Pilha();
	pilha *torreB=Alocar_Pilha();
	pilha *torreC=Alocar_Pilha();
	char x, y;
	int contMonge=0, contJogadas=100, i, resp;
	
	
	do{	// inserir monges/jogadores em uma fila de espera para comecar as partidas 
		Inserir_Monge(jogMonges);
		contMonge++;
		printf("Adicionar Novo Monge:\nS - SIM   |   N - NÃO\n");
		scanf("%c", &x);
	}while(x=='s' || x=='S');
	
	aux=jogMonges->pri;	//  o primeiro monge da fila chamado
	i=0;
	while(i<contMonge){ // criar partidas para todos os jogadores cdastrados 
		contJogadas=150; // delimitar numero de tentaivas
		
		aux->monge.qtdMovento=0;  // seus movimentos sao zerados 
		
		Torre_qtdDiscos(7, torreA); // preencher a primaira pilha/torre
		Torre_qtdDiscos(0, torreB); // preencher a primaira pilha/torre
		Torre_qtdDiscos(0, torreC); // preencher a primaira pilha/torre
		
		do{
			if(contJogadas==150){// printar as torres antes de 
				x='0';
				y='0';
				system ("CLS");
				Printar_Torre(x,y, torreA, torreB, torreC);
			} 
			printf("%s -> mov: %i/150\n\n", aux->monge.nome, aux->monge.qtdMovento+1);
			printf("Mover de [X] para [Y]\n");
			scanf(" %c %c", &x, &y);
			system ("CLS");
			Printar_Torre(x,y, torreA, torreB, torreC);
			aux->monge.qtdMovento++;
			contJogadas--;
			resp=Vitoria(torreB, torreC);
		}while(contJogadas>0 && resp==0);
		aux=aux->ant;
		i++;
	}	
	
	system ("CLS");
	printf("PLACAR\n\n");
	aux=jogMonges->pri;
	i=0;
	while(i<contMonge){
		printf("[%s] Gastou [%i] Movimentos\n", aux->monge.nome, aux->monge.qtdMovento);
		aux=aux->ant;
		i++;
	}
	
	return 0;
}
