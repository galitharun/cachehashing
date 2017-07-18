#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PRIME 1009 

typedef struct record{
	char* key;
	char* value;
}record;

typedef struct hash_table{
	record rec;
	hash_table* next;
}hash_table;


int hash_function(char* str){
	long long int hash = 0;
	int i = 0;
	for (; str[i] != '\0'; i++){
		hash += str[i] * (PRIME + i);
	}
	return hash % 150;
}


void add_to_hashtable(hash_table** ht, int hash_value, record rec){
	hash_table* created = (hash_table*)malloc(sizeof(hash_table));
	created->rec = rec;
	created->next = NULL;
	if (ht[hash_value] == NULL){
		ht[hash_value] = created;
	}
	else{
		hash_table *temp;
		for (temp = ht[hash_value]; temp->next != NULL; temp = temp->next);
		temp->next = created;
	}

}

void insertRecord(hash_table** table,char *key,char *value){
	record rec;
	rec.key=key;
	rec.value = value;
	int hash_value = hash_function(rec.key);
	add_to_hashtable(table, hash_value, rec);
}

void display(hash_table** table){
	for (int i = 0; i < 150; i++){
		hash_table* temp;
		temp = table[i];
		if (temp == NULL){
			printf("NO RECORD:%d\n", i);
		}
		else{
			for (; temp != NULL; temp = temp->next){
				printf("{%s : %s}\n", temp->rec.key, temp->rec.value);
			}
		}
	}
}

void displayRecord(hash_table** table, char* str){
	int h_value = hash_function(str);
	hash_table* temp;
	temp = table[h_value];
	if (temp == NULL)
	{
		printf("NOT FOUND\n");
	}
	else{
		for (; temp != NULL; temp = temp->next){
			if (strcmp(temp->rec.key, str) == 0){
				printf("{%s : %s}\n", temp->rec.key, temp->rec.value);
			}
		}
	}
}


void removeRecord(hash_table** table, char* str){
	int h_value = hash_function(str);

	if (strcmp(table[h_value]->rec.key, str) == 0){
		table[h_value] = table[h_value]->next;
	}
	else{
		hash_table* temp;
		hash_table* prev;
		for (temp = table[h_value]; (strcmp(table[h_value]->rec.key, str) != 0); temp = temp->next);
		for (prev = table[h_value]; prev->next != temp; prev = prev->next);
		prev->next = temp->next;
		free(temp);
	}

}
hash_table **get_table(){
	hash_table** table = (hash_table**)calloc(150, sizeof(hash_table*));
	return table;
}
