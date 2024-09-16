#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


//this first part gonna make our base structture for our hashtable algorithm
//were gonna make the item struct that gonna store our key and value
//and then were gonna making the hash table with the size, counter, and pointer to our item

//this going to set our item and allocated it into another chunk of memory
static item* new_item(const char* k , const char* v) //this one gonna declare the function
{
    item* i = malloc(sizeof(item)); //this one gonna make i variable with type of item that we make before and pointing it into a new item struct 
    i ->key = strdup(k); //this one gonna copy string k and allocated it in to key
    i ->value = strdup(v); // same like the above, this one gonna copy v and allocated it into value
    return i;
}

//now were going to set our hash table
hash_table* new_ht(void)
{
    hash_table* ht = malloc(sizeof(hash_table)) //this one gonna allocated. yeah you know what this do
    {
        ht ->size = 10; //setting the size into 10
        ht ->count = 0; //setting the count into 0 since theres no item stored
        ht -> items = calloc((size_t)ht ->size, sizeof(item*)); //this one gonna derefrence items and make another memory with size of item and with the number of size
        return ht;
    }
}

//another fucntion that we need is a fucnt that can delete an item in our hashtable and also a fucntion that can delete the entire table
//so were making a fuction that freeing memory by deleteing the hash_table and items

static void del_item(item* i) //a fucntion that we make to delete one item
{
    free(i->key); //freeing the key
    free(i->value); //freeing the value
    free(i); //freeing the item
}

void del_hash_table(hash_table* ht) //fucntion that we make to delete entire hash table
{
    for (int i = 0; i < ht->size; i++)  //a loop that gonna check all the table
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


// so now were done with the basic structure of hash function, we got the item struct, the hash table, and function that can clean our item and hash table
//the next step is the hash code so now we can do the hashing procces
/*this code shoul do"
1. Take a string as its input and return a number between 0 and m, our desired bucket array length.
2. return the index evenly for an average input, so we can get lower chance for collisions*/
//at this case were gonna hashing using the polynomial rolling method that use addition and multiplication(look at the hash code function pict)

static int hash_code(char* s, const int p, const int b) //p is the prime number, b is the bucket size
{
    long hash = 0; //variable that were gonna return later
    const int string_len = strlen(s); //string length for the formula
    for (int i = 0; i < string_len; i++) //loop for the summation formula
    {
        hash += (long) pow(p, string_len - (i+1)) * s[i]; //the formula
        hash = hash % b; //were taking the modulo so were having integer that never more than our bucket size
    }
    return (int)hash; //returning hash (obviusly)
}
// we have our hash code now to let us do the hashing


/* this one is our hashing method with double hashing
using double hashing were gonna use our hash code again after the collisions happen then return the index*/
//or simply like this -> index = hash_a(string) + i * hash_b(string + 1) % num_buckets

static int get_hash(const char* s, const int num_bucket, const int attempt)
{
    const int hash_a = hash_code(s, HT_PRIME_1, num_bucket);
    const int hash_b = hash_code(s, HT_PRIME_2, num_bucket);
    unsigned int index = (hash_a + (attempt * (hash_b + 1))) % num_buckets;
    return index;
}//honestly idont want to explain all of these, so good luck me in the future


//now were going to make another funct(inserting, searching, etc.)

//inserting: were iterating trhough table and insert the item, then we increment the count

void insert(hash_table* ht, const char* key, const char* value)
{
    item* i_item = new_item(key, value); //creating item that store key and value
    int index = get_hash(i_item -> key, ht -> size, 0); //initializing the first hash
    item* current_item = ht -> items[index]; //checking if theres an item in current index
    int i = 1;
    while (current_item != NULL)//the while loop, if the current item is not null mean its occupied
    {
        index = get_hash(i_item -> key, ht -> size, i); // adjusting the loop to find a new plpace in hash table using the i
        current_item = ht -> items[index]; // do another hashing to check the next potential slot 
        i++;//incrementing the i
    }
    ht -> items[index] = i_item; //storing the item in the final index
    ht -> count++; //incrementing count
}//now we have our insert funtion


//searching: were looping trhough table just like insert, if there macth item key, were then gonna return the item value, if the loop hits null then we return null
char* search(hash_table ht, const char* key)
{
    int index = get_hash(key, ht ->size, 0);
    item* s_item = ht -> item
}



