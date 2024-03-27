#include <stdio.h>
#include <locale.h>
#include <float.h>

#define MAX_VENDAS 100

#define RESET "\033[0m"
#define VERMELHO "\033[1;31m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define AZUL "\033[1;34m"
#define CIANO "\033[1;36m"

typedef struct {
    float valTotal;
    char categ;
    char tipoPaga;
} Venda;

void cadastroVenda(Venda vendas[], int *numVendas) {
    if (*numVendas >= MAX_VENDAS) {
        puts("Limite de vendas alcançado.");
        return;
    }

    float valTotal;

    while (1) {
        printf("Valor total da venda: ");
        if (scanf("%f", &valTotal) == 1) {
            break;
        }

        puts(VERMELHO "Valor inválido. Digite um número válido." RESET);
        // Limpar o buffer de entrada
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    printf("Categoria dos produtos vendidos (A, B ou C): ");
    scanf(" %c", &vendas[*numVendas].categ);

    printf("Tipo de pagamento (D - débito, C - crédito ou P - pix): ");
    scanf(" %c", &vendas[*numVendas].tipoPaga);

    vendas[*numVendas].valTotal = valTotal;
    (*numVendas)++;

    puts("Venda cadastrada com sucesso!");
}

void listaVenda(Venda vendas[], int numVendas) {
    puts("\nLista de vendas realizadas:");

    for (int i = 0; i < numVendas; i++) {
        printf("\nVenda %d:\nValor Total: %.2f\nCategoria: %c\nTipo de Pagamento: %c\n\n",
               i + 1, vendas[i].valTotal, vendas[i].categ, vendas[i].tipoPaga);
    }
}

void listaVendaPorCat(Venda vendas[], int numVendas, char categ) {
    printf("\nLista de vendas realizadas na categoria %c:\n", categ);

    for (int i = 0; i < numVendas; i++) {
        if (vendas[i].categ == categ) {
            printf("\nVenda %d:\nValor Total: %.2f\nTipo de Pagamento: %c\n\n",
                   i + 1, vendas[i].valTotal, vendas[i].tipoPaga);
        }
    }
}

void totalPorTipo(Venda vendas[], int numVendas, char tipoPaga) {
    float totalVendas = 0;

    for (int i = 0; i < numVendas; i++) {
        if (vendas[i].tipoPaga == tipoPaga) {
            totalVendas += vendas[i].valTotal;
        }
    }

    printf("\nTotal de vendas realizadas com tipo de pagamento %c: %.2f\n\n",
           tipoPaga, totalVendas);
}

float calcLucro(Venda vendas[], int numVendas) {
    float lucroTotal = 0;

    for (int i = 0; i < numVendas; i++) {
        float custo = vendas[i].valTotal * 0.7; // 70% do valor total como custo
        lucroTotal += vendas[i].valTotal - custo;
    }

    return lucroTotal;
}

void maiorVenda(Venda vendas[], int numVendas) {
    if (numVendas == 0) {
        puts("\nNenhuma venda cadastrada.");
        return;
    }

    int indiceMaiorVenda = 0;

    for (int i = 1; i < numVendas; i++) {
        if (vendas[i].valTotal > vendas[indiceMaiorVenda].valTotal) {
            indiceMaiorVenda = i;
        }
    }

    printf("\nMaior venda realizada:\nValor Total: %.2f\ncateg: %c\nTipo de Pagamento: %c\n",
           vendas[indiceMaiorVenda].valTotal, vendas[indiceMaiorVenda].categ,
           vendas[indiceMaiorVenda].tipoPaga);
}

void menorVenda(Venda vendas[], int numVendas) {
    if (numVendas == 0) {
        puts("\nNenhuma venda cadastrada.");
        return;
    }

    int indicemenorVenda = -1;
    float menorValorPix = FLT_MAX;

    for (int i = 0; i < numVendas; i++) {
        if (vendas[i].tipoPaga == 'P') {
            if (vendas[i].valTotal < menorValorPix) {
                indicemenorVenda = i;
                menorValorPix = vendas[i].valTotal;
            }
        }
    }

    if (indicemenorVenda != -1) {
        printf("\nMenor venda realizada via PIX:\nValor Total: %.2f\ncateg: %c\nTipo de Pagamento: %c\n",
               vendas[indicemenorVenda].valTotal, vendas[indicemenorVenda].categ,
               vendas[indicemenorVenda].tipoPaga);
    } else {
        puts("\nNenhuma venda realizada via PIX.");
    }
}
int main() {
    system("color 00");
    setlocale(LC_ALL, "portuguese");
    Venda vendas[MAX_VENDAS];
    int numVendas = 0;
    int opcao;

    do {
        system("cls");
        puts(AZUL "\n===============================MENU=================================" RESET);
        puts("| 1. Cadastrar nova venda                                          |");
        puts("| 2. Listar todas as vendas realizadas                             |");
        puts("| 3. Listar vendas por categoria                                   |");
        puts("| 4. Total de vendas por tipo                                      |");
        puts("| 5. Lucro total de vendas                                         |");
        puts("| 6. Maior venda                                                   |");
        puts("| 7. Menor venda PIX                                               |");
        puts("| 8. Sair                                                          |");
        puts(AZUL "====================================================================" RESET);
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                cadastroVenda(vendas, &numVendas);
                break;
            case 2:
                system("cls");
                listaVenda(vendas, numVendas);
                break;
            case 3:
                system("cls");
                printf("\nDigite a categoria (A, B ou C): ");
                char categ;
                scanf(" %c", &categ);
                listaVendaPorCat(vendas, numVendas, categ);
                break;
            case 4:
                system("cls");
                printf("\nDigite o tipo de pagamento (D - débito, C - crédito ou P - pix): ");
                char tipoPaga;
                scanf(" %c", &tipoPaga);
                totalPorTipo(vendas, numVendas, tipoPaga);
                break;
            case 5:
                system("cls");
                printf("\nLucro total das vendas: %.2f\n", calcLucro(vendas, numVendas));
                break;
            case 6:
                system("cls");
                maiorVenda(vendas, numVendas);
                break;
            case 7:
                system("cls");
                menorVenda(vendas, numVendas);
                break;
            case 8:
                system("cls");
                puts("Encerrando o programa.");
                break;
            default:
                puts("Opção inválida. Tente novamente.");
        }
        system("pause");
    } while (opcao != 8);

    return 0;
}

