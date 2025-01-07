#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    
    if(numerator == 0 && denominator !=0){
        printf("%d//%d=0\n",numerator,denominator);
      /*if numerator is 0 , our fractinoal number is zero.(Even though I checked before in case of being denominator 0 , I still check it to escape from any wrong answer.)
        NOTE :I did this just because it is easy to read as a human being. */
    }
 
    else {
        printf("%d//%d\n", numerator,denominator);
    }      //writing the other results.
    
}

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 =n1*d2 + n2*d1; /*I am applying the rule of adding.*/
    *d3 = d1*d2;
    
    fraction_simplify(n3, d3); /*Everytime I find a result, I send them simplify function.*/
}

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 =(n1*d2 ) - (n2*d1); /*I am appliying the rule of sub.*/
    *d3 = d1*d2;
    
    fraction_simplify(n3, d3);
}

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * n2; //I am applying the rule of multiply
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
}

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    if(n2 ==0 ){
        *n3 = n1*d2;
        *d3 = d1*n2;
        printf("UNDEFINED!:\n");
        /*TIP:If our second number's numerator is 0 , the result of denominator will be 0.We know that when denominator is 0 , it is an undefined number.*/

    }
    else {
        *n3 = n1*d2; //I am applying the rule of division
        *d3 = d1*n2;
    }

    fraction_simplify(n3, d3);
}

void fraction_simplify(int * n, int * d) {
    
    char flag ='N'; /*The flag is (N) normal right now.I am gonna change the situations by chancing the flag.*/
    
    
    if((*n>0 &&*d<0)){ /*If this condition is true,our number is negative.*/
        *d =-*d;
        flag ='M'; /*The answer of this fracitonal number is minus.Flag is 'M'(MINUS) right now.I am gonna make it positive by multiply it with '-'.After I made it positive, I am gonna find the Greatest Common Divisor(gcd).Then , I am gonna write the result by using '-' again.*/
    }
    
   if((*n<0 && *d>0)){ /*If this condition is true,our number is negative.*/
        *n = -*n;
        flag ='M'; /*The answer of this fracitonal number is minus.Flag is 'M'(MINUS)right now.It is the same logical process with the above.I also use 'M' because same process are also valid for this situation.*/
    }
    
    if(*n<0 && *d<0){ /*If this condition is true,our number is positive.*/
    *n=-*n;
    *d =-*d;
    char flag ='N'; /*in this case ,I know that two minus make positive.That's why after I made the numerator and denominator positive , I assign flag to 'N'.(NORMAL).*/
        
    }
  
    
    int gcd=1; //Firstly,I assigned the greatest common divison 1 , then I will find the GCD.

    for(int i = 2 ;(i<=*n && i<=*d) ; i++){
        if(*n %i == 0 && *d%i ==0){
            gcd =i; /*I am calculating the gcd right now.*/
        }
    }
    /*After I found the GCD , I am gonna simplify them by using their flag which I assigned above.I did that because even our number was negative first ,I made them positive before I start to find the gcd.*/
    if(flag =='N'){
        *n = *n/gcd; /*I will find the simplified version of numerator.*/
        *d = *d/gcd; /*I will find the simplified version of denominator.*/
    }
    
    
    if(flag =='M'){
        *n= -*n/gcd; /*If flag is'M' , I know that my number was negative.So I use '-' to make it negative again.*/
        *d=*d/gcd;
      }
}


