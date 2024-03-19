#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

// Definição de constantes
#define DEC 0
#define BIN 1
#define OCT 2
#define HEX 3
#define TAMBUFFER 16
#define TAMBUFFERNUMENTRADA 255

char dicionarioHex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; // Dicionário para formar números hexadecimais

// Declaração de prototipos
int converterDeDecimal(int*, int, int, int); // Converte de decimal para as outras bases
int converterParaDecimal(char*, int); // Converte das outras bases para decimal
void imprimirBuffer(int*, int, int); // Imprime o buffer do resultado da conversão
int procurarNoDicionario(char); // Retorna o valor decimal equivalente ao valor hexadecimal do dicionario
int inverterPosicoesVetor(char*, char*, int); // Coloca as posicoes do buffer 1 nas posicoes contrarias no buffer 2

int main() {
	char strNumEntrada[TAMBUFFERNUMENTRADA] = {'\0'};
	int numEntrada = 0;
	int formatoEntrada = 0;
	int formatoSaida = 0;
	int buffer[TAMBUFFER] = {0};
	int tamanhoSaida = 0;
	char quit = '\0';

	do {
		numEntrada = 0;
		formatoEntrada = 0;
		formatoSaida = 0;
		quit = '\0';
		memset(strNumEntrada, '\0', sizeof(strNumEntrada));
		memset(buffer, 0, sizeof(buffer));
		tamanhoSaida = 0;
		
		printf("Informe o numero a ser convertido: ");	
		gets(strNumEntrada);

		printf("Informe o formato do numero (DEC = 0, BIN = 1, OCT = 2, HEX = 3): ");
		scanf("%d", &formatoEntrada);
	
		printf("Informe o formato da saida (DEC = 0, BIN = 1, OCT = 2, HEX = 3): ");
		scanf("%d", &formatoSaida);

		numEntrada = converterParaDecimal(strNumEntrada, formatoEntrada);
		tamanhoSaida = converterDeDecimal(buffer, TAMBUFFER, numEntrada, formatoSaida);
		
		printf("O resultado e ");
		imprimirBuffer(buffer, tamanhoSaida, (formatoSaida == HEX));

		flushall();

		printf("\n\ndigite 'q' para sair ou qualquer outra tecla para continuar... \n");
		scanf("%c", &quit);
	} while (quit != 'q');	

	return 0;
}

int converterDeDecimal(int* buffer, int tamanhoBuffer, int numDecimal, int baseSaida) {	
	int indice = 0;
	int resultado = 0;
	int resto = 0;
	int divisor = 0;

	// Conforme a base de saída, nós escolhemos o divisor já 
	// que a lógica é sempre a mesma para todos
	if (baseSaida == BIN)
		divisor = 2;
	else if (baseSaida == OCT)
		divisor = 8;
	else if (baseSaida == DEC)
		divisor = 10;
	else if (baseSaida == HEX)
		divisor = 16;

	do {
		if (indice == 0) {
			resto = numDecimal % divisor;
			resultado = numDecimal / divisor;
		} else {
			resto = resultado % divisor;
			resultado = resultado / divisor;
		}

		buffer[indice++] = resto; // Armazena o resultado da conversão no buffer
	} while(resultado > 0);

	return indice;
}

int converterParaDecimal(char* numEntrada, int formato) {	
	int saida = 0;
	int base = 0;
	int indiceDeParada = 0;
	int valorNaPosicao = 0;
	char numEntradaInvertido[TAMBUFFERNUMENTRADA] = {'\0'};
	int indice = 0;

	if (formato == BIN)
		base = 2;
	else if (formato == OCT) {
		base = 8;
		indiceDeParada = 1;
	} else if (formato == DEC)
		base = 10;
	else if (formato == HEX) {
		base = 16;
		indiceDeParada = 2;
	}

	indice = inverterPosicoesVetor(numEntradaInvertido, numEntrada, TAMBUFFERNUMENTRADA);
	indice -= (indiceDeParada + 1);

	do {
		if (numEntradaInvertido[indice] != '\0') {
			valorNaPosicao = procurarNoDicionario(numEntradaInvertido[indice]);
			saida += (int)pow((double)base, indice) * valorNaPosicao;		
		}
	} while(indice-- >= 0);

	return saida;
}

int procurarNoDicionario(char valorHex) {
	int i = 0;
	for (; i < 16; i++) {
		if (dicionarioHex[i] == valorHex)
			return i;
	}
}

int inverterPosicoesVetor(char* invertido, char* original, int tamanho) {
	int indice = tamanho - 1;
	int indiceInvertido = 0;

	for (; indice >= 0; indice--) {
		if ( original[indice] != '\0')
			invertido[indiceInvertido++] = original[indice];
	}

	return indiceInvertido;
}

void imprimirBuffer(int* buffer, int tamanhoBuffer, int hex) {
	int i = 0;

	if (hex)
		printf("0x");
	
	for (i = (tamanhoBuffer - 1); i >= 0; i--) {
		if (hex)
			printf("%c", dicionarioHex[buffer[i]]);	
		else
			printf("%d", buffer[i]);	
	}
}