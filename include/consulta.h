#ifndef CONSULTA_H
#define CONSULTA_H

typedef struct {
    char crm_medico[7];
    char cpf_paciente[12];
    char data[11];
    char sintomas[100];
    char encaminhamentos[100];
} Consulta;

typedef struct {
    char chave[12];
    int posicao;
} IndexConsulta;

void inserir_nova_consulta(void);
void listar_consultas_por_medico(void);
void listar_consultas_por_paciente(void);
void listar_consultas_por_data(void);

IndexConsulta* ler_arquivo_index_consulta(const char *nome_arquivo, int *tamanho);
int busca_binaria_consulta(IndexConsulta *v, int tam, const char *chave);
void salvar_vetor_index_consulta(const char *nome_arquivo, IndexConsulta *v, int tam);
void troca_consulta(IndexConsulta *v, int i, int j);
void quicksort_consulta(IndexConsulta *v, int L, int R);
void inserir_ordenado_consulta(IndexConsulta **v, int *tam, IndexConsulta novo_index);

#endif
