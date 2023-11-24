#include <stdio.h>
#include <stdlib.h>

void stampa_scacchiera(char **scacchiera)
{
    printf("   a b c d e f g h\n");
    printf("------------------\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d| ", i + 1);
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", scacchiera[i][j]);
        }
        printf("\n");
    }
}

char **crea_scacchiera()
{
    char **scacchiera;

    scacchiera = malloc(8 * sizeof(char *));
    for (int i = 0; i < 8; i++)
    {
        *(scacchiera + i) = malloc(8 * sizeof(char));
    }
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < 8; j++)
            {
                switch (j)
                {
                case 0:
                case 7:
                    scacchiera[i][j] = 'r';
                    break;
                case 1:
                case 6:
                    scacchiera[i][j] = 'b';
                    break;
                case 2:
                case 5:
                    scacchiera[i][j] = 'n';
                    break;
                case 3:
                    scacchiera[i][j] = 'q';
                    break;
                case 4:
                    scacchiera[i][j] = 'k';
                }
            }
        }
        else if (i == 1 || i == 2)
        {
            int indice = i == 1 ? i : 6;
            for (int j = 0; j < 8; j++)
            {
                scacchiera[indice][j] = i == 1 ? 'i' : 'I';
            }
        }

        else if (i == 3)
        {
            for (int j = 0; j < 8; j++)
            {
                switch (j)
                {
                case 0:
                case 7:
                    scacchiera[7][j] = 'R';
                    break;
                case 1:
                case 6:
                    scacchiera[7][j] = 'B';
                    break;
                case 2:
                case 5:
                    scacchiera[7][j] = 'N';
                    break;
                case 3:
                    scacchiera[7][j] = 'Q';
                    break;
                case 4:
                    scacchiera[7][j] = 'K';
                }
            }
        }
    }

    for (int i = 2; i <= 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scacchiera[i][j] = 'O';
        }
    }
    return scacchiera;
}

int main()
{
    char **scacchiera = crea_scacchiera();

    stampa_scacchiera(scacchiera);
}