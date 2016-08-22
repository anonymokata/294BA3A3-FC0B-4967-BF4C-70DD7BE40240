#include "roman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _SIMPLIFICATION_T 
{
    const char* wide;
    const char* narrow;
} SIMPLIFICATION_T;

static int match_len(const char* find, const char* num)
{
    int len = 0;
    while (*find != 0)
    {
        if (*find++ != *num++)
            return 0;
        len++;
    }
    return len;
}

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
    if (strcmp(num, "XL") == 0)
        num = "XXXX";
    if (strcmp(num, "LXL") == 0)
        num = "LXXXX";
    return num;
}

static char* merge(const char* num1, const char* num2)
{
    const char ordered[] = { 'L', 'X', 'V', 'I' };
    size_t len1, len2;
    size_t i;
    char* retval;
    char* ptr;
    
    len1 = strlen(num1);
    len2 = strlen(num2);
    retval = malloc(len1 + len2 + 1);
    ptr = retval;
    
    for (i=0; i < DIMENSION_OF(ordered); i++)
    {
        char letter = ordered[i];
        while (*num1 == letter)
            *ptr++ = *num1++;
        while (*num2 == letter)
            *ptr++ = *num2++;
    }
    *ptr = 0;
    
    return retval;
}

static char* simplify(char* retval, const SIMPLIFICATION_T* simplifications, const int num_simplifications)
{
    char* ptr1 = retval;
    char* ptr2 = retval;
    char* last = 0;
    int i;
    
    while (*ptr1 != 0)
    {
        for (i=0; (i < num_simplifications && (last != ptr1)); i++)
        {
            int len = match_len(simplifications[i].wide, ptr1);
            if (len > 0)
            {
                const char* narrow = simplifications[i].narrow;
                while (*narrow)
                {
                    *ptr2++ = *narrow++;
                }
                ptr1 += (len - 1);
                last = ptr1;
                break;
            }
        }
        if (last != ptr1)
        {
            *ptr2++ = *ptr1;
        }
        ptr1++;
    }
    *ptr2 = 0;
    
    if (last != 0)
        retval = simplify(retval, simplifications, num_simplifications);
    
    return retval;
}

static char* compactor(char* retval)
{
    const SIMPLIFICATION_T simplifications_adders[] =
    {
        { "IIIII", "V" },
        { "VV",    "X" },
        { "XXXXX", "L" },
        { "LL",    "C" },
    };
    
    const SIMPLIFICATION_T simplifications_nicety[] =
    {
        { "IIII", "IV" },
        { "VIV",  "IX" },
        { "XXXX", "XL" },
    };
    
    retval = simplify(retval, simplifications_adders, (int)DIMENSION_OF(simplifications_adders));
    retval = simplify(retval, simplifications_nicety, (int)DIMENSION_OF(simplifications_nicety));
    return retval;
}

const char* roman_add(const char* num1, const char* num2)
{
    char* retval;
    
    if (!args_valid(num1, num2))
        return 0;
    
    //expand if needed
    num1 = expander(num1);
    num2 = expander(num2);
    
    //merge numbers to add
    retval = merge(num1, num2);
    retval = compactor(retval);
    
    return retval;
}
