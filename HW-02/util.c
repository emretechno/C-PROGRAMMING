#include <stdio.h>
#include "util.h"
#include <math.h>

#include <ctype.h> /*At part S or I display, user may enter the lowercase.By means of this library I turned lowercase into uppercase.(toupper function).It is the only thing I used in cytpe.*/

void check_leap_year(int year){ /*Part 1 function.*/
    
   
    if( (year % 400 ==0 && year % 4000 !=0 )  || (year % 4 ==0 && year % 100 != 0) ){ /*This  is the rule of leap year.I learn it from wikipedia.If year is divisible by 400 and not divisible by 4000  or divisible by 4 and not divisible by 100, this is a leap year.For example 4000 is not a leap year.Any year divisible by 4000 will not be a leap year.*/
        /*My source is : https://en.wikipedia.org/wiki/Leap_year*/
        
            printf("\n%d is a leap year\n",year);
        
    }
    
    else { /*Else ,it is not a leap year.*/
        
        printf("\n%d is not a leap year.\n",year);
        
    }
}



void enchanced_calculator(int m , int n){
    
    char format; /*User is gonna enter letter  so my type must be char.*/
    char operand; /*User is gonna enter char.*/
    double num1,num2 =0; /*I should initialize the numbers before get from the user.My type should be double because the result may not be integer in scientific result.*/
    
    printf("please enter the operator\n");
    printf("(+ , - , / , * , %% , ! ,^):");
    scanf(" %c",&operand); /*One space is obligation.*/
    
    while( (operand != '+') && (operand != '-') && (operand != '/') && (operand != '*') && (operand != '%') && (operand != '!') && (operand != '^') ){ /*User must enter just these operators.If he enters another operand except these , my while loop is gonna run until user enters a valid operation.*/
        
        printf("You entered an invalid operator.Please enter again \n");
        printf("(+ , - , / , * , %% , ! ,^,):"); /*User must be enter a valid operator.*/
        scanf(" %c",&operand); /*Getting from user again.*/
        
    }
    
    if(operand != '!'){ /*If user does not choose the factorial , he is gonna enter two numbers.*/
        
        printf("Please enter the number 1:\n");
        scanf("%lf",&num1);
        printf("Please enter the number 2:\n");
        scanf("%lf",&num2);
        
    }
    
    else { /* This else is for factorial situation.User should  enter just one number in factorial calculation.There is no second number.*/
        
        printf("Please enter the number you wanna calculate the factorial:\n");
        scanf("%lf",&num1);
        
        while(num1 < 0){ /*There is no negative factorial.User must be enter positive number.*/
            
            printf("ERROR! There is no negative factorial number.\n");
            printf("Enter an valid value:\n");
            scanf("%lf",&num1);
        }
    }
    
    if(m == 0 && n == 0){ /*If m and n equals zero,then I understood that user did not choose the S and ' m and n 'did not change.*/
        
        format = 'I';
    }

    else { /*It means scientific format.I must take double otherwise the result may be integer.*/
        
        format = 'S';
    }
    
  
    calculate_the_result(format,operand,num1,num2,m,n); /*It is gonna calculate the result.*/

}
    
void calculate_the_result (char format , char operand, double num1 , double num2,int m , int n){
    
       double result = 0; /*I initialize the result.*/
    
    /*I did not want to write 2 switch case that is why I find the solution this way.*/
    
    switch(operand) { /*Switch case algorithm.*/
            
            /*In  this case , If format is I , I turned every double number into integer.(TYPE CASTING).If format is S I did not change the type of double.*/
            /*In every case , my logic is same.I turned my double number to integer if format is I.Otherwise , I didnot change.*/
            
        case '+' :
            
            if(format== 'I'){ /*Summing process.*/
                
                printf("%d + %d = %d\n",(int)num1,(int)num2,(int)num1+ (int) num2); /*Type casting.*/
            }
            
            
            else {
                /*Format = S*/
                printf("%lf + %lf = ",num1,num2);
                result = num1+num2; /*Result.*/
            }
            
            break;
            
        case '-' :
            
            if(format == 'I'){ /*substracting process.*/
                
                printf("%d - %d = %d\n",(int)num1,(int)num2,(int)num1-(int)num2); /*Type casting.*/
            }
            
            
            else { /*Format = S*/
                printf("%lf - %lf = ",num1,num2);
                result = num1-num2; /*Result.*/
            }
            
            break;
            
        case '/' :
            if(format == 'I'){
                
                if(num2 == 0){ /*Undefinite problem.I just checked it.*/
                    
                    printf("ERROR!!A number cannot division by 0.");
                }
                
                else {
                    
                    printf("%d / %d = %d\n",(int)num1,(int)num2,(int)num1/(int)num2); /*Type casting.*/
                }
            }
            
            
            else { /*Format = S*/
                if(num2 == 0){ /*Undefinite problem.I just checked it.*/
                    
                    printf("ERROR!!A number cannot division by 0.");
                }
                else {
                    printf("%lf / %lf = ",num1,num2);
                    result = num1/num2;
                }
            }
            
            break;
            
        case '*' :
            
            if(format == 'I'){
                
                printf("%d * %d = %d\n",(int)num1,(int)num2,(int)num1*(int)num2); /*Type casting.*/
            }
            
            else { /*Format = S*/
                printf("%lf * %lf = ",num1,num2);
                result = num1*num2;
            }
            
            break;
            
        case '%' :
            
            if(format == 'I'){
                
                if(num2 == 0){ /*Undefinite problem.*/
                    
                    printf("ERROR!!A number  cannot division by 0.");
                }
                
                else {
                    
                    printf("%d %% %d = %d\n",(int)num1,(int)num2,(int)num1 % (int)num2); /*Type casting.*/
                }
            }
            
            
            else { /*Format = S*/
                if(num2 == 0){ /*Undefinite problem.*/
                    
                    printf("ERROR!!A number  cannot division by 0.");
                }
                else{
                    
                    printf("%lf %% %lf =",num1,num2);
                    result = find_mod(num1,num2);
                    
                }
            }
            
            break;
            
        case '!' :
            
            if(format == 'I'){ /*I sent number to my function which is find_factorial.*/
                
                printf("%d! = %d\n",(int)num1, find_factorial(num1)); /*Type casting.*/
            }
            
            else { /*Format = S*/
                printf("%.0lf! = ",num1);
                result = find_factorial((int)num1); /*Result.*/
                
            }
            
            break;
            
        case '^' :
            if(format == 'I'){ /*I sent number to my exponential function which is find_exponential.*/
                
                printf("%d^%d = %d\n",(int)num1,(int)num2,find_exponential(num1,num2)); /*Type casting.*/
            }
            
            else { /*Format = S*/
                printf("%.2lf^%.2lf =",num1,num2);
                result = pow(num1,num2);
            }
            
            break;
            
        default :
            printf("INVALID OPERATION.");
    }
    
    if(format == 'S'){
        
        int digit_result = find_digit((long long int) result); /*Firstly ,I must find the number of digit of result to check whether m > number of digit of result.*/

        if(m < digit_result){ /*I checked the invalid situation.*/
            
            printf(" ERROR!! m cannot be less than number of digit of result.Invalid m value!..\n");
        }
        
        else {

            print_scientific_result(m,n,digit_result,result); /*If my format is not Integer ,I  send it to scientific print function to write scientific.*/
    }
     
          
    }
    
    
    }

void print_scientific_result(int m , int n , int digit_result ,long double result){
    
    
  
    
    int error =0; /*It will control the error message in my algorithm.*/
    if( (long long int) result != 0){ /*If my result is zero , I write e over %d differen from is my result is not zero.That's why I used if else.*/
        

    result = result * find_exponential(10,9-digit_result); /*After finding the number of digits of the result , I  multiply it with 10 over 9- number of digits) to make it result  9 digits to my result digits. So the result   9 digits.Btw the double max is giving error if I make my result more than 9 digits..*/
        
        
        if( (long long int) result !=result){ /*After I made my result 9  digits and my result is not still integer, I understand that I could not find the all digits of result.Thus, there will be a loss of digit in scientific display.For example my result is 12345.67 and  m is 5 , so I checked this situation and my algortihm will give an warning such as following:*/
            error =1;
        }

   
    
        int reverse = make_reverse((long long int) result); /*I find  the reverse of my result.For example my result was 1234 , my reversed is 4321.Then I find % 10 of reversed so I can reach the 1234 again.*/
        
        int digit_reverse=find_digit(reverse); /*Then I find the number of digit of reverse number.*/
     
        if(digit_reverse >=m){ /*Then I will check the digit_reverse sitatuons which depend on m.*/
            /*If my reversed number's number of digit greater than m  , then there will be no need to add zero.This if controls this situation.*/
            
            for(int i = 1; i<=m-n ; i++){ /*I firstly write the as many as m-n times.*/
                
                printf("%d",reverse %10); /*I finding the every number of digit of reversed number.*/
                
                reverse = reverse /10;
                
            }
            printf("."); /*after my dot.*/
            
            for(int i = 1; i<=n ; i++){ /*I am continuning the writing the other digits of my reversed number.*/
                printf("%d",reverse %10);
                reverse = reverse /10;
                
            }
            printf("e%d",n-(m-digit_result)); /*Then I am writing the e over %d part.*/
        }
        
        else if (digit_reverse<m){ /*But if my digit of reversed number less than m , I must add zeros.*/
            
            if(digit_reverse<m-n){ /*In this if condition , there are two situations: digit_reverse may be etiher greater than m-n or less than m-n.I am checking the first situation right now.*/
            
                while(reverse!=0){ /*I know that my reversed number's number of digit is less than m-n, So I firsly write my number.*/
                    printf("%d",reverse %10); /*Writing the every digit of reversed number.*/
                    reverse = reverse /10;
                    
                }
                for(int j = digit_reverse+1 ; j<=m-n ; j++){
                    printf("%d",0); /*Then I am adding the essential  zeros.*/
                }
                printf("."); /*After I wrote the dot,*/
                for(int  i = 1; i<=n ; i++){ /*I am adding zero n times because I know that my number was finished before dot(my digit_reverse was les than m-n.It means I finished my all digits.*/
                    
                    printf("%d",0);
                }
                printf("e%d",n-(m-digit_result)); /*Now Im writing the e over %d part.Same as above one.*/
            }
            
            else { /*This else controls the if digit_reverse>=m-n stiatuion.*/
                
                int control_dot =0; /*It controls the time when I am gonna add dot.*/
                
                while(reverse !=0){
                    printf("%d",reverse %10); /*I am writing the every digit of my reverse number.*/
                    reverse = reverse /10;
                    control_dot++; /*Every time I write the digit , I also increase the control_dot one to find the true place to add a dot.*/
                    if(control_dot == m-n){ /*it is time to add dot because it equals to m-n.*/
                        printf(".");
                    }
                }
                
                for(int j = control_dot+1 ; j<=m; j++){ /*After the controldot +1 , I add zeros because I need it.*/
                    printf("%d",0);
                }
                printf("e%d",n-(m-digit_result)); /*Then writing the total e over %d part.*/
                
            }
        }
           
        check_error(error); /*After I wrote the result , I check the error if it exists.*/
        
        printf("\n");
        
        }
    
    
            
                                    /*When The integer type of result is zero , This part is gonna run because 0.05323 result are kind of different from others!!!!!!*/
                
    
    else { /*I checked the like 0.0004455 results.It is kind of different from other result which are not integer zero.*/
     
        result = result * find_exponential(10,9-digit_result);  /*After finding the number of digits of the result , I  multiply it with 10 over (9- number of digits) to make it result  9 digits. So the result  becomes 9 digits..I chose nine because I literally want to check as much as possible digit after decimal point.I chose 9 to find the more truth result.*/
        int digit_multiplied_result = find_digit(result);
        
        if((int)result != result){ /*After I made my result m digits and my result is not still integer, I understand that I could not find the all digits of result.Thus, there will be a loss of digit in scientific display.For example my result is 12345.67 and  m is 5 , so I chechked this situation and my algortihm will give an warning such as following:*/
            
            error=1;
        }
        
            int reverse = make_reverse((long long int) result);
        
            int digit_reverse=find_digit(reverse);
        int number_of_zero_at_first = 8-digit_multiplied_result; /*I must find the number of zero of the  after decimal point to substract it on e%d part.You can check that I substract the number_of_zero_at_first.*/

        if(digit_reverse >=m-n){
            
            int control_dot =0; /*It controls the time when I am gonna add dot.*/
            while(reverse !=0){
                printf("%d",reverse %10); /*I am writing the every digit of my reverse number.*/
                reverse = reverse /10;
                control_dot++; /*Every time I write the digit , I also increase the control_dot one to find the true place to add a dot.*/
                if(control_dot == m-n){ /*It is time to add dot.*/
                    
                    printf(".");
                }
            }
            for(int i = control_dot+1 ; i<=m; i++){ /*After the controldot +1 , I add zeros how many I need.*/
                printf("%d",0);
            }
            printf("e%d",n-(m)-number_of_zero_at_first); /*Then writing the total e over %d part.*/
        }
        else { /*This else controls whether digit_reverse <m-n situation.*/
            while(reverse!=0){
                printf("%d",reverse %10); /*If my digit_reverse less than m-n ,  I can write the all of my reversed number's digit.I write it.*/
                reverse = reverse /10;
                
            }
            for(int j = digit_reverse+1 ; j<=m-n ; j++){ /*Then I am compeleting the missing zeros.*/
                printf("%d",0);
            }
            printf("."); /*After my dot , I am adding n times zero.*/
            for(int  i = 1; i<=n ; i++){
                printf("%d",0);
            }
            printf("e%d",n-(m)-number_of_zero_at_first); /*Then writing the total e over %d part.*/
        }

      
        
        check_error(error); /*After I wrote the result , I check the error if it exists.*/

        
        printf("\n");
    }
}



int find_factorial(int num1){
    
    int fact = 1; /*factorial.*/
    
    for(int i = 2; i <= num1 ; i++){ /*I starts with 2 to work my code faster.*/
        
        fact = fact *i; /*Multiplying the number by i.*/
    }
    
    return (fact); /*Return the result which is factorial of num1.*/
}

    
int find_exponential(int num1,int  num2){
    
    long long int pow =1;/*power*/
    
    for(int i =1 ; i <= num2; i++){
        pow = pow * num1; /*I am finding the exponential of num1,num2.*/
        
    }
    return (pow); /*I return the result.*/
}


int find_digit(int num){
   
    int digit_num = 0; /*It will be the number of digit of num.*/
    
    if(num == 0){
        
        digit_num =1; /* 0 is also one digit.Do not forget this situation.*/
    }
    
    else {
        
        while(num != 0){
            
            num = num /10; /*Dividing number to 10 to find the number of every digit. */
            digit_num++;
        }
    }
    
    return (digit_num); /*I return the number of digit of num.*/
}



double find_mod(double num1 , double num2){ /*It finds the mod.*/
    double rem;
    
    if(num1 < num2){ /*If num1 less than num2 , The mod is 0.*/
        rem =0;
        
    }
    
    else {
        
        while(num1 >= num2){ /*Else, I substract num2  from num1 and find the mod. */
            num1 = num1 - num2;
        }
        rem = num1; /*This is the mod .*/
        
    }
    
    return rem; /*Remainder is the mod actually.*/
}


void check_error(int error){
    
    
    if(error ==1){ /*If error is 1 , I print the error message.*/
        
        printf("\nWARNING!!!!The m value you entered is less than total number of digit of result.That's why there will be a loss of digit in scientific display! "); /*If I could not my result to integer, I understand that there is at least one number which I couldnot turned.These numbers create a loss of digit and this reason is written because of that problem.*/
        
        
        printf("\nNote:The needless amount of zero number after decimal (which is a feature of double numbers) can be understood as a loss of digit.If this warning's reason is this exception,please DO NOT CONSIDER IT.\n"); /*The reason of this warning is cause of feature of double numbers.In double numbers , there are approximately 10 zeros after decimal point.Thus , sometimes my algorithm may detect these zeros as a loss of digit.I just wanted to write a not because of this problem. */
        
    }
    
}

int make_reverse(long long int result ){ /*This function makes the result reversed.*/
    
    int reminder; /*That will be my remainder.I couldnot have written my name as a remainder because there is a ready function in C that is why I used reminder.*/
    
     int reverse=0; /*I will find the reverse of my result to use all of the digit later.Thus,its name will be reverse.*/
    
    while((long long int) result !=0) {
        
        reminder = (long long int) result % 10; /*Every time I find the remainder of result.*/
        
        reverse = reverse * 10 + reminder; /*I sum it with reverse and then multiply it by 10. */
        result = result /10; /*Then I divide my result by 10 to find the all dig*/
        
    }
    return reverse; /*Then I return the reversed number.*/
}



float calculate_final_grade(float exam_1 , float exam_2 , float exam_3 , float assign_1 , float assign_2){/*Variables must be float or double.I chose float.*/
    
    float final_grade = ( (((exam_1+exam_2+exam_3)/3)*0.6) + (((assign_1+assign_2)/2)*0.4));/*This formule is given in pdf.I just placed the variables.*/
    return final_grade; /* I return the result.*/
    
}




void print_final_grade(float final_grade) {  /*This function writes the result.*/
    
    if(final_grade >= 60){ /*If grade is bigger than 60 , student is succesfull.*/
        
        printf("Final grade is %.2f\n",final_grade);
        printf("You passed.\n"); /* I print the result message.*/
        
    }
    
    else { /*Else , student is failed.*/
        
        printf("Your final grade is %.2f\n",final_grade);
        printf("You failed.\n"); /* I print the result message.*/
        
    }
}
