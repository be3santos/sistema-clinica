#ifndef USUARIO_H
#define USUARIO_H

typedef struct {
    char usuario[20];
    char senha[10];
} Login;

void cadastrar_novo_usuario(void);
int verificar_login(void);

#endif
