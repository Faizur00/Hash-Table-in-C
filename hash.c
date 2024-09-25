#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash.h"
#include "prime.h"

//defining a global variable for deleted item
static item DELETED_ITEM = {NULL, NULL};
// make our base structture for our hashtable algorithm
//make the item struct that gonna store our key and value
//making the hash table with the size, counter, and pointer to our item

//this going to set our item and allocated it into another chunk of memory
static item* new_item(const char* k , const char* v) //this one gonna declare the function
{
    item* i = malloc(sizeof(item)); //this one gonna make i variable with type of item that we make before and pointing it into a new item struct 
    i ->key = strdup(k); //this one gonna copy string k and allocated it in to key
    i ->value = strdup(v); // same like the above, this one gonna copy v and allocated it into value
    return i;
}

//now were going to set our hash table
static hash_table* new_sized(const int base_size)
{
    hash_table* ht = malloc(sizeof(hash_table)); 
    ht -> base_size = base_size;
    ht -> base_size = next_prime(base_size); //setting the size into base size

    ht -> count = 0; //setting the count into 0 since theres no item stored
    ht -> items = calloc((size_t)ht ->base_size, sizeof(item*)); //this one gonna derefrence items and make another memory with size of item and with the number of size
    return ht;
}

//make the updater for sie of the hash table using tmp table
hash_table* ht_new(void)
{
    return new_sized(HT_INITIAL_BASE_SIZE);
}

//making the rezise funct
static void resize_table(hash_table* ht, const int base_size)
{
    if (base_size < HT_INITIAL_BASE_SIZE)
    {
        return;
    }
//inserting all element to the new table
for (int i = 0; i< ht -> base_size; i++)
{
    item* item = ht->items[i];
    if (item != NULL && item != &DELETED_ITEM)
    {
        hash_table* new_ht = ht_new();
        insert(new_ht, item ->key, item -> value);
    }
}
//copying the info of the size and coutn to the new table
hash_table* new_ht = ht_new();
ht -> base_size = new_ht -> base_size;
ht -> count = new_ht -> count;

//updating the real table size 
const int tmp_size = ht -> base_size;
ht ->base_size = new_ht -> base_size;
new_ht -> base_size = tmp_size;

item** tmp_items = ht -> items;
ht -> items = new_ht -> items;
new_ht -> items = tmp_items;

//deleting the new table
del_hash_table(new_ht);
}
//another fucntion that we need is a fucnt that can delete an item in our hashtable and also a fucntion that can delete the entire table
//so were making a fuction that freeing memory by deleteing the hash_table and items

//making new resize funct with resize up and down
static void resize_up(hash_table* ht)
{
    const int new_size = ht -> base_size * 2;
    resize_table(ht, new_size);
}

static void resize_down(hash_table* ht)
{
    const int new_size = ht -> base_size /2;
    resize_table(ht, new_size);
}

//making function that can delete single item in table
static void del_item(item* i)
{
    free(i->key); //freeing the key
    free(i->value); //freeing the value
    free(i); //freeing the item
}

void del_hash_table(hash_table* ht)//making function that can delete entire table

{
    for (int i = 0; i < ht->base_size; i++)  //a loop that gonna check all the table
    {
        item* checker = ht->items[i]; //declareng variable to make the checker faster
        if (checker != NULL) //if we having a non null/ if we having an item in our table
        {
            del_item(checker); //were gnna delete it
        }
    }
    free(ht->items); //now were freeing the items
    free(ht); //this funct freeing the ht taht we make before so now its completly removed
}


//making hash code
/*this code do:
1. Take a string as its input and return a number between 0 and m, our desired bucket array length.
2. return the index evenly for an average input, so we can get lower chance for collisions*/
//at this case were gonna hashing using the polynomial rolling method that use addition and multiplication(look at the hash code function pict)

static int hash_code(const char* s, const int prime, const int bucket) //p is the prime number, b is the bucket size
{
    long hash = 0; //variable that were gonna return later
    const int string_len = strlen(s); //string length for the formula
    for (int i = 0; i < string_len; i++) //loop for the summation formula
    {
        hash += (long) pow(prime, string_len - (i+1)) * s[i]; //the formula
        hash = hash % bucket; //were taking the modulo so were having integer that never more than our bucket size
    }
    return (int)hash; //returning hash (obviusly)
}
// we have our hash code now to let us do the hashing


/* this one is our hashing method
using double hashing were gonna use our hash code again after the collisions happen then return the index*/
//or simply like this -> index = hash_a(string) + i * hash_b(string + 1) % num_buckets

static int get_hash(const char* s, const int num_bucket, const int attempt)
{
    const int hash_a = hash_code(s, HT_PRIME_1, num_bucket);
    const int hash_b = hash_code(s, HT_PRIME_2, num_bucket);
    int index = (hash_a + (attempt * (hash_b + 1))) % num_bucket; 
    return index;
}//honestly idont want to explain all of these, so good luck me in the future


//now were going to implement our hash before (inserting, searching, etc.)
//inserting: were iterating trhough table and insert the item, then we increment the count
void insert(hash_table* ht, const char* key, const char* value)
{
    //making sure we dont do floating number math
    const int load = ht -> count * 100 /  ht -> base_size;
    if (load > 70)
    {
        resize_up(ht);
    }
 
    item* i_item = new_item(key, value); //creating item that store key and value
    int index = get_hash(i_item -> key, ht -> base_size, 0); //initializing the first hash
    item* current_item = ht -> items[index]; //checking if theres an item in current index
    int i = 1;
    while (current_item != NULL && current_item != &DELETED_ITEM)//the while loop, if the current item is not null mean its occupied
    {
        if (current_item != &DELETED_ITEM)
        {
            if (strcmp(current_item -> key, key) == 0)
            {
                del_item(current_item);
                ht -> items[index] = i_item;
                return;
            }
        }
        index = get_hash(i_item -> key, ht -> base_size, i); // adjusting the loop to find a new plpace in hash table using the i
        current_item = ht -> items[index]; // do another hashing to check the next potential slot 
        i++;//incrementing the i
    }
    ht -> items[index] = i_item; //storing the item in the final index
    ht -> count++; //incrementing count
}//now we have our insert funtion


//searching: were looping trhough table just like insert, if there macth item key, were then gonna return the item value, if the loop hits null then we return null
char* search(hash_table* ht, const char* key)
{
    int index = get_hash(key, ht->base_size, 0); //intializing the index
    item* s_item = ht -> items[index]; //making item based on the index
    int i = 1;
    while (s_item != NULL) // looping trhough table
    {
        if (s_item != &DELETED_ITEM)
        {
            if (strcmp(s_item -> key, key) == 0) //comparing the item key with the key on item that on the table
            {
                return s_item -> value; 
            }
        }
        index = get_hash(key, ht -> base_size, i); //updating the index
        s_item = ht -> items[index];
        i++;
    }
    return NULL; //returning null if theres no macthing key
}

//deleting : we only mark the item on table as deleted since its too complicated to literally delete an item 

//making delete function that mark the item as "deleted"
void delete(hash_table* ht, const char* key) 
{
    //making sure we dont do floating number under 0.1 math in delete funct
    const int load = ht -> count * 100 / ht -> base_size;
    if (load < 10)
    {
        resize_down(ht);
    }

    int index = get_hash(key, ht -> base_size, 0);
    item* d_item = ht -> items[index];
    int i = 1;
    while (d_item != NULL)
    {
        if (strcmp(d_item -> key, key) == 0)
        {
            del_item(d_item);
            ht -> items[index] = &DELETED_ITEM;
        }
        index = get_hash(key, ht -> base_size, i);
        d_item = ht -> items[index];
        i++;
    }   
    ht -> count--; 
}

int main (void)
{
    return 0;
}