# include <stdio.h>
# include <cs50.h>

// take and validate the user data
// the pyramid should be more than 0 and less than 23.
// then draw the pyramid.

int main(void)
{
    int height;
    do
    {
        height = get_int("Height of the Pyramid: "); // taking users input and storing in height.
    }
    while(0 > height || height > 23);      // validating the users input.


    for(int i = 0 ; i < height ; i++)       // to draw pyramid. i equal to the # in a line and h - i equal to the space.
    {
        for(int j = 0 ;j < height - i - 1; j++ )    // for the space. Right side of pyramid (h - i).
        {
            printf(" ");
        }
        for(int k = 0; k <= i; k++)              // for the pyramid. Right side of pyramid  (i).
        {
            printf("#");
        }
        printf(" ");                        // for the space. Middle part.
        printf(" ");                        // for the space. Middle part.
        for(int l = 0; l <= i; l++)
        {
            printf("#");                    //for the pyramid. Left side of the pyramid. (i)
        }
        printf("\n");

    }



}
