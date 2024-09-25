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

hash_table* ht_new(void);
static item* new_item(const char* k , const char* v);
void del_hash_table(hash_table* ht);
void insert(hash_table* ht, const char* key, const char* value);


//declaring all constant in fucntion
#ifndef HASH_H
#define HASH_H
#define HT_INITIAL_BASE_SIZE 100
#define HT_PRIME_1 61
#define HT_PRIME_2 53
#endif