#include "tabelaHash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matarProgramaFaltaMemoria() {
    fputs("Falha ao alocar memoria.\n", stderr);
    exit(1);
}

struct aluno* getAluno1() {
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if (!retorno) matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("Luiz Henrique Murback Wiedmer"));  // sizeof conta o \0
    if (!retorno->nome)
        matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("lhmw22"));
    if (!(retorno->nomeDinf))
        matarProgramaFaltaMemoria();

    strcpy(retorno->nome, "Luiz Henrique Murback Wiedmer");
    strcpy(retorno->nomeDinf, "lhmw22");
    retorno->grr = 20221234;

    return retorno;
}

struct aluno* getAluno2() {
    return NULL;
}

void imprimirDadosAlunos() {
    struct aluno* aluno = getAluno1();

    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if (!aluno) return;

    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

size_t hash(int k, size_t m) {
    return (size_t) k % m;
}

//aloca na memoria um nodo com a chave e o retorna
struct nodoHash* gerarNodoHash(int chave) {
    struct nodoHash* nodo;
    nodo = malloc(sizeof(*nodo));
    if (nodo == NULL)
        matarProgramaFaltaMemoria();
    nodo->chave = chave;
    nodo->ant = NULL;
    nodo->prox = NULL;
    return nodo;
}

//aloca na memoria uma listaHash e a retorna
struct listaHash* gerarListaHash() {
    struct listaHash* l = malloc(sizeof(*l));
    if (l == NULL)
        matarProgramaFaltaMemoria();
    l->ini = NULL;
    l->fim = NULL;
    return l;
}

struct listaHash** gerarTabelaHash(size_t tamTabela) {
    struct listaHash** tabelaHash = (struct listaHash**) malloc(sizeof(struct listaHash*) * tamTabela);
    if (tabelaHash == NULL)
        matarProgramaFaltaMemoria();
    for (size_t i = 0; i < tamTabela; i++){
        tabelaHash[i] = NULL;
    }
    return tabelaHash;
}

//retorna 1 se a listaHash estiver vazia e 0 caso contrário
int listaVazia(struct listaHash* l) {
    if (l->ini == NULL)
        return 1;
    return 0;
}

//busca o nodo com a chave na listaHash e o retorna se ele existir, caso contrário retorna NULL
struct nodoHash* buscaNaLista(struct listaHash* l, int chave) {
    struct nodoHash* nodo = l->ini;
    while ((nodo != NULL) && (nodo->chave != chave)){
        nodo = nodo->prox;
    }
    return nodo;
}

//insere a chave na listaHash
struct nodoHash* insereNaLista(int chave, struct listaHash* l) {
    struct nodoHash* nodo =  gerarNodoHash(chave);
    if (listaVazia(l)) {
        l->ini = nodo;
        l->fim = nodo;
    }
    else {
        l->fim->prox = nodo;
        nodo->ant = l->fim;
        l->fim = nodo;
    }
    return nodo;
}

struct nodoHash* inserir(struct listaHash* tabelaHash[], size_t tamTabela, int chave) {
    size_t i = hash(chave, tamTabela);
    if (tabelaHash[i] == NULL)
        tabelaHash[i] = gerarListaHash();
    else
        if (buscaNaLista(tabelaHash[i], chave) != NULL)
            return NULL;
    struct nodoHash* nodo = insereNaLista(chave, tabelaHash[i]);
    return nodo;
}

//libera a memoria alocada para a listaHash
void liberarListaHash(struct listaHash* l) {
    struct nodoHash* nodo = l->fim;
    while (nodo != NULL) {
        l->fim = nodo->ant;
        free(nodo);
        nodo = l->fim;
    }
    free(l);
}

void liberarTabelaHash(struct listaHash* tabelaHash[], size_t tamTabela) {
    for (size_t i = 0; i < tamTabela; i++) {
        if (tabelaHash != NULL){
            if (tabelaHash[i] != NULL){
                liberarListaHash(tabelaHash[i]);
                tabelaHash[i] = NULL;
            }
        }
    }
    free(tabelaHash);
}

//imprime a listaHash do inicio ao fim e termina imprimindo NULL
void imprimirListaHash(struct listaHash* l) {
    struct nodoHash* nodo = l->ini;
    while (nodo != NULL) {
        printf(" [%d] ->", nodo->chave);
        nodo = nodo->prox;
    }
    printf(" NULL");
}

void imprimirTabelaHash(struct listaHash* tabelaHash[], size_t tamTabela) {
    for (size_t i = 0; i < tamTabela; i++) {
        printf("%ld", i);
        if (tabelaHash[i] != NULL)
            imprimirListaHash(tabelaHash[i]);
        else
            printf(" NULL");
        printf("\n");
    }
}

struct nodoHash* buscar(struct listaHash* tabelaHash[], size_t tamTabela, int chave) {
    size_t i = hash(chave, tamTabela);
    struct listaHash* l = tabelaHash[i];
    return buscaNaLista(l, chave);
}

void excluir(struct listaHash* tabelaHash[], size_t tamTabela, struct nodoHash* nodo) {
    size_t i = hash(nodo->chave, tamTabela);
    if ((nodo->ant == NULL) && (nodo->prox == NULL)) {
        tabelaHash[i]->ini = NULL;
        tabelaHash[i]->fim = NULL;
        free(nodo);
        return;
    }
    if (nodo->ant == NULL) {
        tabelaHash[i]->ini = nodo->prox;
        nodo->prox->ant = NULL;
        free(nodo);
        return;
    }
    if (nodo->prox == NULL) {
        tabelaHash[i]->fim = nodo->ant;
        nodo->ant->prox = NULL;
        free(nodo);
        return;
    }
    nodo->ant->prox = nodo->prox;
    nodo->prox->ant = nodo->ant;
    free(nodo);
}