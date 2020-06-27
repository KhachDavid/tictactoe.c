#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 3  //defining the SIZE of the BOARD

void display_table(char board[][SIZE]); 
void clear_table(char board[][SIZE]);
void get_player1_move(char board[][SIZE], int row, int col);
void get_player2_move(char board[][SIZE], int row, int col);
bool check_end_of_game(char board[][SIZE]);
bool legal_move(char board[][SIZE], int row, int col);
bool play_again(char *value);
void print_score(char* player11, char* player22, int player11_score, int player22_score);

//print_winner (board);

int main(void)  //main function...straightforward
{
    char *play_more = malloc(33); //allocating memory to arrange a loop 
    char *index = malloc(33);     //for playing the game more than once
    
    char* player1 = malloc(20);   //allocating memory to use player1's name in the file name
    
    player1 = get_string("Who is player 1? ");
    char* player2 = get_string("Who is player 2? ");
    
    FILE* file;
    file = fopen(player1, "w"); //opening a file to write the history of the match
    
    if (file == NULL) //making sure the file existst
    {
        printf("NOT FOUND...");
    }
    
    
    int player1_score = 0; //setting each player's score to 0
    int player2_score = 0;
    
    print_score(player1, player2, player1_score, player2_score); //printing the initial score
    
    do //doing this while players want to play (while loop is in LINE 130)
    {
        char board[SIZE][SIZE] = {{0}}; /* initialize all variables */
    
        clear_table(board);      //putting _ in the table  
        display_table(board);   //showing the initial board
    
        while (check_end_of_game(board) == false) //if game is finished do the stuff from LINE 122, otherwise roll up another game
        {
            int *e, *f; //creating pointers to use them to see if the moves are legal
            do
            {
                int a, b;
                do
                {
                    a = get_int("\nWhich ROW do you want to move?\n"); 
                    e = &a; //passing the address of their input to the initial pointers
                }
                while (a > SIZE || a < 0); //forcing the user to cooperate 
    
                do
                {
                    b = get_int("Which COLUMN do you want to move?\n"); 
                    f = &b;
                }
                while ((b > SIZE || b < 0)); //forcing the user to cooperate 
        
            }
            while ((legal_move(board, *e, *f) == false)); //using the pointers to make sure the moves being made are legal 
        
            get_player1_move(board, *e, *f); //executing the moves
            
            display_table(board);    //displaying the updated board
    
            if (check_end_of_game(board) == true) //checking if the game is finished
            {
                printf("%s won!!!!\nBetter luck next time :( %s\n\n", player1, player2);
                //todo
                player1_score++; //if player1 is the winner...Updating their total by one
                sleep(1);
                continue; //breaking out of the loop to avoid prompting the players2 to make a move after the game is done
            }
            
            int *g, *h; //same thing as player 1
            do
            {
                int c;
                do
                {
                    c = get_int("\nWhich ROW do you want to move?\n"); 
                    g = &c;
                }
                while (c > SIZE || c < 0);
    
                int d;
                do
                {
                    d = get_int("Which COLUMN do you want to move?\n");
                    h = &d;
                }
                while (d > SIZE || d < 0);  
            }
            while (legal_move(board, *g, *h) == false);
        
            get_player2_move(board, *g, *h);
    
            display_table(board); 
        
            if (check_end_of_game(board) == true)
            {
                printf("%s won!!!!\nBetter luck next time %s\n\n", player2, player1);
                sleep(1);
                player2_score++;
                //todo
            }
            
            fwrite(board, sizeof(char), sizeof(board), file); //writing the board content to a file
            
        }
        print_score(player1, player2, player1_score, player2_score); //printing the update scores
        fprintf(file, "%s %i-%i %s\n", player1, player1_score, player2_score, player2); //writing the scores to a file
        
        printf("%s and %s Do you want to play again?\n", player1, player2);
        printf("TYPE 'yes' if you want to continue\nAny other button if you want to exit\n");
        index = get_string("TYPE HERE: "); 
        strcpy(play_more, index); //copying the index value to the play_more argument for our main loop
    }
    while (play_again(play_more) == true);
    
    free(play_more); //freeing the memory to avoid leaks
    free(index);
    
    return 0;
}

/* display table function */
void display_table(char board[][SIZE])
{
    int row, col;
    printf("\nThe current state of the game is:\n");
    for (row = 0; row < SIZE; row++) 
    {
        for (col = 0; col < SIZE; col++) 
        {
            putchar(' '); 
            if (board[row][col])
            {
                putchar(board[row][col]);  /* use putchar for a single char */
            }
            
            else
            {
                putchar('_');
            }
        }
        putchar('\n');
    }

}
/* clear table function */
void clear_table(char board[][SIZE])
{
    int row, col;
    // char board[row][col]; /no need to redeclare/

    for (row = 0; row < SIZE; row++)
    {
        for (col = 0; col < SIZE; col++)
        {
            board[row][col] = '_';      // just clear, no need to check 
        }
    }
}

void get_player1_move(char board[][SIZE], int row, int col)
{
    board[row - 1][col - 1] = 'x';
}

void get_player2_move(char board[][SIZE], int row, int col)
{
    board[row - 1][col - 1] = 'o';
}

bool check_end_of_game(char board[][SIZE])
{
    int row, col;
    bool flag = false;
    int counter1 = 0;
    int counter3 = 0;
    int counter5 = 0;
    int counter7 = 0;
    int counter9 = 0;
    int counter8 = 0;
    int counter2 = 0;
    int counter4 = 0;
    
    for (row = 0; row < SIZE; row++)
    {
        for (col = 0; col < SIZE; col++)
        {
            if (board[row][col] == 'x') //checking rows
            {
                counter1++; //algorithm for checking if the game is won
                
                if (col + 1 == SIZE && counter1 == SIZE)
                {
                    flag = true;
                }
            }
            
            else
            {
                counter1 = 0;
            }
            
            if (board[col][row] == 'x') //checking columns
            {
                counter3++;
                
                if (col + 1 == SIZE && counter3 == SIZE)
                {
                    flag = true;
                }
            }
            
            else
            {
                counter3 = 0;
            }
            
            if (row == col && board[row][col] == 'x') //main diagonal condition
            {
                counter9++;
                if (counter9 == SIZE)
                {
                    flag = true; 
                }
            }
            
            if (row + col + 1 == SIZE && board[row][col] == 'x') //secondary diagonal condition
            {
                counter8++;
                if (counter8 == SIZE)
                {
                    flag = true; 
                }
            }
        }    
    }
    
    for (row = 0; row < SIZE; row++) //same story but with o
    {
        for (col = 0; col < SIZE; col++)
        {
            if (board[row][col] == 'o')
            {
                counter5++;
                
                if (col + 1 == SIZE && counter5 == SIZE)
                {
                    flag = true;
                }
            }
            else
            {
                counter5 = 0;
            }
            
            if (board[col][row] == 'o')
            {
                
                counter7++;
                
                if (col + 1 == SIZE && counter7 == SIZE)
                {
                    flag = true;
                }
            }
            else
            {
                counter7 = 0;
            }
            
            if (row == col && board[row][col] == 'o')
            {
                counter2++;
                if (counter2 == SIZE)
                {
                    flag = true; 
                }
            }
            
            if (row + col + 1 == SIZE && board[row][col] == 'o')
            {
                counter4++;
                if (counter4 == SIZE)
                {
                    flag = true; 
                }
            }
        }
    }
    return flag;
}

bool legal_move(char board[][SIZE], int row, int col)
{
    bool flag = true;
    
    if (board[row - 1][col - 1] == 'o' || board[row - 1][col - 1] == 'x')
    {
        flag = false;
    }
        
    return flag;
}

bool play_again(char *value)
{
    bool flag = false;
    
    if (strcmp(value, "yes") == 0)
    {
        flag = true;
    }
    
    return flag;
}

void print_score(char* player11, char* player22, int player11_score, int player22_score)
{
    printf("%s %i-%i %s\n\n",player11, player11_score, player22_score, player22);
}
