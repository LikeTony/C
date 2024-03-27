#include <stdio.h>
#include <locale.h>

#define MAX_ESTUD 100
#define TOTAL_AULAS 80
#define MIN_NOTA 0
#define MAX_NOTA 10
#define MEDIA_PRESEN 0.75

// Definição das cores
#define RESET "\033[0m"
#define VERMELHO "\033[1;31m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[1;33m"
#define AZUL "\033[1;34m"
#define CIANO "\033[1;36m"

typedef struct{
    float b1;
    float b2;
    int faltas;
    float mediaAluno;
    float mediaGeral;
}Aluno;

int main(){
    system("color 00");
    setlocale(LC_ALL, "portuguese");
    Aluno Alunos[MAX_ESTUD];
    int numAlunos;

    printf("Digite o número de Alunos da turma: ");
    scanf("%d", &numAlunos);

    if (numAlunos <= 0 || numAlunos > MAX_ESTUD) {
        printf("Número de Alunos inválido!\n");
        return 0;
    }

    for(int i = 0; i < numAlunos; i++){
        printf("\nAluno %d:\n", i + 1);

        do{
            printf("Digite a nota 1 (0 a 10): ");
            scanf("%f", &Alunos[i].b1);

            if(Alunos[i].b1 < MIN_NOTA){
                printf(VERMELHO "Nota mínima é 0\n" RESET);
            }
            if(Alunos[i].b1 > MAX_NOTA){
                printf(VERMELHO "Nota máxima é 10\n" RESET);
            }
        }while (Alunos[i].b1 < MIN_NOTA || Alunos[i].b1 > MAX_NOTA);

        do{
            printf("Digite a nota 2 (0 a 10): ");
            scanf("%f", &Alunos[i].b2);

            if(Alunos[i].b2 < MIN_NOTA){
                printf(VERMELHO "Nota mínima é 0\n" RESET);
            }
            if(Alunos[i].b2 > MAX_NOTA){
                printf(VERMELHO "Nota máxima é 10\n" RESET);
            }
        }while (Alunos[i].b2 < MIN_NOTA || Alunos[i].b2 > MAX_NOTA);

        do{
            printf("Digite o número de faltas: ");
            scanf("%d", &Alunos[i].faltas);
        }while (Alunos[i].faltas < 0 || Alunos[i].faltas > TOTAL_AULAS);

        Alunos[i].mediaAluno = (0.4 * Alunos[i].b1) + (0.6 * Alunos[i].b2);
    }

    int opcao;
    do{
        system("cls");
        printf(AZUL "\n======================Menu=======================\n");
        printf("|| " RESET"1. Listar todos os dados de todos os Alunos" AZUL " ||\n");
        printf("|| " RESET"2. Quantos tiraram menos que 6             " AZUL " ||\n");
        printf("|| " RESET"3. Reprovados por falta                    " AZUL " ||\n");
        printf("|| " RESET"4. Média individual                        " AZUL " ||\n");
        printf("|| " RESET"5. Maior nota 2                            " AZUL " ||\n");
        printf("|| " VERMELHO "6. Sair                                    " AZUL " ||");
        printf(AZUL "\n=================================================" RESET);
        printf("\nDigite a opção desejada: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                system("cls");
                printf("\nDados dos Alunos:\n");
                for (int i = 0; i < numAlunos; i++) {
                    printf("Aluno %d:\n", i + 1);
                    printf("Nota 1: %.2f\n", Alunos[i].b1);
                    printf("Nota 2: %.2f\n", Alunos[i].b2);
                    printf("Faltas: %d\n", Alunos[i].faltas);
                    printf("Média: %.2f\n", Alunos[i].mediaAluno);
                    printf("------------------------\n");
                }
                system("pause");
                break;
            case 2:
                system("cls");
                printf("\nQuantidade de Alunos com média individual abaixo de 6: ");
                int contadormediaAlunoAbaixoSeis = 0;
                for (int i = 0; i < numAlunos; i++) {
                    if (Alunos[i].mediaAluno < 6.0) {
                        contadormediaAlunoAbaixoSeis++;
                    }
                }
                printf("%d\n", contadormediaAlunoAbaixoSeis);
                system("pause");
                break;
            case 3:
                system("cls");
                printf("\nQuantidade de Alunos reprovados por falta: ");
                int contadorReprovadosPorFalta = 0;
                for (int i = 0; i < numAlunos; i++) {
                    if (Alunos[i].faltas > (TOTAL_AULAS * (1 - MEDIA_PRESEN))) {
                        contadorReprovadosPorFalta++;
                    }
                }
                printf("%d\n", contadorReprovadosPorFalta);
                system("pause");
                break;
            case 4:
                system("cls");
                printf("\nDigite o ID do aluno: ");
                int alunoID;
                scanf("%d", &alunoID);

                if (alunoID < 1 || alunoID > numAlunos) {
                    printf("\nID do aluno inválido!\n");
                    system("pause");
                    break;
                }

                printf("\nMédia do Aluno %d: %.2f\n", alunoID, Alunos[alunoID - 1].mediaAluno);
                system("pause");
                break;
            case 5:
                system("cls");
                printf("\nMaior nota 2: ");
                float maiorb2 = Alunos[0].b2;
                for (int i = 1; i < numAlunos; i++) {
                    if (Alunos[i].b2 > maiorb2) {
                        maiorb2 = Alunos[i].b2;
                    }
                }
                printf("%.2f\n", maiorb2);
                system("pause");
                break;
            case 6:
                printf("\nEncerrando o programa...\n");
                system("pause");
                break;
            default:
                printf("\nOpção inválida! Digite um número de 1 a 6.\n");
                system("pause");
                break;
        }
    }while(opcao != 6);

    return 0;
}

