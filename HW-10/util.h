#ifndef _UTIL_H_
#define _UTIL_H_


typedef struct Student{ /*My student struct*/
    char name[50];
    int stu_id;
    char borrowed_books[50];
    struct Student *next;
}student;

typedef struct book {  /*My book struct*/
    char isbn_number[20];
    char title[50];
    char author[50];
    int publication_year;
    char borrowed_status[50];
    struct book *next;
} book;

student *add_student(student *head ,int stu_id , char *name , char *borrowed_books);
student *delete_student(student *head ,char *name_book);
student *read_student_file(student *stu_head );

book * add_book(book *head ,char *isbn_number,char *title , char *author , int publication_year,char *status,int type);
book *read_book_file(int *n , book * head);
book *update_books(book *head , char *isbn_number,char *feature , char *value);
book *filter_and_sort_books(book *head , int filter_choice , char *filter , int sort_choice);
book *delete_books(book *head , char *isbn_number);
book * make_reverse(book *head,book *reverse_head);

int is_exist_student(student *head , int Id);
int is_valid_id(student *head , int id,char *name,char *existed_name);
int is_possible_delete(book *head , char *isbn_number);
int is_valid_isbn(book *head , char *isbn_number);
int borrow_books(book *head , char *isbn_number);
int return_books(book *head , char *isbn_number);

void display_borrowed_books(student *head,int Id);
void update_student_txt(student *head);
void searchbooks(int search_choice , char *search_value , book *head);
void print_books(book *head);
void find_name_book(book *head , char *isbn_number , char *name);
void update_book_txt(book *head);
void menu();

#endif /* _UTIL_H_ */

