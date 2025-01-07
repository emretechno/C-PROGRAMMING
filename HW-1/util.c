#include <stdio.h>
#include "util.h"
/*MY CODE DICTIONARY!!!!!
 
-> In my code ,  underscore means of.For example digit_n1 = digit of n1 , result_multiply = result of multiply.temp_n2 = temp of n2.
 
-> 'n'  means number. For example n1 means  number one , n2 mean number two.
 
-> Reason of writing '4' in add_space function is that in front of the every number, I add 4 space because I wanted to write the more aesthetichlty.The reason of +1 space is becvause of '-' symbol.I must increase one more  space in minus situations.
 
->All of my if else conditions on multiply function is because negative situations.My spaces and division line  depends on negative numbers.(There is an example of some outputs of multiply.You should check it from out_multiply png. */

void euclid_algorithm(int n1 ,int n2){
    
    printf("Please enter the first number\n");
    scanf("%d",&n1);
    
    printf("Please enter the second number\n");
    scanf("%d",&n2);
     
    
    int gcd =1; /*I assigned one.If while doesnt come true , my gcd will be 1.It means the prime number between them are.*/
    int remainder=1; /*I should initiliazed it.*/
    if(n1<n2){  /*First number must be greater than second number.That is why I sort them if first one is less than second number.*/

        int temp = n1; /*It is the algorithm.I checked form wikipedia and some youtube channels(example:BU DERS Youtube Channel.)*/
        n1 =n2;
        n2 =temp;
    }
    
    while(remainder !=0){ /*When remainder is 0 , my loop stops.*/
        
            remainder = n1 % n2; /*I find the remainder*/
        
            if(remainder ==0){ /*If remainder is 0  ,I can say that our greatest common divisor is n2.*/
                gcd = n2;       /*If this this condition is not true , gcd will be 1 as expected.*/
                
            }
            else {    /*else , n1 is the divided and n2 is divider.*/
                n1= n2;     /*new n1 is n2.*/
                n2 =remainder;   /*new n2 is remainder.*/
            }
        }
    
    
    if(n1<=0 || n2<=0 || (n1<=0 && n2 <0)){ /*We know that negative numbers have no greatest common divisor.If user enter a negative number , there will be no common divisor.This condition checks this situation.*/
        printf("There is no greatest common divisor!."); /*There is no gcd in negative siuations.*/
    }
    else{
        printf("The greatest common divisor is= %d\n",gcd); /*I wrote the result of gcd.*/
    }
    printf("\n\n\n");
}



void displaying_sum(int n1 , int n2){
    
    
    printf("Please enter the first number:\n"); /*Input output things.*/
    scanf("%d",&n1);
    
    printf("Please enter the second number:\n");
    scanf("%d",&n2); /*Get number from user*/
    
    printf("First number : %d\n",n1);
    printf("Second number : %d\n",n2);
    printf("Result:\n\n");
    
    int result_sum = n1+n2;
    printf("      %6d\n",n1); /* max 6 digits are valid for this code.Bunu ingilizce anlatamam:Hocam ben her sayi oncesinde 4 bosluk ekledim 4 space.Sebebi ise sayilar terminale yapisik gibi durmasin daha estetik dursun diye.O yuzden carpma fonksiyonunda oldugu gibi add space fonksiyonuna 4 ekledim.*/
    printf("      %6d\n",n2); /* Same*/
    printf("  +\n"); /*My sum symbol (+) */
    printf("  ----------\n");/*My division line.I used '9' times '-' symbol.'4' is becase I used 4 space in front of the numbers.'6' is because I used max  6 digit numbers  */
    printf("      %6d\n",result_sum); /*The result is written.*/
    
    }







/*My multiply algorithm works for all 0 situations , negative positive situations and every number of digit.I know it is kind of long ,but everything works flawless for every situation.Not only for 3 digits , but also every number of digits.Even though  my code is kind of long ,but it works for every stiatuon.*/

void displaying_multiply(int n1 , int n2){
    /*My algorithm is all about the digit numbers.I find all the digits and add space by  means of 'add_space' function.However , there are some exceptions because of 0 and negative situtations.That is why  I add some if conditions the solve them.*/
    printf("Please enter the first number:\n");
    scanf("%d",&n1);
    printf("Please enter the second number:\n");
    scanf("%d",&n2);
    printf("First number : %d\n",n1);
    printf("Second number : %d\n",n2);
    printf("Result:\n\n");
  
    int temp_n2 =n2; /*I use temp to not change the value of n2*/
    
    int digit_n1 =finding_digit(n1);/* I am finding the digit*/

    int digit_n2=finding_digit(n2); /*Calculating the digits to find the amount of space.*/
    
    int result_multip = n1*n2; /*Result of multiply.*/
  
    int digit_result=finding_digit(result_multip); /*Digit of result.*/
    
    if(n1 ==0){
        digit_result = digit_n2; /*If n1 = 0 , digit of n1 must be equal to digit of n2.Otherwise , there will be lack of space. */
    }
    if(n2 ==0){
        digit_result = digit_n1; /*Same process for n2 as above one.*/
    }
    int space_of_n1=(digit_result)-(digit_n1); /*I am calculating the needed space except '0' situations.*/
    
    int space_of_n2=(digit_result)-(digit_n2);/*Also same for this one.*/

    if(n1 >=0 && n2 <0){
      add_space(space_of_n1+1); /*I'm adding the spaces in front of the number.If one of them are negative , I must add one more space because of minus symbol.The reason of 1 is because of '-' symbol.*/
    }
    else {
        add_space(space_of_n1); /*There is no need for one more space if one of them are not minus*/
    }
    printf("    %d\n",n1); /*My first number was written.*/
    
    
    if(n1<0 && n2 >=0 ){
        add_space(space_of_n2+1); /*I'm adding the spaces in front of the number.Same process for this.The reason of 1 is because of '-' symbol.*/
    }
    else {
        add_space(space_of_n2); /*Else , no need to add one more space.*/
    }
    
    
    printf("    %d\n",n2); /*My second number is written.*/
    printf("  *\n");  /*Kod terminal cercevesine  yapismasin  diye 2 bosluk ekledim basina. */
    
    
    if(result_multip<0){ /*I am drawing the division line right now.*/
        add_division_line(digit_result+4+1); /*same logic with the space.For this time , I must add one more division line ('-') because of minus symbol.*/
        /*Meaning of 4 is that I add 4 space in front of the every number to see them more aestetichly.*/
    }
    else if(n1<=0 && n2<=0){
        add_division_line(digit_result+4+1); /*Same process for this division line.*/

    }
   
    else {
        add_division_line(digit_result+4); /*No need for  one more space.There is no exception.*/
    }
    

  /* Until this phase , found number of digits of  n1 , n2 and result(n1*n2).Then I used as many spaces as the difference in the number of digits between result and n1 and n2.*/
    /*Now I will write the remain multiplies.Bir basamak sola kaydirma kurali burada kullanilacak.*/

    int remain;
    int k =0; /*It provides the rule of summing in multiplication(HER CARPIM SONRASI YAZACAGIMIZ SAYIYI BI BOSLUK SOLA KAYDIRMA KURALI).I add this 'k' to for loop.Her carpmada bi sola kaydirir yazilacak sayiyi.*/
   
    while(temp_n2!= 0){ /*This loop is gonna run as many as number of digits of n2*/
        
        remain =temp_n2%10; /*AS A RULE OF MULTIPLYING, EVERY DIGIT OF SECOND NUMBER IS MULTIPLIED BY FIRST NUMBER.That is why I must find  all of the digits of n2.*/
        
        temp_n2 = temp_n2/10; /*I am calculating the every digit of n2 one by one*/
        
        int result_remain_multip = remain *n1; /*Every digit of second number is multiplied by first number.*/
        int digit_result_remain=finding_digit(result_remain_multip);  /*I'm calculating the number of digit of result_remain_multip by sending it to find_digit function*/
        
        
        
        
        
        if(result_remain_multip ==0){  /*Bu kosul  sadece outputa 0 yazmak yerine n1 in basamk sayisi kadar 0 yazmasi icink kurulmus gorece extra bir kosul.Example  123
                                     123
                                       0
                                    *___
                                     000 yaziyor , bir tane  0 yazmak yerine. */
            
           int  space_of_result_remain =(digit_result)-(digit_n1)-k;
            /*I am calculating the number of space I will use.NOTE : I used 'k' to reduce the number of space in every digit because as a rule of mult, we should do it(Bir basamak sola kaydirirsin her carpim sonucunda.Bu kosulu her seferinde 1 arttirdigim k sagliyor.*/
            
            if(n1 <0 || n2 <0){
                add_space(space_of_result_remain+1);
            }/*I'm adding the spaces in front of the number.I must add one more space cause of minus symbol.*/
            
            else {
                add_space(space_of_result_remain); /*No need for one more space  this conditon.*/

            }
            printf("    %d",result_remain_multip);
            for(int i = 1; i<=digit_n1-1 ; i++){
                printf("%d",0); /* Iste burada tek 0 yazmasin basamak sayisi kadar 0 yazsin kosulunu sagliyorum:
                                                                                                                123
                                                                                                                  0
                                                                                                               *___
                                                                                                                000 gibi.*/
            }
            printf("\n");
        }
        else { /*If result_remain_multip 0 degilse  bu kosul yani normal kosul .*/
            
            int space_of_result_remain =(digit_result)-(digit_result_remain)-k; /*Do not forget to sub  'k'.It is the maain thing about swiping left in every result of remain multiply.By using k ,evey time I decrease one spcace(Bir basamak sola kayidiriyorum.*/
            
            if(n1 <0 && n2 <0){
                add_space(space_of_result_remain+1); /*if both n1 and n2 are negative , amount of space must increase one because of - symbol*/
            }
            
            else {
                add_space(space_of_result_remain); /*Normal situation.If there is no exception , this loop works.*/
            }
            
            printf("    %d\n",result_remain_multip); /*Do not forget to write resultl of remain multiply.*/

        }
        
        k++;  /*I must increase k '+1' for every digit of second number.*/
    }
    
    
    
    
    if(n2 ==0){
        add_space(digit_n1+4-1);
        printf("%d\n",0); /*sonucun 0 cikma istisnasi.*/
    }
    printf("  +\n"); /*Kod terminal cercevesine  yapismasin  diye 2 bosluk ekledim. */
    
    if(result_multip<0 ||(n1<=0 && n2<=0)){ /*We must add 1 more line  because of minus '-' symbol.*/
        
        add_division_line(digit_result+4+1); /*If result is negative , one more division line is essential.*/
    }
    
    else {
        add_division_line(digit_result+4); /*No need if it is not negative.*/

    }
    
    
    
    
    
    if(result_multip==0){  /*All of these are because of 0 exceptation.*/
        
        if(n1 ==0 && n2 !=0){
            
            add_space(digit_n2+4-1); /*If result_multip = 0 , I should decrease one space.All other if conditions also work with that logical process.*/
            printf("%d",result_multip);
        }
        
        if(n2 ==0  && n1!=0){  /*If I use || operator instead of three if condition, there will be  a space mistake.That is why I could not use it.*/
            add_space(digit_n1+4-1);
            printf("%d",result_multip);
        }
        
        if(n1 ==0 && n2 ==0){
            add_space(digit_n1+4-1); /*Same logic with the above one.I should  not forger any exeeptions.*/
            printf("%d",result_multip);
        }
        
    }
   else if(n1<=0 && n2<=0 && result_multip !=0){
        add_space(1); /*Do not forget add 1 space because of  minus.*/
        printf("    %d",result_multip); /*n1 * n2 is our result.*/

    }
    
    else {
        printf("      %d",result_multip); /*Normal situation.If there is no exception , this loop works.n1 * n2 is our result.*/

    }
    
    
    
    printf("\n\n\n");

}




void checking_range(int n1){
    
    printf("Please enter an integer number between 1 and 10(inclusive):\n");
    scanf("%d",&n1); /*I am taking an integer from user.*/
    
    if(n1>5 &&  n1<=10){ /*If number is greater than 5 , I print it.(Cannot be greater than 10).*/
        printf("The integer you entered is greater than 5.\n");
    }
    
    else if(n1<=5 && n1>=1){  /*If number is less or equal to 5, I print it.(Cannot be less than 1).*/
        printf("The integer you entered is less than or equal to 5.\n");
    }
    
    else{  /*If number is not in valid range ,I print that "invalid input".*/
        printf("invalid input!.\n");
    }
    
}



int finding_digit(int number){
  
    int digit_number=0; /*I will find the digit number.*/
    if(number ==0){
        digit_number =1; /*0 is also 1 digit.Do not forget this condition.0 is one digit as we know.*/
    }
    while(number !=0){
        number = number/10;
        digit_number++; /*I am calculating the number of digit.*/
    }
 
    return digit_number; /*It is an int function so I must return.*/
    
}




void add_space(int space_of_number){
    printf("  "); /*I wanted to add 2 space because it will look better by  means of this.It just changes my code aesthetichly as I explained.*/
    for(int i=1 ; i<=space_of_number ; i++){ /*After I find the differences of digits of number , I add space as many as that difference.*/
        printf(" "); /*Adding space.*/
    }
}


void add_division_line(int digit_result){

    printf("  "); /*I wanted to add 2 space because it will look better by  means of this.It just changes my code aesthetichly.Yani kod terminale yapismasin biraz bosluk olsun istedim.*/
    for(int i = 1; i<=digit_result ; i++){   /*Same process is also valid for this function.By means of that function , my length of divison line will look perfect.It will depend on every digit.*/
        printf("-"); /*Same logic with space.Instead of space , I add division line.*/
    }
    printf("\n");
}

