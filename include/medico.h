#ifndef MEDICO_H
#define MEDICO_H

typedef struct {
    char crm[7];
    char nome[50];
    char especialidade[20];
    char data_nascimento[11];
    float valor_hora;
    char telefone[14];
} Medico;

typedef struct {
    char crm[7];
    int posicao;
} IndexMedico;

int validar_crm(const char *crm);

void inserir_novo_medico(void);
int buscar_medico_por_nome(const char *nome_busca, Medico *medico_encontrado);
void listar_medicos_por_especialidade(void);
void alterar_dados_medico(void);

IndexMedico* ler_arquivo_index_medico(int *tamanho_medico);
int busca_binaria_medico(IndexMedico *v, int tam, IndexMedico novo_index);
void salvar_vetor_index_medico(IndexMedico *v, int tam);
void troca_medico(IndexMedico *v, int i, int j);
void quicksort_medico(IndexMedico *v, int L, int R);
void inserir_ordenado_medico(IndexMedico **v, int *tam, IndexMedico novo_index);

#endif
