#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/consulta.h"
#include "../include/medico.h"
#include "../include/paciente.h"

void inserir_nova_consulta(void) {
    Consulta nova_consulta;
    char crm[7], cpf[12];

    printf("\n========== INSERIR NOVA CONSULTA ==========\n");
    printf("CRM do Medico (6 digitos): ");
    if (scanf("%s", crm) != 1) {
        printf("Erro ao ler CRM.\n");
        return;
    }

    if (!validar_crm(crm)) {
        printf("Erro: CRM invalido!\n");
        return;
    }

    FILE *arquivo_medicos = fopen("medicos.bin", "rb");
    if (arquivo_medicos == NULL) {
        printf("Erro ao abrir arquivo de medicos.\n");
        return;
    }

    Medico medico;
    int medico_encontrado = 0;
    while (fread(&medico, sizeof(Medico), 1, arquivo_medicos)) {
        if (strcmp(medico.crm, crm) == 0) {
            medico_encontrado = 1;
            break;
        }
    }
    fclose(arquivo_medicos);

    if (!medico_encontrado) {
        printf("Medico com CRM %s nao encontrado.\n", crm);
        return;
    }

    printf("CPF do Paciente (11 digitos): ");
    if (scanf("%s", cpf) != 1) {
        printf("Erro ao ler CPF.\n");
        return;
    }

    if (!validar_cpf(cpf)) {
        printf("Erro: CPF invalido!\n");
        return;
    }

    FILE *arquivo_pacientes = fopen("pacientes.bin", "rb");
    if (arquivo_pacientes == NULL) {
        printf("Erro ao abrir arquivo de pacientes.\n");
        return;
    }

    Paciente paciente;
    int paciente_encontrado = 0;
    while (fread(&paciente, sizeof(Paciente), 1, arquivo_pacientes)) {
        if (strcmp(paciente.cpf, cpf) == 0) {
            paciente_encontrado = 1;
            break;
        }
    }
    fclose(arquivo_pacientes);

    if (!paciente_encontrado) {
        printf("Paciente com CPF %s nao encontrado.\n", cpf);
        return;
    }

    strcpy(nova_consulta.crm_medico, crm);
    strcpy(nova_consulta.cpf_paciente, cpf);

    printf("Data da Consulta (dd/mm/aaaa): ");
    if (scanf("%s", nova_consulta.data) != 1) {
        printf("Erro ao ler data.\n");
        return;
    }

    if (!validar_data(nova_consulta.data)) {
        printf("Erro: Data invalida!\n");
        return;
    }

    printf("Sintomas: ");
    if (scanf(" %[^\n]", nova_consulta.sintomas) != 1) {
        printf("Erro ao ler sintomas.\n");
        return;
    }

    printf("Encaminhamentos: ");
    if (scanf(" %[^\n]", nova_consulta.encaminhamentos) != 1) {
        printf("Erro ao ler encaminhamentos.\n");
        return;
    }

    FILE *arquivo_consultas = fopen("consultas.bin", "ab");
    if (arquivo_consultas == NULL) {
        printf("Erro ao abrir arquivo de consultas.\n");
        return;
    }

    fseek(arquivo_consultas, 0, SEEK_END);
    int posicao = ftell(arquivo_consultas) / sizeof(Consulta);
    fwrite(&nova_consulta, sizeof(Consulta), 1, arquivo_consultas);
    fclose(arquivo_consultas);

    IndexConsulta novo_index_medico, novo_index_paciente;

    strcpy(novo_index_medico.chave, crm);
    novo_index_medico.posicao = posicao;

    int tamanho_medico = 0;
    IndexConsulta *indices_medico = ler_arquivo_index_consulta("index_consultas_medico.bin", &tamanho_medico);
    inserir_ordenado_consulta(&indices_medico, &tamanho_medico, novo_index_medico);
    salvar_vetor_index_consulta("index_consultas_medico.bin", indices_medico, tamanho_medico);
    free(indices_medico);

    strcpy(novo_index_paciente.chave, cpf);
    novo_index_paciente.posicao = posicao;

    int tamanho_paciente = 0;
    IndexConsulta *indices_paciente = ler_arquivo_index_consulta("index_consultas_paciente.bin", &tamanho_paciente);
    inserir_ordenado_consulta(&indices_paciente, &tamanho_paciente, novo_index_paciente);
    salvar_vetor_index_consulta("index_consultas_paciente.bin", indices_paciente, tamanho_paciente);
    free(indices_paciente);

    printf("Consulta cadastrada com sucesso!\n");
}

void listar_consultas_por_medico(void) {
    char crm[7];
    
    printf("\n========== LISTAR CONSULTAS POR MEDICO ==========\n");
    printf("Digite o CRM do medico (6 digitos): ");
    if (scanf("%s", crm) != 1) {
        printf("Erro ao ler CRM.\n");
        return;
    }

    if (!validar_crm(crm)) {
        printf("Erro: CRM invalido!\n");
        return;
    }

    int tamanho = 0;
    IndexConsulta *indices = ler_arquivo_index_consulta("index_consultas_medico.bin", &tamanho);

    int pos = busca_binaria_consulta(indices, tamanho, crm);
    if (pos == -1) {
        printf("Nenhuma consulta encontrada para o medico com CRM %s.\n", crm);
        free(indices);
        return;
    }

    FILE *arquivo_consultas = fopen("consultas.bin", "rb");
    if (arquivo_consultas == NULL) {
        printf("Erro ao abrir arquivo de consultas.\n");
        free(indices);
        return;
    }

    Consulta consulta;
    fseek(arquivo_consultas, indices[pos].posicao * sizeof(Consulta), SEEK_SET);
    fread(&consulta, sizeof(Consulta), 1, arquivo_consultas);

    printf("\nData: %s\n", consulta.data);
    printf("Paciente: %s\n", consulta.cpf_paciente);
    printf("Sintomas: %s\n", consulta.sintomas);
    printf("Encaminhamentos: %s\n", consulta.encaminhamentos);
    printf("----------------------------\n");

    fclose(arquivo_consultas);
    free(indices);
}

void listar_consultas_por_paciente(void) {
    char cpf[12];
    
    printf("\n========== LISTAR CONSULTAS POR PACIENTE ==========\n");
    printf("Digite o CPF do paciente (11 digitos): ");
    if (scanf("%s", cpf) != 1) {
        printf("Erro ao ler CPF.\n");
        return;
    }

    if (!validar_cpf(cpf)) {
        printf("Erro: CPF invalido!\n");
        return;
    }

    int tamanho = 0;
    IndexConsulta *indices = ler_arquivo_index_consulta("index_consultas_paciente.bin", &tamanho);

    int pos = busca_binaria_consulta(indices, tamanho, cpf);
    if (pos == -1) {
        printf("Nenhuma consulta encontrada para o paciente com CPF %s.\n", cpf);
        free(indices);
        return;
    }

    FILE *arquivo_consultas = fopen("consultas.bin", "rb");
    if (arquivo_consultas == NULL) {
        printf("Erro ao abrir arquivo de consultas.\n");
        free(indices);
        return;
    }

    Consulta consulta;
    fseek(arquivo_consultas, indices[pos].posicao * sizeof(Consulta), SEEK_SET);
    fread(&consulta, sizeof(Consulta), 1, arquivo_consultas);

    printf("\nData: %s\n", consulta.data);
    printf("Medico: %s\n", consulta.crm_medico);
    printf("Sintomas: %s\n", consulta.sintomas);
    printf("Encaminhamentos: %s\n", consulta.encaminhamentos);
    printf("----------------------------\n");

    fclose(arquivo_consultas);
    free(indices);
}

void listar_consultas_por_data(void) {
    char data[11];
    
    printf("\n========== LISTAR CONSULTAS POR DATA ==========\n");
    printf("Digite a data da consulta (dd/mm/aaaa): ");
    if (scanf("%s", data) != 1) {
        printf("Erro ao ler data.\n");
        return;
    }

    if (!validar_data(data)) {
        printf("Erro: Data invalida!\n");
        return;
    }

    FILE *arquivo_consultas = fopen("consultas.bin", "rb");
    if (arquivo_consultas == NULL) {
        printf("Erro ao abrir arquivo de consultas.\n");
        return;
    }

    Consulta consulta;
    int encontradas = 0;

    while (fread(&consulta, sizeof(Consulta), 1, arquivo_consultas)) {
        if (strcmp(consulta.data, data) == 0) {
            printf("\nMedico: %s\n", consulta.crm_medico);
            printf("Paciente: %s\n", consulta.cpf_paciente);
            printf("Sintomas: %s\n", consulta.sintomas);
            printf("Encaminhamentos: %s\n", consulta.encaminhamentos);
            printf("----------------------------\n");
            encontradas++;
        }
    }
    fclose(arquivo_consultas);

    if (encontradas == 0) {
        printf("Nenhuma consulta encontrada para a data %s.\n", data);
    }
}

IndexConsulta* ler_arquivo_index_consulta(const char *nome_arquivo, int *tamanho) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    IndexConsulta *indices = NULL;
    *tamanho = 0;

    if (arquivo != NULL) {
        fread(tamanho, sizeof(int), 1, arquivo);
        if (*tamanho > 0) {
            indices = (IndexConsulta *)malloc((*tamanho) * sizeof(IndexConsulta));
            if (indices == NULL) {
                printf("Erro de alocacao de memoria!\n");
                fclose(arquivo);
                return NULL;
            }
            fread(indices, sizeof(IndexConsulta), *tamanho, arquivo);
        }
        fclose(arquivo);
    }
    return indices;
}

int busca_binaria_consulta(IndexConsulta *v, int tam, const char *chave) {
    if (v == NULL) {
        return -1;
    }

    int esq = 0, dir = tam - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (strcmp(v[meio].chave, chave) == 0) {
            return meio;
        } else if (strcmp(v[meio].chave, chave) < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return -1;
}

void salvar_vetor_index_consulta(const char *nome_arquivo, IndexConsulta *v, int tam) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    fwrite(&tam, sizeof(int), 1, arquivo);
    fwrite(v, sizeof(IndexConsulta), tam, arquivo);
    fclose(arquivo);
}

void troca_consulta(IndexConsulta *v, int i, int j) {
    IndexConsulta aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void quicksort_consulta(IndexConsulta *v, int L, int R) {
    if (v == NULL || L >= R) {
        return;
    }

    int i = L, j = R;
    IndexConsulta vm = v[(L + R) / 2];

    do {
        while (strcmp(v[i].chave, vm.chave) < 0) i++;
        while (strcmp(v[j].chave, vm.chave) > 0) j--;

        if (i <= j) {
            troca_consulta(v, i, j);
            i++;
            j--;
        }
    } while (i <= j);

    if (L < j) quicksort_consulta(v, L, j);
    if (R > i) quicksort_consulta(v, i, R);
}

void inserir_ordenado_consulta(IndexConsulta **v, int *tam, IndexConsulta novo_index) {
    int pos = busca_binaria_consulta(*v, *tam, novo_index.chave);
    if (pos != -1) {
        printf("Erro: Chave ja existe no indice!\n");
        return;
    }

    *tam += 1;
    *v = (IndexConsulta *)realloc(*v, (*tam) * sizeof(IndexConsulta));
    if (*v == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    int i;
    for (i = *tam - 1; i > 0 && strcmp((*v)[i - 1].chave, novo_index.chave) > 0; i--) {
        (*v)[i] = (*v)[i - 1];
    }
    (*v)[i] = novo_index;

    quicksort_consulta(*v, 0, *tam - 1);
}
