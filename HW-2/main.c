//
//  main.c
//  hw_02
//
//  Created by Yusuf Emre Kılıçer on 15.03.2023.
//

#include <stdio.h>
#include <math.h>
#include <ctype.h> /*At part2 , user may enter the lowercase.By means of ctype.h library , I turned lowercase to Uppercase.(toupper function).It is the only thing I used in cytpe.*/
#include "util.h"


int main() {
   printf("\n\n-----PART 1-----\n\n");
    
    int year;
    
    printf("Please enter a year you want to check.\n");
    
    scanf("%d",&year);
  
     
    while(year < 0){ /*A year cannot be negative.I control this situation.*/
        
        printf("Please enter an valid year!:\n"); // If user still enter a negative number,It will give an error.
        
        scanf("%d",&year);
        
         }
 
  check_leap_year(year);  /*I send it to function which I created in util.c */
  
    
    
    
    
    printf("\n\n-----PART 2-----\n\n");
    
    char format; /*Controls the S or I  */
    
    printf("Please choose an output format.(S or I)\n");
    
    printf("NOTE:'S' means scientific output ,'I' means integer output.\n");
    
    scanf(" %c",&format);/*User must choose the format.*/
    
    format = toupper(format); /*If user uses lowecase , I convert it to uppercase by using toupper.*/
    
    while(format != 'S' && format != 'I'){ /*User can choose either S or I. There is no other situation.*/
        
        printf("You entered an invalid output format.Please enter again.(S or I)\n");
        scanf(" %c",&format);/*There is only two format.That is why this loop is gonna run until user enter an valid format.*/
        format = toupper(format); /*If user uses lowecase , I convert it to uppercase by using toupper.*/
    }
    
    int m=0;/* initializing the numbers.*/
    int n =0; /* initializing the numbers.*/
    
    if(format == 'S'){ /*If format is S , m and n values are essential.User is gonna enter it.If user does not , I realize that the format is I.*/
        
        printf("Please enter the m and n value:\n");
        scanf("%d %d",&m,&n);
        
    }

  
        while( n > m ){ /*n cannot be greater than m .That is why I check this condition by using while loop.*/
            
            printf("The value of m  cannot be less than n \n");
            printf("Your m value was-> %d\n",m);
            printf("Please enter the n value again:\n");
            scanf("%d",&n);/*This loop is gonna work until user enter a greater m value than n.*/
            
        }
    
    
    enchanced_calculator(m,n); /*I send it to enchanced calculator function.*/
    
    
  
    
  
    printf("\n\n-----PART 3-----\n\n");
    
    
    float exam_1 , exam_2 , exam_3; /*I must use float because the result of final grade may not be an integer.I cannot use integer while the final grade is not integer.. */
    
    float assign_1 ,assign_2; /*Result of assignment  may be float , that is why my variables also must be float.*/
    printf("Please enter 3 exam grades of student.(Out of 100)\n");
    
    scanf("%f %f %f",&exam_1,&exam_2,&exam_3); /*In sequence ,user enters.*/

     printf("Please enter 2 assignment grades of student.(Out of 100)\n");
    
     scanf("%f %f",&assign_1,&assign_2); /*In sequence ,user enters.*/

       /*Controlling the any exception situation with while.*/
    while( (exam_1 < 0 || exam_1 > 100) || (exam_2 < 0 || exam_2 > 100) || (exam_3 < 0 || exam_3 > 100) || (assign_1< 0 || assign_1 > 100) || (assign_2 < 0 || assign_2> 100) ){
        /*This while loop controls the situation if grades are less than 0 or greater than 100 which is invalid.*/
      
        
       if((exam_1 < 0 || exam_1 > 100)){
          printf("Invalid input.You must enter a number between 0 and 100.Please enter exam_1 again\n");
            scanf("%f",&exam_1);

            
    }
        
       if((exam_2 < 0 || exam_2 > 100)){
      printf("Invalid input.You must enter a number between 0 and 100.Please enter exam_2 again\n");
        scanf("%f",&exam_2);

            
      }
        
    if((exam_3 < 0 || exam_3> 100)){
           printf("Invalid input.You must enter a number between 0 and 100.Please enter exam_3 again\n");
     scanf("%f",&exam_3);

            
       }
        
    if((assign_1 < 0 || assign_1 > 100)){
         printf("Invalid input.You must enter a number between 0 and 100.Please enter assign_1 again\n");
        scanf("%f",&assign_1 );

            
           }
        
       if(assign_2 < 0 || assign_2 > 100){
      printf("Invalid input.You must enter a number between 0 and 100.Please ente rassign_2 again\n");
       scanf("%f",&assign_2);

            
      }
        
        /*And this loop continiues until user enter a valid value.*/
    }

    
    float final_grade = calculate_final_grade(exam_1,exam_2,exam_3,assign_1,assign_2);/*I made a function to calculate the final grade.*/
    
    print_final_grade(final_grade); /* And this function writes the result whether  student failed or didnot fail.*/


    return (0);
}



