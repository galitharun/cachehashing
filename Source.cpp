#include"Hashing.h"

#define chunk 1048554
#define mb_size 1048576
#define total 100

struct part
{
	part *prev;
	int delim;
	char data[1048554];
	part *next;
};

struct bucket
{
	part *link;
}mb_bucket;

char *data; int *bit;
hash_table** table;
part *first, *last;

void init_bit(int *arr)
{
	for (int i = 0; i < total; i++)
	{
		arr[i] = 0;
	}
}
int getFree(int *arr)
{
	for (int i = 0; i < total; i++)
	{
		if (arr[i] == 0)
		{
			arr[i] = 1;
			return i;
		}
	}
}
void setFree(int *arr, int pos)
{
	arr[pos] = 0;
}
void *allocMemory()
{
	int location = getFree(bit);
	return (void *)(data + location * mb_size);
}
part *getNode()
{
	part *rtn = (part *)allocMemory();
	return rtn;
}
void addCache(char *key, char *value)
{
	part *node = getNode();
	strcpy(node->data, key);
	strcat(node->data, ":");
	node->delim = strlen(key);
	strcat(node->data, value);
	insertRecord(table, key, value);
	if (mb_bucket.link == NULL)
	{
		mb_bucket.link = node;
		first = node;
		last = node;
		node->next = NULL;
		node->prev = NULL;
	}
	else
	{
		last->next = node;
		node->prev = last;
		node->next = NULL;
		last = node;
	}
}

void memcache()
{
	data = (char *)malloc(sizeof(char) * (total * mb_size));
	bit = (int *)malloc(sizeof(int) * (total));
	table = get_table();
	init_bit(bit);
	char ch;
	int k;
	do
	{
		char *key = (char *)malloc(sizeof(char) * 30);
		char *value = (char *)malloc(sizeof(char) * 1024);
		printf("SELECT AN OPTION FROM THE FOLLOWING\n1.INSERT\n2.GET\n3.GET ALL\n4.REMOVE\n");
		scanf("%d", &k);
		switch (k)
		{
		case 1:
			printf("enter key\n");
			scanf("%s", key);
			printf("enter value\n");
			scanf("%s", value);
			addCache(key, value);
			break;
		case 2:
			printf("enter key\n");
			scanf("%s", key);
			displayRecord(table, key);
			break;
		case 3:
			display(table);
			break;
		case 4:
			printf("enter key\n");
			scanf("%s", key);
			removeRecord(table, key);
		default:break;
		}
		fflush(stdin);
		printf("do you want to continue??y or n\n");
		scanf("%c", &ch);
	} while (ch == 'y');
}

int main()
{
	
	memcache();
}
