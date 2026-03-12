#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    char cpf[12];
    char nome[30];
    char data_nascimento[11];
    char telefone[14];
} Paciente;

typedef struct {
    char chave[12];
    int posicao;
} IndexPaciente;

int validar_cpf(const char *cpf);
int validar_data(const char *data);
int validar_telefone(const char *telefone);

void inserir_novo_paciente(void);
void alterar_dados_paciente(void);
int buscar_paciente_por_nome(const char *nome_busca, Paciente *paciente_encontrado);

IndexPaciente* ler_arquivo_index_paciente(int *tamanho);
int busca_binaria_paciente(IndexPaciente *v, int tam, IndexPaciente novo_index);
void salvar_vetor_index_paciente(IndexPaciente *v, int tam);
void troca_paciente(IndexPaciente *v, int i, int j);
void quicksort_paciente(IndexPaciente *v, int L, int R);
void inserir_ordenado_paciente(IndexPaciente **v, int *tam, IndexPaciente novo_index);

#endif
