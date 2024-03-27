#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>

#define MAX_NOME 50
#define MAX_EMAIL 50
#define MAX_TELEFONE 12
#define MAX_CONTATOS 50

// Definição das cores
#define RESET "\033[0m"
#define VERMELHO "\033[1;31m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define AZUL "\033[1;34m"
#define CIANO "\033[1;36m"

struct Contato {
    int id;
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
};

struct Contato agenda[MAX_CONTATOS];
int totalContato = 0;

bool validarEmail(const char *email) {
    const char *arroba = strchr(email, '@');
    const char *ponto = strchr(email, '.');
    const char *com = strstr(email, ".com");
    const char *combr = strstr(email, ".com.br");

    if (arroba == NULL || ponto == NULL || com == NULL && combr == NULL)
        return false;

    if (arroba > ponto || arroba == email || ponto - arroba < 2)
        return false;

    const char *caractereEntre = arroba + 1;
    const char *ultCaracter = ponto - 1;

    if (caractereEntre >= ultCaracter)
        return false;

    return true;
}

void cadContato() {
    system("cls");
    char email[MAX_EMAIL];
    bool emailValido = false;

    struct Contato novoContato;
    novoContato.id = totalContato + 1;

    printf(AMARELO "Cadastro de Contato:\n" RESET);

    // Nome
    do {
        printf("Nome: ");
        fgets(novoContato.nome, MAX_NOME, stdin);
        novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0';

        if (strlen(novoContato.nome) == 0) {
            printf(VERMELHO "O nome não pode estar em branco. Por favor, insira um nome válido.\n" RESET);
        }
    } while (strlen(novoContato.nome) == 0);

    // Email
    do {
        printf("Email: ");
        fgets(email, MAX_EMAIL, stdin);
        email[strcspn(email, "\n")] = '\0';

        if (validarEmail(email)) {
            emailValido = true;
        } else {
            printf(VERMELHO "O email fornecido é inválido. Certifique-se de inserir um email válido.\n" RESET);
        }
    } while (!emailValido);

    strcpy(novoContato.email, email);

    // Telefone
    do {
        printf("Telefone: ");
        fgets(novoContato.telefone, MAX_TELEFONE, stdin);
        novoContato.telefone[strcspn(novoContato.telefone, "\n")] = '\0';

        if (strlen(novoContato.telefone) == 0) {
            printf(VERMELHO "O telefone não estar em branco.\n" RESET);
        } else if (strlen(novoContato.telefone) != 11) {
            printf(VERMELHO "O telefone deve conter 11 dígitos.\n" RESET);
        } else {
            bool digitos = true;
            for (int i = 0; i < strlen(novoContato.telefone); i++) {
                if (!isdigit(novoContato.telefone[i])) {
                    digitos = false;
                    break;
                }
            }
            if (!digitos) {
                printf(VERMELHO "O telefone deve conter apenas dígitos. Por favor, insira um telefone válido.\n" RESET);
            } else {
                break;  // Sai do loop se todas as condições forem atendidas
            }
        }
    } while (1);  // Loop infinito


    printf(VERDE "\nContato cadastrado com sucesso!\n" RESET);

    // Adicionar o novo contato à agenda
    agenda[totalContato] = novoContato;
    totalContato++;
    system("pause");
}
void listContato() {
    system("cls");

    if (totalContato == 0) {
        printf("%sNenhum contato cadastrado.%s\n", VERMELHO, RESET);
        return;
    }

    printf("%sLista de Contatos:%s\n", AMARELO, RESET);

    for (int i = 0; i < totalContato; i++) {
        struct Contato contato = agenda[i];
        printf("ID: %d\n", contato.id);
        printf("Nome: %s\n", contato.nome);
        printf("Email: %s\n", contato.email);
        printf("Telefone: %s\n", contato.telefone);
        printf("\n");
    }
}

void quantContato() {
    system("cls");

    printf("%sQuantidade de Contatos Cadastrados: %d%s\n", AZUL, totalContato, RESET);
}

void buscarPNome() {
    system("cls");

    char nomeBusca[MAX_NOME];
    printf("Digite o nome para buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrados = 0;
    for (int i = 0; i < totalContato; i++) {
        struct Contato contato = agenda[i];
        if (strcasecmp(contato.nome, nomeBusca) == 0) {
            printf("ID: %d\n", contato.id);
            printf("Nome: %s\n", contato.nome);
            printf("Email: %s\n", contato.email);
            printf("Telefone: %s\n", contato.telefone);
            printf("\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("%sNenhum contato encontrado com o nome especificado.%s\n", VERMELHO, RESET);
    } else {
        printf("Total de contatos encontrados: %d\n", encontrados);
    }
}

void buscarPEmail() {
    system("cls");

    char emailBusca[MAX_EMAIL];
    printf("Digite o email para buscar: ");
    fgets(emailBusca, MAX_EMAIL, stdin);
    emailBusca[strcspn(emailBusca, "\n")] = '\0';

    int encontrados = 0;
    for (int i = 0; i < totalContato; i++) {
        struct Contato contato = agenda[i];
        if (strcasecmp(contato.email, emailBusca) == 0) {
            printf("ID: %d\n", contato.id);
            printf("Nome: %s\n", contato.nome);
            printf("Email: %s\n", contato.email);
            printf("Telefone: %s\n", contato.telefone);
            printf("\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("%sNenhum contato encontrado com o email especificado.%s\n", VERMELHO, RESET);
    } else {
        printf("Total de contatos encontrados: %d\n", encontrados);
    }
}

void buscarPInicial() {
    system("cls");

    char inicialBusca;
    printf("Digite a inicial para buscar: ");
    scanf("%c", &inicialBusca);
    flush();

    int encontrados = 0;
    for (int i = 0; i < totalContato; i++) {
        struct Contato contato = agenda[i];
        if (tolower(contato.nome[0]) == tolower(inicialBusca)) {
            printf("ID: %d\n", contato.id);
            printf("Nome: %s\n", contato.nome);
            printf("Email: %s\n", contato.email);
            printf("Telefone: %s\n", contato.telefone);
            printf("\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("%sNenhum contato encontrado com a inicial especificada.%s\n", VERMELHO, RESET);
    } else {
        printf("Total de contatos encontrados: %d\n", encontrados);
    }
}

void listarPorDDD() {
    system("cls");

    char dddBusca[MAX_TELEFONE];
    printf("Digite o DDD para buscar: ");
    fgets(dddBusca, MAX_TELEFONE, stdin);
    dddBusca[strcspn(dddBusca, "\n")] = '\0';

    int encontrados = 0;
    for (int i = 0; i < totalContato; i++) {
        struct Contato contato = agenda[i];
        if (strncmp(contato.telefone, dddBusca, 2) == 0) {
            printf("ID: %d\n", contato.id);
            printf("Nome: %s\n", contato.nome);
            printf("Email: %s\n", contato.email);
            printf("Telefone: %s\n", contato.telefone);
            printf("\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("%sNenhum contato encontrado com o DDD especificado.%s\n", VERMELHO, RESET);
    } else {
        printf("Total de contatos encontrados: %d\n", encontrados);
    }
}

void flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        system("cls");

        printf(CIANO"\n==========================================\n");
        printf("||          Agenda de Contatos          ||\n");
        printf("||======================================||\n");
        printf("||"RESET "1. Cadastrar um novo contato          "CIANO"||\n");
        printf("||"RESET"2. Listar contatos                    "CIANO"||\n");
        printf("||"RESET"3. Quantidade de contatos             "CIANO"||\n");
        printf("||"RESET"4. Buscar contato por nome            "CIANO"||\n");
        printf("||"RESET"5. Buscar contato por email           "CIANO"||\n");
        printf("||"RESET"6. Buscar contato por inicial         "CIANO"||\n");
        printf("||"RESET"7. Listar contatos pelo DDD           "CIANO"||\n");
        printf("||"VERMELHO "8. Sair                         \t"CIANO"||\n");
        printf(CIANO "==========================================\n" RESET);

        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        flush();

        switch (opcao) {
            case 1:
                cadContato();
                break;
            case 2:
                listContato();
                break;
            case 3:
                quantContato();
                break;
            case 4:
                buscarPNome();
                break;
            case 5:
                buscarPEmail();
                break;
            case 6:
                buscarPInicial();
                break;
            case 7:
                listarPorDDD();
                break;
            case 8:
                printf("%sEncerrando o programa. Até mais!%s\n", VERMELHO, RESET);
                break;
            default:
                printf("%sOpção inválida. Tente novamente.%s\n", VERMELHO, RESET);
                break;
        }
        flush();
    } while (opcao != 8);

    return 0;
}
