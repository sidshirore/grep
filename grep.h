typedef struct node{
	char c;
	struct node *prev;
	struct node *next;
}node;

typedef struct line{
	node *front;
	node *rear;
}line;

void init(line *l);

void printline(line l);

void appendchar(line *l, char c);

void destroyline(line *l);

int search(line l, char *str);

int wsearch(line l, char *str);

int isearch(line l, char *str);

int wisearch(line l, char *str);
