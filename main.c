#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Definisco la struttura scacchiera (NOTA: la struttura è comoda perchè posso dichiarare anche il parametro ruotata per
// facilitare la funzione stampa_scacchiera e per future features che si potranno implementare)
typedef struct Scacchiera
{
    char **scacchiera;
    int ruotata;
} Scacchiera;

// Stampo la scacchiera data una scacchiera s, in base a se il turno è del bianco o del nero sarà ruotata a dovere
void stampa_scacchiera(Scacchiera s)
{
    if (!(s.ruotata))
        printf("   a b c d e f g h\n");
    else
        printf("   h g f e d c b a\n");
    printf("------------------\n");
    for (int i = 0, len = 8; i < 8; i++, len--)
    {
        if (!(s.ruotata))
            printf("%d| ", len);
        else
            printf("%d| ", i + 1);

        for (int j = 0; j < 8; j++)
        {
            if (islower(s.scacchiera[i][j]) && s.scacchiera[i][j] != 'O')
                printf("\033[1;34m%c\033[0m ", s.scacchiera[i][j]);
            else if (isupper(s.scacchiera[i][j]) && s.scacchiera[i][j] != 'O')
                printf("\033[1;37m%c\033[0m ", s.scacchiera[i][j]);
            else
                printf("%c ", s.scacchiera[i][j]);
        }
        printf("\n");
    }
}
// Ruoto la scacchiera dopo la mossa di uno dei due giocatori
void ruota_scacchiera(Scacchiera *s)
{
    for (int i = 0, len = 7; i < 4; i++, len--)
    {
        char *temp = s->scacchiera[i];
        s->scacchiera[i] = s->scacchiera[len];
        s->scacchiera[len] = temp;
    }
    s->ruotata = !(s->ruotata);
}
// Creo una scacchiera, utile farlo in una funzione per consentire al giocatore di giocare più di una partita per esecuzione
// del programma
Scacchiera crea_scacchiera()
{
    Scacchiera scacchiera;
    scacchiera.ruotata = 0;

    scacchiera.scacchiera = malloc(8 * sizeof(char *));
    for (int i = 0; i < 8; i++)
    {
        *(scacchiera.scacchiera + i) = malloc(8 * sizeof(char));
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
                    scacchiera.scacchiera[i][j] = 'r';
                    break;
                case 1:
                case 6:
                    scacchiera.scacchiera[i][j] = 'b';
                    break;
                case 2:
                case 5:
                    scacchiera.scacchiera[i][j] = 'n';
                    break;
                case 3:
                    scacchiera.scacchiera[i][j] = 'q';
                    break;
                case 4:
                    scacchiera.scacchiera[i][j] = 'k';
                }
            }
        }
        else if (i == 1 || i == 2)
        {
            int indice = i == 1 ? i : 6;
            for (int j = 0; j < 8; j++)
            {
                scacchiera.scacchiera[indice][j] = i == 1 ? 'i' : 'I';
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
                    scacchiera.scacchiera[7][j] = 'R';
                    break;
                case 1:
                case 6:
                    scacchiera.scacchiera[7][j] = 'B';
                    break;
                case 2:
                case 5:
                    scacchiera.scacchiera[7][j] = 'N';
                    break;
                case 3:
                    scacchiera.scacchiera[7][j] = 'Q';
                    break;
                case 4:
                    scacchiera.scacchiera[7][j] = 'K';
                }
            }
        }
    }

    for (int i = 2; i <= 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scacchiera.scacchiera[i][j] = 'O';
        }
    }
    return scacchiera;
}

int main()
{
    Scacchiera scacchiera = crea_scacchiera();
    stampa_scacchiera(scacchiera);

    ruota_scacchiera(&scacchiera);
    stampa_scacchiera(scacchiera);
}