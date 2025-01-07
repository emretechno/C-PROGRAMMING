#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct f_tree{
    char name[20];
    int age;
    struct f_tree *mother;
    struct f_tree *father;
} f_tree;
f_tree* add_family(f_tree *root);
f_tree* remove_person(f_tree *root);
f_tree* add_person(f_tree *root);
f_tree* remove_family(f_tree *root);
void print_nuclear_family(f_tree *root);
void search_relatives(f_tree *root,char *name);
void print_family_tree(f_tree *root);
void find_name(f_tree *root, char *name ,  char *name_father, char *name_mother);
void remove_family_tree(char *filename);
void print_relatives(f_tree *root, char *name);
int is_exist(f_tree *root,char *name);
#endif /* _UTIL_H_ */

