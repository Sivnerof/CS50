#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* 
An application that uses Luhn's algorithm to validate a credit card number,
and checks who the issuer is.

This was a real headache to code without the use of arrays or functions.
But was definetly worth it. 
*/

int main(void)
{
    long cardNumber;

    do
    {
        cardNumber = get_long("Card Number?");
    }
    while (cardNumber < 1);

    long cardNumberCopy = 0;
    int cardLength = 0;
    int sumOfNonMultiplied;
    int sumBit;
    int carryBit;
    int sumOfMultiplied = 0;
    int totalSumValidated;
    bool isAmex = false;
    bool masterCard = false;
    bool isVisa = false;

    while (cardNumber > 0)
    {
        //Start card length counter up here to use as if else modulo / counter for card length
        cardLength++;

        //Take last digit of card number, example 4 in 4003600000000014
        cardNumberCopy = cardNumber % 10;

        //Every other starting from right most
        if (cardLength % 2 == 0)
        {
            //Multiply by two
            cardNumberCopy *= 2;

            //Handle carry bit if sum is overflowed
            //Storing sum in one variable and carry in another adding them and bringing them back together
            if (cardNumberCopy > 9)
            {
                //Right most bit used then knocked off
                sumBit = cardNumberCopy % 10;
                cardNumberCopy /= 10;

                //Now repeated with the left bit
                carryBit = cardNumberCopy % 10;
                cardNumberCopy = sumBit + carryBit;
            }

            //Result is stored in the sum of all others to be multiplied
            sumOfMultiplied += cardNumberCopy;

        }

        //Here we take the ones we never multiplied and just add them together
        else
        {
            sumOfNonMultiplied = sumOfNonMultiplied + cardNumberCopy % 10;

        }

        //Here we set some booleans to true if the first two digits seem to belong to a certain issuer

        //Mastercard
        if ((cardNumber % 100 == 51 || cardNumber % 100 == 52 || cardNumber % 100 == 53 || cardNumber % 100 == 54
             || cardNumber % 100 == 55) && cardNumber < 99)
        {
            masterCard = true;
        }

        //American Express
        else if ((cardNumber % 100 == 34 || cardNumber % 100 == 37) && cardNumber < 99)
        {

            isAmex = true;
        }

        //Visa, here we use mod and card number length 10 instead because Visa is recognized by the single digit 4
        else if ((cardNumber % 10 == 4) && cardNumber < 10)
        {
            isVisa = true;
        }


        //Knock off right most digit and repeat the process
        cardNumber = cardNumber / 10;

    }
    //Now take everything, add it together and modulo again to check that last digit is zero
    totalSumValidated = ((sumOfNonMultiplied + sumOfMultiplied) % 10);

    //Final verification process
    if (totalSumValidated == 0)
    {
        if (masterCard == true && cardLength == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (isAmex == true && cardLength == 15)
        {
            printf("AMEX\n");
        }
        else if (isVisa == true && (cardLength == 13 || cardLength == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}