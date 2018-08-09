# include <stdio.h>
# include <cs50.h>
# include <stdlib.h>
# include <string.h>
# define _XOPEN_SOURCE       /* See feature_test_macros(7) */
# include <unistd.h>

int main(int argc, string argv[])
{
    string hashed_password;             // global variable
    string password;
    string x;
    char temp_pass[];

    if (argc == 2)
    {
        hashed_password = argv[1];
    }
    else
    {
        printf("Give me a hashed password.\n");
        return 1;
    }
    
    
    


    return 0;
}