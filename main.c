#include "hash.h"
#include "prime.h"
#include <stdio.h>

int main (void)
{   
    hash_table* ht = ht_new();
    insert(ht, "name", "faiz");
    insert(ht, "city", "mks");
    insert(ht, "age", "19");
    insert(ht, "drink", "coke");
    insert(ht, "food", "burger");    
    insert(ht, "num1", "one");
    insert(ht, "num2", "two");
    insert(ht, "num3", "trhee");


    for (int i = 0; i < ht -> base_size; i ++)
    {
        if ( ht -> items[i] != NULL)
        {
            printf("%s  ", ht->items[i]-> value);
        }
    }
}