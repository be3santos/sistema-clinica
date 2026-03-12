#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/medico.h"
#include "../include/paciente.h"

int validar_crm(const char *crm) {
    if (crm == NULL || strlen(crm) != 6) {
        return 0;
    }
    
    for (int i = 0; i < 6; i++) {
        if (!isdigit(crm[i])) {
            return 0;
        }
    }
    
    return 1;
}

void inserir_novo_medico(void) {
    FILE *arquivo;

    arquivo = fopen("medicos.bin", "ab+");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de medicos.\n");
        return;
    }

    int tamanho_medico = 0;
    IndexMedico *indices = ler_arquivo_index_medico(&tamanho_medico);

    Medico novo_medico;
    
    printf("\n========== INSERIR NOVO MEDICO ==========\n");
    printf("Digite o CRM do medico (6 digitos): ");
    if (scanf(" %[^\n]", novo_medico.crm) != 1) {
        printf("Erro ao ler CRM.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    if (!validar_crm(novo_medico.crm)) {
        printf("Erro: CRM invalido! Use 6 digitos.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    IndexMedico novo_index;
    strncpy(novo_index.crm, novo_medico.crm, sizeof(novo_index.crm) - 1);
    novo_index.crm[sizeof(novo_index.crm) - 1] = '\0';

    int posicao_binaria = busca_binaria_medico(indices, tamanho_medico, novo_index);
    if (posicao_binaria < tamanho_medico &&
        strcmp(indices[posicao_binaria].crm, novo_index.crm) == 0) {
        printf("Erro: CRM ja cadastrado!\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite o nome do medico: ");
    if (scanf(" %[^\n]", novo_medico.nome) != 1) {
        printf("Erro ao ler nome.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    if (scanf(" %[^\n]", novo_medico.data_nascimento) != 1) {
        printf("Erro ao ler data.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    if (!validar_data(novo_medico.data_nascimento)) {
        printf("Erro: Data invalida! Use formato dd/mm/aaaa.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite o telefone do medico: ");
    if (scanf(" %[^\n]", novo_medico.telefone) != 1) {
        printf("Erro ao ler telefone.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    if (!validar_telefone(novo_medico.telefone)) {
        printf("Erro: Telefone invalido!\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite a especialidade do medico: ");
    if (scanf(" %[^\n]", novo_medico.especialidade) != 1) {
        printf("Erro ao ler especialidade.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    printf("Digite o valor da hora de trabalho do medico: ");
    if (scanf("%f", &novo_medico.valor_hora) != 1) {
        printf("Erro ao ler valor da hora.\n");
        free(indices);
        fclose(arquivo);
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    int pos = ftell(arquivo) / sizeof(Medico);
    fwrite(&novo_medico, sizeof(Medico), 1, arquivo);

    novo_index.posicao = pos;
    inserir_ordenado_medico(&indices, &tamanho_medico, novo_index);
    quicksort_medico(indices, 0, tamanho_medico - 1);
    salvar_vetor_index_medico(indices, tamanho_medico);

    printf("Medico salvo com sucesso!\n");

    free(indices);
    fclose(arquivo);
}

int buscar_medico_por_nome(const char *nome_busca, Medico *medico_encontrado) {
    FILE *arquivo = fopen("medicos.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de medicos!\n");
        return -1;
    }

    int posicao = 0;
    while (fread(medico_encontrado, sizeof(Medico), 1, arquivo)) {
        if (strcmp(nome_busca, medico_encontrado->nome) == 0) {
            fclose(arquivo);
            return posicao;
        }
        posicao++;
    }

    fclose(arquivo);
    return -1;
}

void listar_medicos_por_especialidade(void) {
    char especialidade_busca[20];
    Medico medico;

    printf("\n========== LISTAR MEDICOS POR ESPECIALIDADE ==========\n");
    printf("Digite a especialidade que deseja buscar: ");
    if (scanf(" %[^\n]", especialidade_busca) != 1) {
        printf("Erro ao ler especialidade.\n");
        return;
    }

    FILE *arquivo = fopen("medicos.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de medicos!\n");
        return;
    }

    int encontrados = 0;

    printf("\nMedicos encontrados na especialidade '%s':\n", especialidade_busca);
    while (fread(&medico, sizeof(Medico), 1, arquivo)) {
        if (strcmp(especialidade_busca, medico.especialidade) == 0) {
            printf("\nNome: %s\n", medico.nome);
            printf("CRM: %s\n", medico.crm);
            printf("Data de Nascimento: %s\n", medico.data_nascimento);
            printf("Telefone: %s\n", medico.telefone);
            printf("Especialidade: %s\n", medico.especialidade);
            printf("Valor da Hora de Trabalho: R$ %.2f\n", medico.valor_hora);
            printf("--------------------------\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum medico encontrado com a especialidade '%s'.\n", especialidade_busca);
    }

    fclose(arquivo);
}

void alterar_dados_medico(void) {
    char nome_busca[50];
    Medico medico;

    printf("\n========== ALTERAR MEDICO ==========\n");
    printf("Digite o nome do medico que deseja alterar: ");
    if (scanf(" %[^\n]", nome_busca) != 1) {
        printf("Erro ao ler nome.\n");
        return;
    }

    int posicao = buscar_medico_por_nome(nome_busca, &medico);
    if (posicao == -1) {
        printf("Medico nao encontrado!\n");
        return;
    }

    printf("\nDigite o novo nome: ");
    if (scanf(" %[^\n]", medico.nome) != 1) {
        printf("Erro ao ler nome.\n");
        return;
    }

    printf("Digite a nova data de nascimento: ");
    if (scanf(" %[^\n]", medico.data_nascimento) != 1) {
        printf("Erro ao ler data.\n");
        return;
    }

    if (!validar_data(medico.data_nascimento)) {
        printf("Erro: Data invalida!\n");
        return;
    }

    printf("Digite o novo telefone: ");
    if (scanf(" %[^\n]", medico.telefone) != 1) {
        printf("Erro ao ler telefone.\n");
        return;
    }

    if (!validar_telefone(medico.telefone)) {
        printf("Erro: Telefone invalido!\n");
        return;
    }

    printf("Digite a nova especialidade: ");
    if (scanf(" %[^\n]", medico.especialidade) != 1) {
        printf("Erro ao ler especialidade.\n");
        return;
    }

    printf("Digite o novo valor da hora de trabalho: ");
    if (scanf("%f", &medico.valor_hora) != 1) {
        printf("Erro ao ler valor.\n");
        return;
    }

    FILE *arquivo = fopen("medicos.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de medicos!\n");
        return;
    }

    fseek(arquivo, posicao * sizeof(Medico), SEEK_SET);
    fwrite(&medico, sizeof(Medico), 1, arquivo);
    fclose(arquivo);

    printf("\nDados do medico alterados com sucesso!\n");
}

IndexMedico* ler_arquivo_index_medico(int *tamanho_medico) {
    FILE *arquivo;

    arquivo = fopen("index_medico.bin", "rb");
    IndexMedico *indices = NULL;
    *tamanho_medico = 0;

    if (arquivo != NULL) {
        fread(tamanho_medico, sizeof(int), 1, arquivo);
        if (*tamanho_medico > 0) {
            indices = (IndexMedico *)malloc((*tamanho_medico) * sizeof(IndexMedico));
            if (indices == NULL) {
                printf("Erro de alocacao de memoria!\n");
                fclose(arquivo);
                return NULL;
            }
            fread(indices, sizeof(IndexMedico), *tamanho_medico, arquivo);
        }
        fclose(arquivo);
    }
    return indices;
}

int busca_binaria_medico(IndexMedico *v, int tam, IndexMedico novo_index) {
    if (v == NULL) {
        return 0;
    }

    int esq = 0, dir = tam - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (strcmp(v[meio].crm, novo_index.crm) == 0) {
            return meio;
        } else if (strcmp(v[meio].crm, novo_index.crm) < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return esq;
}

void salvar_vetor_index_medico(IndexMedico *v, int tam) {
    FILE *arquivo = fopen("index_medico.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    fwrite(&tam, sizeof(int), 1, arquivo);
    fwrite(v, sizeof(IndexMedico), tam, arquivo);
    fclose(arquivo);
}

void troca_medico(IndexMedico *v, int i, int j) {
    IndexMedico aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void quicksort_medico(IndexMedico *v, int L, int R) {
    if (v == NULL || L >= R) {
        return;
    }

    int i = L, j = R;
    IndexMedico vm = v[(L + R) / 2];

    do {
        while (strcmp(v[i].crm, vm.crm) < 0) i++;
        while (strcmp(v[j].crm, vm.crm) > 0) j--;

        if (i <= j) {
            troca_medico(v, i, j);
            i++;
            j--;
        }
    } while (i <= j);

    if (L < j) quicksort_medico(v, L, j);
    if (R > i) quicksort_medico(v, i, R);
}

void inserir_ordenado_medico(IndexMedico **v, int *tam, IndexMedico novo_index) {
    int pos = busca_binaria_medico(*v, *tam, novo_index);

    *tam += 1;
    *v = (IndexMedico *)realloc(*v, (*tam) * sizeof(IndexMedico));
    if (*v == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    for (int i = *tam - 1; i > pos; i--) {
        (*v)[i] = (*v)[i - 1];
    }
    (*v)[pos] = novo_index;
}
