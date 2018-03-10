#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "macros.h"
#include "validadorDeInput.h"
#include "simplex.h"

int main(const unsigned int argc, const unsigned char *argv[])
{
	int retorno;
	if( argc == 1 )
	{
		printf(" Ok, então você passou só um argumento :/\n");
		printf("\n\n");
		printf(" Digite --help para saber os parâmetros que o programa aceita\n");
		return 0;
	}
	else
	{
		retorno = validaInput(argv);
		if( retorno == INPUT_VALIDO )
		{
			printf(" Começando analise do arquivo |%s|\n", argv[1]);
			Tableaux tabela;
			printf("Tabela Criada\n");
			readFromFile(&tabela, argv[1]);
			printTableaux(&tabela, "Mensagem que eu quero");
			simplex(&tabela);
		}
		else if( retorno == SOLICITANDO_HELP )
		{
			return 0;
		}
		else
		{
			printf(" Entrada inválida detectada, abortando\n");
			return -1;
		}
	}
	return 0;
}
