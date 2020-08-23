#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<sys/types.h>

#include<sys/stat.h>

#include<fcntl.h>

#include<unistd.h>

#include "grep.h"

typedef struct grepmode{
	int status; //print or count
	int Case;	//sensitive or insensitive
	int type; //match or unmatch
	int print;
	int word; //word or substring
	int recursion;
}grepmode;

void grep(char *filename, char *pattern, grepmode g);

grepmode check(char *ch);

grepmode reset();

#define YES 1 

#define NO 0

#define PRINT 100

#define COUNT 101

#define MATCH 200

#define UNMATCH 201

#define SENSITIVE 300

#define INSENSITIVE 301

#define WORD 400

#define SUBSTRING 401

int main(int argc, char* argv[]){
	int i = 0, j, k;
	line l;
	grepmode g;
	char ch;
	
	if(argc < 3){
		printf("Invalid number of arguments\n");
		return 0;
	}
	
	else if(argv[1][0] != '-'){
		i = 2;
		while(i < argc){
			g.status = PRINT;
			g.type = MATCH;
			
			if(argc > 3)
				g.print = YES;
			else
				g.print = NO;
			
			g.Case = SENSITIVE;
			grep(argv[i], argv[1], g);
			i++;	
		}
	}
	
	else if(argv[1][0] == '-'){
		i = 3;
		g = check(argv[1]);
		if(g.recursion == YES){
			g.print = YES;
			j = 2;
			k = 1;
			while(i < argc){
				g = reset();
				printf("Status:%d Case:%d Type:%d Word:%d\n", g.status, g.Case, g.type, g.word);
				g = check(argv[k]);
				printf("Status:%d Case:%d Type:%d Word:%d\n", g.status, g.Case, g.type, g.word);
				g.print = YES;
				grep(argv[i], argv[j], g);
				k = k + 3;
				j = j + 3;
				i = i + 3;
			}
		}
		else{
			while(i < argc){			
				if(argc > 4)
					g.print = YES;
				else
					g.print = NO;

				grep(argv[i], argv[2], g);
				i++;		
			}
		}
	}
	
	return 0;
}

void grep(char *filename, char *pattern, grepmode g){
	int fd, n, count = 0;
	line l;
	char ch;
	
	init(&l);
	fd = open(filename, O_RDONLY);
	
	if(fd == -1){
		printf("Unable to open file");
		return;
	}
	
	while(read(fd, &ch, sizeof(char))){
		if(ch != '\n')
			appendchar(&l, ch);
			
		else{
			if(g.word == WORD){
				if(g.Case == INSENSITIVE)
					n = wisearch(l, pattern);
				if(g.Case == SENSITIVE)
					n = wsearch(l, pattern);
			}
			else if(g.Case == SENSITIVE){
				n = search(l, pattern);
			}
			else if(g.Case == INSENSITIVE){
				n = isearch(l, pattern);
			}
			
			if(g.type == MATCH && n == 1){
				if(g.status == PRINT){
					if(g.print == YES)
						printf("%s:", filename);
					
					printline(l);	
				}
				
				else if(g.status == COUNT){
					count++;
				}
			}
			
			else if(g.type == UNMATCH && n == 0){
				if(g.status == PRINT){
					if(g.print == YES)
						printf("%s:", filename);
						
					printline(l);	
				}
				
				else if(g.status == COUNT){
					count++;
				}
			}
			destroyline(&l);
			init(&l);
		}
	}
	
	if(g.status == COUNT){
		if(g.print == YES)
			printf("%s:", filename);

		printf("%d\n", count);	
	}
}

grepmode check(char *ch){
	int i = 0, j = 1;
	grepmode g;
	char arr[] = "vciwe";
	
	while(arr[i] != '\0'){
		j = 1;
		
		while(ch[j] != '\0'){
			if(arr[i] == ch[j]){
				if(i == 0)
					g.type = UNMATCH;
		
				if(i == 1)
					g.status = COUNT;
		
				if(i == 2)
					g.Case = INSENSITIVE;
		
				if(i == 3)
					g.word = WORD;
		
				if(i == 4)
					g.recursion = YES;	
					
				j = 1;
				break;	
			}
			else
				j++;
		}
		i++;
	}
	
	if(g.status != COUNT)
		g.status = PRINT;
	
	if(g.type != UNMATCH)
		g.type = MATCH;
		
	if(g.Case != INSENSITIVE)
		g.Case = SENSITIVE;	
		
	if(g.word != WORD)
		g.word = SUBSTRING;
	
	if(g.recursion != YES)
		g.recursion = NO;	
	
	return g;
}

grepmode reset(){
	grepmode g;
	g.status = PRINT;
	g.type = MATCH;
	g.Case = SENSITIVE;
	g.word = SUBSTRING;
	g.print = YES;
	return g;
}

