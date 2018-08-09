# include <stdio.h>
# include <cs50.h>
# include <ctype.h>
# include <string.h>

int main(int argc, string argv[])
{
    string key_word;
    string temp_key;
    int num_key_word;
    string plaintext;
    int plaintext_to_ascii;
    int num_to_ascii;
    int ascii_to_num;
    int ascii;
    char ciphertext;
    int counter = 0;

    if (argc == 2)
    {
        key_word = argv[1];
    }
    else
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    temp_key = key_word;
    for (int i= 0; i<strlen(key_word); i++)
    {
        if (isalpha(key_word[i]))
        {
            temp_key = key_word;
        }
        else
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }
    printf("plaintext: ");
    plaintext = get_string("");
    printf("ciphertext: ");

    for (int j = 0; j<strlen(plaintext); j++)
    {
        if (counter == strlen(temp_key))
        {
            counter = 0;
        }
        if (isalpha(plaintext[j]))
        {
            plaintext_to_ascii = (int) plaintext[j];
            if (isupper(temp_key[counter]))
                {
                    if (isupper(plaintext[j]))
                    {
                        ascii_to_num = (plaintext_to_ascii - 65) % 26;
                        num_key_word = ((int) temp_key[counter] - 65)% 26;
                        ascii = (ascii_to_num + num_key_word)% 26;
                        num_to_ascii = ascii + 65;
                        ciphertext = (char) num_to_ascii;
                        counter ++;
                        printf("%c", ciphertext);
                    }
                    else
                    {
                        ascii_to_num = (plaintext_to_ascii - 97) % 26;
                        num_key_word = ((int) temp_key[counter] - 65)% 26;
                        ascii = (ascii_to_num + num_key_word)% 26;
                        num_to_ascii = ascii + 97;
                        ciphertext = (char) num_to_ascii;
                        counter ++;
                        printf("%c", ciphertext);
                    }
                }

            else
                {
                    if (isupper(plaintext[j]))
                    {
                        ascii_to_num = (plaintext_to_ascii - 65) % 26;
                        num_key_word = ((int) temp_key[counter] - 97)% 26;
                        ascii = (ascii_to_num + num_key_word)% 26;
                        num_to_ascii = ascii + 65;
                        ciphertext = (char) num_to_ascii;
                        counter ++;
                        printf("%c", ciphertext);
                    }
                    else
                    {
                        ascii_to_num = (plaintext_to_ascii - 97) % 26;
                        num_key_word = ((int) temp_key[counter] - 97)% 26;
                        ascii = (ascii_to_num + num_key_word)% 26;
                        num_to_ascii = ascii + 97;
                        ciphertext = (char) num_to_ascii;
                        counter ++;
                        printf("%c", ciphertext);
                    }
                }

        }
        else
        {
            ciphertext = plaintext[j];
            printf("%c", ciphertext);
        }
    }

    printf("\n");
    return 0;
}