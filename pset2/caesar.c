// give user cipher text.. from plaintext..
# include <stdio.h>
# include <cs50.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

int main(int argc, string argv[])
{
    int key;                    // global variable;
    string plaintext;
    string temp_plaintext;
    int ascii;
    int ascii_to_num;
    int adding_key;
    int num_to_ascii;
    char ciphertext;


    if (argc == 2)          // checking command argument equal to 2
    {
        key = atoi(argv[1]);    // using function atoi to convert string to int;

    }
    else
    {
        printf("Give me a key\n");      // error checking
        return 1;
    }
    printf("Plaintext: ");
    plaintext = get_string("");

    temp_plaintext = plaintext;
    printf("ciphertext: ");

    for (int i = 0 ; i < strlen(temp_plaintext); i++)       // converting normal text to cipher text
    {
        if (isalpha(temp_plaintext[i]))     // checking char is alphabet or not
        {
            if (islower(temp_plaintext[i]))     // checking alphabet is lower or not;
            {
                ascii = (int)temp_plaintext[i];     //converting char to ascii number;
                ascii_to_num = (ascii - 97) % 26;   // converting ascii to numberical index
                adding_key = (ascii_to_num + key)% 26;  // adding key to number;
                num_to_ascii = (adding_key + 97);       // converting number to ascii
                ciphertext = (char) num_to_ascii;       // converting ascii to char;
                printf("%c", ciphertext);
            }
            if (isupper(temp_plaintext[i]))     // checking char is upper or not;
            {
                ascii = (int)temp_plaintext[i];     // same as above;
                ascii_to_num = (ascii - 65) % 26;
                adding_key = (ascii_to_num + key)%26;
                num_to_ascii = adding_key + 65;
                ciphertext = (char) num_to_ascii;
                printf("%c", ciphertext);
            }
        }
        else
        {
            ciphertext = temp_plaintext[i];     // passing char other than alphabet i.e, numbers
            printf("%c", ciphertext);
        }
    }

    printf("\n");
    return 0;       //return from main function;
}