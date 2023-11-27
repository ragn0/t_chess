#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct Piece
{
    char id;
    int is_pinned;
} Piece;

typedef struct Coordinates
{
    int row;
    int col;
    Piece piece;
} Coordinates;

typedef struct ChessBoard
{
    Coordinates *squares;
    int is_white_turn;
    int check;
} ChessBoard;

typedef struct Move
{
    char piece;
    char origin[2];
    char destination[2];
} Move;

void clear(void)
{
    while (getchar() != '\n')
        ;
}

ChessBoard create_chessboard()
{
    ChessBoard cb;
    cb.check = 0;
    cb.is_white_turn = 1;
    char *pieces = "RNBQKBNR";

    cb.squares = malloc(64 * sizeof(Coordinates));
    for (int row = 0, counter = 0; row < 8; row++)
    {
        for (int col = 0, k = 0; col < 8; col++, counter++, k++)
        {
            if (row == 0 || row == 7 || row == 1 || row == 6)
            {
                cb.squares[counter].piece.id = row == 0 ? tolower(pieces[k]) : row == 7 ? pieces[k]
                                                                           : row == 1   ? 'i'
                                                                                        : 'I';
            }
            else
            {
                cb.squares[counter].piece.id = '0';
            }
            cb.squares[counter].col = col;
            cb.squares[counter].row = row;
            cb.squares[counter].piece.is_pinned = 0;
        }
    }
    return cb;
}

void rotate_chessboard(ChessBoard *cb)
{
    cb->is_white_turn = !(cb->is_white_turn);
    for (int i = 0; i < 32; i++)
    {
        Coordinates temp = cb->squares[i];
        cb->squares[i] = cb->squares[63 - i];
        cb->squares[63 - i] = temp;
    }
}

Piece find_piece_from_coords(ChessBoard cb, Coordinates co)
{
    int square = ((co.row + 1) * (co.col + 1) + (co.row) * (8 - (co.col + 1))) - 1;
    return cb.squares[square].piece;
}

Coordinates *find_coords_from_piece(ChessBoard cb, Piece p)
{
    int n = 1;
    Coordinates *coordinates = malloc(n * sizeof(Coordinates));
    for (int i = 0; i < 63; i++)
    {
        if (cb.squares[i].piece.id == p.id)
        {
            if (n == 1)
            {
                coordinates[0] = cb.squares[i];
                n++;
            }
            else
            {
                coordinates = realloc(coordinates, n * sizeof(Coordinates));
                coordinates[n - 1] = cb.squares[i];
                n++;
            }
        }
    }
    return coordinates;
}

void print_chessboard(ChessBoard cb)
{
    if (cb.is_white_turn)
        printf(" | a b c d e f g h\n");
    else
        printf("   h g f e d c b a\n");
    printf("------------------\n");
    for (int i = 0, counter = 0; i < 8; i++)
    {
        printf("%d| ", cb.is_white_turn ? 8 - i : i + 1);
        for (int j = 0; j < 8; j++, counter++)
        {
            if (islower(cb.squares[counter].piece.id))
                printf("\033[1;34m%c \033[0m", cb.squares[counter].piece.id);
            else if (isupper(cb.squares[counter].piece.id))
                printf("\033[1;37m%c \033[0m", cb.squares[counter].piece.id);
            else
                printf("%c ", cb.squares[counter].piece.id);
        }
        printf("\n");
    }
}

Move parse_move(char *move)
{
    Move parsed_move;
    // SAN FORMAT
    if (isupper(move[0]))
    {
        parsed_move.piece = move[0];
        strncpy(parsed_move.destination, move + 1, 2);
        return parsed_move;
    }
    // UCI FORMAT
    else if (islower(move[0]))
    {
    }
    // ICFF FORMAT
    else
    {
    }
}

void check_legal_move(Move move, ChessBoard cb)
{
}

int main()
{
    ChessBoard cb = create_chessboard();
    print_chessboard(cb);
    Piece p;
    p.id = 'N';
    for (int i = 0; i < 2; i++)
    {
        printf("row: %d col: %d\n", find_coords_from_piece(cb, p)[i].row, find_coords_from_piece(cb, p)[i].col);
    }

    /*while (1)
    {
        printf("Insert your move! (type ? to learn more, exit to stop the game)\n");
        scanf("%s", move);
        clear();
        if (strcmp(move, "exit") == 0)
        {
            exit(1);
        }
        else if (strncmp(move, "?", 1) == 0)
        {
            printf("e2e4	Muovi un pezzo da e2 a e4\n5254	Muovi un pezzo da e2 a e4\nNc3	Muovi un cavallo in c3\nO-O	Arrocco corto\nO-O-O	Arrocco lungo\nc8=Q	Promuovi il pedone c8 a regina\n");
            continue;
        }
    }*/

    return 0;
}
