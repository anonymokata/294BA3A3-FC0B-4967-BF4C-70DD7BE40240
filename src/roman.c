#include "roman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int args_valid(const char* num1, const char* num2)
{
    //check for null inputs
    if ((num1 == 0) || (num2 == 0))
        return 0;
    
    //check for empty inputs
    if ((num1[0] == 0) || (num2[0] == 0))
        return 0;
    
    return 1;
}

static const char* expander(const char* num)
{
    if (strcmp(num, "IV") == 0)
        num = "IIII";
    else if (strcmp(num, "V") == 0)
        num = "IIIII";
    return num;
}

static char* compactor(char* retval)
{
    size_t len = strlen(retval);
    char* ptr1 = retval;
    char* ptr2 = retval;
    int i;
    int count = 0;
    
    while (*ptr1 != 0)
    {
        if (*ptr1 == 'I')
        {
            count++;
            if (count == 5)
            {
                count = 0;
                *ptr2++ = 'V';
            }
        }
        else
            count = 0;
        ptr1++;
    }
    if (count == 4)
    {
        *ptr2++ = 'I';
        *ptr2++ = 'V';
    }
    else
    {
        for (i=0; i < count; i++)
            *ptr2++ = 'I';
    }
    *ptr2++ = 0;
    return retval;
}

const char* roman_add(const char* num1, const char* num2)
{
    char* retval;
    size_t len1, len2, newlen;
    
    if (!args_valid(num1, num2))
        return 0;
    
    //expand if needed
    num1 = expander(num1);
    num2 = expander(num2);
    
    //grab lengths and allocate enough memory for us to build the final string
    len1 = strlen(num1);
    len2 = strlen(num2);
    newlen = len1 + len2;
    retval = malloc(newlen + 1);
    
    //concat the two strings to get added string
    sprintf(retval, "%s%s", num1, num2);
    
    return compactor(retval);
}
