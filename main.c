#include <stdio.h>

#include "tabelaHash.h"

int main(){
	imprimirDadosAlunos();
	size_t i; char c;
	scanf("%15zu", &i);
	struct listaHash** tabelaHash = gerarTabelaHash(i);
	scanf("%1c", &c);
	while (c != 'f') {
		int chave;
		struct nodoHash* nodoAux;
		switch (c) {
		case 'i':
			scanf("%15d", &chave);
			if (inserir(tabelaHash, i, chave) == NULL)
				printf("Falha ao inserir %d.\n", chave);
			break;
		case 'r':
			scanf("%15d", &chave);
			nodoAux = buscar(tabelaHash, i, chave);
			if (nodoAux != NULL)
				excluir(tabelaHash, i, nodoAux);
			else
				printf("Falha ao remover %d.\n", chave);
			break;
		case 'b':
			scanf("%15d", &chave);
			nodoAux = buscar(tabelaHash, i, chave);
			if (nodoAux != NULL)
				printf("Encontrado %d.\n", nodoAux->chave);
			else
				printf("Nao encontrado %d.\n", chave);
			break;
		case 'l':
			imprimirTabelaHash(tabelaHash, i);
		default:
			break;
		}
		scanf("%1c", &c);
	}
	liberarTabelaHash(tabelaHash, i);
	tabelaHash = NULL;
	return 0;
}