#ifndef VALIDADOR_JOVI
#define VALIDADOR_JOVI
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include "macros.h"

bool nomeArquivoValido(const char *nomeArquivo)
{
	int fd = open(nomeArquivo, O_RDONLY);
	if( fd <= 0 )
	{
		return false;
	}
	else
	{
		close(fd);
		return true;
	}
}

void showHelp(void)
{
	printf(" *********** HELP ***************\n");
	printf(" Para saber a respeito da sintaxe aceita, digite --help syntax\n");
	printf(" Para ler um arquivo, passe o endereço ou nome dele como parâmetro\n");
	return;
}

int validaInput(const unsigned char **input)
{
	if( strcmp(input[1], "--help") == 0 )
	{
		showHelp();
		return SOLICITANDO_HELP;
	}
	else
	{
		printf(" Arquivo para ler = |%s|\n", input[1]);
		if( nomeArquivoValido(input[1]) )
		{
			printf(" Arquivo existe no sistema de arquivos\n");
			return INPUT_VALIDO;
		}
		else
		{
			printf(" Arquivo |%s| não existe\n", input[1]);
			printf(" Rode o programa novamente com a opção \"--help\"\n");
			return INPUT_INVALIDO;
		}
	}
}





#endif //VALIDADOR_JOVI
