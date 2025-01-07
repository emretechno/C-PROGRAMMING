#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A second fractional number: 13/11 */
    int num2 =13, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
      
    
    printf("---------------------------------------------\n");
    printf("Welcome to my program.Yusuf Emre Kilicer...\n");
    printf("This time , you are gonna enter your own fractional numbers!\n");
    
    
    printf("Please enter the first number's numerator:\n");
    scanf("%d",&num1);
    printf("Please enter the first number's denominator:\n");
    scanf("%d",&den1);
    
    printf("Please enter the second number's numerator:\n");
    scanf("%d",&num2);
    printf("Please enter the second number's denominator:\n");
    scanf("%d",&den2);
        
    /*In this loop , I am checking the undefined numbers.Denominators cannot be 0.Thus,I am preventing this case.If user continious to enter 0 , he cannot quit the loop until he enters a valid number.*/
    while(den1 ==0 || den2 ==0){
        if(den1==0){
            printf("The first number's denominator can not be 0.Please enter a different number!\n");
            scanf("%d",&den1);
        }
        if(den2==0){
            printf("The second  number's denominator can not be 0.Please enter a different number!\n");
            scanf("%d",&den2);
        }
    }
    /*The user should see his own fractional numbers.*/
    printf("Your first fractional number is:\n");
    fraction_print(num1,den1);
    printf("Your second fractional number is:\n");
    fraction_print(num2,den2);
    /*I showed his fractional numbers and my algorithm is starting:*/

    printf("\nThe result of addition is :\n");
    fraction_add(num1,den1,num2,den2,&num3,&den3);
    fraction_print(num3,den3);
    printf("\n");
    
    
    printf("The result of substraction is :\n");
    fraction_sub(num1,den1,num2,den2,&num3,&den3);
    fraction_print(num3,den3);
    printf("\n");
    
    printf("The result of multiplication is :\n");
    fraction_mul(num1,den1,num2,den2,&num3,&den3);
    fraction_print(num3,den3);
    printf("\n");

    
    printf("The result of division is :\n");
    fraction_div(num1,den1,num2,den2,&num3,&den3);
    fraction_print(num3,den3);
    printf("\n");

    return(0);
}
