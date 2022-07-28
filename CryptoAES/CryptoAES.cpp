#include <stdio.h>
#include <string.h>

#include "Rijndael.h"

#define KEYBITS  256
#define BlockSize 16

int encrypt(char *password, char *paths[]);
int decrypt(char *password, char *paths[]);

int main(int argc, char **argv)
{
	// Argumentos
	// 0 - Nome do programa
	// 1 - Comando v�lido "encrypt" ou "decrypt"
	// 2 - Caminho do arquivo fonte
	// 3 - Caminho do arquivo destino
	// 4 - Senha para uso na criptografia
	if (argc != 5) 
	{
      printf("Parameters does not match.\r\n");
      return 0;
    }
	
	char *paths[2] = { argv[2], argv[3] };
	
	if (!strcmp(argv[1],"encrypt"))
	{
		return encrypt(argv[4], paths);
	}
	else if(!strcmp(argv[1],"decrypt"))
	{
		return decrypt(argv[4], paths);
	}
	else
	{
		return 0;
	}
}

// Fun��o encrypt AES
int encrypt(char *password, char *paths[])
{
	unsigned long rk[RKLENGTH(KEYBITS)];
	unsigned char key[KEYLENGTH(KEYBITS)];
	int i;
	bool Continue=true;
	int nrounds;
	FILE *input, *output;
	int CountSize = 0;
	
	for (i = 0; i < sizeof(key); i++)
	{
		key[i] = *password != 0 ? *password++ : 0;  
	}
	
	nrounds = rijndaelSetupEncrypt(rk, key, 256);
	
	input = fopen(paths[0], "rb");
	if (input == NULL)
	{
		printf("input file is null\r\n");
		return 0;
	}
	output = fopen(paths[1], "wb");
	if (output == NULL)
	{
		printf("output file is null\r\n");
		return 0;
	}
	
	while (Continue)
	{
		unsigned char plaintext[BlockSize];
		unsigned char ciphertext[BlockSize];
		// Retira dezesseis bytes do texto a ser criptografado
		for (i=0;i<BlockSize;i++)
		{
			plaintext[i]=fgetc(input);
			if (feof(input))//(plaintext[i]==0xFF)
			{ 
				fclose(input);
				Continue=false;
				// Completa block com espa�os
				for (;i<BlockSize;i++) plaintext[i]=' ';
				break;
			}
		}
		CountSize+=16;
		printf("  output %d\r", CountSize);
		/*
		// Apenas para visualiza��o em debug
		printf("plaintext:\r\n");
		for (i=0;i<BlockSize;i++) printf("%x ",plaintext[i]);
		printf("\r\n");
		for (i=0;i<BlockSize;i++) printf("%c ",plaintext[i]);
		printf("\r\n");
		*/
		// Executa algoritmo rijndael
		rijndaelEncrypt(rk, nrounds, plaintext, ciphertext);
		/*
		// Apenas para visualiza��o em debug
		printf("ciphertext:\r\n");
		for (i=0;i<BlockSize;i++) printf("%x ",ciphertext[i]);
		printf("\r\n\n");
		*/
		
		if (fwrite(ciphertext, 1, sizeof(ciphertext), output)==EOF)
		{
			fclose(output);
			printf("error when trying to write file\r\n");
		}
	}
	fclose(output);
	printf("\nEnd\n");
	return 1;
}

// Fun�a� decript AES
int decrypt(char *password, char *paths[])
{
	unsigned long rk[RKLENGTH(KEYBITS)];
	unsigned char key[KEYLENGTH(KEYBITS)];
	int i;
	bool Continue=true;
	int nrounds;
	FILE *input, *output;
	int CountSize = 0;

	for (i = 0; i < sizeof(key); i++)
	{
		key[i] = *password != 0 ? *password++ : 0;
	}
	nrounds = rijndaelSetupDecrypt(rk, key, 256);

	input = fopen(paths[0], "rb");
	if (input == NULL)
	{
		printf("input file is null\r\n");
		return 0;
	}
	output = fopen(paths[1], "wb");
	if (output == NULL)
	{
		printf("output file is null\r\n");
		return 0;
	}
	
	while (true)
	{
		unsigned char plaintext[BlockSize];
		unsigned char ciphertext[BlockSize];
		for (i=0;i<BlockSize;i++)
		{
			ciphertext[i]=fgetc(input);
			if (feof(input))//(ciphertext[i]==EOF||ciphertext[i]==0xFF)
			{
				fclose(input);
				Continue=false;
				break;
			}
		}
		CountSize+=16;
		printf("  output %d\r", CountSize);
		if (!Continue) break;
		/*
		// Apenas para visualiza��o em debug
		printf("ciphertext:\r\n");
		for (i=0;i<BlockSize;i++) printf("%x ",ciphertext[i]);
		printf("\r\n");
		*/
		rijndaelDecrypt(rk, nrounds, ciphertext, plaintext);
		/*
		// Apenas para visualiza��o em debug
		printf("plaintext:\r\n");
		for (i=0;i<BlockSize;i++) printf("%x ",plaintext[i]);
		printf("\r\n");
		for (i=0;i<BlockSize;i++) printf("%c ",plaintext[i]);
		printf("\r\n\n");
		*/
		fwrite(plaintext, 1, sizeof(plaintext), output);
	}
	fclose(output);
	printf("\nEnd\n");
	return 1;
}
