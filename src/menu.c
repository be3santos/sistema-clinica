#include <stdio.h>
#include "../include/menu.h"

void menu_principal(void) {
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1 - Efetuar Login\n");
    printf("2 - Cadastrar Usuario\n");
    printf("0 - Encerrar Programa\n");
    printf("====================================\n");
    printf("Escolha uma opcao: ");
}

void menu_pos_login(void) {
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1 - Pacientes\n");
    printf("2 - Medicos\n");
    printf("3 - Consultas\n");
    printf("0 - Fazer Logout\n");
    printf("====================================\n");
    printf("Escolha uma opcao: ");
}

void menu_pacientes(void) {
    printf("\n========== MENU PACIENTES ==========\n");
    printf("1 - Inserir Novo Paciente\n");
    printf("2 - Buscar Paciente Por Nome\n");
    printf("3 - Alterar Dados Paciente\n");
    printf("0 - Voltar\n");
    printf("====================================\n");
    printf("Escolha uma opcao: ");
}

void menu_medicos(void) {
    printf("\n========== MENU MEDICOS ==========\n");
    printf("1 - Inserir Novo Medico\n");
    printf("2 - Buscar Medico Por Nome\n");
    printf("3 - Listar Medico Por Especialidade\n");
    printf("4 - Alterar Dados Medico\n");
    printf("0 - Voltar\n");
    printf("====================================\n");
    printf("Escolha uma opcao: ");
}

void menu_consultas(void) {
    printf("\n========== MENU CONSULTAS ==========\n");
    printf("1 - Inserir Nova Consulta\n");
    printf("2 - Listar Consultas por Medico\n");
    printf("3 - Listar Consultas por Paciente\n");
    printf("4 - Listar Consultas por Data\n");
    printf("0 - Voltar\n");
    printf("====================================\n");
    printf("Escolha uma opcao: ");
}
