//this make a struct for the item taht will store the value and our key
typedef struct
{
    char* key;
    char* value;
}item;

//this one gonna make our hash table
typedef struct
{
    int base_size;
    int count;
    item** items;
}hash_table;

//declaring all of our fucntion in .c
hash_table* ht_new(void); //making the base size
void insert(hash_table* ht, const char* key, const char* value);// inserting
char* search(hash_table* ht, const char* key);// searching
void delete(hash_table* ht, const char* key);//deleting
void del_hash_table(hash_table* ht); //delete the enitre table


hash_table* ht_new(void);

//declaring all constant in fucntion
#ifndef HASH_H
#define HASH_H
#define HT_INITIAL_BASE_SIZE 6
#define HT_PRIME_1 3
#define HT_PRIME_2 2
#endif