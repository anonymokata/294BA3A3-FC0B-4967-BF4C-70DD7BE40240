#include "roman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const char letters[] = { 'C', 'L', 'X', 'V', 'I' };

static const char* simplify_adders_wide[]  = { "IIIII", "VV", "XXXXX", "LL" };
static const char* simplify_adders_short[] = { "V",     "X",  "L",     "C"  };

static const char* simplify_nicety_wide[]  = { "IIII", "VIIII", "VIV", "XXXX", "LXXXX", "LXL" };
static const char* simplify_nicety_short[] = { "IV",   "IX",    "IX",  "XL",   "XC",    "XC"  };

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

static char* replacer(char* dst, char* src, const char** orig, const char** repl, const int num)
{
    char* ptr1 = src;
    char* ptr2 = dst;
    char* last = 0;
    int i;

    while (*ptr1 != 0)
    {
        for (i=0; (i < num && (last != ptr1)); i++)
        {
            int len = match_len(orig[i], ptr1);
            if (len > 0)
            {
                const char* ptr3 = repl[i];
                while (*ptr3)
                {
                    *ptr2++ = *ptr3++;
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
        dst = replacer(src, dst, orig, repl, num);
    
    return dst;
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

static char* expander(const char* num)
{
    //worst case expansion is 5/2
    char* src = malloc( strlen(num) * 3 );
    char* dst = malloc( strlen(num) * 3 );
    strcpy(src, num);
    return replacer(dst, src, simplify_nicety_short, simplify_nicety_wide, (int)DIMENSION_OF(simplify_nicety_wide));
}

static char* merge(const char* num1, const char* num2)
{
    size_t len1, len2;
    size_t i;
    char* retval;
    char* ptr;
    
    len1 = strlen(num1);
    len2 = strlen(num2);
    retval = malloc(len1 + len2 + 1);
    ptr = retval;
    
    for (i=0; i < DIMENSION_OF(letters); i++)
    {
        char letter = letters[i];
        while (*num1 == letter)
            *ptr++ = *num1++;
        while (*num2 == letter)
            *ptr++ = *num2++;
    }
    *ptr = 0;
    
    return retval;
}

static char* compactor(char* retval)
{
    retval = replacer(retval, retval, simplify_adders_wide, simplify_adders_short, (int)DIMENSION_OF(simplify_adders_wide));
    retval = replacer(retval, retval, simplify_nicety_wide, simplify_nicety_short, (int)DIMENSION_OF(simplify_nicety_wide));
    return retval;
}

const char* roman_add(const char* num1, const char* num2)
{
    char* retval;
    char* tmp1;
    char* tmp2;
    
    if (!args_valid(num1, num2))
        return 0;
    
    //expand if needed
    tmp1 = expander(num1);
    tmp2 = expander(num2);
    
    //merge numbers to add
    retval = merge(tmp1, tmp2);
    retval = compactor(retval);
    
    //throw out temp space
    free(tmp1);
    free(tmp2);
    
    return retval;
}
