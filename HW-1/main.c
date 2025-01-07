

#include <stdio.h>
#include "util.h"

int main() {/* MY CODE DICTIONARY.
->  'n'  means number. For example n1 means  number one , n2 mean number two.*/
   
int n1=0;  /*I initialized the n1 before send it to
function.In pdf , it was written that "your functions gets number from the user" .That's why I get from user in functions,not in main.*/
    
int n2=0;  /*I initialized the n2.Same process with n1 */
    
    
printf("PART 1!\n");
printf("In this part ,we are gonna calculate the Greatest Common Divisor by using euclidian algorithm.\n");
euclid_algorithm(n1,n2); /*I send to my function.*/
    
    
printf("PART 2!\n");
printf("In this part , I am gonna display you to sum process.\n");
displaying_sum(n1,n2); /*It is sent to function.*/
    
    
    
printf("PART 3!\n");
printf("In this part , I am gonna display you to multiply process.\n");
displaying_multiply(n1,n2); /*n1 and n2 will be taken in function*/
    
    
    
printf("PART 4! \n");
printf("In this part , You are gonna enter a number and I am gonna make my exit.\n");
checking_range(n1); /*Same things.*/

    return (0);
}
