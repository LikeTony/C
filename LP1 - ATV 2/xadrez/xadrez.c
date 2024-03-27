#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define VERDE "\033[0;32m"
#define VERMELHO "\033[0;31m"
#define RESET "\033[0m"

int main() {
    //variaveis
    int x, y, validacao = 1 ;
    int possibi = 0;
    setlocale(LC_ALL, "Portuguese");
    system("color 00");

    while(validacao == 1){
    // Requisições
        printf("Digite a linha onde o cavalo está posicionado (de 1 a 8): ");
        scanf("%d", &x);
        printf("Digite a coluna onde o cavalo está posicionado (de 1 a 8): ");
        scanf("%d", &y);

        if((x > 0 && x < 9) && (y > 0 && y < 9)){
            if (x + 2 <= 8 && y + 1 <= 8) possibi++;
            if (x + 2 <= 8 && y - 1 >= 1) possibi++;
            if (x - 2 >= 1 && y + 1 <= 8) possibi++;
            if (x - 2 >= 1 && y - 1 >= 1) possibi++;
            if (x + 1 <= 8 && y + 2 <= 8) possibi++;
            if (x + 1 <= 8 && y - 2 >= 1) possibi++;
            if (x - 1 >= 1 && y + 2 <= 8) possibi++;
            if (x - 1 >= 1 && y - 2 >= 1) possibi++;
            validacao = 0;
            //Exibir
            printf(VERDE "A quantidade de possíveis movimentos do cavalo é: %d\n", possibi);
            printf(RESET);
        }else{
            if(x <= 0 || x >= 9){
                printf(VERMELHO "Valor de X inválido\n\n" RESET);
            }
            if(y <= 0 || x >= 9){
                printf(VERMELHO "Valor de Y inválido\n\n" RESET);
            }
        }

    }

    ///fim
    return 0;
}
