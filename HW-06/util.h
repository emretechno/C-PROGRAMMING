#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_PRODUCT 100
#define MAX_LENGTH 100

int the_menu(void);
int file_operations(void);
int add_new_product(FILE *);
int delete_product(FILE *, FILE *);
int add_feature(FILE *);
int add_stock(FILE *);
int query_products(void);
int check_stock_status(void);
int stock_control_brand(float [][3] , int *);
int export_report(float [][3] , int );
int find_comma(FILE *);
int find_total_line(FILE *);
int delete_stock_entry(FILE *,FILE *);
int list_all_products(FILE *);
int query_specific_stock(FILE *);
int list_specific_branch(FILE *);
int list_outof_stock(FILE *);
int filter_products(FILE * );
int update_stock(FILE *,FILE *);
int my_strcmp(const char *,const char *);
int update_product(FILE *  , FILE * );
void bubble_sort(int [MAX_PRODUCT] [MAX_PRODUCT], int, int);


#endif /* _UTIL_H_ */

