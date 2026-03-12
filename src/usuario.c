#include <stdio.h>
#include <string.h>
#include "../include/usuario.h"

void cadastrar_novo_usuario(void) {
    Login novo_usuario, usuarios;
    FILE *arquivo;

    arquivo = fopen("login.bin", "a+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de login.\n");
        return;
    }

    int cadastrou = 0;

    while (cadastrou != 1) {
        printf("Digite o nome do usuario: ");
        if (scanf(" %[^\n]", novo_usuario.usuario) != 1) {
            printf("Erro ao ler usuario.\n");
            fclose(arquivo);
            return;
        }
        printf("Digite a senha: ");
        if (scanf(" %[^\n]", novo_usuario.senha) != 1) {
            printf("Erro ao ler senha.\n");
            fclose(arquivo);
            return;
        }

        int senha_existe = 0;
        rewind(arquivo);

        while (fread(&usuarios, sizeof(Login), 1, arquivo)) {
            if (strcmp(usuarios.senha, novo_usuario.senha) == 0) {
                printf("Essa senha ja existe!\n");
                senha_existe = 1;
                break;
            }
        }

        if (senha_existe != 1) {
            fwrite(&novo_usuario, sizeof(Login), 1, arquivo);
            printf("Usuario Cadastrado com sucesso!!!\n");
            cadastrou = 1;
        }
    }

    fclose(arquivo);
}

int verificar_login(void) {
    Login usuario, usuario_entrada;
    FILE *arquivo;

    arquivo = fopen("login.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de login nao encontrado.\n");
        return 0;
    }

    int tentativas = 1;

    while (tentativas <= 3) {
        printf("Digite o login: ");
        if (scanf(" %[^\n]", usuario_entrada.usuario) != 1) {
            printf("Erro ao ler login.\n");
            fclose(arquivo);
            return 0;
        }

        printf("\nDigite a senha: ");
        if (scanf(" %[^\n]", usuario_entrada.senha) != 1) {
            printf("Erro ao ler senha.\n");
            fclose(arquivo);
            return 0;
        }

        rewind(arquivo);

        while (fread(&usuario, sizeof(Login), 1, arquivo)) {
            if (strcmp(usuario.usuario, usuario_entrada.usuario) == 0 &&
                strcmp(usuario.senha, usuario_entrada.senha) == 0) {
                fclose(arquivo);
                return 1;
            }
        }

        printf("Informacoes erradas. Voce tem mais %d tentativas\n", 3 - tentativas);
        tentativas++;
    }

    fclose(arquivo);
    return 0;
}
