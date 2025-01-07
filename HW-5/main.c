 
#include <stdio.h>
#include <math.h>
#define SIZE_FILENAME 32
#define SIZE_ALPHABET 26

typedef enum { /*I am using enum just like you want.The values of colors are starting from 0 and it is increasing one by one.*/

     RED,GREEN,BLUE,YELLOW,ORANGE
    
} color;

/*-----PART 1  FUNCTIONS---*/

int part1(void);
void read_file(FILE * , int * ); /*In this part , I am reading the file  and I know that array is also a pointer thus I send my frequency array as a pointer.*/
int make_uppercase(int); /*By chancing the ascii values of chars , I create my own uppercase function */
void print_frequencies(int *); /*To print the frequencies of all the letters , I send my array as a pointer as you want;*/

/*-----PART 2  FUNCTIONS---*/

int part2(void);
int the_int_choice(char); /*This function sends char to integer to use is in enum because user enters char (like r ) not int.That is why I need a function to turn it integer.*/
color mix (color color1 , color color2 ); /*This function will be my function pointer.*/
color colorMixer( color color1 , color  color2, color(*mix)(color , color)); /*This function prototype has 2 variable and a function pointer  as you want from us.It will be detailed in the function.Using pointer is essential .*/


/*-----PART 3  FUNCTIONS---*/

int part3(void);
void print_current_board(char [3][3] ,int); /*Every time users enters the coordinates , this function prints the curren board of the game.*/
int check_status(char [3][3] , int); /*This function checks the status of game.If game is over (I also check the winner  or if it is draw) returns 1.*/
void check_continuity(char); /*This function checks whether user wants to continue or not.*/


int main(void) {

    part1();
         
    part2();

    printf("\n\nWELCOME TO TIC TAC TOE GAME !\n");
    
    part3();
     
    return 0;
    
}


int part1(void){
    FILE *fp;
    char  file_name[SIZE_FILENAME]; /*I determined the size of filename 32.You may change if you want.*/
    int frequency[SIZE_ALPHABET] = {0}; /*There are 26 letters as I defined above.This will be my frequencies of all of the letters.*/
    printf("Enter the file name :");
    scanf(" %s",file_name); /*Firstly , user is gonna write the name of file.*/
    fp= fopen(file_name , "r");

    if(fp == NULL){
        printf("There is no such a file!You should enter a existing file name.\n");
    }

   else {
    read_file(fp , frequency); /*I am sending to function.*/
    fclose(fp);
    print_frequencies(frequency); /*I call print_frequencies function to print my frequency array.*/
   }
    
 return 0;
}


void read_file(FILE * fp , int *count){

           char c;
           while ( (c =fgetc(fp)) !=EOF ){ /*My loop is gonna run until the end of the file.*/
 
            if((c >=65 && c<=90)  || ( c>=97 && c<=122) ){ /*I only control the char variables by using this if.These numbers are the ascii values of chars,For example between (A-Z) equals 65-90 and , between (a-z) equals 97-122.After my char  got into the if condition I make it uppercase  by using toupper function.*/
             
            c = make_uppercase(c); 
           /*I am making lowercases to uppercase.*/   

               count[c -'A']++;  /*After that , I substract 'A' to start to my array's index from 0 to 26.Any letter char will increment my frequency array and I will find the all of freqnecies of letters.*/
            }

           }

}

int make_uppercase(int c){

    if(c >=97 && c <=122){ /*If my char's value between 97 - 122  , it means it is a loweracase.In this situation , I substract the 32 from the ascii value.*/

       c = c - 32; /*By means of this substraction ,  my lowercase becomes an uppercase.*/

       /*Yani her kucuk harf buyuk harf arasinda 32 lik bi fark var.Dolayisiyla  32 fazlasi kucuk harf olan harften 32 cikararak buyuk harfi buluyorum.I could have explained this part English.I'm Sorry!.*/

       }
    return c; /*Then I return the integer provison of c*/
}

void print_frequencies(int * counts){

    printf("Letter Frequency :\n");
     /*Then , I am printing the all of the elements which are the frequencies of letters.*/
       for(int i = 0 ; i< 26; i++){ /*There were 26 elements and I should print it all.*/
        printf("%c : %d\n",'A'+i , counts[i]); /*Do not forget to add 'A' near to i to make char provision of i.*/

       }
       printf("\n");
}




int  part2(void){
    
    char renk;
    color color1,color2; /*Firstly , I am creating the color1 and color2 variable .*/
  
    printf("Please enter color 1 (r,g,b,y,o) :");
    scanf(" %c",&renk); /*User is gonna enter the colour as char.*/
    color1 = the_int_choice(renk); /*In this function , I am turning char into integer by using enums.Now , I know my color1 variable in integer form by means of this function.*/
     
    printf("Please enter  color 2 (r,g,b,y,o) :"); /*same logic in this process.*/
    scanf(" %c",&renk); /*When user enter a char , I am turning it into the integer*/
    color2= the_int_choice(renk);
    int index = colorMixer(color1,color2,mix); /*And in this part, I am sending my variables to  colorMixer function which takes the pointer function as argument.*/
    /*Mix function is sending as a function pointer argument as you wanted.*/
return 0;
  
}
int the_int_choice(char input){
    /*Input is the users input.By using enums  and switch case , I am turning it into integer.*/
    
    while( (input !='r') && (input !='g') && (input !='b') && (input !='y') && (input !='o')){
        printf("enter a valid input ! (r,g,b,y,o):");
        scanf(" %c",&input);
    }
   int choice;

   switch (input){
   
   case 'r': /*if user enter r , means it is red.*/
     choice = RED;
    break;

    case 'g': /*If user enters g ,means he chose green.*/
     choice= GREEN;
    break;

    case 'b':
    choice = BLUE; /*same process.*/
    break;

    case 'y': /*same*/
    choice = YELLOW;
    break;

    case 'o': /*same*/
    choice = ORANGE;   
    break;

   default:

    break;
   }
    
   return choice; /*In the end , I am returning the choice.Do not forget that my choice variable was integer , not char.*/
  
}


color colorMixer(color color1, color color2 , color (*mix)(color, color)){
    
    printf("Mixed Color : "); /*The essenital writing for output.*/
    int mixed =mix(color1,color2); /*Then I  call the function pointer.*/
    
    return mixed; /*This mixed variable is in integer form.*/
     
}

  color mix(color color1 , color color2){

  float vect_colors[5][3]= {   /*I wanted to create 2D array to store the color vectors.It looked easy and also it is related to Yakub Hoca's lectures.My 2 dimensiol array starts with 0 and it points the red vector.Then first array points green vector.And same logic continues. */

        {1,0,0}, /*RED          [0][3]*/
        {0,1,0}, /*GREEN        [1][3]*/
        {0,0,1}, /*BLUE         [2][3]*/
        {0.5,0.5,0}, /*YELLOW   [3][3]*/
        {0.5,0.4,0.2}, /*ORANGE [4][3]*/
        
    };

   
      float mixed[3]= {0}; /*This array will be my result of mixed array.I assign the all of the elements zero because I will make a summing process later..*/
      
      for(int i = 0 ; i< 3; i++){ /*I am just summing the color1 vector with the mixed array.*/
        mixed[i] = mixed[i] + vect_colors[color1][i]/2; /*/2 is obligation because it writes on pdf.This formula is given by you.*/
      }
    for (int j = 0 ; j < 3 ; j++) { /*Then same logic.I am summing the mixed array with color2 vector*/
        mixed[j] = mixed[j] + vect_colors[color2][j]/2; /*  /2  is obligation as you wanted.The formula is given by you.*/
    }
    /*After I find the mixed array , I will find the closest one by using euclidian distance.Let's Start !*/
      
     /*In min_distance , I chose the first array of vect_lentgth is the closest one.I mean ,I just assumed that the RED vector is the closest one.However, I will check the all other vectors wheter there is a closer than red or not.*/
    float min_distance =sqrt (  (pow(mixed[0] - vect_colors[0][0],2))  +  (pow(mixed[1] - vect_colors[0][1],2)) +  (pow(mixed[2] - vect_colors[0][2],2)) );
    /*By using euclidian distance ,I assuming that  the min_distance is first ( 0 . index )  vector length. , I will try the others.*/
      
     int index_min_distance = 0 ;
     for(int k = 1 ; k <=4 ; k++){ /*I check  the first one so I do not need the start the for loop with 0 , I can start with 1.*/
         
        float  distance = 0; /*Everytime after I calculate the distance , I must distance 0 to find the clear result for every vector.*/
        distance = sqrt (  (pow(mixed[0] - vect_colors[k][0],2))  +  (pow(mixed[1] - vect_colors[k][1],2)) +  (pow(mixed[2] - vect_colors[k][2],2)) );
         /*Eger iki tane array da ayni mesafedeyse , ben ilk olani dondurmeyi tercih ettim.Ancak distance <=min_distance yaparak en sonuncuyu da yazdirabilirdim.Ben bunu tercih ettim.*/
         
        if(distance < min_distance){ /*After I calculate the distance , I check if the distance is less than mininumum distance.If the distance is less the minimum distance , my distance will be new mininum distance,*/
            min_distance = distance; /*My distance is new min_distace.*/
            index_min_distance = k; /*And I find the index of new minimum distance.My k value which is used in for loop is the index of vect_length array.*/
        }
     }
 /*After I find the index of minimum distance, I am printing it by using switch case.*/
switch(index_min_distance){
        
      case 0: /*In enum , RED WAS 0 , GREEN WAS 1 , BLUE WAS 2 , YELLOW WAS 3 , ORANGE WAS 4  defined.Do not forget that.I am just printing the names.*/
    printf("RED ");
    break;
       case 1:
    printf("GREEN ");
    break;
       case 2:
    printf("BLUE ");
    break;
       case 3:
    printf("YELLOW ");
    break;
       case 4:
    printf("ORANGE ");
    break;
    default:
    printf("Invalid ");
    break;


   } 
       printf("["); /*And then I am printing the '[' symbol manually.*/
      
       for(int k = 0 ; k <3; k++){
        printf("%.1f",vect_colors[index_min_distance][k]); /*Then I am printing the index of minimum distance vector length which we found above.*/
        if(k !=2){
            printf(", "); /*Do not add comma at the end the array.But I should add before the end of the array.*/
        }
    }
        printf("]\n"); /*Then I am printing the '] ' symbol manually.*/
      
      return index_min_distance;
      
      }






int part3(void){
    char cont; /*Y/N question.Controls the continuity.*/
    int size = 3; /*Size is deternmined as  3 in pdf.*/
    char board[size][size]; /*Then , I will use a 2 dimensiol array to show the board of game.It's size will be [3][3] as you wanted.*/
    int x_row , x_col, o_row , o_col = 0; /*x_row = row of x , x_col = column of x , o_row = row of o and o_col = column of o*/

   for(int row = 0 ; row < size ; row++){ /*I need two  for loop the assign my board array short lines.First for loop for row , and second one is for column.*/
       
    for(int column = 0 ; column < size ; column++){

        board[row][column] ='_'; /*_ symbol will be my board.*/
    }

   }
    print_current_board(board, size); /*I print the current board which is emtpy right now.*/
    
    int status =0; /*Status will determine the course of game.I control this status by sending it to check_status function.*/
    
    while (status !=1){ /*This while loop is gonna run until status is 1 because when the status is 1 , it means the game is finish and no need rung anymore.*/

        if(status != 1){ /*This if is essential because when one of the player wins the game, my while loop is gonna run until at the end of the while.To prevent this, I add 2 'if status != 1 conditions the end the game directly.I did not want to use break.*/

        printf("\nPlayer 1 (X) enter the row and coln :"); /*Getting the location from user.*/
        scanf("%d %d",&x_row , &x_col);

       

        while(x_row <0 || x_row >=3){ /*The only valid row is 0 - 1 or 2.All of the other invalid situations are controlled by while.*/
            printf("Enter a valid size of row!(0-2):");
            scanf("%d",&x_row);

        }

          while(x_col <0 || x_col >=3){ /*Same logic .Invalid situations.*/
            printf("Enter a valid size of col!(0-2):");
            scanf("%d",&x_col);


        }
          while((board[x_row][x_col] =='O')|| (board[x_row][x_col] =='X')){ /*Then checking if that place is full or not because user may try to enter a full location.By means of this while , I prevent this situation.*/
         printf("This location is full!\nEnter a different row and coln :");
         scanf("%d %d",&x_row,&x_col);       /*User should enter a empty location.Fulled locations are not valid.I must check this exceptations.*/

       }

        board[x_row][x_col] ='X'; /*Now , I assinged x to location which user entered.*/
            
        print_current_board(board, size);/*Then I print the current board situation.*/
            
        status = check_status(board , size); /*Then checking if game is over or not.*/

        }

       if(status != 1){ /*Same if condition.If player one wins the game , my while loop is gonna run until at the end of the code.I am preventing this problem.*/

        printf("\nPlayer 2 (O) enter the row and coln :");
        scanf("%d %d",&o_row , &o_col);

      

          while(o_row <0 || o_row >=3){ /*same invalid situations.*/
            printf("Enter a valid size of row!(0-2):");
            scanf("%d",&o_row);

        }

          while(o_col <0 || o_col  >=3){ /*same invalid situations.*/
            printf("Enter a valid size of col!(0-2):");
            scanf("%d",&o_col);

        }
           while( (board[o_row][o_col] =='X') || (board[o_row][o_col] =='O') ){ /*Checking if the place is full or not.If it is full, user enters a different location. */
         printf("This location is full!\nEnter a different row and coln :");
         scanf("%d %d",&o_row,&o_col);       

       }
      
        board[o_row][o_col] ='O'; /*Then I am assingning O the location which user entered.*/
        print_current_board(board, size); /*Then I am  printing the current board situation.*/
        status = check_status(board , size); /*After every move , I check the situation of game if it is over or not.*/

       }
     
    }
    
    printf("\nDo you wanna play again?(Y/N):"); /*When the game is over , I ask the user if he wants to play again or exit.*/
      scanf(" %c",&cont);
      while( (cont !='Y' && cont !='y' && cont !='N' && cont !='n')){
      printf("Enter a valid answer!(Y/N) :");
      scanf(" %c",&cont);

    }
    check_continuity(cont);

    return 0;
}

void print_current_board(char board[3][3] , int size){
    
    /*Now , it is time to display the board whenever user moves.Any time user enters the location, I call this function the show the curren situaton of game.*/
    
    /*In this function , I am just printing the 2D array means of 2 for loop.Nothing more.*/
    
    for(int row = 0 ; row < size ; row++){

     for(int column = 0 ; column < size ; column++){
         printf("%c ",board[row][column]); /*Just printing  the array.*/
     
     }
        printf("\n");
    }
    
}
/*Note:This fumction also controls the draw situation.*/
int check_status(char board[3][3], int size){
    int status =0;
    
    /*In this function , by using the rules of tic tac toe game , I am gonna check if the game is over or not.*/
    
    for(int i = 0 ; i<size ; i++){
        if((board[i][0] ==  board[i][1]) && (board[i][1] == board[i][2])){ /*I am just checking the rows. like-> x x x or o o o .There are three columns that is why I used for loop as many as column number.*/
            /*The horizantal endings.*/
            if(board[i][0] == 'X'){ /*The game is over but who won ?.If the board is x  , player 1 is winner.*/
                printf("Player 1(X) has won the game !");
                status =1; /*Game is over means status = 1*/
                break;
            }
            else if(board[i][0] == 'O'){ /* Else  , means player 2 two won the game.*/
                printf("Player 2(O) has won the game !");
                status =1; /*Then status is 1 , game is over.*/
                break;
            }
            
        }
        
    }
    if(status !=1){ /*This condition is an obligation because there may be two same ending game. like xxx
                                                                                                      oxo
                                                                                                      xox .Like these situation there will be two type of ending.That is why , if the game is end before , I am not checking other ending situations.*/
    for(int j = 0; j< size ; j++){ /*Same logic but this time , I am checking the columns.*/
        
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) { /*I used for loop as many as row number to check the all of the columns (vertical)*/                                                        
                                                                        
            if (board[0][j] == 'X') { /*Yes the game is over , but who won.If the board is X , means player 1 won.*/
                printf("Player 1(X) has won the game !\n");
                status =1; /*Status is 1 means the game is over.*/
                break;  /*no need to check other for loop after game is over.*/
            }
            
            else if (board[0][j] == 'O') {  /*Else if it is O , means player 2 two won the game.*/
                printf("Player 2(O) has won the game !\n");
                status =1; /*Status is 1 means the game is over.*/
                break; /*no need to check other for loop after game is over.*/
                
            }
        }
    }
    }

    if(status !=1){ /*Same logic. If game is end before , I do not need to check the other ending situations.If game is over ,moy code just continiues.*/
    if ((board[0][2] == board [1][1]) && (board[1][1] == board[2][0])){ /*And this is the end condition of crossed sequence.*/
        
        if(board[0][2] =='X'){ /*If above condition is true , means game is over.But who won ? .If the board  is X , means player 1 wins the game.*/
            printf("Player 1(X) has won the game !\n");
            status =1; /*game is over.*/
            
        }
        
        else if(board[0][2] =='O'){ /*If it is O , means player 2 has won the game.*/
            printf("Player 2(O) has won the game !\n");
            status =1; /*game is over.*/
        }
        
    }
    }
    
    if(status !=1){ /*Same logicThe game may be over.Thus,no need to check the other end scenarios.*/
    if((board[0][0] == board[1][1]) && ( board[1][1] == board[2][2])){ /*And this is the other end condition of crossed sequence.*/
        
        if(board[0][0] =='X'){ /*same if conditions. X means player 1 won the game.*/
            printf("Player 1(X) has won the game !\n");
            status =1;
            
        }
    
        
        else if(board[0][0] =='O'){ /*same if conditions. O means player 1 won the game.*/
            printf("Player 2(O) has won the game !\n");
            status =1; /*game is over means status is 1.*/
        }     
    }
    }
  /*After this part , I am gonna control the draw situation.*/
    int flag_draw =1; /*This variable will be my draw flag.*/
    for(int row = 0 ; row < size ; row++){
        for(int column = 0 ; column < size ; column++){
            if( board[row][column] =='_'){ /*After I check the every element of my array , if there is no '_' ,It means my board is full of with X and O. Else . there is still '_' chars and flag_draw =0*/
                flag_draw =0; /*If there is still a '_' char , we do not know the winner yet.There maybe still a winner.Thus , I make my flag draw 0.*/
            }
        }
    }
    /*After this loop if the flag_draw still equals  1 ,it means there is no '_' char. The board is full of  with x and  o .*/
    if(flag_draw == 1 && status == 0){ /*If flag_draw ==1 , means there is no '_' char. The  game is full of with x and o but there is also no winner.If there was, the status of game would be 1 , not  0.Then I understand that that game should be over and it is draw.*/
        printf("The game is draw!");
        status =1;
    }

return status; /*In the and , I return the status of game.*/
}

void check_continuity(char cont){

        if (cont =='Y' || cont == 'y' ){ /*If user enters Y , I call the part3 function which starts the game again.*/
        part3(); /*When the user enters Y , it means the game should start again.Thus ,I am calling my part3 function again.*/
    }
    else {
        printf("\nYou quit the game.See you again!\n"); /*Exit message...*/
    }
}
