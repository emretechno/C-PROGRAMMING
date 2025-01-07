#include <stdio.h>
#include <stdlib.h>
#include <time.h>  /*essential for srand time null */


#define stu_dscunt_rate 12.5/100 /*Student discount rate.*/
#define add_dscunt_rate 1/10 /*Additional discount rate*/
#define VAT_RATE 18/100 /*Vat rate.*/
#define std_nmbr 210104004017 /*Student number which is long int type -_-. I defined these variables to make my code more readable.*/

/*Part 1 functions*/
void part1();
void write_menu_txt(FILE *); /*This function writes the menu on 'menu.txt' file.*/

void read_menu_txt(FILE *); /*This function reads the menu.txt and write it on console.(Not prices, only dishes as expected).*/

void take_orders(FILE *,FILE *); /*This function takes the orders and calculates the total price.*/

double read_price_write_receipt(FILE *, FILE *, int , int); /*This function read the prices from menu.txt and then write the name of food on receipt.txt add enough space automaticly. */

void calculate_the_discount(FILE * , char, double ); /*This function calculates the total discount and print it the payable  price on receipt.txt*/

void read_receipt_txt(FILE *); /*In the end ,I read receipt and then print it on terminal by using getchar.*/


/*Part 2 functions.*/

void start_the_game(); /*It starts the game.*/

void print_rock_paper_scissors(int); /*It prints the choices of user and programmer.*/

void the_winner_game(int , int); /*It prints the result whether user or programmer won.*/
/*NOTE:In this homework , I find the prices by scaning file.I did not find the prices manually.Thus,my code is kind of longer.However I did not know that we can define the prices of meals.*/


int main() {
    part1();
    printf("\n\n\n-------------------------------  PART 2   -------------------------------------------------\n\n");


    start_the_game(); /*Starting the game.*/

    
    return 0;
}
void part1(){
    
    printf("-------------------------------  PART 1  -------------------------------------------------\n\n");
     FILE *menu; /*File opening stuff.*/
     FILE *receipt;
     menu = fopen("menu.txt","w"); /*I open  the txt files.*/
     receipt = fopen("receipt.txt","w"); /*SAME.*/

     if(menu == NULL){ /*Checking if my file opened or not.*/
         printf("File could not opened!");
     }


     if(receipt == NULL){ /*Same.*/
         printf("File could not opened!");
     }
     

     /*I want to write my menu.txt.Thus I called this function.*/
     
     write_menu_txt(menu); /*By means of this function , my menu is ready.*/

     fclose(menu); /*Do not forget to close it.*/
     
     
     
     /*Then I want to print my menu.txt on console.That is why I called this function.*/

     menu = fopen("menu.txt","r"); /*Now, The mod of file must be 'r' because I am gonna read it in read_menu_txt function.*/

     read_menu_txt(menu); /*I send my file pointer.I opened my menu.txt file before I send to my function.*/

     fclose(menu); /*Do not forget to close the file.*/

     
     
     /*In this part , I am setting up to current time and date before I take the orders.As u suggested the strftime , it is an obligation to use string.It is the rule of strftime.*/

    time_t current_time = time(NULL);/*declare the current time first to null.Then I am gonna scan it from my computer*/
    struct tm *time_info; /*This is the rule of strftime function.*/
    char time_string[20]; /*array is obligation for strftime.*/
    time(&current_time);
    time_info = localtime(&current_time); /*I am scanning from my computer to time and date.*/
    strftime(time_string, sizeof(time_string), "%d.%m.%Y/%H:%M:%S", time_info);/*I research it from geeks2geek.This is my source :
                                                                                
    https://www.geeksforgeeks.org/strftime-function-in-c/     */
     
     /*Then I am printing the current time and date on receipt.txt */
    
           fprintf(receipt,"\n\n%ld        %s\n\n",std_nmbr,time_string);
           fprintf(receipt,"---------------------------------------\n\n");
           fprintf(receipt,"PRODUCT                   PRICE(TL)\n\n");
           fprintf(receipt,"---------------------------------------\n\n");
     
     



     
     /*Now , I am gonna take the orders and I am gonna write these orders on receipt.txt file in this function.*/
         
     take_orders (menu,receipt);  /*NOTE :read_price_write_receipt function and calculate_the_discount function will be used in take_orders function. ! */
   
     fclose(receipt); /*I closed 'w' mode receipt file.*/

     read_receipt_txt(receipt);/*Then I want to print the prepared receipt on console.The 'r' mode of file  will be opened in the function.*/

     

}
void write_menu_txt(FILE *menu){
    /*In this part , I am just writing the menu by using fprintf.Nothing else.*/
    /*Not: I could not use Turkish letters because of C compiler , they counted twice even though they are just one letter.It is because I count letters of every meals , I should have used English characters.Then , by means of these counted letters, I can add enough space automatically.
     FOR EXAMPLE :If you write Lahmacunnnnn instead of Lahmacun , my output of receipt will be stragiht and balanced.    */
     

   
    fprintf(menu,"------- THE MENU-----\n");
    fprintf(menu,"PRODUCT:    PRICE(TL)\n");
    fprintf(menu,"1->Kebap        %.2lf\n",75.99); /*Line 3*/
    fprintf(menu,"2->Lahmacun     %.2lf\n",21.50); /*Line 4*/
    fprintf(menu,"3->Pide         %.2lf\n",40.00);
    fprintf(menu,"4->Doner        %.2lf\n",55.60);
    fprintf(menu,"5->Kola         %.2lf\n",15.00);
    fprintf(menu,"6->Su            %.2lf\n",5.00);
    fprintf(menu,"7->Kunefe       %.2lf\n",60.00);
    fprintf(menu,"8->Sutlac       %.2lf\n",32.50);
    fprintf(menu,"9->Manti        %.2lf\n",58.58);
    fprintf(menu,"10->Hamburger   %.2lf\n",34.34);
    fprintf(menu,"11->Kavurma     %.2lf\n",58.34);
    fprintf(menu,"12->Guvec      %.2lf\n\n@",120.58);

 
}
void read_menu_txt(FILE *menu){
    
/*In this function , I am reading the menu and print the output on console.*/
    
    char c;
    while((c = fgetc(menu)) !='@'){ /*I did not want to use EOF because there may be some problems with EOF on UBUNTU.That is why I add '@' char at the end of the file and I use '@'  char as EOF. */
     
    
       
        if(c ==' '){ /*In this part , The prices on the menu should not seen on console.That is why when my char comes to space , means I read the name of meal. */

            while (c !='\n') /*Then ,until my c reaches the new line , I do not write it on the console because if I do , the prices are also gonna seen in console which I do not want.*/
            {

                c =fgetc(menu); /*My loop runs until my char reaches to newline char ('\n').*/
            }
            

        }

        printf("%c",c); /*I write the names of meals, not the prices of meals by means of above algorithm.*/
    }
 
}
 /*BEN EGER KULLANICI URUN SECIM ESNASINDA 0 SECERSE SIPARISI BITIRDIM.EGER SERVIS SAYISINI 0 GIRERSE DE BITIRDIM.*/
void take_orders(FILE *menu, FILE *receipt){
   
    int product;
    
    double result=0;
    
    int quantity=-1; /*I just assingned -1 to quantity to make my while loop  more accurately .Then I take it quantity from user as u guessed.I initiliaze it shortly.*/
    double total_prc =0; /*It will be my discountless total price.*/
    
    /*User quits the order when he presses the second zero , not first zero . That is why arranged the second zero as a quiting the game.*/
    
      while(product!=0){ /*Until user enters quantity 0 , my program will prompt user to enter the meal.*/

        printf("Please choose a product (1-12).(To exit ,enter 0)\n"); /*Only between 1-12.*/
        scanf("%d",&product);
          
        while(product <0 || product >12){ /*Valid interval is between 1 and 12.*/
            
            printf("Please enter a valid meal!.(1-12)\n");
            scanf("%d",&product);
        }
          
          
          if(product !=0){
              
              printf("How many servings do you want?\n"); /*Taking from user to amount of serving number.*/
              scanf("%d",&quantity);
          }
          
          else {
              printf("You end the ordering!\n");
              quantity =0; /*I just assigned random number if my product is zero because I know that user wants to quit he if enters 0.Thus,no matter I assigned the quantity.*/
          }
          
           while(quantity <0){
              
              printf("Serving number cannot be zero or negative!.Enter a valid number.\n");
              scanf("%d",&quantity);
          }
          
          if(quantity ==0){ /*If user enters the service 0  , I make also product zero to finish the loop.*/
              product =0;
          }

          menu = fopen("menu.txt","r"); /*I open my menu.txt read mode because I am gonna read it in this part.*/
          double result;
          
          if(product !=0){  /*If quantity is 0 , it means that user wants to quit,He does not want to write it on receipt.Thats why I do not print it on receipt.txt.*/
              
              result = read_price_write_receipt(menu , receipt , product+1 , quantity); /*In this part , I am finding the price by using read_price function.In this function , I read the price from menu.txt and write the name of meal.Then I return result price of every meal seperately.*/
              
              total_prc  = total_prc +result; /*I am adding the all of the  seperated result to calculate the total price.*/

              
          }
         
          

    
    }


     
     /*Checking if customer is student or not and then I am gonna calcualate the total discount by using total price above.*/
     
     char customer_type;
     
     printf("Are you Student ?(Y/N) \n");
     scanf(" %c",&customer_type);
    

     
     while( (customer_type !='Y' && customer_type !='y' ) &&  ( customer_type !='N' &&  customer_type !='n')) { /*Only valid answer is either yes or no.There is no other option.I provide the rule by using while condition.*/
         printf("Please enter a valid answer!(Y/N)\n");
         scanf(" %c",&customer_type);

     }
     
     
     /*After I determined the user's type (STUDENT OR NOT ) , I am gonna calculate the all discounts and print them on receipt.txt.*/
    /*My total price was ready right now.Now It is time to use it.*/
    
    calculate_the_discount(receipt,customer_type,total_prc); /*After I find the total discount , I write the payable price on receipt.txt in this function.*/


    
}
double read_price_write_receipt(FILE *menu , FILE *receipt ,int option  , int quantity){
    
   
    double result = 0.0;
    int length_meal =0; /*Count the letters of meals.*/
    char c;
    int count_line=0; /*I am gonna count the line by using getchar.*/
     double price = 0.0; /*Initialize the price first.*/
     
      fprintf(receipt,"%2d* ",quantity); /*In this part , I am printing the service number on receipt.txt file*/
 
         while((c = fgetc(menu)) !='@'){/*I did not want to use EOF because there may be some problems on UBUNTU.That is why I add '@' char at the end of the file and I use '@'  char as EOF. */

       if(c == '\n'){
           count_line++; /*If c is '\n' , means it is a new line.Then I increase count_line one.*/
          }
             if(count_line ==option){ /*when option(case) is equal to count line , It means it is the exact line to scan the price form menu.txt*/
             
             if( (c >=65 && c<=90)  ||( c>=97 && c<=122)){ /*These are the ASCII VALUES of letters.When my c is equal to one of the letter , I read it until the space.This process is clearly writes the name of meal.*/
             
              while(c !=' '){
               fprintf(receipt,"%c",c); /*In this part , I am writing the name of meal on receipt.txt.*/
                  length_meal++; /*I am counting the letters of meals.Then I am gonna use it below.*/
                 
                 
               c = fgetc(menu); /*Until my char reaches the space , I am assigning c to fgetc(menu)*/
               
              }
              }

                fscanf(menu,"%lf",&price); /*Then scanning the price on the spesific line.I find the exact line by counting the lines.*/
                        
              }
      }
    
    
    result = quantity*price;
    fprintf(receipt," %*.2lf\n\n",30-length_meal,result); /*MY total  space is  30.Then I am substracting the length of meal to create a straight receipt.*/

    return result; /*Then return the price of product.*/

    
}
void calculate_the_discount(FILE *receipt , char type,double total_prc){
    double student_discount =0; /*amount of student discount */
    double additional_discount =0; /*amount of additional discount.*/

         fprintf(receipt,"TOTAL %29.2lf\n\n",total_prc); /*Printing the first total price before discounted.*/
           

           if(type =='Y' || type == 'y' ){ /*If type is Y or y  , means if user is student , I calculate the studen discount and write it to receipt.*/

            student_discount = total_prc * stu_dscunt_rate; /*Multiply total price to student discount rate as I defined.*/
            fprintf(receipt,"Student Discount:%18.2lf\n\n",(-student_discount)); /*And print it to receipt.txt*/

           }

           if(total_prc >= 150){ /*If total prices is greater than 150 , then Calculate the amount of discount and print it o receipt.txt*/

            additional_discount = total_prc * add_dscunt_rate; /*Calculating the amount of discount.*/
            fprintf(receipt,"Additional Discount:%15.2lf\n\n",-(additional_discount)); /*These %15 or other values are arranged by counting the letters and adding enough space.*/


           } /*Note , If the above if condition are not correct , then additinal and student discount is 0 as expected.If  they are true , then amount of discounts are calculated.*/

            fprintf(receipt,"\n---------------------------------------\n\n");
            double total_discount = student_discount+ additional_discount; /*calculate the total discount until this part.*/
            double discounted_price = (total_prc) - (total_discount); /*Now I am calculating the new prices which I find by substiting the total discount from total price.*/

            fprintf(receipt,"Price :%28.2lf\n\n",discounted_price ); /*Indirimli hali*/
            double total_vat = discounted_price * VAT_RATE; /*now I am calculating amount of wat.*/
            fprintf(receipt,"Price + VAT:%23.2lf\n@",(discounted_price)+(total_vat)); /*amounts of spaces are arranged by counting the letters.Instead of using space , I used %28lf or other values.*/


}

void read_receipt_txt(FILE *receipt){
    /*Same reading process.Logic is the same as reading menu_txt function.,*/
    receipt = fopen("receipt.txt","r");
       char c;

  while((c = fgetc(receipt)) !='@'){ /*I did not want to use EOF because there may be some problems on UBUNTU.That is why I add '@' char at the end of the file and I use '@'  char as EOF. */
      
        printf("%c",c);
    }
    fclose(receipt);
}


void start_the_game(){

    char cont ='\0'; /*initializing the char type first.Then I am gonna take it from user in while loop. */
    int option;
    int me;
    while( cont !='N' &&  cont !='n' ){ /*My loop should run until user enters N.*/
        printf("Please make a choice!\n");
        printf("1: Stone, 2: Paper, 3: Scissors\n");

        scanf("%d",&option); /*Taking user's choice.*/
        while(option !=1 && option !=2 && option !=3){ /*there are only 3 option (1,2 or 3).If user enters invalid input ,I send an error and take it again.*/
            printf("Please make a valid choice.\n");
            scanf("%d",&option);
        }
        printf("You chose ");
        print_rock_paper_scissors(option); /*I print the user's choice*/
        
        srand(time(NULL));
        me = rand() % 3 + 1; /*me means programmer.It should be random every roll that is why I used srand time null. */
        printf("I chose ");
        print_rock_paper_scissors(me); /*Then I print the programmer'schoice.*/
        
        
        the_winner_game(option,me); /*I am finding the winner in this function.*/
        printf("Do you wanna continue?(Y/N)\n"); /*Ask your whether he wanna continue or not.*/
        scanf(" %c",&cont);
        while(( cont !='Y' && cont !='y')  && (  cont !='N' &&  cont !='n')){
            printf("Enter a valid choice. (Y/N)\n");
            scanf(" %c",&cont);
           
        }
    }
    /*When to loop is over , means user entred N and the game is also over.*/
    printf("You quit the game...\n");
        
        
}

void print_rock_paper_scissors(int choice){
   /*By using switch case , I print the result of choices.1 is stone , 2 is paper and 3 is scissors.*/
    
    switch(choice){
        case 1:
            printf("Stone.");
            break;
        case 2:
            printf("Paper.");
            break;
        case 3:
            printf("Scissors.");
            break;
        default:
            printf("Invalid choice.");
            break;
         
    }
    
}

void the_winner_game(int user  , int me){

    /*These are rules of rock paper scissors game.I just check the every situtation and print the winner.*/
    if(user == me){
        printf("It is a tie!\n");
    }



    else if(user ==1 && me ==2){ /*Paper wins against rock.*/
        printf("I Won!\n");  /*Means programmer won.*/
    }

     else  if(user ==2 && me ==1){ /*vice verse*/
        printf("You Won!\n");  /*Means user won..*/
    }




    else  if(user ==3 && me ==1){ /*stone  wins against scissors*/
        printf("I Won!\n");
    }

    else if(user ==1 && me ==3){ /*vice verse */
        printf("You Won!\n");
    }




   else  if(user ==2 && me ==3){ /*scissors wins against paper.*/
        printf("I Won!\n");
    }
   
   else if(user ==3 && me ==2 ){ /*vice verse*/
        printf("You Won!\n");
    }
    
    
}
