#include <stdio.h>
#include <stdlib.h>
int M[10], N[10], topm = -1, topn = -1;
char a[10];

// Function pointer
typedef void (*Func)(int);
Func victory;

// Functions to shorten code
int freeSpace(int condition, char array[], int index1, int index2, int index3)
{
    if (condition == 2)
    {
        if (array[index1] == ' ')
            return index1 + 1;
        if (array[index2] == ' ')
            return index2 + 1;
        if (array[index3] == ' ')
            return index3 + 1;
    }
    return -1;
}

void display(char b[])
{
    printf(" %c | %c | %c \n", b[0], b[1], b[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", b[3], b[4], b[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", b[6], b[7], b[8]);
}
void victoryX(int a)
{
    if (a == 3)
    {
        gtk_label_set_text(Turn, "\tGAME OVER \nX  IS  THE  WINNER !!!");
        gtk_button_set_label(resetButton, "Play Again");
        g_print("X IS THE WINNER!!!\n");
        *Alive = 0; // dead
    }
}

void victoryY(int a)
{
    if (a == 3)
    {
        gtk_label_set_text(Turn, "\tGAME OVER \nO  IS  THE  WINNER !!!");
        gtk_button_set_label(resetButton, "Play Again");
        g_print("O IS THE WINNER!!!\n");
        *Alive = 0; // dead
    }
}
// single Function to check for X and Y by passing parameters
int check(int k[10], int XorY, int mode)
{
    int i, counth1 = 0, counth2 = 0, counth3 = 0, countv1 = 0, countv2 = 0, countv3 = 0, countlc = 0, countrc = 0;

    // to determine whether victoryX or victoryY
    if (XorY == 1)
        victory = victoryX;
    else
        victory = victoryY;

    if (topm >= 1)
    {
        for (i = 0; i < topm + 1; i++)
        {
            if (k[i] == 1 || k[i] == 2 || k[i] == 3)
            {
                counth1++;
                victory(counth1);
            }
            if (k[i] == 4 || k[i] == 5 || k[i] == 6)
            {
                counth2++;
                victory(counth2);
            }
            if (k[i] == 7 || k[i] == 8 || k[i] == 9)
            {
                counth3++;
                victory(counth3);
            }
            if (k[i] == 1 || k[i] == 4 || k[i] == 7)
            {
                countv1++;
                victory(countv1);
            }
            if (k[i] == 2 || k[i] == 5 || k[i] == 8)
            {
                countv2++;
                victory(countv2);
            }
            if (k[i] == 3 || k[i] == 6 || k[i] == 9)
            {
                countv3++;
                victory(countv3);
            }
            if (k[i] == 1 || k[i] == 5 || k[i] == 9)
            {
                countlc++;
                victory(countlc);
            }
            if (k[i] == 3 || k[i] == 5 || k[i] == 7)
            {
                countrc++;
                victory(countrc);
            }
        }
    }
    if (mode == 1)
    {
        if (topn == -1)
        {
            if (b[4] == ' ')
                return 5;
            else
                return 1;
        }
        if (topm >= 1)
        {
            if (freeWill(counth1, b, 0, 1, 2) != -1)
                return freeWill(counth1, b, 0, 1, 2);
            if (freeWill(counth2, b, 3, 4, 5) != -1)
                return freeWill(counth2, b, 3, 4, 5);
            if (freeWill(counth3, b, 6, 7, 8) != -1)
                return freeWill(counth3, b, 6, 7, 8);
            if (freeWill(countv1, b, 0, 3, 6) != -1)
                return freeWill(countv1, b, 0, 3, 6);
            if (freeWill(countv2, b, 1, 4, 7) != -1)
                return freeWill(countv2, b, 1, 4, 7);
            if (freeWill(countv3, b, 2, 5, 8) != -1)
                return freeWill(countv3, b, 2, 5, 8);
            if (freeWill(countlc, b, 0, 4, 8) != -1)
                return freeWill(countlc, b, 0, 4, 8);
            if (freeWill(countrc, b, 2, 4, 6) != -1)
                return freeWill(countrc, b, 2, 4, 6);
            return 25;
        }
    }
}

int computer_move(int k[10])
{
    if (b[(k[topm] - 3) - 1] == ' ')
        return k[topm] - 3;
    if (b[(k[topm] - 1) - 1] == ' ')
        return k[topm] - 1;
    if (b[(k[topm] + 3) - 1] == ' ')
        return k[topm] + 3;
    if (b[(k[topm] + 1) - 1] == ' ')
        return k[topm] + 1;
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == ' ')
            return i + 1;
    }
}

void two_player()
{
    int i = 0, chance = 0, place_value;
    while (i < 5)
    {
        if (chance == 0)
        {
            printf("X's turn enter the place no[1-9]:");
            scanf("%d", &place_value);
            M[++topm] = place_value;
            a[place_value - 1] = 'X';
            display(a);
            check(M, 1, 0); // passing M -> k and 1 -> XorY to "check" Function
            chance = 1;
        }
        if (i == 4)
            break;
        if (chance == 1)
        {
            printf("O's turn enter the place no[1-9]:");
            scanf("%d", &place_value);
            N[++topn] = place_value;
            a[place_value - 1] = 'O';
            display(a);
            check(N, 0, 0); // passing N -> K and 0 -> XorY to "check" Function
            chance = 0;
        }
        i++;
    }
    printf("MATCH DRAW!!!");
    exit(0);
}

void single_player()
{
    int i = 0, chance = 0, place_value, move;
    while (i < 5)
    {
        if (chance == 0)
        {
            printf("X's turn enter the place no[1-9]:");
            scanf("%d", &place_value);
            M[++topm] = place_value;
            a[place_value - 1] = 'X';
            display(a);
            move = check(M, 1, 0); // passing M -> k and 1 -> XorY to "check" Function
            chance = 1;
        }
        if (i == 4)
            break;
        if (chance == 1)
        {
            move = check(N, 0, 1);
            if (move == 25)
                move = check(M, 1, 1);
            if (move == 25)
            {
                if (M[0] == 5)
                {
                    if (a[(M[topm] - 6) - 1] == ' ')
                        move = M[topm] - 6;
                    else
                        move = computer_move(M);
                }
                else
                    move = computer_move(M);
            }
            N[++topn] = move;
            a[move - 1] = 'O';
            display(a);
            move = check(N, 0, 0); // passing N -> K and 0 -> XorY to "check" Function
            chance = 0;
        }
        i++;
    }
    printf("MATCH DRAW!!!");
    exit(0);
}
int main()
{
    int i, chance = 0, place_value, mode;
    for (i = 0; i < 9; i++)
        a[i] = ' ';
    while (1)
    {
        printf("Select the mode you wish to play:\n1.Single player\t2.Two player\t3.Exit\n");
        scanf("%d", &mode);
        if (mode == 1)
            single_player(chance, place_value);
        else if (mode == 2)
            two_player(chance, place_value);
        else if (mode == 3)
            exit(0);
        else
            printf("Invalid choice \n");
    }
    return 0;
}