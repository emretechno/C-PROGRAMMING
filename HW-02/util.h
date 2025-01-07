#ifndef _UTIL_H_
#define _UTIL_H_

/*Part 1.*/
void check_leap_year(int);



/*Part 2 functions. */

int find_digit(int);

int find_factorial(int);

int find_exponential(int,int); /*I did not want to use read funct(pow) , I used my function.But I used pow function in Scientific form.*/

int make_reverse(long long int );

double find_mod(double , double); /*I did not want to use fmod function,I wrote my own function.*/

void enchanced_calculator(int , int); /*I send to calculator first.*/

void calculate_the_result (char ,char ,double ,double,int ,int); /*Then I calcualate the result*/


void print_scientific_result(int,int,int , long double); /*Then I print the result.*/


void check_error(int); /*If you could read the reasons of warning, I would really appreciate it.*/



/*Part 3 functions.*/
float calculate_final_grade(float , float ,float ,float ,float);

void print_final_grade(float);



#endif /* _UTIL_H_ */

