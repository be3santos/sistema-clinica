# Sistema de Gerenciamento de Clínica

Um sistema completo desenvolvido em C para gerenciar pacientes, médicos e consultas de uma clínica. Utiliza manipulação de arquivos binários e índices de busca para otimização de desempenho.

## Características

- ✅ **Gestão de Pacientes**: Inserir, buscar e alterar dados de pacientes
- ✅ **Gestão de Médicos**: Cadastro, listagem por especialidade e alteração de dados
- ✅ **Gestão de Consultas**: Registro de consultas com médicos e pacientes
- ✅ **Sistema de Login**: Autenticação de usuários com limite de tentativas
- ✅ **Busca Otimizada**: Algoritmo de busca binária para melhor desempenho
- ✅ **Validações de Dados**: CPF, CRM, Data e Telefone validados
- ✅ **Armazenamento em Arquivo Binário**: Persistência eficiente de dados

## Estrutura do Projeto

```
projeto/
├── main.c                 # Arquivo principal com função main()
├── include/              # Headers (.h)
│   ├── menu.h           # Funções de menu
│   ├── usuario.h        # Autenticação e login
│   ├── paciente.h       # Estruturas e funções de pacientes
│   ├── medico.h         # Estruturas e funções de médicos
│   ├── consulta.h       # Estruturas e funções de consultas
│   └── arquivo.h        # Utilitários de arquivo
├── src/                  # Implementações (.c)
│   ├── main.c
│   ├── menu.c
│   ├── usuario.c
│   ├── paciente.c
│   ├── medico.c
│   ├── consulta.c
│   └── arquivo.c
├── Makefile              # (Opcional) Para compilação
└── README.md             # Este arquivo
```

## Como Compilar

### Usando GCC (Linux/Mac)
```bash
gcc -o sistema main.c src/menu.c src/usuario.c src/paciente.c src/medico.c src/consulta.c src/arquivo.c -I./include
```

### Usando MinGW (Windows)
```bash
gcc -o sistema.exe main.c src/menu.c src/usuario.c src/paciente.c src/medico.c src/consulta.c src/arquivo.c -I./include
```

### Usando Makefile (se disponível)
```bash
make
```

## Como Executar

```bash
./sistema
```

ou no Windows:
```bash
sistema.exe
```

## Usuário de Teste

Primeiro, cadastre um usuário:
- **Opção**: "2 - Cadastrar Usuario" no menu principal
- **Usuário**: seu_usuario
- **Senha**: sua_senha

Depois faça login:
- **Opção**: "1 - Efetuar Login" no menu principal

## Estruturas de Dados

### Paciente
```c
typedef struct {
    char cpf[12];
    char nome[30];
    char data_nascimento[11];  // dd/mm/aaaa
    char telefone[14];
} Paciente;
```

### Médico
```c
typedef struct {
    char crm[7];
    char nome[50];
    char especialidade[20];
    char data_nascimento[11];  // dd/mm/aaaa
    float valor_hora;
    char telefone[14];
} Medico;
```

### Consulta
```c
typedef struct {
    char crm_medico[7];
    char cpf_paciente[12];
    char data[11];             // dd/mm/aaaa
    char sintomas[100];
    char encaminhamentos[100];
} Consulta;
```

## Validações Implementadas

| Campo | Validação |
|-------|-----------|
| CPF | 11 dígitos numéricos |
| CRM | 6 dígitos numéricos |
| Data | Formato dd/mm/aaaa |
| Telefone | Mínimo 8 caracteres |
| Entrada | Verificação de scanf() |

## Funções Principais por Módulo

### menu.c
- `menu_principal()` - Menu de login
- `menu_pos_login()` - Menu pós-autenticação
- `menu_pacientes()` - Menu de pacientes
- `menu_medicos()` - Menu de médicos
- `menu_consultas()` - Menu de consultas

### usuario.c
- `cadastrar_novo_usuario()` - Cria novo usuário
- `verificar_login()` - Valida credenciais (máx. 3 tentativas)

### paciente.c
- `inserir_novo_paciente()` - Adiciona novo paciente
- `buscar_paciente_por_nome()` - Busca linear por nome
- `alterar_dados_paciente()` - Modifica dados existentes
- `validar_cpf()` - Valida formato de CPF
- Funções de índice com busca binária

### medico.c
- `inserir_novo_medico()` - Cadastra novo médico
- `buscar_medico_por_nome()` - Busca linear por nome
- `listar_medicos_por_especialidade()` - Lista por especialidade
- `alterar_dados_medico()` - Modifica dados
- `validar_crm()` - Valida formato de CRM
- Funções de índice com busca binária

### consulta.c
- `inserir_nova_consulta()` - Registra nova consulta
- `listar_consultas_por_medico()` - Lista por CRM
- `listar_consultas_por_paciente()` - Lista por CPF
- `listar_consultas_por_data()` - Lista por data

## Arquivos Gerados

O sistema cria automaticamente os seguintes arquivos binários:

- `login.bin` - Dados de usuários
- `pacientes.bin` - Dados de pacientes
- `index_pacientes.bin` - Índices de pacientes
- `medicos.bin` - Dados de médicos
- `index_medico.bin` - Índices de médicos
- `consultas.bin` - Dados de consultas
- `index_consultas_medico.bin` - Índices de consultas por médico
- `index_consultas_paciente.bin` - Índices de consultas por paciente

## Recursos Utilizados

### Algoritmos
- **Quicksort** - Ordenação de índices
- **Busca Binária** - Busca otimizada em índices
- **Busca Linear** - Busca em arquivo binário

### Estruturas de Dados
- Vetores dinâmicos com `malloc()` e `realloc()`
- Índices para otimização de busca
- Arquivos binários para persistência

### Funcionalidades C
- Manipulação de arquivos (`fopen`, `fread`, `fwrite`)
- Alocação dinâmica de memória
- Strings e arrays
- Estruturas `struct`
- Ponteiros e referências

## Tratamento de Erros

O sistema inclui validações para:
- Falha ao abrir arquivos
- Erros de alocação de memória
- Entrada inválida do usuário (scanf)
- Dados duplicados (CPF/CRM)
- Registros não encontrados

## Melhorias Futuras

- [ ] Suporte a banco de dados SQL
- [ ] Interface gráfica (GTK/Qt)
- [ ] Relatórios e estatísticas
- [ ] Backup e restore de dados
- [ ] Criptografia de senhas
- [ ] Log de atividades
- [ ] Suporte a múltiplos usuários simultâneos

## Notas de Implementação

- O sistema é **de arquivo único** (não cliente-servidor)
- Dados são salvos em **arquivos binários** no diretório da aplicação
- **NÃO** inclui criptografia de senhas (apenas string simples)
- Validações de CPF **não** verificam dígito verificador
- Funciona em **Windows, Linux e macOS**

## Autor

Desenvolvido como projeto educacional em C para demonstrar:
- Modularização de código
- Uso de headers e separação de responsabilidades
- Manipulação de arquivos binários
- Algoritmos de busca e ordenação
- Boas práticas de programação

## Licença

Este projeto é fornecido como está para fins educacionais.
