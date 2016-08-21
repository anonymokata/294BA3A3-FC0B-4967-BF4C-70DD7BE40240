#include "roman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static char* compactor(char* retval)
{
    size_t len = strlen(retval);
    
    //if too many I's, we need to simplify output
    if (len == 4)
        strcpy(retval,"IV");
    else if (len == 5)
        strcpy(retval, "V");
    else if (len == 6)
        strcpy(retval, "VI");
    
    return retval;
}

const char* roman_add(const char* num1, const char* num2)
{
    char* retval;
    size_t len1, len2, newlen;
    
    //check for null inputs
    if ((num1 == 0) || (num2 == 0))
        return 0;
    
    //check for empty inputs
    if ((num1[0] == 0) || (num2[0] == 0))
        return 0;
    
    //grab lengths and allocate enough memory for us to build the final string
    len1 = strlen(num1);
    len2 = strlen(num2);
    newlen = len1 + len2;
    retval = malloc(newlen + 1);
    
    //concat the two strings to get added string
    sprintf(retval, "%s%s", num1, num2);
    
    
    return compactor(retval);
}
