// Implements a dictionary's functionality
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

typedef struct node
    {
        string word[LENGTH + 1];
        struct node *next;
    }
    node;

node *hashtable[26];
int size_of_dict = 0;
int hash_table(char word)  //create hash table;
{
    char f_char = word;
    int ascii_char = (int) f_char;
    int hash_t;
    if (isupper(f_char))
    {
        hash_t = ascii_char - 65;

    }
    if (islower(f_char))
    {
        hash_t = ascii_char - 97;
    }

    return hash_t;
}
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';
    int c_hash = hash_table(temp[0]);
    node *cursor = hashtable[c_hash];
    if (!cursor)
    {
        return false;
    }
    while(!cursor)
    {
        if (strcmp((word),(cursor->word)) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *dict;
    dict = fopen(dictionary, "r");

    char word[LENGTH + 1];
    //scan dictionary word by word;
    while (fscanf(dict, "%s", word) != EOF)
    {
        //malloc space for new node; //if malloc return null then return unload; // implement hashtable // word into linked list;    // last pointer into null

        int hash = hash_table(word[0]);
        if (hash < 0 || hash > 25)
        {
            return false;
        }
        node *words = hashtable[hash];
        bool found = false;
        // checking word in in the linked list
        for (node *ptr = words; ptr != NULL; ptr=ptr->next)
        {
            if(ptr->word == word)
            {
                found = true;
                break;
            }
        }
        // adding new word in list
        if (!found) // if found is false
        {
            // adding new node
            node *new_node = malloc(sizeof(node));
            if(!new_node)
            {
                break;
                return 2;
            }
            strcpy(new_node->word , word);
            new_node->next = hashtable[hash];
            hashtable[hash] = new_node;
            if (words)
            {
                for (node *ptr = words; ptr != NULL; ptr = ptr->next)
                {
                    if (!ptr->next)
                    {
                        ptr->next = new_node;
                        break;
                    }
                }
            }
            else
            {
                words = new_node;
            }
        }
        size_of_dict ++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(size_of_dict==0)
    {
        return 0;
    }
    else
    {
        return size_of_dict;

    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int hash = 0;
    int Size = size();
    node *ptr = hashtable[hash];
    while (hash < Size)
    {
        if (!ptr)
        {
            hash ++;
        }
        else
        {
            while(ptr)
            {
                node *next = ptr->next;
                free(ptr);
                ptr = next;
            }
            hash ++;
        }
    }
    return true;
}