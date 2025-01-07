
#include <stdio.h>
#include <time.h>
#include <stdlib.h> /*For rand() and srand() functions and malloc.*/
#define ARRAY_SIZE 3
#define up 'U' /*You can change the directions whatever you want.*/
#define down 'D'
#define left 'L'
#define right 'R'
//NOT ! I DIDNOT CALCULATE TOTAL SCORE FOR COMPUTER BECAUSE THE TOTAL NUMBER OF MOVEMENT ARE INSANELY HIGH AND IT IS NOT POSSIBLE TO GET A GOOD SCORE FOR COMPUTER.

typedef struct puzzle_board{ /*I WANTED TO USE ALMOST EVERYTHING IN STRUCT*/
    char board[ARRAY_SIZE][ARRAY_SIZE];
    FILE *scores; /*The file pointer for scores.txt*/
    FILE *f_board; /*The file pointer for board.txt*/
    int total_move; /*The total move of the user or computer.*/
    char number; /*The number that user or computer entered.*/
    char direction; /*The direction that user or computer entered.*/
    int total_score; /*The total score of the user.*/
    int type; /*Type 1 means user mode.Type 2 means computer mode. */
    } puzzle;

int the_menu(puzzle *); /*This is the menu.*/
int play_game_as_user(puzzle *); /*This function is used to play game as a user.*/
int is_solveable(puzzle *); /*This function is used to control the game is solveable or not.*/
int is_legal_move(int , int , puzzle *); /*This function is used to control the move is legal or not.*/
int finish_with_pc(puzzle *); /*This function is used to finish the game with pc.*/
int is_game_finish(puzzle *); /*This function is used to control the game is finished or not.*/
int show_best_score(puzzle *); /*This function is used to show the best score.*/
int print_total_move(puzzle *p); /*This function is used to print the total move of the user or computer.*/
int calculate_total_score(int); /*This function calculates the total score*/

void print_board(puzzle *p); /*This function is used to print the board.*/
void create_board(puzzle *p); /*This function is used to create the board at the beginning of the game.*/
void find_number_indexes(int * , int * , char,puzzle *); /*This function is used to find the indexes of the number that user entered.*/
void auto_finish(puzzle *,int,int); /*This is my recursive function which ends the game approximately 10-30 second as you want*/
void computers_choice(int , int , char * , char *); /*This function is used to convert the computer's integer choices to char.*/
void writes_the_scores(puzzle *); /*This function is used to write the total score of the user to the scores.txt file.I save all of the scores which user solved.*/


int main() {
   
  puzzle p; /*My struct*/

  printf("Welcome to the 8-Puzzle Game.");
    the_menu(&p); /*This function is used to create the board and play the game.*/
    return 0;
}
int the_menu( puzzle *p){
        srand(time(NULL));

      int option; /*This variable is used to get the option from user.*/
    
     int flag = 1;
  do{ /*                READ ME !!!!!              */
  /*Befores start the menu , I am creating a solvable board but if it is not solvable , it may take 3 or 4 seconds to find a solvable board.This is the reason if you wondered why there is a waiting time befor the menu,*/
   printf("\nThe solvable board is getting ready...\n");
    create_board(p); /*Creates the board at the beginning of the game.*/
   /*Controls the game is solveable or not.If it is not solveable , it will create a new board until it is solveable.*/
    while( is_solveable(p) == 0 ){ /*If the game is not solveable , it will create a new board until it is solveable.*/
        create_board(p);
    
    }
     /*Classic menu switch cases.*/
   printf("\nPlease select an option : ");
   printf("\n1-Play game as a user\n");
   printf("2-Finish the game with pc\n");
   printf("3-Show the best score\n");
   printf("4-Exit\n > ");
   scanf("%d",&option);
   while(option <1 || option>4){ /*If the user enters an invalid option , it will ask again.*/
    printf("Enter a valid option(1-4) :");
    scanf("%d",&option);
   }
   switch(option){
    case 1 : flag = play_game_as_user(p); break;
    case 2 : flag =    finish_with_pc(p); break;
    case 3 : flag =    show_best_score(p); break;
    case 4 : printf("You quit the game.See you !\n"); flag =0; break;
   }
  } while(flag); /*Until flag is 0 , my loop is gonna run.*/
    return 0;
}
void create_board(puzzle *p){ /*This function is used to create the board at the beginning of the game.*/
  char *nbrs;
 nbrs = (char*)malloc(sizeof(char)*8);  /*This array is used to determine the numbers that are not used.*/
 int empty_x = rand()%3; /*Determines the empty space randomly*/
 int empty_y = rand()%3; /*Determines the empty space randomly*/
 int size = ARRAY_SIZE;

 for(int i = 0 ; i< size ; i++){
    for(int j = 0 ; j< size ; j++){
        if(i == empty_x && j == empty_y) p->board[i][j] = '_'; /*Adds '_' char to empty place.*/
        else {
            int num = rand()%8+1;   /*It creates a random number but they must be unique.To control this , I used following array.*/
            while(nbrs[num-1]!= '\0'){ /* cikan random sayinin indeksi null degilse , kullanilmis demektir.Kullanilmayan sayi bulunana dek while dongusu calisir,*/
                num = rand()%8+1; /*Bir kere kullanilan sayi tekrar kullanilmasin diye burda kullanilmayan sayi bulana  kadar gecistirme yapiyoruz.*/
            }
            
            nbrs[num-1] = num; /*Whileden cikmis ise bu sayi daha once kullanilmamis anlamina gelir.*/
            p->board[i][j] = num + '0'; /*I added '0' to convert integer to char.*/
        }
      

    }
 }
 while(is_game_finish(p) == 1){ /*If the game starts with finished  board , it creates a new board. There is  8! change to happen this.*/
 create_board(p);
 }
      free(nbrs); /*Frees the nbrs array.*/

}
int is_solveable(puzzle *p){
    char temp_puzzle[ARRAY_SIZE*ARRAY_SIZE] = {'1','2','3','4','5','6','7','8','_'}; /*initializing the array.*/
    int k = 0;
    for(int i= 0; i< ARRAY_SIZE ;i++){ /*This loop is used to copy the board to the temp array.It must be one dimension to check the solvebility of game.*/
        for(int j= 0 ; j < ARRAY_SIZE ; j++){
            temp_puzzle[k] = p->board[i][j]; /*I copy the board to the temp array.*/
            k++;
        }
    }

    /*After I created an 1-Dimension array , I am checking if it is solveble or not.*/
       int inversions = 0;
    for (int i = 0; i <8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if ( (temp_puzzle[i] != '_') &&( temp_puzzle[j] != '_') && (temp_puzzle[i] > temp_puzzle[j])) { /*Except the empty  space, I am comparing the elemnts of array and then I increment inversion one.*/
                inversions++; /*Increments the inversions by 1.*/
            }
        }
    }
    return (inversions %2 == 0 ); /*If the total inversion is odd , means it is not solvable.If it is even , means the game is solvable*/
}

int play_game_as_user(puzzle *p){ /*This function is used to play game as a user.*/
   p->type = 1; /*Type one means user-played mode.*/
    int type = 1; /*Type one means user-played mode.*/
    int index_x,index_y; /*These variables are used to find the indexes of the number that user entered.*/
    int flag= is_game_finish(p); /*This variable is used to control the game is finished or not.If flag is 1 means game over.Else, it continues*/
  /*Flag is gonna start with 0 because the cannot be finished at the first.*/

    printf("You selected play game as a user!\n");
    printf("The game has started ! Good luck ('_')\n");

    p->total_move = 0; /*Total move is 0 at the beginning of the game.*/

   print_board(p); /*Prints the board at the beginning of the game.*/

 
    printf("Example input -> 2-%c (Move 2 to right)\n",up);

    while(flag == 0 ){ /*If the game is not finished , it will ask the user to enter a number and direction to move.When flag is 1 , means the game is over.Else ,the game is gonna continue*/
    printf("\nPlease enter a number and direction to move (Write 0-E to exit) : "); /*Asks the user to enter a number and direction to move.*/
    scanf(" %c-%c",&p->number,&p->direction); /*Gets the number and direction from user.*/
    printf("\n");
   if(p->number !='0' && p->direction != 'E'){ /*If the user enters 0-E , it means the user wants to exit the game.*/
    p->total_move++; /*Increments the total move by 1.*/

    find_number_indexes(&index_x,&index_y,p->number,p); /*I must send the adresses of index_x and index_y because I need them in this function.Send by reference*/
    while(is_legal_move(index_x,index_y,p) == 0){ /*If the move is invalid , it will ask the user to enter a number and direction to move again.*/
   
      p->total_move--; /*If the move is invalid , it will decrement the total move by 1.*/
     printf("%c - %c is an illegal move.Please enter a number and direction to move : ",p->number,p->direction); /*Asks the user to enter a number and direction to move again.*/
     scanf(" %c-%c",&p->number,&p->direction); /*Gets the number and direction from user.*/
     if(p->number == '0' && p->direction == 'E') break; /*If the user enters 0-E , it means the user wants to exit the game.*/

    find_number_indexes(&index_x,&index_y,p->number,p); /*Finds the indexes of the number that user entered.It will be explained in the function.*/
    p->total_move++; /*Increments the total move by 1.*/
      
    }
   
      p->board[index_x][index_y] = '_'; /*If the move is valid , it will change the place of the number that user entered with '_' char as expected..*/

    switch(p->direction){ /*By user's direction entries , I arrange the location and write the number which user entered in that new index. */
      
        case up : index_x-- ;   p->board[index_x][index_y] = p->number;       break;  /*Case up means decrease x index one*/
        case down : index_x++;  p->board[index_x][index_y] = p->number;       break;  /*Case down means increase x index one*/
        case left : index_y--;  p->board[index_x][index_y] = p->number;       break; /*Case left means decrease y index one*/
        case right : index_y++; p->board[index_x][index_y] = p->number;       break; /*Case right means increase y index one*/
    }

if(p->number !='0' && p->direction !='E')  print_board(p); /*Prints the board after the user's move.*/
   
    flag = is_game_finish(p); /*Controls the game is finished or not.If flag is 1 means game over.Else, it continues*/
   }
    if(p->number == '0' && p->direction == 'E') flag =1; /*If the user enters 0-E , it means the user wants to exit the game.*/
    }
     if(p->number != '0' && p->direction != 'E'){
    print_total_move(p); /*Prints the total move of the user after the game is over..*/
    p->total_score = calculate_total_score(p->total_move); /*Calculates the total score of the user.*/
    printf("Your total score is : %d\n",p->total_score); /*Prints the total score of the user.*/
    writes_the_scores(p); /*Writes the total score of the user to the scores.txt file.*/
     }
     else printf("You quit the game.There is no total score.See you !\n"); /*If the user enters 0-E , it means the user wants to exit the game.*/
    return 1; /*Returns 1 to continue the main menu.*/
}


int finish_with_pc(puzzle *p){ /*This function is used to finish the game with pc.*/
    int flag= is_game_finish(p); /*This variable is used to control the game is finished or not.If flag is 1 means game over.Else, it continues*/
 p->type = 2; /*Type two means computer-played mode.*/
    printf("You selected finish the game with pc!\n");
    printf("The game has started !\n");

    p->total_move = 0; /*Total move is 0 at the beginning of the game.*/


    print_board(p); /*Prints the board at the beginning of the game.*/
  
    auto_finish(p,flag,0); /*This is the recursive  function that  used to finish the game with pc.It will be explained in the function.*/

  
    return 1; /*Returns 1 to continue the main menu.*/
}
void auto_finish(puzzle *p,int flag,int last_number){ /*This is the recursive  function that  used to finish the game with pc.*/

  if(flag != 0 ){ /*If flag is not 0  , It is 1. If flag is one means the game is over so my recursive function is gonna stop.Else, It will continue until flag becomes 1.*/
    print_total_move(p); /*Prints the total move of the computer after the game is over..*/
    printf("\nThe game is over ! \n");
    return;
  }
    int index_x,index_y; /*These variables are used to find the indexes of the number that computer entered.*/

    int cmp_numberr = rand()%8+1; /*Computers random number but it is integer, I am gonna convert it to char.*/
    while(cmp_numberr == last_number){ /*If the computer enters the same number as the last number , it will create a new number until it is different from the last number.*/
      cmp_numberr = rand()%8+1;
    }
    int cmp_directionn = rand()%4+1; /*Computers random direction but it is integer, I am gonna convert it to char.*/

    computers_choice(cmp_numberr,cmp_directionn,&p->number,&p->direction); /*This function is used to convert the computers choices to char.*/

    find_number_indexes(&index_x,&index_y,p->number,p); /*Finds the indexes of the number that computer entered.It will be explained in the function.*/
        p->total_move++; /*Increments the total move by 1.*/

    while(is_legal_move(index_x,index_y,p) == 0){ /*If the move is invalid , it will ask the user to enter a number and direction to move again. 0 means it is illegal move*/
      p->total_move--; /*If the move is invalid , it will decrement the total move by 1.It cannot count as a valid movement.*/
      cmp_numberr = rand()%8+1; /*These  are the new random numbers.It is gonna run until a legal movement,*/
   while(cmp_numberr == last_number){ /*If the computer enters the same number as the last number , it will create a new number until it is different from the last number.*/
      cmp_numberr = rand()%8+1;
    }
      cmp_directionn = rand()%4+1;  /*random direciton*/
    computers_choice(cmp_numberr,cmp_directionn,&p->number,&p->direction); /*This function is used to convert the computers choices to char.*/
    find_number_indexes(&index_x,&index_y,p->number,p); /*Finds the indexes of the number that computer entered.It will be explained in the function.*/
     p->total_move++; /*Increments the total move by 1.*/
     
    }
     /*By means of above while , only valid movements are written because the while loop does not end until it is a valid movement.*/
    printf("Computer's move : %c - %c\n",p->number,p->direction); /*Prints the computers move.*/

      p->board[index_x][index_y] = '_'; /*If the move is valid , it will change the place of the number that computer entered with '_' char as expected..*/

    switch(p->direction){ /*By computer's direction entries , I arrange the location and write the number which computer entered in that new index. */

        case up : index_x-- ;   p->board[index_x][index_y] = p->number;   break; /*Case up means decrease x index one*/
        case down : index_x++;  p->board[index_x][index_y] = p->number;   break; /*Case down means increase x index one*/
        case left : index_y--;  p->board[index_x][index_y] = p->number;   break; /*Case left means decrease y index one*/
        case right : index_y++; p->board[index_x][index_y] = p->number;   break; /*Case right means increase y index one*/
    }

      flag = is_game_finish(p); /*Controls the game is finished or not.If flag is 1 means game over.Else, it continues*/
     print_board(p); /*Prints the board after the computer's move.*/
  /*--->>>>*/auto_finish(p,flag,cmp_numberr); /*Recursive call as you want*/
}
void print_board(puzzle *p){

 if(p->total_move ==0) {
  p->f_board = fopen("board.txt","w"); 
  fprintf(p->f_board,"The game has started ! Good luck ('_')\n"); /*If the total move is 0 , it means the game is just started so I am gonna create a new board.txt file.I must delete if it is written before,*/
 }
 else p->f_board  =  fopen("board.txt","a"); /*If the total move is not 0 , it means the game is not just started so I am gonna append the board.txt file and write the all the boards..*/
 

 if(p->f_board == NULL){
     printf("Error in opening file!\n");
     return;
 }
              if(p->total_move != 0 ){
                if(p->type == 1 ) fprintf(p->f_board,"Your  movement : %c - %c\n",p->number,p->direction); /*If the total move is not 0 , it means the game is not just started so I am gonna print the user's move to the screen.*/
                if(p->type == 2) fprintf(p->f_board,"Computer's move : %c - %c\n",p->number,p->direction); /*If the total move is not 0 , it means the game is not just started so I am gonna print the user's move to the screen.*/
              }
    for(int i = 0 ; i< ARRAY_SIZE ; i++){ /*This loop is used to print the board to the screen and write the board to the board.txt file.*/
       
        for(int j = 0 ; j< ARRAY_SIZE ; j++){

             printf("%c ",p->board[i][j]); /*Prints the board to the screen.*/
             fprintf(p->f_board,"%c ",p->board[i][j]); /*Writes the board to the board.txt file.*/
        }

               printf("\n");
               fprintf(p->f_board,"\n");
    }
         
               fclose(p->f_board);

}

void find_number_indexes(int *index_x,int *index_y,char number,puzzle *p){
 /*In this function . I search the all of the elements of array . When I find the number , I save save indexes this number as pointer.Then I use it in main.*/
 
    for(int i = 0 ; i< ARRAY_SIZE ; i++){
        for(int j = 0 ; j< ARRAY_SIZE ; j++){
            if(p->board[i][j] == number){
                *index_x = i;
                *index_y = j;
                break;
            }
        }
    }
}


int is_legal_move(int index_x,int index_y,puzzle *p){
  
      switch(p->direction){ /*I firstly aply the change which user or computer entered.After this change, I check if it is less than 0 or greater than 2*/
      
        case up : index_x-- ;  break;
        case down : index_x++; break;
        case left : index_y--; break;
        case right : index_y++ ; break;
    }

    if(index_x < 0 || index_x > 2 || index_y < 0 || index_y > 2) return 0; /*After the direction process , if indexes are not between 0-2 , return 0 .means illegal move.*/
  
    if(p->number < '1' || p->number > '8') return 0; /*If the number is not between 1 and 8 , it is an illegal move.Function returns 0 I and use this returned number as flag.*/
    
    if(p->board[index_x][index_y] == '_'  )  return 1;
 else return 0; /*If the number is not equal to '_' , it means there is a number in that index so it is an illegal move.Function returns 0 I and use this returned number as flag.*/

}
int is_game_finish(puzzle *p){

    int flag = 1; /*I assume the game is finished at the beginning.*/
    int l = 1;
    for(int i = 0 ; i<8 ; i++){
        if(p->board[i/3][i%3] != '0' + (i+1)) flag = 0;  /*If the board is not equal to the expected board , it means the game is not finished.*/
    }
    return flag; /*If the game is finished , it returns 1.Else , it returns 0.*/
}



void computers_choice(int cmp_numberr ,int cmp_directionn,char *number, char * direction){
   
    /*This function turns integer numbers which are created by pc to char.Then , they are used in main again.*/
  *number = cmp_numberr + '0' ;/*Converting integer to char*/
  
  switch(cmp_directionn){
    case 1: *direction = up; break;  /*Converting integer to char*/
    case 2: *direction = down; break;
    case 3: *direction = left; break;
    case 4: *direction = right; break;
    default : printf("Error in computers_choice function!\n"); break;
  }

}
int print_total_move(puzzle *p){
    if(p->type == 1 )  printf("\nYour total number of moves  are: %d\n",p->total_move); /*Type 1 means user-played mode.*/
    if(p->type == 2 )  printf("\nComputer's total number of moves  are: %d\n",p->total_move); /*Type 2 means computer-played mode.*/
    return 1;
}


int calculate_total_score(int total_move){
    return (1000 - (10 * total_move)); /*This is the formula that used to calculate the total score.*/
}

void writes_the_scores(puzzle *p){
   
   p->scores = fopen("scores.txt","a"); /*Opens the scores.txt file to append.*/
    if(p->scores == NULL){ /*If the file cannot be opened , it prints an error message.*/
        printf("Error in opening file!\n");
        return;
    }
    fprintf(p->scores,"%d\n",p->total_score);  /*Writes the total score of the user to the scores.txt file.*/
    fclose(p->scores); /*Closes the file.*/
}
int show_best_score(puzzle *p){

  p->scores= fopen("scores.txt","r"); /*Opens the scores.txt file to read.*/

if(p->scores == NULL){
    printf("There is no such scores.txt.You should finish at least one game to see the score!.\n");
     return 1;
}
int max;
fscanf(p->scores,"%d",&max); /*I assume the max score is first score , Then I read all of the other scores and check if there is a bigger than max this max score.*/
int score;
while(fscanf(p->scores,"%d",&score) == 1 && !feof(p->scores)){
 if(score >= max){ /*If there is a bigger score than max , I change the max score with this score.*/
    max = score;
 }
}
  if(score >=max ){ /*Do not forget to consider the last score if there is no newline after the score.*/
    max =score;
  }
 printf("\nTHE BEST SCORE IS - > %d\n",max); /*Prints the best score.*/
fclose(p->scores); /*Closes the file.*/
    return 1;
}
