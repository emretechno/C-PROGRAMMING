#include <stdio.h> 
#include <stdlib.h> /*I use this library for malloc , realloc and free functions.*/
#include <time.h> /*I use this library for random moves.*/

#define bait '.'
#define empty ' '
#define obstacle 'o'
#define snk_head 'O'
#define snk_body 'X'

#define BOARD_X 10
#define BOARD_Y 10
#define BOARD_Z 3
#define DEPTH_OBS 9

#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'



typedef struct point{ /*I use this struct to represent a point in the board.*/
     int n;
     int row;
     int col;
   
} point;


typedef struct block{ /*I use this struct to represent a block in the board.*/
    int value;
    char type ;
} Block;


Block ***init_board(); /* *** is obligation because my array is 3D.*/
void draw_board(Block ***board); /*I use this function to draw the board.*/
void play(Block  ***); /*I use this function to start the game.*/
int move(Block ***board , point *,int * , int *); /*I use this function to move the snake.*/
int check_status(Block ***board,point *k, int , int); /*I use this function to check the status of the game.*/
point *update(Block ***board , point * , int * , int *,int * , int *); /*I use this function to update the board.*/

int main(){
    srand(time(NULL)); /*For random moves, I need this function.*/
    Block ***board = init_board();  /*I generate a board there and return it.*/
      play(board); /*I start the game.*/

      for(int i = 0 ; i< BOARD_X ; i++){ /*I free the memory.*/
        for(int j = 0 ; j< BOARD_Y ; j++){ 
            free(board[i][j]);
        }
        free(board[i]);
      }
      free(board); 
    return 0;
}
Block ***init_board(){
    /* *** IS OBLIGATION*/
    Block ***board = (Block ***)malloc(sizeof(Block **)*BOARD_X); /*I allocate the memory for board. X axis*/

     for(int i = 0 ; i< BOARD_X ; i++){ 
        board[i] = (Block **)malloc(sizeof(Block *)*BOARD_Y); /*Y axis*/
        for(int j = 0 ; j< BOARD_Y ; j++){
            board[i][j] = (Block *)malloc(sizeof(Block)*BOARD_Z); /*Z axis*/
            board[i][j]->value = 0;
            board[i][j]->type = empty;
    }
     }

   board[0][0]->type = snk_head; /*I initialize the snake head in 0,0 coordinate.*/
    int bait_x = rand()%BOARD_X; /*I generate a bait.*/
    int bait_y = rand()%BOARD_Y; /*I generate a bait.*/
    while(bait_x == 0 && bait_y == 0){ /*If the bait is on 0 , 0 ; create a new bait,*/
        bait_x = rand()%BOARD_X;
        bait_y = rand()%BOARD_Y;
    }
    board[bait_x][bait_y]->type = bait; /*I update the board as new bait.*/

   int obstacle_x = rand()%BOARD_X; /*I generate an obstacle.*/
   int obstacle_y = rand()%BOARD_Y; 
    while((obstacle_x == 0 && obstacle_y == 0) ||( obstacle_x == bait_x && obstacle_y == bait_y)){ /*if the coordinates are on bait on 0 , 0 ; create a new osbtale.*/
        obstacle_x = rand()%BOARD_X;
        obstacle_y = rand()%BOARD_Y;
    } /*MY NESTED BLOCK  IS HERE*/
    for(int i = 0 ; i< BOARD_X ; i++){
        for(int j = 0 ; j<BOARD_Y  ; j++){
            for(int k = 0 ; k<BOARD_Z ; k++){
              board[i][j][k].value = 0;
    board[obstacle_x][obstacle_y][k].type = obstacle; /*I update the board as new obstacle.*/
    board[obstacle_x][obstacle_y][k].value = rand()%DEPTH_OBS +1; /*I update the board as new obstacle value.*/
        }
        }
    }

    return board; /*Return the board as u want*/
}
void play(Block ***board ){
 
   int obs_counter = 1; /*I use this variable to count the number of obstacles.*/
   int total_move = 0; /*I use this variable to count the number of moves.*/
  
  

      point *snake = (point *)malloc(sizeof(point) * 1); /*I use this struct to represent the snake.*/
        snake[0].row =  0; /*I initialize the snake.*/
        snake[0].col =0;  
        snake[0].n = 1; 
        int row = 0;
        int col = 0;
      if(snake == NULL){ /*I check the memory allocation.*/
        printf("Memory allocation error");
        exit(1); 
      }
  
    draw_board(board); /*I draw the board.*/
   
    
    while(move(board,snake,&row,&col)){ /*Until the move returns 0 , my while is gonna run.When it is zero , means the game is over.*/

  
        total_move++; /*I increase the number of moves in every move*/
        snake =update(board,snake, &total_move , &obs_counter,&row,&col); /*I update the as you want board.*/
        draw_board(board); /*Then I draw the board.*/

    }

    printf("Game over !\n");
    free(snake); /*I free the memory.*/
}




int  move(Block ***board,point *snake,int * row, int *col){
     snake[0].row = *row;  /*Snake tail[0] means the curren row and col and it also means it is the head.*/
    snake[0].col = *col; /*I am finding the last head coordinates.*/

char direction; 
printf("Enter the direction you want to move: ");
scanf(" %c",&direction); /*I get the direction from the user.*/
switch(direction){
    case up: (*row)--; break;  /*I update the row and col according to the direction.*/
    case down: (*row)++; break;
    case left: (*col)--; break;
    case right: (*col)++; break;
    default : printf("Invalid direction !\n"); break;
}
 if(check_status(board , snake , *row , *col) == 1) return 0; /*I check the status of the game.If it is over , return 0*/
    return 1;
}
point * update(Block ***board, point* snake, int *total_movement, int *obs_counter, int *row, int *col){
   
 if(board[*row][*col]->type == empty){ /*If the changed coordinates in board is emtpy, this empty place will be head.*/
        board[*row][*col]->type = snk_head; /*Now it is the head of the snake*/

  if(snake->n== 1) board[snake->row][snake->col]->type = empty; /*The  previous coordinat became empty now.*/
 
 if(snake->n > 1) { /*But if it is length more than 1 , I need for loop to make the previous coordinates empty.*/
        for(int i =  snake->n-1; i>=1  ; i--){ /*Bas haric kuyruk kisimlarini empty yapiyorum.*/
            board[snake[i].row][snake[i].col]->type = empty;
            board[snake[i].row][snake[i].col]->value = 0;
              snake[i].row = snake[i-1].row; /*ayni zamanda snake arrayinin koordinatlarini bir kaydiriyorum.Yani aslinda shifting islemi sagliyorum...*/
        snake[i].col =   snake[i-1].col; /*Bir  onceki indeksi bir sonraki indekse kaydirma*/
        }
     snake[0].row = *row; /*Burada basin yeni koordinatlarini atiyorum.*/
    snake[0].col = *col; /*Basin row ve col degerleri guncellendi*/

        for(int j = 1 ; j< snake->n ; j++){ /*Yeni bodymizi guncellemistik , simdi iste o bodyleri yazma vakti.*/

            board[snake[j].row][snake[j].col]->type = snk_body;
        }
 }
    
}
 else if(board[*row][*col]->type == bait){ 
    board[*row][*col]->type = snk_head; /*New space will be head of snake.*/
  snake->n++; /*I increase the length of the snake one*/
        
     snake = (point *)realloc(snake , sizeof(point) * snake->n); /*In this part , reallocation is obligation.*/
    
    for(int i =snake->n -1   ; i>=1  ; i--){ /*Shifting one indeks to previous indeks.*/
        snake[i].row = snake[i-1].row;
        snake[i].col =  snake[i-1].col;
    }

    snake[0].row = *row; /*I update the head coordinates.*/
    snake[0].col = *col; /*I update the head coordinates.*/

 
    for(int i = 1 ; i<snake->n ; i++){ /*Snakes body was updated, now is time to print them.*/
        board[snake[i].row][snake[i].col]->type = snk_body;
    }
    int bait_x = rand()%BOARD_X;
    int bait_y = rand()%BOARD_Y;
    while(board[bait_x][bait_y]->type != empty){ /*I generate a new bait.*/
        bait_x = rand()%BOARD_X; /*The bait must be in empty cell as expected.*/
        bait_y = rand()%BOARD_Y;
    }

    board[bait_x][bait_y]->type = bait; /*I update the board as new bait.*/

 }
 else if(board[*row][*col]->type == obstacle && snake[0].n >= board[*row][*col]->value){ /*If the snake hit the obstacle.*/
    board[*row][*col]->type = snk_head; /*New space will be head of snake.*/
    (*obs_counter)--; /*I decrease the number of obstacles.*/
    for(int i = snake->n-1 ; i>=1 ; i--){ 

        board[snake[i].row][snake[i].col]->type = empty; /*The previous body coordinates must be empty.*/
        snake[i].row = snake[i-1].row; /*Shifting one indeks to previous indeks.*/
        snake[i].col = snake[i-1].col; /*Shifting one indeks to previous indeks.*/
    }
    for(int i = 1 ; i<snake->n ; i++){ /*Then I print the updated body in board.*/
        board[snake[i].row][snake[i].col]->type = snk_body;
    }
    snake[0].row = *row; /*I update the head of snake coordinates.*/
    snake[0].col = *col; /*I update the head of snake coordinates.*/
  
 }
   if(*total_movement == 5){ /*If the total movement is 5 , I generate a new obstacle.*/
        if(*obs_counter <3){ /* I will generate new obstacle until total obstacle is three.*/
     int obs_x = rand()%BOARD_X; /*I generate a new obstacle.*/
    int obs_y = rand()%BOARD_Y;
    while(board[obs_x][obs_y]->type != empty){ /*The obstacle must be in empty cell as expected.*/
       
        obs_x = rand()%BOARD_X;
        obs_y = rand()%BOARD_Y;
    }
    (*obs_counter)++;
    for(int i = 0 ; i< BOARD_X ; i++){
        for(int j = 0 ; j<BOARD_Y  ; j++){

    board[obs_x][obs_y]->type = obstacle; /*I update the board as new obstacle.*/
    board[obs_x][obs_y]->value = rand()%DEPTH_OBS +1; /*I update the board as new obstacle value.*/
        }
    }
     *total_movement =0;
}
}
if(*obs_counter == 3){ /*If the total obstacle is three , I will delete all of them first.*/
    if(*total_movement == 5){
        int chosen = rand()%3;
        int counter  = 0;
    for(int i =  0 ;i< BOARD_X; i++){
        for(int j = 0 ; j< BOARD_Y ; j++){ /*I delete all of them.*/
            if(board[i][j]->type == obstacle){
                 counter++;

         if(counter == chosen+1){ /*I update the board as new obstacle.*/  
           int new_obs = rand() % DEPTH_OBS + 1;

          while(new_obs<=board[i][j]->value){ /*I generate a new obstacle.*/
           new_obs = rand() % DEPTH_OBS + 1;
            if(new_obs == 9) break;
             }

        board[i][j]->value = new_obs;

           for(int i = 0 ; i< BOARD_X ; i++){
           for(int j = 0 ; j<BOARD_Y  ; j++){
            for(int z = 0 ; z <BOARD_Z ; z++){
           board[i][j][chosen].value = new_obs; /*I update the board as new obstacle value.*/
        
            }

        }
    }
         }
         

               }

         }
    }
       
    
    *total_movement = 0;
    }
}

return snake; /*I return the snake tail.*/
}

 int check_status(Block ***board , point* snake , int row  , int col ){
   if(row<0 || row>=BOARD_X || col<0 || col>=BOARD_Y){ /*If the snake hit the wall.*/
    printf("You hit the  wall !. GAME OVER.\n");
    return 1;
   }
 else if(board[row][col]->type == obstacle && snake->n<board[row][col]->value){ /*If the snake hit the obstacle.*/
printf("You hit the obstacle !. GAME OVER.\n");
    return 1;

  }
else if (board[row][col]->type == snk_body){ /*If the snake hit itself.*/
    printf("You hit yourself !. GAME OVER.\n");
    return 1;
}
     return 0; /*If the game is not over.*/
 }



void draw_board(Block ***board){
    for(int i =  0 ; i<BOARD_X*4+1 ; i++){
        printf("-"); /*Once ust cizgiyi bastir*/
    }
printf("\n");
    for(int i = 0; i < BOARD_X; i++){
        printf("|"); 
        for(int j = 0; j < BOARD_Y; j++){
            for(int k = 0 ; k<BOARD_Z ; k++){
          if(board[i][j]->type != obstacle) printf( " %c ",board[i][j]->type); /*Obstalce degil iste type.*/
          else printf(" %d ",board[i][j][k].value); /*Obstacle ise degerini basacak*/
            printf("|");
            break;

        }
       
        }

        printf("\n");
          for(int i =  0 ; i<BOARD_X*4+1 ; i++){
        printf("-"); /*sonra alt cizgiyi bastir*/
    }
printf("\n");
    }   
}