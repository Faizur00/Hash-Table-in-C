#include "hash.h"
#include "prime.h"
#include <stdio.h>

int main (void)
{   
    hash_table* ht = ht_new();   
    insert(ht, "num1", "one");
    insert(ht, "num2", "two");
    insert(ht, "num3", "trhee");
    insert(ht, "num4", "four");
    insert(ht, "num5", "five");
    insert(ht, "num6", "six");
    insert(ht, "num7", "seven");
    insert(ht, "num8", "eight");
    insert(ht, "num9", "nine");
    printf("\n");



    for (int i = 0; i < ht -> base_size; i ++)
    {
        if ( ht -> items[i] != NULL)
        {
            printf("%s  ", ht->items[i]-> value);
        }
    }
    printf("\nsize now is %i \n",ht -> base_size);
}