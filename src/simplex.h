#ifndef SIMPLEX_JOVI
#define SIMPLEX_JOVI
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "macros.h"



static const double epsilon   = 1.0e-8;
int equal(double a, double b) 
{ 
	return fabs(a-b) < epsilon; 
}


typedef struct 
{
	int m, n; // m=rows, n=columns, matrix[m x n]
	double **matrix;
	char **variavel;
	int solutionColumn;
} Tableaux;




void nl(int k)
{ 
	int j; 
	for(j=0;j<k;j++) 
	{
		putchar('.'); 
	}
	putchar('\n'); 
}

void printTableaux(Tableaux *tab, const char* mes) 
{
	static int counter=0;
	int i, j;
	printf("\n%d. Tableaux %s:\n", ++counter, mes);
	nl(100);// Faz a linha bonitinha

	printf("%-6s%5s", "coluna:\t", "\t    x1");
	for(j=2;j<tab->n + 1; j++) 
	{ 
		if (j == tab->n/2 + 1)
		{
			printf("\t    Sol");			
		}
		else
		{
			if (j > tab->n/2 + 1)
			{
				printf("\t     x%d", j - 1);							
			}
			else
			{
				printf("\t    x%d", j);			
			}
		}
	} 
	printf("\n");

	for(i=0;i<tab->m; i++) 
	{
		if (i==0) 
		{
			printf("maximizar: \t"); 
		}
		else
		{
			printf("restricao %d:\t", i);
		}
		for(j=0;j<tab->n; j++) 
		{
			if (equal((int)tab->matrix[i][j], tab->matrix[i][j]))
			{
				printf(" %6lf", tab->matrix[i][j]);
			}
			else
			{
				printf(" %6.2lf", tab->matrix[i][j]);
			}
		}
		printf("\n");
	}
	nl(100);
}




bool variavelJaExiste(Tableaux *tableaux, char *variavel)
{
	int i = 0;
	for(i = 0 ; i < tableaux->n; i++)
	{
		if (strcmp(tableaux->variavel[i], variavel ) == 0 )
		{
			return true;
		}	
	}
	return false;
}


double getMultiplicadorDaString(char *string)
{
	unsigned int i;
	unsigned int multiplicador = 1;
	bool depoisDoPonto = false;
	bool primeiraVezDepoisDoPonto = true;
	double resultado = 0.0;
	for( i = 0 ; i < strlen(string) ; i++)
	{
		if (string[i] == '0' || string[i] == '1' || string[i] == '2' || string[i] == '3' || string[i] == '4' || string[i] == '5' || string[i] == '6' || string[i] == '7' || string[i] == '8' || string[i] == '9' || string[i] == '.')
		{
			if (string[i] == '.')
			{
				depoisDoPonto = true;
			}
			else
			{
				if (depoisDoPonto)
				{
					if (primeiraVezDepoisDoPonto)
					{
						multiplicador = 1;
						primeiraVezDepoisDoPonto = false;
					}
					multiplicador *= 10;
					resultado = resultado + (string[i] - '0')/(double)multiplicador;
				}
				else
				{
					resultado = (resultado*(double)multiplicador) + (string[i] - '0');
					if (resultado != 0)
					{
						multiplicador *= 10;
					}
				}
			}
		}
		else
		{
			if (resultado == 0 && !depoisDoPonto)
			{
				resultado = 1.0;
			}
			break;
		}
	}
	if (resultado <= 0)
	{
		printf("Warning: resultado == %lf\n", resultado);
	}
	return resultado;
}

char *getVariavelDaString(char *string)
{
	unsigned int i;
	unsigned int proximaPosicaoDaLetra = 0;
	bool primeiraLetra = false;
	char *resultado = (char *)calloc(sizeof(char), 1024);
	for( i = 0 ; i < strlen(string) ; i++)
	{
		if (string[i] == '0' || string[i] == '1' || string[i] == '2' || string[i] == '3' || string[i] == '4' || string[i] == '5' || string[i] == '6' || string[i] == '7' || string[i] == '8' || string[i] == '9' || string[i] == '.')
		{
			if (primeiraLetra)
			{
				resultado[proximaPosicaoDaLetra] = string[i];
			}
		}
		else
		{
			primeiraLetra = true;
			if (string[i] == ';')
			{
				break;
			}
			resultado[proximaPosicaoDaLetra] = string[i];
		}
	}
	return resultado;
}


int getNumeroVariavelNoTableauxx(Tableaux *tableaux, char * variavel)
{
	if (strlen(variavel) <= 0)
	{
		return ERRO;
	}
	// printf("10\n");
	int i;
	// printf("11\n");
	for(i = 0 ; i < tableaux->n ; i++)
	{
		// printf("12\n");
		printf("Tableaux->variavel[%d] → |%s|, eu quero o |%s|\n", i, tableaux->variavel[i], variavel);
		if(strcmp(tableaux->variavel[i], variavel) == 0)
		{
			// printf("13\n");
			return i;
		}
	}
	return ERRO;
}

int getOperadorDaString(char *string)
{
	if (string[0] == '+')
	{
		return 1;
	}
	else if (string[0] == '-')
	{
		return -1;
	}
	else
	{
		return string[0];
	}
}


double getValorSolucaoDaString(char *string)
{
	unsigned int i;
	unsigned int multiplicador = 1;
	bool depoisDoPonto = false;
	bool primeiraVezDepoisDoPonto = true;
	double resultado = 0.0;
	for( i = 0 ; i < strlen(string) ; i++)
	{
		if (string[i] == '0' || string[i] == '1' || string[i] == '2' || string[i] == '3' || string[i] == '4' || string[i] == '5' || string[i] == '6' || string[i] == '7' || string[i] == '8' || string[i] == '9' || string[i] == '.')
		{
			if (string[i] == '.')
			{
				depoisDoPonto = true;
			}
			else
			{
				if (depoisDoPonto)
				{
					if (primeiraVezDepoisDoPonto)
					{
						multiplicador = 1;
						primeiraVezDepoisDoPonto = false;
					}
					multiplicador *= 10;
					resultado = resultado + (string[i] - '0')/(double)multiplicador;
				}
				else
				{
					resultado = (resultado*(double)multiplicador) + (string[i] - '0');
					if (resultado != 0)
					{
						multiplicador *= 10;
					}
				}
			}
		}
		else
		{
			if (resultado == 0 && !depoisDoPonto)
			{
				resultado = 0.0;
			}
			break;
		}
	}
	if (resultado < 0)
	{
		printf("Warning resultado == %lf\n", resultado);
	}
	return resultado;
}



void registraFuncaoObjetivo(Tableaux *tableaux, FILE *fp, int quantidadeDeVariaveis)
{
	printf("Registrando função objetivo no tableaux\n");
	char *identificador = (char *)calloc(sizeof(char), 1024);//Variavel pode ter, no máximo, 1024 Bytes
	double multiplicador;
	int nVariavelInserida = 0;
	int i;
	int sinalDoValor = 1;
	while(!feof(fp))
	{
		fscanf(fp, "%s", identificador);
		printf("Identificador = |%s|\n", identificador);
		
		tableaux->variavel[nVariavelInserida] = getVariavelDaString(identificador);
		tableaux->matrix[0][nVariavelInserida] = sinalDoValor * -1 * getMultiplicadorDaString(identificador);
		nVariavelInserida++;
		for(i = 0;i < strlen(identificador);i++)
		{
			if(identificador[i] == ';')
			{
				return;
			}
		}
		fscanf(fp, "%s", identificador);
		if (strlen(identificador) <= 0)
		{
			tableaux->variavel[nVariavelInserida] = strdup("solucao");
			tableaux->matrix[0][nVariavelInserida] = 0;
			break;
		}
		sinalDoValor = getOperadorDaString(identificador);
	}
}

void registraRestricao(Tableaux *tableaux, FILE *fp, int quantidadeDeVariaveis, int numeroDaRestricao)
{
	printf("Registrando conteúdo da %dª restrição\n", numeroDaRestricao);
	char *identificador = (char *)calloc(sizeof(char), 1024);
	int i;
	int numeroVariavelNoTableauxx;
	int sinalDoValor = 1;
	
	while(!feof(fp))//um easter egg
	{
		// printf("1\n");
		fscanf(fp, "%s", identificador);
		// printf("2\n");
		printf("String pra checar agora : |%s|\n", identificador);
		numeroVariavelNoTableauxx = getNumeroVariavelNoTableauxx(tableaux , getVariavelDaString(identificador));
		// printf("3\n");
		tableaux->matrix[numeroDaRestricao][numeroVariavelNoTableauxx] = sinalDoValor*(getMultiplicadorDaString(identificador));
		printf("tableaux->matrix = %lf\n", tableaux->matrix[numeroDaRestricao][numeroVariavelNoTableauxx]);
		// printf("4\n");
		for(i = 0 ; i < strlen(identificador) ; i++)
		{
			// printf("5\n");
			if(identificador[i] == ';')
			{
				// printf("6\n");
				return;
			}
		}
		// printf("7\n");
		fscanf(fp, "%s", identificador);
		// printf("8\n");
		sinalDoValor = getOperadorDaString(identificador);
		if (sinalDoValor == '<')
		{
			printf("Adicionando solução à restricao %d\n", numeroDaRestricao);
			fscanf(fp, "%s", identificador);
			printf("   Variavel obtida = %s\n", identificador);
			// numeroVariavelNoTableauxx = getNumeroVariavelNoTableauxx(tableaux , getVariavelDaString(identificador));
			// tableaux->variavel[tableaux->n-1] = 
			tableaux->matrix[numeroDaRestricao][tableaux->n - 1] = getValorSolucaoDaString(identificador);
			break;
		}
		// printf("9\n");
	}
}

int readFromFile(Tableaux *tableaux, const unsigned char *fileName)
{
	if(fileName == NULL)
	{
		printf(" Nome de arquivo nulo\n");
		return ERRO;
	}
	if(tableaux == NULL)
	{
		printf("Passando nulo como argumento para tableaux\n");
		return ERRO;
	}
	printf("Iniciando leitura do arquivo somente-leitura |%s|\n", fileName);
	FILE *fp = fopen((const char *)fileName, "r");
	if (fp == NULL)
	{
		printf("Falha ao abrir arquivo, cheque a existência do arquivo e as permissões do usuario executor desse software\n");
		return ERRO;
	}

	char *operacao = (char *)calloc(sizeof(char), 100);//Assumindo que a primeira string pode ter no máximo 100 caracters (sim, sei que é inseguro...)
	char *identificador = (char *)calloc(sizeof(char), 1024);//Assumindo que a segunda string possa ter, no máximo 1024 bytes (caracteres)

	fscanf(fp, "%s %s\n", operacao, identificador);

	printf("Operação detectada = |%s|\n", operacao);
	printf("Identificador de variável detectado = |%s|\n", identificador);

	if (strcmp(operacao, "maximize") == 0)
	{
		printf("Inicializando identificação de função objetivo para maximização\n");
	}
	else
	{
		printf("Operação |%s| não suportada\n", operacao);
		return ERRO;
	}

	int quantidadeDeVariaveis = 1;
	int posicaoDeChecagem = 0;

	while(!feof(fp))
	{
		memset(identificador, '\0', 1024*sizeof(char) + 1);
		fscanf(fp, "%s", identificador);
		posicaoDeChecagem = strlen(identificador) -1;
		if (identificador[posicaoDeChecagem] == ';')
		{
			printf("Variável identificada = |%s|\n", identificador);
			quantidadeDeVariaveis += 1;
			printf("Finalizada checagem de função objetivo\n");
			break;
		}
		if (strcmp(identificador, "+") == 0 || strcmp(identificador, "-") == 0)
		{
			printf("Operação detectada = |%s|\n", identificador);
		}
		else
		{
			printf("Variável identificada = |%s|\n", identificador);
			quantidadeDeVariaveis += 1;
		}
	}

	quantidadeDeVariaveis +=1; //Adiciona espaço pra colocar a solução

	int quantidadeDeLinhas = 0;//Acabou de contar a linha da função objetivo, mas não passou o \n (que é o primeiro caracter que ele vai ler)
	char caracter;

	while(!feof(fp))
	{
		caracter = fgetc(fp);// Não preciso saber por enquanto, o que tem daqui pra baixo...
		if (caracter == '\n')
		{
			quantidadeDeLinhas++;
		}
	}

	printf("Quantidade de variáveis da função objetivo = %d\n", quantidadeDeVariaveis);
	printf("Quantidade de linhas do problema: %d\n", quantidadeDeLinhas);

	tableaux->n = quantidadeDeVariaveis;
	tableaux->m = quantidadeDeLinhas;


	tableaux->n += (tableaux->m - 1);


	// fclose(fp);// Pra reposicionar o ponteiro na posição correta.... é feio... eu sei
	// fp = fopen((const char *)fileName, "r");
	// if (fp == NULL)
	// {
	// 	printf("Falha ao abrir arquivo, cheque a existência do arquivo e as permissões do usuario executor desse software\n");
	// 	return ERRO;
	// }
	// printf("Posição no arquivo → |%d|\n", fgetpos(fp));
	fseek(fp, SEEK_SET, 0);

	memset(identificador, '\0', 1024*sizeof(char));

	printf("Alocando espaço para tableaux\n");
	tableaux->matrix = (double **)calloc(sizeof(double *), tableaux->m);//Numero de linhas
	int i;
	for( i = 0 ; i < tableaux->n; i++ )
	{
		tableaux->matrix[i] = (double *)calloc(sizeof(double), tableaux->n);//Numero de colunas
	}
	tableaux->variavel = (char **)calloc(sizeof(char *), quantidadeDeVariaveis);
	printf("Espaço alocado para tableaux\n");
	
	tableaux->n -= (tableaux->m - 1);


	fscanf(fp, "%s", operacao);//Pro ponteiro passar de "maximize", pra primeira variavel da função objetivo
	// printf(" QUe merda isso pegou = |%s|\n", operacao);

	registraFuncaoObjetivo(tableaux, fp, quantidadeDeVariaveis);

	for( i = 1 ; i < tableaux->m ; i++ )
	{
		registraRestricao(tableaux, fp, quantidadeDeVariaveis, i);
	}

	return OK;
}


void pivotOn(Tableaux *tab, int row, int col) 
{
	int i, j;
	double pivot;

	pivot = tab->matrix[row][col];
	assert( pivot > 0 );// Se cancelar o programa, é porque o pivot tá doidão

	for(j=0;j<tab->n;j++)// Gera a nova linha pivot
	{
		tab->matrix[row][j] /= pivot;
	}

	assert( equal(tab->matrix[row][col], 1.0 ));// Após a nova linha pivô ser gerada, o número pivô precisa ser igual a 1, já que foi dividido por ele mesmo.

	for(i=0 ; i < tab->m ; i++) 
	{ // foreach remaining row i do
		double multiplier = tab->matrix[i][col];// Pega a variável da linha que está na coluna do pivô
		if( i != row )// Se a linha não é a linha pivô
		{
			for(j=0; j<tab->n ; j++)//Varre as variáveis da linha
			{ // r[i] = r[i] - z * r[row];
				tab->matrix[i][j] -= multiplier * tab->matrix[row][j];
			}	
		}
	}
}

// Acha a coluna do pivô = A coluna mais negativa (com o valor mais negativo)
int findPivotColumn(Tableaux *tab) 
{
	int j, pivotColumn = 1;
	double lowest = tab->matrix[0][pivotColumn];
	for(j=0; j< tab->n + ((tab->m-1)*2) ; j++) 
	{
		if (tab->matrix[0][j] < lowest) 
		{
			lowest = tab->matrix[0][j];
			pivotColumn = j;
		}
	}

	printf("Coluna mais negativa na linha[0] é a coluna %d = %lf.\n", pivotColumn, lowest);
	if( lowest >= 0 ) 
	{
		return -1; // Se todas as colunas forem positivas, ficam otimas
	}
	return pivotColumn;
}

// Acha a linha do pivot, com o menor numero positivo = coluna[0] / coluna[pivot]
int findPivotRow(Tableaux *tab, int pivotColumn) 
{
	int i = 0;
	double x;
	double valor = 61287812.1;
	double menor = 45615675.1;
	int linha;
	for(i = 0;i < tab->m;i++)
	{
		x = tab->matrix[i][tab->n - (tab->m)];

		valor = x/tab->matrix[i][pivotColumn];
		if (valor < menor && valor > 0)
		{
			menor = valor;
			linha = i;
		}
	}

	return linha;
	


	// int i, pivotRow = 0;
	// double min_ratio = -1;
	// printf("Ratios A[row_i,0]/A[row_i,%d] = [",pivotColumn);
	// for(i=1;i<tab->m;i++)
	// {
	// 	double ratio = tab->matrix[i][0] / tab->matrix[i][pivotColumn];
	// 	printf("%3.2lf, ", ratio);
	// 	if ( (ratio > 0  && ratio < min_ratio ) || min_ratio < 0 ) 
	// 	{
	// 		min_ratio = ratio;
	// 		pivotRow = i;
	// 	}
	// }
	// printf("].\n");
	// if (min_ratio == -1)
	// {
	// 	return -1; // Unbounded.
	// }
	// printf("Found pivot A[%d,%d], min positive ratio=%g in row=%d.\n", pivotRow, pivotColumn, min_ratio, pivotRow);
	// return pivotRow;
}

void add_slack_variables(Tableaux *tab) //Adiciona as variáveis auxiliares
{
	int i, j;
	for(i=1; i<tab->m; i++) 
	{
		for(j=1; j<tab->m; j++)
		{
			tab->matrix[i][j + tab->n -1] = (i==j);
		}
	}
	tab->n += tab->m -1;
}

void check_b_positive(Tableaux *tab) //Checa se a solução é positiva
{
	int i;
	for(i=1; i<tab->m; i++)
	{
		assert(tab->matrix[i][tab->n - 1] >= 0);
		// assert(tab->matrix[i][((tab->n) / 2)+1]);
	}
}

// Given a column of identity matrix, find the row containing 1.
// return -1, if the column as not from an identity matrixrix.
int findBasisVar(Tableaux *tab, int col) 
{
	int i, xi=-1;
	for(i=1; i < tab->m; i++) 
	{
		if (equal( tab->matrix[i][col],1) ) 
		{
			if (xi == -1)
			{
				xi=i;   // found first '1', save this row number.
			}
			else
			{
				return -1; // found second '1', not an identity matrixrix.
			}

		} 
		else if (!equal( tab->matrix[i][col],0) ) 
		{
			return -1; // not an identity matrixrix column.
		}
	}
	printf("Coluna do valor da matriz identidade que contem \"1\" = |%d|\n", xi);
	return xi;
}

void printOptimalVector(Tableaux *tab, const char *message) 
{
	int j, xi;
	printf("%s em ", message);
	for(j=1;j<tab->n;j++) 
	{ // for each column.
		xi = findBasisVar(tab, j);
		if (xi != -1)
		{
			printf("S%d=%3.2lf, ", j, tab->matrix[xi][(tab->n/2)] );
		}
		else
		{
			printf("S%d=0, ", j);
		}
	}
	printf("\n");
} 

void simplex(Tableaux *tab) 
{
	int loop=0;
	add_slack_variables(tab);
	check_b_positive(tab);
	printTableaux(tab,"Tabela com variáveis auxiliares");
	while( ++loop ) 
	{
		int pivotColumn, pivotRow;

		pivotColumn = findPivotColumn(tab);//Encontra a coluna pivo
		if( pivotColumn < 0 ) 
		{
			printf("Descoberto valor ótimo tableaux->mat[0,%d]=%3.2lf (sem numeros negativos na linha 0 (z)).\n", (tab->n - tab->m),tab->matrix[0][(tab->n - tab->m)]);
			printOptimalVector(tab, "Vetor com as soluções (da solução ótima)");
			break;
		}
		printf("Coluna pivô=%d.\n", pivotColumn + 1);

		pivotRow = findPivotRow(tab, pivotColumn);//Encontra a linha pivo
		if (pivotRow < 0) 
		{
			printf("ERRO: Pivot não encontrado, linha bugada.\n");
			break;
		}
		printf("Linha pivot=%d\n", pivotRow + 1);

		pivotOn(tab, pivotRow, pivotColumn);
		printTableaux(tab,"Depois de gerar os valores com o pivot");
		printOptimalVector(tab, "Vetor com valores de solucao");

		printf("tableaux->n == %d\n", tab->n);

		if(loop > 40000) 
		{
			printf("Numero de iterações excedeu o limite > %d.\n", loop);
			break;
		}
	}
}




#endif //SIMPLEX_JOVI
