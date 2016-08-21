#include "roman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char* roman_add(const char* num1, const char* num2)
{
    char* retval;
    size_t len1, len2;
    
    //check for null inputs
    if ((num1 == 0) || (num2 == 0))
        return 0;
    
    //grab lengths and allocate enough memory for us to build the final string
    len1 = strlen(num1);
    len2 = strlen(num2);
    retval = malloc(len1 + len2 + 1);
    
    //concat the two strings to get added string
    sprintf(retval, "%s%s", num1, num2);
    
    return retval;
}
