#include <cs50.h>
#include <stdio.h>

int getNumberLenght(long number)
{
    int i = 0;
    int lenght = 1;
    while (number / 10 > 0)
    {
        number = number / 10;
        lenght++;
    }
    return (lenght);
}

int getLastNDigits(long number, int n)
{
    int i = 0;
    int lenght = getNumberLenght(number);
    int remainingLength = lenght;

    while (number / 10 > 0)
    {
        number = number / 10;
        remainingLength--;
        if (remainingLength == n)
        {
            return (number);
        }
    }
    return (0);
}

int getSumOfEverySecondsProduct(long number)
{
    int i = 0;
    int sumOfEachSedond = 0;
    int length = getNumberLenght(number);

    while (i <= length)
    {
        number = number / 10;
        int newNum = (number % 10) * 2;

        if (newNum > 9)
        {
            while (newNum > 9)
            {
                sumOfEachSedond += newNum % 10;
                newNum = newNum / 10;
            }
            sumOfEachSedond += newNum;
        }
        else
        {
            sumOfEachSedond += newNum;
        }
        number = number / 10;
        i++;
    }
    return (sumOfEachSedond);
}

int getSumOfOtherNums(long number)
{
    int i = 0;
    int sumofOtherNums = 0;
    int length = getNumberLenght(number);

    while (i < length)
    {
        int newNum = (number % 10);
        sumofOtherNums += newNum;
        number = number / 10;
        number = number / 10;
        i++;
    }
    return (sumofOtherNums);
}

int isAmericanExpress(long number)
{
    // 15 and start with 34 or 37
    int length = getNumberLenght(number);
    if (length != 15)
    {
        return (0);
    }
    int lastDigit = getLastNDigits(number, 2);
    if (lastDigit == 34 || lastDigit == 37)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int isVisa(long number)
{
    int length = getNumberLenght(number);
    if (length != 13 && length != 16)
    {
        return (0);
    }
    int lastDigit = getLastNDigits(number, 1);
    if (lastDigit == 4)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int isMaster(long number)
{
    // 16 numbers & starts with 51, 52, 53, 54, or 55
    int length = getNumberLenght(number);
    if (length != 16)
    {
        return (0);
    }
    int lastDigit = getLastNDigits(number, 2);
    if (lastDigit >= 51 && lastDigit <= 55)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int main(void)
{
    // get number from user
    long number = get_long("Number: ");
    // get the sum of the digits of each second number multiplied by two
    int sumOfEachSedond = getSumOfEverySecondsProduct(number);
    // get the sum of all other digits
    int sumofOtherNums = getSumOfOtherNums(number);
    // get the checkSum
    int checkSum = sumofOtherNums + sumOfEachSedond;

    // Validation checks
    if (checkSum % 10 == 0)
    {
        if (isVisa(number) == 1)
        {
            printf("VISA\n");
        }
        else if (isMaster(number) == 1)
        {
            printf("MASTERCARD\n");
        }
        else if (isAmericanExpress(number) == 1)
        {
            printf("AMEX\n");
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