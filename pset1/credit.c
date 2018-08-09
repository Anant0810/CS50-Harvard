# include <stdio.h>
# include <cs50.h>
# include <ctype.h>

// American Express numbers all start with 34 or 37 ;15-digit numbers;
// MasterCard numbers all start with 51, 52, 53, 54, or 55; 16-digit numbers;
// Visa numbers all start with 4. 13- and 16-digit numbers.;


int main(void)
{

    long long card_number;
    long long temp_card;
    int digits;
    long long company_id;

    do
    {
        card_number = get_long_long("Card Number: "); // taking input from user.

    }
    while ( 0ll > card_number || card_number > 9999999999999999ll);// validating user input

    temp_card = card_number;
    digits = 0;

    while (temp_card > 0)         // to find digits in Credit card-numbers digits.
    {
        digits++;
        temp_card = temp_card/10;
    }


    company_id = card_number;

    while (company_id > 100)
    {
         company_id /= 10;

    }
    //printf("The Credit Card has %i digits.\n", digits);

// American Express numbers all start with 34 or 37 ;15-digit numbers;
// MasterCard numbers all start with 51, 52, 53, 54, or 55; 16-digit numbers;
// Visa numbers all start with 4. 13- and 16-digit numbers.;

    long long temp_x2 = card_number;
    int sum_digit = 0;
    int sum_other_digit = 0;
    int other_digit_by_2;





    for (int i = 0 ; i < digits; i++)
    {
        if (i % 2 == 0)
        {
            int digit;
            digit = temp_x2 % 10;
            sum_digit += digit;
            //printf("digit: %i\n", digit);
        }

        if (i % 2 != 0)
        {
            int other_digit;
            other_digit = temp_x2 % 10;
            other_digit_by_2 = other_digit * 2;
            if (other_digit_by_2)
            sum_other_digit += other_digit_by_2;



        }
        temp_x2 = temp_x2/10;
        //printf("temp_x: %lli\n", temp_x2);

    }
    sum_other_digit = sum_other_digit;
    printf("Sum of digit: %i\n", sum_digit);
    printf("Sum of other digit: %i\n", sum_other_digit );
//https://github.com/callahanchris/CS50/blob/master/pset1/credit%20card.c

    int sum_of_digits;

    sum_of_digits = sum_digit + sum_other_digit;
    printf("Sum of both digits: %i\n", sum_of_digits);

    if (sum_of_digits % 10 == 0)
    {
            //printf("This is a valid Card.\n");
        if (digits == 15 && (company_id == 34 || company_id == 37))
        {
            printf("AMEX\n");
        }
        else if (digits == 16 && (company_id == 51 || company_id == 52 || company_id == 53 || company_id == 54 || company_id == 55))
        {
            printf("MASTERCARD\n");

        }
        else if ((digits == 13 || digits == 16) &&(company_id/10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}