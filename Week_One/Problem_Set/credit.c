#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    long cardNumber;

    do
    {
        cardNumber = get_long("Card Number?");
    }
    while(cardNumber < 1);

    long cardNumberCopy = 0;
    int cardLength = 0;
    int sumOfNonMultiplied;
    int sumBit;
    int carryBit;
    int sumOfMultiplied = 0;
    int totalSumValidated;
    long cardNumberCopyTwo = cardNumber;
    bool notAmex = false;
    bool notMastercard = false;
    bool notVisa = false;

    while(cardNumber > 0)
    {
        //Start card length counter up here to use as if else modulo / counter for card length
        cardLength++;

        //Take last digit of card number, example 4 in 4003600000000014
        cardNumberCopy = cardNumber % 10;

        //Every other starting from right most
        if(cardLength % 2 == 0)
        {
            //Multiply by two
            cardNumberCopy *= 2;

            //Handle carry bit if sum is overflowed
            //Storing sum in one variable and carry in another adding them and bringing them back together
            if(cardNumberCopy > 9)
            {
                //Right most bit used then knocked off
                sumBit = cardNumberCopy % 10;
                cardNumberCopy /=10;
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


        //Knock off right most digit and repeat the process
        cardNumber = cardNumber / 10;

    }
    //Now take everything, add it together and modulo again to check that last digit is zero
    totalSumValidated = ((sumOfNonMultiplied + sumOfMultiplied) % 10);

    //Now that card is valid and we have length, we need to figure out who the issuer is
    while(cardNumberCopyTwo > 0)
    {
        if((cardNumberCopyTwo % 100 == 51 || cardNumberCopyTwo % 100 == 52 || cardNumberCopyTwo % 100 == 53 || cardNumberCopyTwo % 100 == 54 || cardNumberCopyTwo % 100 == 55) && cardNumberCopyTwo < 99 && cardLength == 16 && totalSumValidated == 0)
        {
            //Mastercard
            printf("MASTERCARD\n");
            notMastercard = true;
        }
        else if((cardNumberCopyTwo % 100 == 34 || cardNumberCopyTwo % 100 == 37) && cardNumberCopyTwo < 99 && cardLength == 15 && totalSumValidated == 0)
        {
            //Amex
            printf("AMEX\n");
            notAmex = true;
        }
        else if((cardNumberCopyTwo % 10 == 4) && cardNumberCopyTwo < 10 && (cardLength == 13 || cardLength == 16) && totalSumValidated == 0)
        {
            //Visa
            printf("VISA\n");
            notVisa = true;
        }
        cardNumberCopyTwo /= 10;
    }
    if((totalSumValidated != 0) || (cardLength == 14) || (cardLength > 16) || (cardLength < 13) || (notAmex == true && notMastercard == true && notVisa == true))
    {
        printf("INVALID\n");
    }
}


