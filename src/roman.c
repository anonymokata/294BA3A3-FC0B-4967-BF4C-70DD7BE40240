#include "roman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const char letters[] = { 'M', 'D', 'C', 'L', 'X', 'V', 'I' };

static const char* simplify_adders_wide[]  = { "IIIII", "VV",     "XXXXX", "LL",    "CCCCC", "DD"                            };
static const char* simplify_adders_short[] = { "V",     "X",      "L",     "C",     "D",     "M"                             };
static const char* simplify_nicety_wide[]  = { "IIII",  "VIIII",  "XXXX",  "LXXXX", "CCCC",  "DCCCC",  "VIV",  "LXL",  "DCD" };
static const char* simplify_nicety_short[] = { "IV",    "IX",     "XL",    "XC",    "CD",    "CM",     "IX",   "XC",   "CM"  };

//returns true if num1 > num2
static int is_bigger(char num1, char num2)
{
    size_t i;
    char mask = 0;
    
    for (i=0; i < DIMENSION_OF(letters); i++)
    {
        if (letters[i] == num2)
            mask |= 2;
        if (letters[i] == num1)
            mask = 1;
    }
    return (mask == 0x03);
}

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
    char* retval;
    
    //worst case expansion is 5/2
    char* src = malloc( strlen(num) * 8 );
    char* dst = malloc( strlen(num) * 8 );
    strcpy(src, num);
    
    //clean up temporary storage
    retval = replacer(dst, src, simplify_nicety_short, simplify_nicety_wide, (int)DIMENSION_OF(simplify_nicety_wide));
    if (retval != src)
        free(src);
    if (retval != dst)
        free(dst);
    
    return retval;
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

static char* cancel(const char* num1, const char* num2)
{
    size_t index, len;
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char* scratch = (char*)malloc(len1 * 2);
    char* retval;
    
    char* ptr2 = (char*)scratch;
    char* ptr1 = (char*)(num1 + len1 - 1);
    char* psub = (char*)(num2 + len2 - 1);
    
    while (ptr1 >= num1)
    {
        if (*ptr1 != *psub)
        {
            if (is_bigger(*ptr1, *psub))
            {
                for (index = 0; index < DIMENSION_OF(simplify_adders_short); index++)
                {
                    if (*ptr1 == simplify_adders_short[index][0])
                    {
                        const char* borrow = simplify_nicety_wide[index];
                        while (*borrow)
                            *ptr1++ = *borrow++;
                        if (*ptr1 != *psub)
                        {
                            *ptr1 = *(ptr1-1);
                            ptr1++;
                        }
                        else
                        {
                            psub--;
                        }
                        *ptr1 = 0;
                        break;
                    }
                }
            }
            else
            {
                *ptr2++ = *ptr1;
            }
        }
        else
        {
            psub--;
        }
        ptr1--;
    } 
    *ptr2 = 0;
    
    //reverse string before returning it
    len = strlen(scratch);
    retval = (char*)malloc(len+ 1);
    for (index = 0; index < len; index++)
        retval[index] = *(--ptr2);
    retval[len] = 0;
    
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

const char* roman_subtract(const char* minuend, const char* subtrahend)
{
    char* retval;
    char* tmp1;
    char* tmp2;
    
    if (!args_valid(minuend, subtrahend))
        return 0;
    
    //expand if needed
    tmp1 = expander(minuend);
    tmp2 = expander(subtrahend);
    retval = cancel(tmp1, tmp2);
    retval = compactor(retval);
    
    //throw out temp space
    free(tmp1);
    free(tmp2);
    
    if (*retval == 0)
        return 0;
    else
        return retval;
}

