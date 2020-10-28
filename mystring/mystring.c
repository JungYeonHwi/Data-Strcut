#include "myString.h"

#include <stdio.h>
#include <stdlib.h>

/*Convert C style string to my_string. Note that the last node always corresponds to NULL character.*/
my_string to_mystring(char* string) {
// Implement your code
	int length = 0;
	while (string[length] != '\0') length++;
	length = length + 1;

	my_string newStr;

	node* pre_Node = NULL;
	node* new_Node;

	for (int num = 0; num < length; num++)
	{
		new_Node = (node*)malloc(sizeof(node));
		new_Node->character = string[num];
		new_Node->next = NULL;

		if (num == 0) newStr.first_symbol = new_Node;
		else pre_Node->next = new_Node;

		pre_Node = new_Node;
	}

	return newStr;
}

/*Print m_string*/
void print_mystring(my_string str) {
// Implement your code
	node* cur_Node = str.first_symbol;

	while (cur_Node->character != '\0') {
		printf("%c", cur_Node->character);
		cur_Node = cur_Node->next;
	}

	printf("\n");
}

/*Return the length of str*/
int my_strlen(my_string str) {
// Implement your code
	int length = 0;
	node* cur_Node = str.first_symbol;

	while (cur_Node->character != '\0') {
		++length;
		cur_Node = cur_Node->next;
	}

	return length;
}

/*Copy the source my_string to destination.
Note that this only works if the length of the destination is less than length of the source.*/
my_string my_strcpy(my_string destination, my_string source) {
// Implement your code
	int source_length, destination_length;

	destination_length = my_strlen(destination);
	source_length = my_strlen(source);

	node* source_Node;
	node* destination_Node;

	if (source_length > destination_length)
	{
		printf("에러\n");
		return source;
	}

	else {
		destination_Node = destination.first_symbol;
		source_Node = source.first_symbol;

		for (int num = 0; num < source_length; num++)
		{
			destination_Node->character = source_Node->character;
			source_Node = source_Node->next;
			destination_Node = destination_Node->next;
		}

		destination_Node->character = source_Node->character;

		return destination;
	}
}

// Concatenate the destination and source.
my_string my_strcat(my_string destination, my_string source) {
// Implement your code
	node* source_Node;
	node* destination_Node;

	destination_Node = destination.first_symbol;
	source_Node = source.first_symbol;

	while (destination_Node->next->character != '\0') {
		destination_Node = destination_Node->next;
	}

	destination_Node->next = source_Node;

	return destination;
}


/* Compare str1 and str2, and return 0, 1, or -1 according to their lexicographical order.*/
int my_strcmp(my_string str1, my_string str2) {
// Implement your code
	node* str1_Node;
	node* str2_Node;

	str1_Node = str1.first_symbol;
	str2_Node = str2.first_symbol;

	while ((str1_Node->character) && (str2_Node->character)) {
		char ch1 = str1_Node->character;
		char ch2 = str2_Node->character;

		if (((ch1 >= 'A') && (ch1 <= 'Z')) && ((ch2 >= 'a') && (ch2 <= 'z')))
		{
			return -1;
		}
		else if (((ch2 >= 'A') && (ch2 <= 'Z')) && ((ch1 >= 'a') && (ch1 <= 'z')))
		{
			return 1;
		}
		else
		{
			if (ch1 == ch2)
			{
				str1_Node = str1_Node->next;
				str2_Node = str2_Node->next;
			}
			else if (ch1 > ch2) return 1;
			else return -1;
		}
	}

	if ((str1_Node->character == NULL) && (str2_Node->character == NULL)) return 0;
	else if (str1_Node->character == NULL) return -1;
	else return 1;
}

/*Search character in str
If such character exists, return the first index and return the lengh of str otherwise.*/
int my_strchr(my_string str, int character) {
// Implement your code
	int str_length;
	str_length = my_strlen(str);

	node* str_Node;
	str_Node = str.first_symbol;

	char Str = str.first_symbol->character;

	for (int num = 0; num < str_length; num++)
	{
		if (Str == character) return num;
		str_Node = str_Node->next;
		Str = str_Node->character;
	}

	return str_length;
}

/*Find the first index of str1 which contains any characters in str2
if no characters in str1, return length of str1*/
int my_strcspn(my_string str1, my_string str2) {
// Implement your code
	int str1_length, str2_length;

	str1_length = my_strlen(str1);
	str2_length = my_strlen(str2);

	node* str1_Node;
	node* str2_Node;

	str1_Node = str1.first_symbol;
	str2_Node = str2.first_symbol;

	char ch1 = str1_Node->character;
	char ch2 = str2_Node->character;

	for (int num = 0; num < str2_length; num++)
	{
		str1_Node = str1.first_symbol;
		ch1 = str1_Node->character;

		for (int k = 0; k < str1_length; k++)
		{
			if (ch1 == ch2) return k;
			else {
				str1_Node = str1_Node->next;
				ch1 = str1_Node->character;
			}
		}
		str2_Node = str2_Node->next;
		ch2 = str2_Node->character;
	}

	return str1_length;
}

/*Check if str1 contains str2.
If str1 contains str2, return the first occurence of str2 in str1
if not contains, return -1*/
int my_strstr(my_string str1, my_string str2) {
// Implement your code
	int str1_length, str2_length;

	str1_length = my_strlen(str1);
	str2_length = my_strlen(str2);

	node* str1_Node;
	node* str2_Node;
	node* tmp;

	str1_Node = str1.first_symbol;
	str2_Node = str2.first_symbol;

	for (int num = 0; num < str1_length; num++)
	{
		str2_Node = str2.first_symbol;

		if (str1_Node->character == str2_Node->character)
		{
			tmp = str1_Node;
			int cnt = 0;

			for (int k = 0; k < str2_length; k++)
			{
				if (tmp->character == NULL)
				{
					break;
				}

				if (tmp->character != str2_Node->character)
				{
					break;
				}
				else
				{
					tmp = tmp->next;
					str2_Node = str2_Node->next;

					cnt++;

					if (cnt == str2_length)
						return num;
				}
			}
		}
		str1_Node = str1_Node->next;
	}
	return -1;
}

/*Reverse my_string*/
my_string my_strrev(my_string str) {
// Implement your code
	int str_length = 0;
	str_length = my_strlen(str);

	my_string newStr;

	node* str_Node;
	node* new_Node;

	int length;
	length = my_strlen(str);

	char list[100];

	str_Node = str.first_symbol;
	new_Node = str.first_symbol;

	for (int i = 0; i < length; i++)
	{
		list[i] = str_Node->character;
		str_Node = str_Node->next;
	}

	for (int num = 0; num < length; num++)
	{
		new_Node = (node*)malloc(sizeof(node));
		new_Node->character = list[length - num - 1];
		new_Node->next = NULL;

		if (num == 0) newStr.first_symbol = new_Node;
		else str_Node->next = new_Node;

		str_Node = new_Node;
	}

	new_Node = (node*)malloc(sizeof(node));
	new_Node->character = '\0';
	new_Node->next = NULL;

	str_Node->next = new_Node;

	return newStr;
}
