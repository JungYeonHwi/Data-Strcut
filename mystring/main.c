#include <stdio.h>

#include "myString.h"

int main() {
   // to_mystring
   my_string s1 = to_mystring("hello world");
   my_string s2 = to_mystring("da");
   my_string s3 = to_mystring("app\0le");  // contains NULL in the middle !!

   // print_mystring
   print_mystring(s1);  // hello world
   print_mystring(s2);  // da
   print_mystring(s3);  // app

   // my_strlen
   printf("%d\n", my_strlen(s1));  // 11
   printf("%d\n", my_strlen(s2));  // 2
   printf("%d\n", my_strlen(s3));  // 3

   // my_strcpy
   my_string s4 = to_mystring("banananana");
   // not copied (error message will be announced)
   my_string s5 = my_strcpy(s2, s4);  // destination is too small

   my_string s6 = my_strcpy(s4, s2);
   print_mystring(s6);  // da

   my_string s7 = my_strcpy(s1, s3);
   print_mystring(s7);  // app

   // my_strcat
   s1 = to_mystring("hello world");
   s2 = to_mystring(" da");
   s1 = my_strcat(s1, s2);
   print_mystring(s1);  // hello world da

   my_string a = to_mystring("a");
   a = my_strcat(a, s2);
   print_mystring(a);  // a da

   // my_strcmp
   my_string apple = to_mystring("apple");
   my_string ABCapple = to_mystring("ABCapple");
   my_string ABC1pple = to_mystring("ABC1pple");
   my_string apple123 = to_mystring("apple123");

   // same case
   printf("%d\n", my_strcmp(apple, apple));  // 0
   // first one is precede (with digit)
   printf("%d\n", my_strcmp(ABC1pple, ABCapple));  // -1
   // second one is precede (one includes the other)
   printf("%d\n", my_strcmp(apple123, apple));  // 1

   // my_strchr
   // if contains
   printf("%d\n", my_strchr(apple, 'p'));  // 1
   // if doesnt contain
   printf("%d\n", my_strchr(ABCapple, '1'));  // 8
   // finding null
   printf("%d\n", my_strchr(ABC1pple, '\0'));  // 8

   // my_strcspn
   my_string bananan = to_mystring("bananan");
   my_string an = to_mystring("an");
   my_string cc = to_mystring("cc");
   // if contains
   printf("%d\n", my_strcspn(apple, an));  // 0
   // if contains multiple characters
   printf("%d\n", my_strcspn(bananan, an));  // 1
   // if does not contain
   printf("%d\n", my_strcspn(apple, cc));  // 5 (length of apple)

   // my_strstr
   my_string e = to_mystring("e");
   // if does not contain
   printf("%d\n", my_strstr(apple, an));  // -1
   // if contains multiple times
   printf("%d\n", my_strstr(bananan, an));  // 1
   // if contains only one letter
   printf("%d\n", my_strstr(apple, e));  // 4

   // my_strrev
   my_string rev = my_strrev(bananan);
   print_mystring(rev);  // nananab

   // quite long string including white space
   my_string helloworldda = to_mystring("hello world da da da");
   rev = my_strrev(helloworldda);
   print_mystring(rev);  // ad ad ad dlrow olleh

   // reverse one letter
   rev = my_strrev(e);
   print_mystring(rev);  // e

   return 0;
}