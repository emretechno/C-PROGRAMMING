

#include <stdio.h>
#include <time.h> /*To use srand(time(NULL)), I need time.h library.*/
#include <stdlib.h> /*To use rand ...*/
#define UP 'w' /*Defining the directions. w for up , s for down , d for right and a for left.*/
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

void Game_Menu(int); /*It has switch case algorithms.*/

void start_the_game(); /*Starts the game and draws the first room*/

void draw_gameplay(int , int ,int ,int ,int); /*It draw the current situation of game in user's every movement.*/

void print_total_movements(int,int); /*It prints the total movements,*/

void print_short_line(int); /*Prints the short lines.*/

int check_status(int,int,int,int); /*In every move , checks the game if it is over or not.*/

int main() {
    /*My code dictionary:
    x and y respresent the real coordinates.For example  , x_door = x coordinate of door . y_char = y coordinate of char.
    status is the current situation of the game.If it is 1 , the game is over. If it is 0 , the game is still active.
    valid_movement = User's literally valid movements.I do not count the hitting the wall movements in that.
    movement_vall = The number of times the user hits the wall.I count the movements seperately.
    */
    printf("\nWELCOME TO 2D PUZZLE GAME!\n");

    Game_Menu(1); /*Menu is gonna start with 1.I send 1 to start the menu.*/
    
    /*My whole  game is working with functions , so I did not want to write a lot of code in main part.Everyting is written under functions.*/
    
    return 0;
}

void Game_Menu(int status){
    
    if(status==1){ /*My menu starts when the status =1.I created an if condition to control the menu.*/
        
        printf("1. New Game\n");
        printf("2. Help\n");
        printf("3. Exit\n");
        
        int option;
        
        scanf("%d",&option); /*Switch case algorithm.*/
 
        while( (option !=1 ) && (option !=2 ) && (option !=3 )){
            printf("Please enter an valid option!:(1),(2) or (3).\n"); /*User must be enter only 1 , 2 or 3.There is no other option.*/
            scanf("%d",&option);
        }
        
        
        switch (option) { /*I made a switch case algorithm.*/
            case 1:
            
                
                start_the_game(); /*This function draws the first situation the game before starts.*/
               
                break; /*Do not forget to add  break in switch case.*/
                
            case 2: /*Case two is the explanation part.I am explaining the rules of game.*/
                printf("Firstly,thank you to choose my puzzle game!\nIn this game ,the character is able to move on space in any of the four cardinal directions which are up,down,left right. Diagonal moves are not allowed.\n\n");
                
                printf("The user will input their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down.\n\n");
                
                printf("You should make smart moves to end the game faster.\n\nThe game will prompt the user for a new move after each move is made until the game is over.\n\n\n");
   
                Game_Menu(status); /*After user saw the help , I send it user to menu again.*/
                
                break;
                 
            case 3: /*In case of 3 , user quits the game with an goodbye sentence.*/
                printf("You quit the game! Goodybe!..\n");
                break;
                
            default: /*Default is the case if none of the all other cases invalid.*/
                printf("You entered an invalid opton!\n");
                break;
        }
    }
 
}


void start_the_game(){
        int size;

                printf("Please enter the size.(Between 5 and 10 inclusive.)\n");
                scanf("%d",&size); /*The size of interval is between 5 and 10.User can enter only the number which is between 5 and 10.*/
                while((size <5) || (size > 10)){ /*User cannot enter a number except this interval.*/
                    printf("Please enter a valid size!.(Between 5 and 10 inclusive.):");
                    scanf("%d",&size);
            

                }
    
                printf("The game has started.Good luck ('_')\n");
      
                
                srand(time(NULL)); /*By means of this , my coordinates of Char and Door will be randwom each time program runs.*/

                int x_door = rand() % size+1; /*I am creating the random coordinates.Note:My coordinates start with 1,1 not 0,0 that is why I must add 1 near of the rand.*/
                
                int y_door = rand() % size+1; /*Same process*. My coordinates are starting with 1,1 not 0,0.That is why I must add +1 near the rand functions.*/
                
                int x_char = rand() % size+1;  /*Same process.I dont want to find the result 0 , I am adding +1 because of that.*/
                
                int y_char = rand() % size+1; /*Same process*/
                
                while(x_door== x_char && y_door==y_char){ /*At the first ,By  1/625 change , the cordinates may be assinged same as C and D.I wanted to check this problem.*/
                    
                    x_door = rand() % size+1; /*If the coordinates of C and D are same  , I must assign new coordinates either door or char.Does not matter.*/
                    y_door = rand() % size+1; /*I chose the change the door.I could have changed also char.*/

                }
                
    
    print_short_line(size); /*It writes the short lines before boxes.(-)*/
    
    for(int y =size ; y>=1;y--){ /*This is my y coordinate,It must be start with size because c writes from top the bottom , but coordinates increase from bottom to top.I just want it to preserve the main logic of coordinate system.For example ,size is 5 ; then my uppermost y coordinate will be 5 and my nethmermost y coordinate will be 1.*/
        printf("\n");
        

        for(int x =1; x<=size+1; x++){ /*This is my x coordinate starts with 1.It must be axis+1 line otherwise, the last box is not be a whole box.It will be half.*/
            
            printf("|");
            if(x_door == x && y_door == y){ /*When the coordinates are same as Door, I write D instead of using space.*/
                printf("D");
            }
          else  if(x_char == x && y_char==y){/*When the coordinates are the same as Char ,T write C instead of using space.*/
                printf("C");
            }
            else {
                printf(" "); /*Otherwise , I will add space.*/
            }
          
   
            
            
        }
    }
    printf("\n");
    
    print_short_line(size); /*It adds the short lines like this :----------------*/
   

    int valid_movement =0; /*I will count the movoments of user.*/
    int movement_wall=0; /*I will count the user's wall hits until the game is over.The number of times the user hits the wall*/
    int status =check_status(x_door,y_door,x_char ,y_char); /*I check the status of game.*/
    
   /*When status is 1  , my loop is gonna stop.It means the game is over and user cannot enter directions anymore.*/

    while (status !=1) {
    char buffer;
    char direction; /*It will be the direction which will be entered by user.*/
    printf("\nReach the door!(w->up ,a->left , s->down ,d->right):");
    scanf(" %c",&direction);

    buffer  = getchar(); /*If user tries to enter more than one char , my buffer will take  it.*/

    if(buffer !='\n'){
     printf("Invalid movement! Please make just one movement!\n"); /*This is my error print**/

    while(buffer !='\n'){
        buffer = getchar(); /*Until user enter the '\n' , all of the other chars will not be read by my direction char.*/
    }
            draw_gameplay(size,x_door,y_door,x_char,y_char); /*I draw the sitatuon of Char and Door.*/

    continue;/*Continue is obligation because if user continues to enter more than one char , my if condition backs to begin.You can think like that I am cleaning the buffer.*/
    }
 
    
        switch(direction){
                
                /*Up ,left , down, right are defined at the top of my code.*/
            case UP: /*Up means y++ */
                
                y_char++; /*If user go up , I must increase the y coordinate one.*/
                
                break;
                
            case LEFT: /*Left means x-- */
                
                x_char--; /*If user go left , I must decrase the x coordinate one.*/
                
                break;
            case DOWN: /*Down means y-- */
                
                y_char--; /*If user go down , I must decrease the y coordinate one.*/
                
                break;
            case RIGHT: /*Right means x++ */
                
                x_char++; /*If user go right , I must increase the x coordinate one.*/
                
                break;
                
            default:
                printf("\nInvalid movement!\n");
                break;
        }
    

        valid_movement++; /*I am counting the total movements when user moves.*/
        
        /*Checking the wall if user hits or not.*/
        while(x_char==0 || x_char==size+1){ /*Hitting walls  are in while loop because user can constantly try to  hit the wall, not for once.*/
            
            if(x_char==0){ /*It's not possible to go further to the left.*/
                
                /*When x coordinate is zero , I realize that my user hit the wall.*/
                printf("You hit the wall!.You cannot go left anymore!\n");
                x_char++; /*I should increase the x coordinate one to not hit the wall.*/
                movement_wall++; /*Then I increase the hitting time of the wall one.*/
                valid_movement--; /*And decrease the valid movement one because hitting wall is not a valid momevent.*/
                
            }
            
            if(x_char==size+1){ /* It's not possible to go further to the right*/
                /*Same logic process are also valid for other 3 walls.I think there is no need to explain them again.*/
                printf("You hit the wall!.You cannot go right anymore!.\n");
                x_char--;
                movement_wall++;
                valid_movement--; /*hitting wall is not a valid movement.I decrease it again.*/

            }
        }
        
        while(y_char==0 || y_char == size+1){ /*Hitting walls are in while loop because user can constantly try to  hit the wall not once.*/
            
            if(y_char==0){ /*It's not possible to go down any further.*/
                
                printf("You hit the wall!.You cannot go down anymore\n");
                y_char++;
                movement_wall++;
                valid_movement--; /*hitting wall is not a valid movement.I decrease it again.*/

            }
            
            if(y_char==size+1){ /*It's not possible to go higher.*/
                
                printf("You hit the wall!.You cannot go up anymore.\n");
                y_char--;
                movement_wall++;
                valid_movement--; /*hitting wall is not a valid movement.I decrease it again.*/
                

            }
            
        }
        

        draw_gameplay(size,x_door,y_door,x_char,y_char); /*I draw the sitatuon of Char and Door in every movement.*/
        
        status = check_status(x_door,y_door,x_char,y_char); /*Everytime after user moved , I check the status of game whether it is over or not. */

    }
    print_total_movements(valid_movement,movement_wall); /*When the status is 1 , I realize that the game is over.After that , I print the movements.Valid movements and hitting the wall movements.*/
    
    
    Game_Menu(status); /*I send user to menu again.If status =1 , means game is over and it also means new menu should be displayed.*/

}


int check_status( int x_door ,int y_door,int x_char, int y_char){
    
  int  status=0; /*First situation , my status is 0.*/
    
    if(x_door==x_char && y_door==y_char){ /*The condition of end the game.*/
         /*But when the game is over , I mean the coordinates of C and D are same, status will be 1.*/
        printf("\nCongratulations! You finish the game."); /*Game over message to user.*/
       status=1; /*Means game over.*/

    }

    return status; /*I return the status of game whether it is over or not.*/
}


void draw_gameplay(int size , int x_door , int y_door , int x_char , int y_char){
    
/*It is the same logic as draw_first_room.Additionally, I am constantly sendind the new coordinates to this function so that every movement of user will ve drawn by means of this function.*/
    
    print_short_line(size);

    for(int y =size ; y>=1; y--){ /*my y axis.*/
        printf("\n");

        for(int x =1; x<=size+1; x++){ /*my x axis*/

            printf("|");

            if(x_door == x && y_door == y){ /*same process also for this.*/
                printf("D");
            }

          else  if(x_char == x && y_char==y){
                printf("C");

            }
            else {
                printf(" ");
            }
          
   
            
            
        }
    }
    printf("\n");
    
    print_short_line(size); /*I print the short lines.(--------------)*/


}

void print_short_line(int size){

    for(int i =1; i<=(2*size) +1  ; i++){ /*I will add the shortlines.*/
        printf("-");

    }
}


void print_total_movements(int valid_movement , int movement_wall){
    
    printf("\nYour total valid movements are: %d\n",valid_movement);


    if(movement_wall !=0){ /*It writes the total movements to the walls*/
    printf("You hit the wall %d times.\n",movement_wall);
    }

    else if(movement_wall ==0){ /*I did not want to ouput like this: You hit the wall 0 times.That is why I created an if condition.*/
        printf("You didn't hit the wall at all.\n");
    }

}
