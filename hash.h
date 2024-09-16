//this make a struct for the item taht will store the value and our key
typedef struct
{
    char* key;
    char* value;
}item;

//this one gonna make our hash table
typedef struct
{
    int size;
    int count;
    item** items;
}hash_table;