#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/paciente.h"

int validar_cpf(const char *cpf) {
    if (cpf == NULL || strlen(cpf) != 11) {
        return 0;
    }
    
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    
    return 1;
}

int validar_data(const char *data) {
    if (data == NULL || strlen(data) != 10) {
        return 0;
    }
    
    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }
    
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (!isdigit(data[i])) {
                return 0;
            }
        }
    }
    
    return 1;
}

int validar_telefone(const char *telefone) {
    if (telefone == NULL || strlen(telefone) < 8) {
        return 0;
    }
    
    for (int i = 0; i < strlen(telefone); i++) {
        if (!isdigit(telefone[i]) && telefone[i] != '(' && 
            telefone[i] != ')' && telefone[i] != ' ' && telefone[i] != '-') {
            return 0;
        }
    }
    
    return 1;
}

void inserir_novo_paciente(void) {
    FILE *arquivo;

    arquivo = fopen("pacientes.bin", "ab+");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de pacientes.\n");
        return;
    }

    int tamanho = 0;
    IndexPaciente *indices = ler_arquivo_index_paciente(&tamanho);

    Paciente novo_paciente;
    
    printf("\n========== INSERIR NOVO PACIENTE ==========\n");
    printf("Digite o CPF do paciente (11 digitos): ");
    if (scanf(" %[^\n]", novo_paciente.cpf) != 1) {
        printf("Erro ao ler CPF.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    if (!validar_cpf(novo_paciente.cpf)) {
        printf("Erro: CPF invalido! Use 11 digitos.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    IndexPaciente novo_index;
    strncpy(novo_index.chave, novo_paciente.cpf, sizeof(novo_index.chave) - 1);
    novo_index.chave[sizeof(novo_index.chave) - 1] = '\0';

    int posicao_binaria = busca_binaria_paciente(indices, tamanho, novo_index);
    if (posicao_binaria < tamanho &&
        strcmp(indices[posicao_binaria].chave, novo_index.chave) == 0) {
        printf("Erro: CPF ja cadastrado!\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite o nome do paciente: ");
    if (scanf(" %[^\n]", novo_paciente.nome) != 1) {
        printf("Erro ao ler nome.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    if (scanf(" %[^\n]", novo_paciente.data_nascimento) != 1) {
        printf("Erro ao ler data.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    if (!validar_data(novo_paciente.data_nascimento)) {
        printf("Erro: Data invalida! Use formato dd/mm/aaaa.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite o telefone do paciente: ");
    if (scanf(" %[^\n]", novo_paciente.telefone) != 1) {
        printf("Erro ao ler telefone.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    if (!validar_telefone(novo_paciente.telefone)) {
        printf("Erro: Telefone invalido!\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    int pos = ftell(arquivo) / sizeof(Paciente);
    fwrite(&novo_paciente, sizeof(Paciente), 1, arquivo);

    novo_index.posicao = pos;
    inserir_ordenado_paciente(&indices, &tamanho, novo_index);
    quicksort_paciente(indices, 0, tamanho - 1);
    salvar_vetor_index_paciente(indices, tamanho);

    printf("Paciente salvo com sucesso!\n");

    free(indices);
    fclose(arquivo);
}

void alterar_dados_paciente(void) {
    char nome_busca[50];
    Paciente paciente;

    printf("\n========== ALTERAR PACIENTE ==========\n");
    printf("Digite o nome do paciente que deseja alterar: ");
    if (scanf(" %[^\n]", nome_busca) != 1) {
        printf("Erro ao ler nome.\n");
        return;
    }

    int posicao = buscar_paciente_por_nome(nome_busca, &paciente);
    if (posicao == -1) {
        printf("Paciente nao encontrado!\n");
        return;
    }

    printf("\nDados Encontrados:\n");
    printf("Nome: %s\nCPF: %s\nData de Nascimento: %s\nTelefone: %s\n",
           paciente.nome, paciente.cpf, paciente.data_nascimento, paciente.telefone);

    printf("\nDigite o novo nome: ");
    if (scanf(" %[^\n]", paciente.nome) != 1) {
        printf("Erro ao ler nome.\n");
        return;
    }

    printf("Digite a nova data de nascimento (dd/mm/aaaa): ");
    if (scanf(" %[^\n]", paciente.data_nascimento) != 1) {
        printf("Erro ao ler data.\n");
        return;
    }

    if (!validar_data(paciente.data_nascimento)) {
        printf("Erro: Data invalida! Use formato dd/mm/aaaa.\n");
        return;
    }

    printf("Digite o novo telefone: ");
    if (scanf(" %[^\n]", paciente.telefone) != 1) {
        printf("Erro ao ler telefone.\n");
        return;
    }

    if (!validar_telefone(paciente.telefone)) {
        printf("Erro: Telefone invalido!\n");
        return;
    }

    FILE *arquivo = fopen("pacientes.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pacientes!\n");
        return;
    }

    fseek(arquivo, posicao * sizeof(Paciente), SEEK_SET);
    fwrite(&paciente, sizeof(Paciente), 1, arquivo);
    fclose(arquivo);

    printf("\nDados do paciente alterados com sucesso!\n");
}

int buscar_paciente_por_nome(const char *nome_busca, Paciente *paciente_encontrado) {
    FILE *arquivo = fopen("pacientes.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pacientes!\n");
        return -1;
    }

    int posicao = 0;
    while (fread(paciente_encontrado, sizeof(Paciente), 1, arquivo)) {
        if (strcmp(nome_busca, paciente_encontrado->nome) == 0) {
            fclose(arquivo);
            return posicao;
        }
        posicao++;
    }

    fclose(arquivo);
    return -1;
}

IndexPaciente* ler_arquivo_index_paciente(int *tamanho) {
    FILE *arquivo;

    arquivo = fopen("index_pacientes.bin", "rb");
    IndexPaciente *indices = NULL;
    *tamanho = 0;

    if (arquivo != NULL) {
        fread(tamanho, sizeof(int), 1, arquivo);
        if (*tamanho > 0) {
            indices = (IndexPaciente *)malloc((*tamanho) * sizeof(IndexPaciente));
            if (indices == NULL) {
                printf("Erro de alocacao de memoria!\n");
                fclose(arquivo);
                return NULL;
            }
            fread(indices, sizeof(IndexPaciente), *tamanho, arquivo);
        }
        fclose(arquivo);
    }
    return indices;
}

int busca_binaria_paciente(IndexPaciente *v, int tam, IndexPaciente novo_index) {
    if (v == NULL) {
        return 0;
    }

    int esq = 0, dir = tam - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (strcmp(v[meio].chave, novo_index.chave) == 0) {
            return meio;
        } else if (strcmp(v[meio].chave, novo_index.chave) < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return esq;
}

void salvar_vetor_index_paciente(IndexPaciente *v, int tam) {
    FILE *arquivo = fopen("index_pacientes.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    fwrite(&tam, sizeof(int), 1, arquivo);
    fwrite(v, sizeof(IndexPaciente), tam, arquivo);
    fclose(arquivo);
}

void troca_paciente(IndexPaciente *v, int i, int j) {
    IndexPaciente aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void quicksort_paciente(IndexPaciente *v, int L, int R) {
    if (v == NULL || L >= R) {
        return;
    }

    int i = L, j = R;
    IndexPaciente vm = v[(L + R) / 2];

    do {
        while (strcmp(v[i].chave, vm.chave) < 0) i++;
        while (strcmp(v[j].chave, vm.chave) > 0) j--;

        if (i <= j) {
            troca_paciente(v, i, j);
            i++;
            j--;
        }
    } while (i <= j);

    if (L < j) quicksort_paciente(v, L, j);
    if (R > i) quicksort_paciente(v, i, R);
}

void inserir_ordenado_paciente(IndexPaciente **v, int *tam, IndexPaciente novo_index) {
    int pos = busca_binaria_paciente(*v, *tam, novo_index);

    *tam += 1;
    *v = (IndexPaciente *)realloc(*v, (*tam) * sizeof(IndexPaciente));
    if (*v == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    for (int i = *tam - 1; i > pos; i--) {
        (*v)[i] = (*v)[i - 1];
    }
    (*v)[pos] = novo_index;
}
