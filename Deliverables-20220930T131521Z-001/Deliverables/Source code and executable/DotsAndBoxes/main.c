#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
//adding colors
#define cR     "\x1b[31m"
#define cB    "\x1b[34m"
#define cReset   "\x1b[0m"

struct playerScore
{
    char name[50];
    int score;
};

void computerMood(int* x, int* y, int dim, char arr1[], char arr2[])
{
    int i, j;
    for(i = 0; i <= 2 * dim; i += 2)
    {
        for(j = 1; j < 2 * dim; j += 2)
        {
            int loc = (i / 2) * dim + j / 2;
            if(arr1[loc] != 0)        continue;
            int bef1 = ((i - 1) / 2) * (dim + 1) + (j - 1) / 2, aft1 = ((i - 1) / 2) * (dim + 1) + (j + 1) / 2;
            if(((loc - dim >= 0) && (arr1[loc - dim] != 0)) && ((i - 1 >= 0) && arr2[bef1] != 0) && (arr2[aft1] != 0))
            {
                *x = i;
                *y = j;
                return;
            }
            int bef2 = ((i + 1) / 2) * (dim + 1) + (j - 1) / 2, aft2 = ((i + 1) / 2) * (dim + 1) + (j + 1) / 2;
            if(((loc + dim < (dim * (dim + 1))) && (arr1[loc + dim] != 0)) && ((i + 1 <= 2 * dim) && arr2[bef2] != 0) && (arr2[aft2] != 0))
            {
                *x = i;
                *y = j;
                return;
            }
        }
    }

    for(i = 1; i < 2 * dim; i += 2)
    {
        for(j = 0; j <= 2 * dim; j += 2)
        {
            int loc = (i / 2) * (dim + 1) + j / 2;
            if(arr2[loc] != 0)    continue;
            int above1 = ((i - 1) / 2) * dim + (j - 1) / 2, below1 = ((i + 1) / 2) * dim + (j - 1) / 2;
            if((loc - 1 >= 0 && arr2[loc - 1] != 0) && ((j - 1 > 0) && arr1[above1] != 0) && (arr1[below1] != 0))
            {
                *x = i;
                *y = j;
                return;
            }
            int above2 = ((i - 1) / 2) * dim + (j + 1) / 2, below2 = ((i + 1) / 2) * dim + (j + 1) / 2;
            if((loc + 1 < (dim * (dim + 1)) && arr2[loc + 1] != 0) && ((j + 1 < 2 * dim) && arr1[above2] != 0) && (arr1[below2] != 0))
            {
                *x = i;
                *y = j;
                return;
            }
        }
    }

    for(i = 0; i <= 2 * dim; i += 2)
    {
        for(j = 1; j < 2 * dim; j += 2)
        {
            int loc = (i / 2) * dim + j / 2;
            if(arr1[loc] != 0)        continue;
            *x = i;
            *y = j;
            return;
        }
    }

    for(i = 1; i < 2 * dim; i += 2)
    {
        for(j = 0; j <= 2 * dim; j += 2)
        {
            int loc = (i / 2) * (dim + 1) + j / 2;
            if(arr2[loc] != 0)    continue;
            *x = i;
            *y = j;
            return;
        }
    }
}
int inputAction(int dim, int x, int y, char arr1[], char arr2[], int turn, int score[],
                int* flag, char box[])
{
    if((x < 0 || x > 2 * dim) || (y < 0 || y > 2 * dim))    return 0;

    int loc;
    if(x % 2 == 0 && y % 2 == 1)
    {
        loc = (x / 2) * dim + y / 2;
        if(arr1[loc] != 0)        return -1;
        arr1[loc] = turn;

        int bef1 = ((x - 1) / 2) * (dim + 1) + (y - 1) / 2, aft1 = ((x - 1) / 2) * (dim + 1) + (y + 1) / 2;
        if(((loc - dim >= 0) && (arr1[loc - dim] != 0)) && ((x - 1 >= 0) && arr2[bef1] != 0) && (arr2[aft1] != 0))
        {
            score[turn - 1]++;
            *flag = 1;
            box[((x - 1) / 2)*dim + y / 2] = turn;
        }
        int bef2 = ((x + 1) / 2) * (dim + 1) + (y - 1) / 2, aft2 = ((x + 1) / 2) * (dim + 1) + (y + 1) / 2;
        if(((loc + dim < (dim * (dim + 1))) && (arr1[loc + dim] != 0)) && ((x + 1 <= 2 * dim) && arr2[bef2] != 0) && (arr2[aft2] != 0))
        {
            score[turn - 1]++;
            *flag = 1;
            box[((x + 1) / 2)*dim + y / 2] = turn;
        }

        return 1;
    }
    else if(x % 2 == 1 && y % 2 == 0)
    {
        loc = (x / 2) * (dim + 1) + y / 2;
        if(arr2[loc] != 0)    return -1;
        arr2[loc] = turn;

        int above1 = ((x - 1) / 2) * dim + (y - 1) / 2, below1 = ((x + 1) / 2) * dim + (y - 1) / 2;
        if((loc - 1 >= 0 && arr2[loc - 1] != 0) && ((y - 1 > 0) && arr1[above1] != 0) && (arr1[below1] != 0))
        {
            score[turn - 1]++;
            *flag = 1;
            box[(x / 2) * dim + (y - 1) / 2] = turn;
        }
        int above2 = ((x - 1) / 2) * dim + (y + 1) / 2, below2 = ((x + 1) / 2) * dim + (y + 1) / 2;
        if((loc + 1 < (dim * (dim + 1)) && arr2[loc + 1] != 0) && ((y + 1 < 2 * dim) && arr1[above2] != 0) && (arr1[below2] != 0))
        {
            score[turn - 1]++;
            *flag = 1;
            box[(x / 2) * dim + y / 2] = turn;
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

char mainInput()
{
    char mainInput;
    printf("Choose to show top10 or play as beginner or expert or quit(t or b or e or q): ");
    while((mainInput = getchar()) != 'b' && mainInput != 'e' && mainInput != 't' && mainInput != 'q')
    {
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        printf("Error!\nEnter another value: ");
    }

    return mainInput;
}
void gameDisplay(int dim, char arr1[], char arr2[], char box[], FILE* fptr)
{
    system("cls");

    int i, j, k, l = 0;

    //Displaying numbers
    printf("  ");   fprintf(fptr, "  ");
    for(i = 0; i < (2 * dim + 1); i++)
    {
        printf("%d ", i);   fprintf(fptr, "%d ", i);
    }
    printf("\n");   fprintf(fptr, "\n");


    //Displaying Grid
    for(i = 0; i < dim; i++)
    {
        printf("%d ", l);     fprintf(fptr, "%d ", l++);
        for(j = 0; j < dim; j++)
        {
            printf(". ");     fprintf(fptr, ". ");
            if(arr1[i * dim + j] == 1)          {printf(cR "- " cReset); fprintf(fptr, "x ");}
            else if(arr1[i * dim + j] == 2)     {printf(cB "- " cReset); fprintf(fptr, "y ");}
            else                                {printf("  "); fprintf(fptr, "  ");}
        }
        printf(".\n");  fprintf(fptr, ".\n");

        printf("%d ", l); fprintf(fptr, "%d ", l++);
        for(k = 0; k < dim; k++)
        {
            if(arr2[i * (dim + 1) + k] == 1)            {printf(cR "| " cReset); fprintf(fptr, "x ");}
            else if(arr2[i * (dim + 1) + k] == 2)       {printf(cB "| " cReset); fprintf(fptr, "y ");}
            else                                        {printf("  "); fprintf(fptr, "  ");}

            if(box[i * dim + k] == 1)             {printf(cR "%c " cReset, 254); fprintf(fptr, "x ");}
            else if(box[i * dim + k] == 2)        {printf(cB "%c " cReset, 254); fprintf(fptr, "y ");}
            else                                  {printf("  "); fprintf(fptr, "  ");}
        }
        if(arr2[i * (dim + 1) + k] == 1)          {printf(cR "|" cReset "\n"); fprintf(fptr, "x" "\n");}
        else if(arr2[i * (dim + 1) + k] == 2)     {printf(cB "|" cReset "\n"); fprintf(fptr, "y" "\n");}
        else                                      {printf(" \n"); fprintf(fptr, " \n");}
    }

    printf("%d ", l);     fprintf(fptr, "%d ", l++);
    for(j = 0; j < dim; j++)
    {
        printf(". ");   fprintf(fptr, ". ");
        if(arr1[i * dim + j] == 1)          {printf(cR "- " cReset); fprintf(fptr, "x ");}
        else if(arr1[i * dim + j] == 2)     {printf(cB "- " cReset); fprintf(fptr, "y ");}
        else                                {printf("  "); fprintf(fptr, "  ");}
    }
    printf(".\n"); fprintf(fptr, ".\n");


}

int get_int()
{
    int result;
    while(scanf("%d", &result) != 1)
    {
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        printf("Error!\nEnter another value: ");
    }

    return result;
}

void displayBox(int score[], int moves[], int lineRem, double timedif)
{
    printf("*********************************\n");
    printf("*\tNumber of moves\t\t*\n");
    printf("*********************************\n");
    printf("* p1:\t%d\t| p2:\t%d\t*\n", moves[0], moves[1]);
    printf("*********************************\n");
    printf("*\t\tScore\t\t*\n");
    printf("*********************************\n");
    printf("* p1:\t%d\t| p2:\t%d\t*\n", score[0], score[1]);
    printf("*********************************\n");
    printf("*Remaining lines:\t%d\t*\n", lineRem);
    printf("*********************************\n");
    printf("*time passed:\t%2.0f:%2.0f\t\t*\n", floor(timedif / 60), fmod(timedif, 60));
    printf("*********************************\n");

}
void addingWinnerToTop10(char winnerPlayer[50], int winnerScore, struct playerScore list1[10], FILE *scoreFilePtr)
{
    int j;
    for(int i = 1; i <= winnerScore; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if((list1[j].score) < i)
            {
                list1[j].score = winnerScore;
                strcpy(list1[j].name, winnerPlayer);
                break;
            }
        }
        if((list1[j].score) == winnerScore)
        {
            break;
        }
    }
}
int main()
{
    struct playerScore list1[10];
    FILE *scoreFilePtr;
    scoreFilePtr = fopen("scores.bin", "rb");
    if(scoreFilePtr == NULL)
    {
        printf("Error! can not open score file");
        exit(1);
    }
    fread(&list1, sizeof(list1), 1, scoreFilePtr);
    fclose(scoreFilePtr);
    time_t start_t, now_t;
    double diff_t;
    char winnerPlayer[50], mainMenuInput;
    time(&start_t);
    int numPlayers, winnerScore;
    mainMenuInput = mainInput();
    if(mainMenuInput == 'q')
    {
        return 0;
    }
    if(mainMenuInput == 't')
    {
        int order = 1;
        for(int j = 25; j >= 0; j--)
        {
            for(int i = 0; i < 10; i++)
            {
                if(list1[i].score == j)
                {
                    printf("%.2d - Name:\t%s\t\tScore: %d\n", order, list1[i].name, list1[i].score);
                    order++;
                }
            }
        }
        system("pause");
        return 0;
    }
    do
    {
        printf("\nEnter number of players (1 or 2): ");
        numPlayers = get_int();
    }
    while(numPlayers < 1 || numPlayers > 2);
    int dim;
    do
    {
        printf("Select a number from 2 to 5 to play on an NxN board: ");
        dim = get_int();
    }
    while(dim < 2 || dim > 5);

    char Game[2][dim * (dim + 1) + 1], Boxes[dim * dim + 1], MoveRem = 2 * dim * (dim + 1);
    memset(Game[0], 0, dim * (dim + 1) + 1);
    memset(Game[1], 0, dim * (dim + 1) + 1);
    memset(Boxes, 0, dim * dim + 1);


    int score[2] = {0}, turn = 1, input[2] = {0, 0}, m, i = 0, gotPoint, noMoves[2] = {0, 0};
    FILE* gridPtr;
    gridPtr = fopen("grid.txt", "w");
    if(gridPtr == NULL)
    {
        printf("Error opening grid file!");
        return 1;
    }
    while(MoveRem > 0)
    {
        //getting time
        time(&now_t);
        diff_t = difftime(now_t, start_t);
        //doing game loop
        gotPoint = 0;
        gameDisplay(dim, Game[0], Game[1], Boxes, gridPtr);
        displayBox(score, noMoves, MoveRem, diff_t);
        printf("\nPlayer %d turn\n", turn);
        do
        {
            printf("Enter the coordinates for the desired line (ex:(x y): ");
            if(numPlayers == 1 && turn == 2)
            {
                computerMood(&input[0], &input[1], dim, Game[0], Game[1]);
            }
            else
            {
                input[0] = get_int();
                input[1] = get_int();
            }
            m = inputAction(dim, input[0], input[1], Game[0], Game[1], turn, score, &gotPoint, Boxes);
            if(m == 0)          printf("Wrong input!\n\n");
            else if(m == -1)   printf("Place already taken!\n\n");
        }
        while(m != 1);
        if(turn == 1)   noMoves[0]++;
        else            noMoves[1]++;
        MoveRem--;
        if(gotPoint == 0)
        {
            turn = turn + pow(-1, i);
            ++i;
        }
    }

    gameDisplay(dim, Game[0], Game[1], Boxes, gridPtr);
    displayBox(score, noMoves, MoveRem, diff_t);
    if(numPlayers == 2)
    {
        if(score[0] > score[1])
        {
            winnerScore = score[0];
            printf("\n" cR "--- Player 1 Won ---\nInput your name : " cReset "\n\n");
            scanf("%s", winnerPlayer);
        }
        else if(score[1] > score[0])
        {
            winnerScore = score[1];
            printf("\n" cB "--- Player 2 Won ---\nInput your name : " cReset "\n\n");
            scanf("%s", winnerPlayer);
        }
        else                        printf("\n--- TIE ---\n\n");
    }
    else
    {
        if(score[0] > score[1])
        {
            winnerScore = score[0];
            printf("\n" cR "--- You Won ---\nInput your name : " cReset "\n\n");
            scanf("%s", winnerPlayer);
        }
        else if(score[1] > score[0]) printf("\n" cB "--- Computer Won ---" cReset "\n\n");
        else                        printf("\n--- TIE ---\n\n");
    }
    for(int i = 0; i < 10; i++)
    {
        if(strcmp(list1[i].name, winnerPlayer) == 0)
        {
            if(winnerScore > list1[i].score)
            {
                list1[i].score = winnerScore;
                scoreFilePtr = fopen("scores.bin", "wb");
                if(scoreFilePtr == NULL)
                {
                    printf("Error! can not open score file");
                    exit(1);
                }
                fwrite(&list1, sizeof(list1), 1, scoreFilePtr);
                fclose(scoreFilePtr);
                system("pause");
                return 0;
            }
        }
    }
    addingWinnerToTop10(winnerPlayer, winnerScore, list1, scoreFilePtr);
    scoreFilePtr = fopen("scores.bin", "wb");
    if(scoreFilePtr == NULL)
    {
        printf("Error! can not open score file");
        exit(1);
    }
    fwrite(&list1, sizeof(list1), 1, scoreFilePtr);
    fclose(scoreFilePtr);
    system("pause");
    return 0;

}
