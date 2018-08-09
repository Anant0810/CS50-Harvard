// Helper functions for music

#include <cs50.h>
#include <string.h>
#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    if (fraction[2] == '8')  // comparing fraction denominator to '8'
    {
        string poss_num = "12345678";   //possibilities of numerator with 8 in denominator 1/8, 2/8, 3/8, 4/8, 5/8, 6/8, 7/8, 8/8;
        for (int i  = 0; i<strlen(poss_num); i++)
        {
            if (fraction[0] == poss_num[i]) // comparing numerator with possibility by for loop;
            {
                int a = poss_num[i] - '0';  // ascii code offset  converting the pointer or string to integer by subtracting it to '0'
                return a;
            }
        }
    }
    else if (fraction[2] == '4')
    {
        string poss_num = "1234"; // possibilities of numerator with 4 in denominator 1/4, 2/4, 3/4, 4/4;
        for (int i  = 0; i<strlen(poss_num); i++)
        {
            if (fraction[0] == poss_num[i])
            {
                int a = poss_num[i] - '0';  // Same as above;
                int b = a*2;
                return b;
            }
        }
    }
    else if (fraction[2] == '2')
    {
        return 4;
    }
    else if(fraction[2] == '1')
    {
        return 8;
    }
    return 0;
}


// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int octave;
    double frequency;


    if (strlen(note) == 2)
    {
        octave = note[1] - '0';
    }
    else
    {
        octave = note[2] - '0';
    }
    if (note[0] == 'C')
    {
        frequency = 440 / pow(2.0, 9.0/12.0);
    }
    if (note[0] == 'D')
    {
        frequency = 440 / pow(2.0, 7.0/12.0);
    }
    if (note[0] == 'E')
    {
        frequency = 440 / pow(2.0, 5.0/12.0);
    }
    if (note[0] == 'F')
    {
        frequency = 440 / pow(2.0, 4.0/12.0);
    }
    if (note[0] == 'G')
    {
        frequency = 440 / pow(2.0, 2/12.0);
    }
    if (note[0] == 'A')
    {
        frequency = 440;
    }
    if (note[0] == 'B')
    {
        frequency = 440 * pow(2.0, 2.0/12.0);
    }
    if (note[1] == '#')
    {
        frequency = frequency * pow(2.0, (1.0/12.0));
    }
    if (note[1] == 'b')
    {
        frequency = frequency / pow(2.0, (1.0/12.0));
    }

    if (octave > 4)
    {
        for (int i = 0; i < (octave)- 4; i++)
        {
            frequency *= 2.0;
        }
    }
    if (octave < 4)
    {
        for (int i = 4 ; i > (octave) ; i--)
        {
            frequency /=2.0;
        }
    }

    int freq = round(frequency);

    return freq;


}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
