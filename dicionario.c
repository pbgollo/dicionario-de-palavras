#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
/*---------------------------------------------------------------*/
typedef struct NodoPalavra {
    char *palavra;
    int ocorrencias;
    struct NodoPalavra *esquerda;
    struct NodoPalavra *direita;
        struct NodoPalavra *proximoMesmoOcorrencias; 
} NodoPalavra;
/*---------------------------------------------------------------*/
typedef struct NodoLetra {
    char letra;
    struct NodoPalavra *arvore_palavras;
    struct NodoLetra *proxima;
} NodoLetra;
/*---------------------------------------------------------------*/
typedef struct {
    NodoPalavra *palavra;    
    int ocorrencias;        
    NodoPalavra **palavras; 
    int tamanho;             
    int capacidade;         
} MaiorOcorrenciaInfo;
/*---------------------------------------------------------------*/
void printaBemVindo();
void printaDivisao();
int pegaOpcao();
void menuPrincipal(NodoLetra **tabelaHash);
char *solicitarPalavraAoUsuario();
char solicitarLetraAoUsuario();
NodoPalavra *criarNodoPalavra(char *palavra);
NodoPalavra *inserirPalavra(NodoPalavra *raiz, char *palavra);
NodoLetra *criarNodoLetra(char letra);
void inserirPalavraEmListaLetra(NodoLetra **tabelaHash);
int consultarPalavra(NodoPalavra *raiz, char *palavra);
int consultaOcorrenciaPalavra(NodoLetra **tabelaHash);
void removePalavra(NodoLetra **tabelaHash);
int contaPalavras(NodoLetra **tabelaHash);
int contarPalavrasNaArvore(NodoPalavra *raiz);
NodoPalavra *removerPalavraArvore(NodoPalavra *raiz, char *palavra);
NodoPalavra *encontrarMenor(NodoPalavra *raiz);
void contaOcorrencias(NodoLetra **tabelaHash);
int somaOcorrencias(NodoPalavra *raiz);
void exibirPalavrasParaLetra(NodoLetra *nodoLetra, int ordemAlfabetica);
void exibirPalavras(NodoPalavra *raiz, int ordemAlfabetica);
void exibirMaiorOcorrencia(NodoLetra **tabelaHash);
void encontrarMaiorOcorrencia(NodoPalavra *raiz, NodoPalavra **palavrasMax, int *ocorrenciasMax);
void umaOcorrencia(NodoLetra **tabelaHash);
int escolherOrdemExibicao();
void percursoPrefixado(NodoPalavra *raiz, int *primeiraPalavra);
void percursoPosFixado(NodoPalavra *raiz, int *primeiraPalavra);
void percursoCentral(NodoPalavra *raiz, int *primeiraPalavra);
/*---------------------------------------------------------------*/
int main() {
    NodoLetra *tabelaHash[26] = {NULL};
    printaBemVindo();
    menuPrincipal(tabelaHash);
    return 0;
}
/*---------------------------------------------------------------*/
void printaBemVindo() {
   printf("━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━\n");
    printf("╭━━╮╱╱╱╱╱╱╱╱╱╱╱╱╱╭╮╱╱╭╮╱╱╱╱╱╱╱╱╭╮╱╱╱╱\n");
    printf("┃╭╮┃╱╱╱╱╱╱╱╱╱╱╱╱╱┃╰╮╭╯┃╱╱╱╱╱╱╱╱┃┃╱╱╱╱\n");
    printf("┃╰╯╰╮╭━━╮╭╮╭╮╱╱╱╱╰╮┃┃╭╯╭╮╭━━╮╭━╯┃╭━━╮\n");
    printf("┃╭━╮┃┃┃━┫┃╰╯┃╭━━╮╱┃╰╯┃╱┣┫┃╭╮┃┃╭╮┃┃╭╮┃\n");
    printf("┃╰━╯┃┃┃━┫┃┃┃┃╰━━╯╱╰╮╭╯╱┃┃┃┃┃┃┃╰╯┃┃╰╯┃\n");
    printf("╰━━━╯╰━━╯╰┻┻╯╱╱╱╱╱╱╰╯╱╱╰╯╰╯╰╯╰━━╯╰━━╯\n");
    printf("╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱\n");
    printf("━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━═━\n");   
}
/*---------------------------------------------------------------*/
void printaDivisao() {
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}
/*---------------------------------------------------------------*/
int pegaOpcao() {
    int opcao;
    printf("> Escolha uma opção:\n");
    printf("[01] Insere palavra\n");
    printf("[02] Consulta palavra\n");
    printf("[03] Remove palavra\n");
    printf("[04] Conta palavras\n");
    printf("[05] Conta ocorrências\n");
    printf("[06] Exibe palavras ordenadas\n");
    printf("[07] Exibe palavras para letra\n");
    printf("[08] Consulta maior número de ocorrências\n");
    printf("[09] Consulta palavra com uma ocorrência\n");
    printf("[10] Realiza percurso pré-fixado\n");
    printf("[11] Realiza percurso central\n");
    printf("[12] Realiza percurso pós-fixado\n");
    printf("[00] Sair\n");
    printf("> Sua opção: ");
    
    while (1) {
        if (scanf("%d", &opcao) != 1) {
            printf("> Opção inválida! Digite novamente: ");
            while (getchar() != '\n');
            continue;
        }

        if (opcao >= 0 && opcao <= 12) {
            break;
        } else {
            printf("> Opção inválida! Digite novamente: ");
        }
    }
    
    return opcao;
}
/*---------------------------------------------------------------*/
void menuPrincipal(NodoLetra **tabelaHash) {
    int opcao = pegaOpcao();
    int ordemAlfabetica;
    printaDivisao();
    NodoLetra *atual;
    int indice;
    char letra;

    while (opcao != 0) {
        switch (opcao) {
            case 1:
                inserirPalavraEmListaLetra(tabelaHash);
                break;
            case 2:
                consultaOcorrenciaPalavra(tabelaHash);
                break;
            case 3:
                removePalavra(tabelaHash);
                break;
            case 4:
                contaPalavras(tabelaHash);
                break;
             case 5:
                contaOcorrencias(tabelaHash);
                break;
            case 6:
                ordemAlfabetica = escolherOrdemExibicao();
                if (ordemAlfabetica == 1) {
                    for (int i = 0; i < 26; ++i) {
                        NodoLetra *atual = tabelaHash[i];
                        while (atual != NULL) {
                            exibirPalavrasParaLetra(atual, ordemAlfabetica); 
                            atual = atual->proxima;
                        }
                    }
                } else {
                    for (int i = 25; i >= 0; --i) {
                        NodoLetra *atual = tabelaHash[i];
                        while (atual != NULL) {
                            exibirPalavrasParaLetra(atual, ordemAlfabetica); 
                            atual = atual->proxima;
                        }
                    }
                }
                break;
            case 7:
                letra = solicitarLetraAoUsuario();
                indice = letra - 'A';
                    if (indice < 0 || indice >= 26) {
                        printf("> Letra inválida\n");
                        break;
                    }
                    atual = tabelaHash[indice];
                    while (atual != NULL) {
                        exibirPalavrasParaLetra(atual, 1);
                        atual = atual->proxima;
                    }
                break;
            case 8:
                exibirMaiorOcorrencia(tabelaHash);
                break;
            case 9:
                umaOcorrencia(tabelaHash);
                break;
            case 10:
                letra = solicitarLetraAoUsuario();
                indice = letra - 'A';
                    if (indice < 0 || indice >= 26) {
                        printf("> Letra inválida\n");
                        break;
                    }
                    atual = tabelaHash[indice];
                    while (atual != NULL) {
                        exibirPalavrasParaLetra(atual, 5);
                        atual = atual->proxima;
                    }
                break;
            case 11:
                letra = solicitarLetraAoUsuario();
                indice = letra - 'A';
                    if (indice < 0 || indice >= 26) {
                        printf("> Letra inválida\n");
                        break;
                    }
                    atual = tabelaHash[indice];
                    while (atual != NULL) {
                        exibirPalavrasParaLetra(atual, 4);
                        atual = atual->proxima;
                    }
                break;
            case 12:
                letra = solicitarLetraAoUsuario();
                indice = letra - 'A';
                    if (indice < 0 || indice >= 26) {
                        printf("> Letra inválida\n");
                        break;
                    }
                    atual = tabelaHash[indice];
                    while (atual != NULL) {
                        exibirPalavrasParaLetra(atual, 3); 
                        atual = atual->proxima;
                    }
                break;
        }

        opcao = pegaOpcao();
        printaDivisao();
    }

    printf("> Programa finalizado com sucesso!\n");
    printaDivisao();
}
/*---------------------------------------------------------------*/
char *solicitarPalavraAoUsuario() {
    char *palavra = (char *)malloc(50 * sizeof(char));
    printf("Digite uma palavra: ");
    scanf("%s", palavra);

    palavra[0] = toupper(palavra[0]);

    for (int i = 1; palavra[i] != '\0'; ++i) {
        palavra[i] = tolower(palavra[i]);
    }
    //printf("%s\n", palavra); 
    return palavra;
}
/*---------------------------------------------------------------*/
char solicitarLetraAoUsuario() {
    char letra;
    printf("> Digite uma letra: ");
    scanf(" %c", &letra);
    letra = toupper(letra); 
    return letra;
}
/*---------------------------------------------------------------*/
int escolherOrdemExibicao() {
    int opcao;
    
    while (1) {
        printf("> Escolha a ordem de exibição:\n");
        printf("[1] Ordem Alfabética (A-Z)\n");
        printf("[2] Ordem Alfabética Inversa (Z-A)\n");
        printf("> Sua opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("> Opção inválida! Digite novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        if (opcao == 1 || opcao == 2) {
            break;
        } else {
            printf("> Opção inválida! Digite novamente.\n");
        }
    }
    
    return opcao;
}
/*---------------------------------------------------------------*/
NodoPalavra *criarNodoPalavra(char *palavra) {
    NodoPalavra *novoNodo = (NodoPalavra *)malloc(sizeof(NodoPalavra));
    novoNodo->palavra = strdup(palavra);
    novoNodo->ocorrencias = 1;
    novoNodo->esquerda = novoNodo->direita = NULL;
    return novoNodo;
}
/*---------------------------------------------------------------*/
NodoPalavra *inserirPalavraArvore(NodoPalavra *raiz, char *palavra) {
    if (raiz == NULL) {
        printf("> A palavra %s foi inserida com sucesso!\n", palavra);
        return criarNodoPalavra(palavra);
    }

    int resultadoComparacao = strcmp(palavra, raiz->palavra);

    if (resultadoComparacao < 0) {
        raiz->esquerda = inserirPalavraArvore(raiz->esquerda, palavra);
    } else if (resultadoComparacao > 0) {
        raiz->direita = inserirPalavraArvore(raiz->direita, palavra);
    } else {
        raiz->ocorrencias++;
        NodoPalavra *novoNodo = criarNodoPalavra(palavra);
        novoNodo->proximoMesmoOcorrencias = raiz->proximoMesmoOcorrencias;
        raiz->proximoMesmoOcorrencias = novoNodo;
        printf("> Foi incrementado o número de ocorrências da palavra %s!\n", palavra);
    }

    return raiz;
}
/*---------------------------------------------------------------*/
NodoLetra *criarNodoLetra(char letra) {
    NodoLetra *novoNodo = (NodoLetra *)malloc(sizeof(NodoLetra));
    novoNodo->letra = letra;
    novoNodo->arvore_palavras = NULL;
    novoNodo->proxima = NULL;
    return novoNodo;
}
/*---------------------------------------------------------------*/
void inserirPalavraEmListaLetra(NodoLetra **tabelaHash) {
    char *palavra = solicitarPalavraAoUsuario();
    char letra = palavra[0];
    int indice = toupper(letra) - 'A';
    
    if (indice < 0 || indice >= 26) {
        printf("> Letra inválida\n");
        free(palavra);
        return;
    }

    NodoLetra *atual = tabelaHash[indice];

    while (atual != NULL && atual->letra != letra) {
        atual = atual->proxima;
    }

    if (atual == NULL) {
        NodoLetra *novoNodo = criarNodoLetra(letra);
        novoNodo->proxima = tabelaHash[indice];
        tabelaHash[indice] = novoNodo;
        atual = novoNodo;
    }

    atual->arvore_palavras = inserirPalavraArvore(atual->arvore_palavras, palavra);

}
/*---------------------------------------------------------------*/
int consultaOcorrenciaPalavra(NodoLetra **tabelaHash) {
    char *consultaPalavra = solicitarPalavraAoUsuario();
    char letra = consultaPalavra[0];
    int indice = toupper(letra) - 'A';

    if (indice < 0 || indice >= 26) {
        printf("> Letra inválida\n");
        free(consultaPalavra);
        return 0;
    }

    NodoLetra *atual = tabelaHash[indice];

    while (atual != NULL && atual->letra != letra) {
        atual = atual->proxima;
    }

    if (atual == NULL) {
        printf("> A palavra %s não foi encontrada no dicionário.\n", consultaPalavra);
        free(consultaPalavra);
        return 0;
    }

    int ocorrencias = consultarPalavra(atual->arvore_palavras, consultaPalavra);
    
    free(consultaPalavra);

    return ocorrencias;
}
/*---------------------------------------------------------------*/
int consultarPalavra(NodoPalavra *raiz, char *palavra) {
    if (raiz == NULL) {
        printf("> A palavra %s não foi encontrada no dicionário.\n", palavra);
        return 0;
    }

    int resultadoComparacao = strcmp(palavra, raiz->palavra);

    if (resultadoComparacao < 0) {
        return consultarPalavra(raiz->esquerda, palavra);
    } else if (resultadoComparacao > 0) {
        return consultarPalavra(raiz->direita, palavra);
    } else {
        printf("A palavra %s ocorre %d vezes.\n", palavra, raiz->ocorrencias);
        return raiz->ocorrencias;
    }
}
/*---------------------------------------------------------------*/
void removePalavra(NodoLetra **tabelaHash) {
    char *removerPalavra = solicitarPalavraAoUsuario();
    char letra = removerPalavra[0];
    int indice = toupper(letra) - 'A';

    if (indice < 0 || indice >= 26) {
        printf("> Letra inválida\n");
        free(removerPalavra);
        return;
    }

    NodoLetra *letraAtual = tabelaHash[indice];
    NodoLetra *letraAnterior = NULL;

    while (letraAtual != NULL && letraAtual->letra != letra) {
        letraAnterior = letraAtual;
        letraAtual = letraAtual->proxima;
    }

    if (letraAtual == NULL) {
        printf("> A palavra %s não foi encontrada no dicionário.\n", removerPalavra);
        free(removerPalavra);
        return;
    }

    letraAtual->arvore_palavras = removerPalavraArvore(letraAtual->arvore_palavras, removerPalavra);

    if (letraAtual->arvore_palavras == NULL) {
        if (letraAnterior == NULL) {
            tabelaHash[indice] = letraAtual->proxima;
        } else {
            letraAnterior->proxima = letraAtual->proxima;
        }

        free(letraAtual);
        printf("> A palavra %s foi removida com sucesso.\n", removerPalavra);
    }

    free(removerPalavra);
}
/*---------------------------------------------------------------*/
NodoPalavra *removerPalavraArvore(NodoPalavra *raiz, char *palavra) {
    if (raiz == NULL) {
        printf("> A palavra %s não foi encontrada no dicionário.\n", palavra);
        return NULL;
    }

    int resultadoComparacao = strcmp(palavra, raiz->palavra);

    if (resultadoComparacao < 0) {
        raiz->esquerda = removerPalavraArvore(raiz->esquerda, palavra);
    } else if (resultadoComparacao > 0) {
        raiz->direita = removerPalavraArvore(raiz->direita, palavra);
    } else {
        if (raiz->ocorrencias > 1) {
            raiz->ocorrencias--;
            printf("> Foi decrementado o número de ocorrências da palavra %s.\n", palavra);
        } else {
            if (raiz->esquerda == NULL) {
                NodoPalavra *temp = raiz->direita;
                free(raiz->palavra);
                free(raiz);
                raiz = temp;
            } else if (raiz->direita == NULL) {
                NodoPalavra *temp = raiz->esquerda;
                free(raiz->palavra);
                free(raiz);
                raiz = temp;
            } else {
                // Caso com dois filhos
                NodoPalavra *temp = encontrarMenor(raiz->direita);
                raiz->palavra = strdup(temp->palavra);
                raiz->ocorrencias = temp->ocorrencias;
                raiz->direita = removerPalavraArvore(raiz->direita, temp->palavra);
            }
        }
    }

    return raiz;
}
/*---------------------------------------------------------------*/
NodoPalavra *encontrarMenor(NodoPalavra *raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}
/*---------------------------------------------------------------*/
int contaPalavras(NodoLetra **tabelaHash) {
    int totalPalavras = 0;

    for (int i = 0; i < 26; ++i) {
        NodoLetra *atual = tabelaHash[i];
        while (atual != NULL) {
            totalPalavras += contarPalavrasNaArvore(atual->arvore_palavras);
            atual = atual->proxima;
        }
    }

    printf("> O dicionário contém %d palavras distintas.\n", totalPalavras);
    return totalPalavras;
}
/*---------------------------------------------------------------*/
int contarPalavrasNaArvore(NodoPalavra *raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return 1 + contarPalavrasNaArvore(raiz->esquerda) + contarPalavrasNaArvore(raiz->direita);
}
/*---------------------------------------------------------------*/
void contaOcorrencias(NodoLetra **tabelaHash) {
    int totalOcorrencias = 0;

    for (int i = 0; i < 26; ++i) {
        NodoLetra *atual = tabelaHash[i];
        while (atual != NULL) {
            totalOcorrencias += somaOcorrencias(atual->arvore_palavras);
            atual = atual->proxima;
        }
    }

    if (totalOcorrencias > 0) {
        printf("> O número total de ocorrências no dicionário é %d.\n", totalOcorrencias);
    } else {
        printf("> Não há ocorrências no dicionário.\n");
    }
}
/*---------------------------------------------------------------*/
int somaOcorrencias(NodoPalavra *raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return raiz->ocorrencias + somaOcorrencias(raiz->esquerda) + somaOcorrencias(raiz->direita);
}
/*---------------------------------------------------------------*/
void exibirPalavrasParaLetra(NodoLetra *nodoLetra, int ordemAlfabetica) {
    printf("%c: ", nodoLetra->letra);

    NodoPalavra *arvorePalavras = nodoLetra->arvore_palavras;
    int primeiraPalavra = 1;
    
    if (ordemAlfabetica == 1) {
        exibirPalavras(arvorePalavras, 1);
    } else if (ordemAlfabetica == 2) {
        exibirPalavras(arvorePalavras, 2);
    } else if (ordemAlfabetica == 3) {
        percursoPosFixado(arvorePalavras, &primeiraPalavra);
    } else if (ordemAlfabetica == 4){
        percursoCentral(arvorePalavras, &primeiraPalavra);
    } else if (ordemAlfabetica == 5){
        percursoPrefixado(arvorePalavras, &primeiraPalavra);
    }
    
    printf("\n");
}
/*---------------------------------------------------------------*/
void exibirPalavras(NodoPalavra *raiz, int ordemAlfabetica) {
    if (ordemAlfabetica == 1) {
        if (raiz != NULL) {
            exibirPalavras(raiz->esquerda, ordemAlfabetica);
            printf("%s (%d vezes) ", raiz->palavra, raiz->ocorrencias);
            exibirPalavras(raiz->direita, ordemAlfabetica);
        }
    } else {
        if (raiz != NULL) {
            exibirPalavras(raiz->direita, ordemAlfabetica);
            printf("%s (%d vezes) ", raiz->palavra, raiz->ocorrencias);
            exibirPalavras(raiz->esquerda, ordemAlfabetica);
        }
    }
}
/*---------------------------------------------------------------*/
void imprimirMaiorOcorrencia(NodoPalavra *raiz) {
    while (raiz != NULL) {
        printf("%s (%d vezes) ", raiz->palavra, raiz->ocorrencias);

        if (raiz->proximoMesmoOcorrencias == raiz) {
            break;
        }

        raiz = raiz->proximoMesmoOcorrencias;
    }
    printf("\n");
}
/*---------------------------------------------------------------*/
void encontrarMaiorOcorrencia(NodoPalavra *raiz, NodoPalavra **palavrasMax, int *ocorrenciasMax) {
    if (raiz != NULL) {
        encontrarMaiorOcorrencia(raiz->esquerda, palavrasMax, ocorrenciasMax);

        if (raiz->ocorrencias > *ocorrenciasMax) {
            raiz->proximoMesmoOcorrencias = NULL;

            *ocorrenciasMax = raiz->ocorrencias;
            *palavrasMax = raiz;
        } else if (raiz->ocorrencias == *ocorrenciasMax) {
            raiz->proximoMesmoOcorrencias = *palavrasMax;
            *palavrasMax = raiz;
        }

        encontrarMaiorOcorrencia(raiz->direita, palavrasMax, ocorrenciasMax);
    }
}
/*---------------------------------------------------------------*/
void exibirMaiorOcorrencia(NodoLetra **tabelaHash) {
    NodoPalavra *palavrasMax = NULL;
    int ocorrenciasMax = 0;

    for (int i = 0; i < 26; ++i) {
        NodoLetra *atual = tabelaHash[i];
        while (atual != NULL) {
            encontrarMaiorOcorrencia(atual->arvore_palavras, &palavrasMax, &ocorrenciasMax);
            atual = atual->proxima;
        }
    }

    if (palavrasMax != NULL) {
        printf("Palavra(s) com o maior número de ocorrências: ");
        imprimirMaiorOcorrencia(palavrasMax);
    } else {
        printf("O dicionário está vazio.\n");
    }
}
/*---------------------------------------------------------------*/
void exibirUmaOcorrencia(NodoPalavra *raiz, int *encontrada) {
    if (raiz != NULL) {
        exibirUmaOcorrencia(raiz->esquerda, encontrada);

        if (raiz->ocorrencias == 1) {
            if (*encontrada) {
                printf(", "); 
            }
            printf("%s", raiz->palavra);
            *encontrada = 1; 
        }

        exibirUmaOcorrencia(raiz->direita, encontrada);
    }
}
/*---------------------------------------------------------------*/
void umaOcorrencia(NodoLetra **tabelaHash) {
    printf("Palavras com uma ocorrência: ");
    
    int encontrada = 0; 

    for (int i = 0; i < 26; ++i) {
        NodoLetra *atual = tabelaHash[i];
        while (atual != NULL) {
            exibirUmaOcorrencia(atual->arvore_palavras, &encontrada);
            atual = atual->proxima;
        }
    }

    if (!encontrada) {
        printf("Nenhuma palavra foi  encontrada.\n");
    } else {
        printf("\n");
    }
}
/*---------------------------------------------------------------*/
void percursoPrefixado(NodoPalavra *raiz, int *primeiraPalavra) {
    if (raiz != NULL) {
        if (!(*primeiraPalavra)) {
            printf(", ");
        }
        printf("%s", raiz->palavra);
        *primeiraPalavra = 0;
        
        percursoPrefixado(raiz->esquerda, primeiraPalavra);
        percursoPrefixado(raiz->direita, primeiraPalavra);
    }
}
/*---------------------------------------------------------------*/
void percursoPosFixado(NodoPalavra *raiz, int *primeiraPalavra) {
    if (raiz != NULL) {
        percursoPosFixado(raiz->esquerda, primeiraPalavra);
        percursoPosFixado(raiz->direita, primeiraPalavra);
        
        if (!(*primeiraPalavra)) {
            printf(", ");
        }
        printf("%s", raiz->palavra);
        *primeiraPalavra = 0;
    }
}
/*---------------------------------------------------------------*/
void percursoCentral(NodoPalavra *raiz, int *primeiraPalavra) {
    if (raiz != NULL) {
        percursoCentral(raiz->esquerda, primeiraPalavra);
        
        if (!(*primeiraPalavra)) {
            printf(", ");
        }
        printf("%s", raiz->palavra);
        *primeiraPalavra = 0;

        percursoCentral(raiz->direita, primeiraPalavra);
    }
}
/*---------------------------------------------------------------*/