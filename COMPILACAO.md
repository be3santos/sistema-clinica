# INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO

## Pré-requisitos
- Um compilador C (GCC, Clang, ou MSVC)
- Make (opcional, para usar Makefile)

## Opção 1: Usando Makefile (Recomendado)

```bash
# Compilar
make

# Executar
make run

# Limpar arquivos compilados
make clean
```

## Opção 2: Compilação Manual com GCC (Linux/Mac)

```bash
gcc -Wall -Wextra -std=c99 -I./include -o sistema \
    main.c src/menu.c src/usuario.c src/paciente.c \
    src/medico.c src/consulta.c src/arquivo.c

# Executar
./sistema
```

## Opção 3: Compilação Manual com MinGW (Windows)

```cmd
gcc -Wall -Wextra -std=c99 -I./include -o sistema.exe ^
    main.c src/menu.c src/usuario.c src/paciente.c ^
    src/medico.c src/consulta.c src/arquivo.c

REM Executar
sistema.exe
```

## Opção 4: Compilação com MSVC (Visual Studio)

```cmd
cl /I include main.c src\menu.c src\usuario.c src\paciente.c ^
   src\medico.c src\consulta.c src\arquivo.c /o sistema.exe

REM Executar
sistema.exe
```

## Verificar Compilação

Se a compilação for bem-sucedida, será criado um executável:
- Linux/Mac: `sistema`
- Windows: `sistema.exe`

## Problemas Comuns

### Erro: "stdio.h not found"
- Configure o path das bibliotecas do seu compilador
- VS Code: Abra a paleta (Ctrl+Shift+P) e procure "C/C++: Select IntelliSense Configuration"

### Erro: "file not found"
- Certifique-se que está no diretório correto do projeto
- Verifique se todos os arquivos .c e .h existem

### Linker errors (undefined reference)
- Certifique-se que todos os arquivos .c foram incluídos na compilação
- Verifique se não há conflitos de nomes de função

## Estrutura de Diretório Esperada

```
projeto em c/
├── main.c
├── Makefile
├── README.md
├── include/
│   ├── arquivo.h
│   ├── consulta.h
│   ├── medico.h
│   ├── menu.h
│   ├── paciente.h
│   └── usuario.h
└── src/
    ├── arquivo.c
    ├── consulta.c
    ├── medico.c
    ├── menu.c
    ├── paciente.c
    └── usuario.c
```

Se a estrutura estiver diferente, ajuste os caminhos nos comandos de compilação.
