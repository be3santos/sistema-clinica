#include <stdio.h>

int arquivo_existe(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo != NULL) {
        fclose(arquivo);
        return 1;
    }
    return 0;
}

void criar_arquivo_vazio(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo != NULL) {
        fclose(arquivo);
    }
}
