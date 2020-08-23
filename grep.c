#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include "grep.h"

void init(line *l){
	l->front = NULL;
	
	l->rear = NULL;
}

void printline(line l){
	node *ptr1 = l.front;
	
	if(l.front == NULL){
		printf(" ");
	}
	
	else{
		do{
			printf("%c", ptr1->c);
		
			ptr1 = ptr1->next;
		}while(ptr1 != l.front);
	
		printf("\n");
	}
	
	return; 
}

void appendchar(line *l, char ch){
	node *newnode = (node*)malloc(sizeof(node));
	newnode->c = ch; 
	if(l->front == NULL){
		l->front = newnode;
		
		l->rear = newnode;
		
		l->front->next = l->front;
		
		l->front->prev = l->front;
	}
	
	else{
		l->rear->next = newnode;
		
		l->rear->next->prev = l->rear;
		
		l->rear = newnode;
		
		l->rear->next = l->front;
		
		l->front->prev = l->rear;
	}
}

void destroyline(line *l){
	while(l->rear != l->front){
		l->rear = l->rear->prev;
	
		free(l->rear->next);
	}
	
	free(l->front);
	
	l->rear = NULL;
	
	l->front = NULL;
}

int search(line l, char *str){
	node *ptr = l.front;
	
	int i = 0;
	
	if(l.front == NULL)
		return 0;
		
	do{
		if(ptr->c == str[i]){
			i++;
			
			ptr = ptr->next;
		}
		else{
			if(i != 0)
				i = 0;
			else
				ptr = ptr->next;	
		}
	}while(ptr != l.front && str[i] != '\0');
	
	if(str[i] == '\0')
		return 1;
	
	else
		return 0;	
}

int wsearch(line l, char *str){
	node *ptr = l.front;
	
	int i = 0;
	
	char ch[100];
	
	if(l.front == NULL)
		return 0;
		
	do{
		i = 0;
	
		while(ptr->c != ' ' && ptr->c != '\t' && ptr != l.rear){
			ch[i] = ptr->c;
	
			i++;
	
			ptr = ptr->next;
		}
		
		if(ptr == l.rear){
			ch[i] = ptr->c;
			
			i++;
		}	
		
		ch[i] = '\0';
		
		if(!strcmp(ch, str))
			return 1;

		ptr = ptr->next;
		
		strcpy(ch, "");
			
	}while(ptr != l.front);
	
	return 0;
}


int isearch(line l, char *str){
	node *ptr = l.front;
	
	line l1;
	
	char ch;
	
	char *str1 = (char*)malloc(sizeof(char) * strlen(str));
	
	int i = 0;
	
	if(l.front == NULL)
		return 0;
	
	init(&l1);
	
	strcpy(str1, str);
	
	while(str1[i] != '\0'){
		if(str1[i] >= 65 && str1[i] <= 90)
			str1[i] = str1[i] + 32;	
			
		i++;
	}
	
	do{
		ch = ptr->c;
		
		if(ch <= 'Z' && ch >='A')
			ch = ch + 32;
		
		appendchar(&l1, ch);
		
		ptr = ptr->next;
	}while(ptr != l.front);
	
	return search(l1, str1);
}

int wisearch(line l, char *str){
	
	node *ptr = l.front;
	
	line l1;
	
	char ch;
	
	char *str1 = (char*)malloc(sizeof(char) * strlen(str));
	
	int i = 0;
	
	if(l.front == NULL)
		return 0;
	
	init(&l1);
	
	strcpy(str1, str);
	
	while(str1[i] != '\0'){
		if(str1[i] >= 65 && str1[i] <= 90)
			str1[i] = str1[i] + 32;	
			
		i++;
	}
	
	do{
		ch = ptr->c;
		
		if(ch <= 'Z' && ch >='A')
			ch = ch + 32;
		
		appendchar(&l1, ch);
		
		ptr = ptr->next;
	}while(ptr != l.front);
	
	return wsearch(l1, str1);
}

/*int main(){
	char *str = "the sid is in SY";
	int i = 0;
	line l;
	init(&l);
	while(str[i] != '\0'){
		appendchar(&l, str[i]);
		i++; 
	}
	printline(l);
	int n = wsearch(l, "SY");
	printf("%d\n", n);
}*/
