#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/menu.h"
#include "include/usuario.h"
#include "include/paciente.h"
#include "include/medico.h"
#include "include/consulta.h"


int main(void) {
    int opcao = -1, opcao2, opcao3, opcao4;

    while (opcao != 0) {
        menu_principal();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }

        if (opcao == 1) {
            if (verificar_login()) {
                printf("\nVoce foi logado com sucesso!!!\n");

                int logado = 1;
                while (logado) {
                    menu_pos_login();
                    if (scanf("%d", &opcao2) != 1) {
                        printf("Entrada invalida!\n");
                        while (getchar() != '\n');
                        continue;
                    }

                    if (opcao2 == 1) {
                        menu_pacientes();
                        if (scanf("%d", &opcao3) != 1) {
                            printf("Entrada invalida!\n");
                            while (getchar() != '\n');
                            continue;
                        }

                        if (opcao3 == 1) {
                            inserir_novo_paciente();
                        } else if (opcao3 == 2) {
                            char nome_busca[50];
                            Paciente paciente_encontrado;

                            printf("\nDigite o nome do paciente que deseja buscar: ");
                            if (scanf(" %[^\n]", nome_busca) != 1) {
                                printf("Erro ao ler nome.\n");
                                continue;
                            }

                            int posicao = buscar_paciente_por_nome(nome_busca, &paciente_encontrado);
                            if (posicao == -1) {
                                printf("Paciente nao encontrado!\n");
                            } else {
                                printf("\n========== DADOS ENCONTRADOS ==========\n");
                                printf("Nome: %s\n", paciente_encontrado.nome);
                                printf("CPF: %s\n", paciente_encontrado.cpf);
                                printf("Data de Nascimento: %s\n", paciente_encontrado.data_nascimento);
                                printf("Telefone: %s\n\n", paciente_encontrado.telefone);
                            }
                        } else if (opcao3 == 3) {
                            alterar_dados_paciente();
                        } else if (opcao3 != 0) {
                            printf("Opcao Inexistente!!!\n");
                        }
                    } else if (opcao2 == 2) {
                        menu_medicos();
                        if (scanf("%d", &opcao3) != 1) {
                            printf("Entrada invalida!\n");
                            while (getchar() != '\n');
                            continue;
                        }

                        if (opcao3 == 1) {
                            inserir_novo_medico();
                        } else if (opcao3 == 2) {
                            char nome_busca[50];
                            Medico medico_encontrado;

                            printf("\nDigite o nome do medico que deseja buscar: ");
                            if (scanf(" %[^\n]", nome_busca) != 1) {
                                printf("Erro ao ler nome.\n");
                                continue;
                            }

                            int posicao = buscar_medico_por_nome(nome_busca, &medico_encontrado);
                            if (posicao == -1) {
                                printf("Medico nao encontrado!\n");
                            } else {
                                printf("\n========== DADOS ENCONTRADOS ==========\n");
                                printf("Nome: %s\n", medico_encontrado.nome);
                                printf("CRM: %s\n", medico_encontrado.crm);
                                printf("Data de Nascimento: %s\n", medico_encontrado.data_nascimento);
                                printf("Telefone: %s\n", medico_encontrado.telefone);
                                printf("Especialidade: %s\n", medico_encontrado.especialidade);
                                printf("Valor da hora de trabalho: R$ %.2f\n\n", medico_encontrado.valor_hora);
                            }
                        } else if (opcao3 == 3) {
                            listar_medicos_por_especialidade();
                        } else if (opcao3 == 4) {
                            alterar_dados_medico();
                        } else if (opcao3 != 0) {
                            printf("Opcao Inexistente!!!\n");
                        }
                    } else if (opcao2 == 3) {
                        menu_consultas();
                        if (scanf("%d", &opcao4) != 1) {
                            printf("Entrada invalida!\n");
                            while (getchar() != '\n');
                            continue;
                        }

                        switch (opcao4) {
                            case 1:
                                inserir_nova_consulta();
                                break;
                            case 2:
                                listar_consultas_por_medico();
                                break;
                            case 3:
                                listar_consultas_por_paciente();
                                break;
                            case 4:
                                listar_consultas_por_data();
                                break;
                            case 0:
                                break;
                            default:
                                printf("Opcao invalida!\n");
                        }
                    } else if (opcao2 == 0) {
                        printf("\nFazendo logout...\n");
                        logado = 0;
                    } else {
                        printf("Opcao Inexistente!\n");
                    }
                }
            } else {
                printf("\nFalha no login. Tentativas excedidas!\n");
            }
        } else if (opcao == 2) {
            cadastrar_novo_usuario();
        } else if (opcao == 0) {
            printf("\nPrograma encerrado!\n");
        } else {
            printf("Opcao Inexistente!\n");
        }
    }

    return 0;
}

