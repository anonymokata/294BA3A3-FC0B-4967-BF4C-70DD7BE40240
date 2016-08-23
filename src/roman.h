#ifndef ROMAN_H
#define ROMAN_H

#define DIMENSION_OF(a) ( sizeof(a) / sizeof(a[0]) )

const char* roman_add(const char* num1, const char* num2);
const char* roman_subtract(const char* minuend, const char* subtrahend);

#endif /* ROMAN_H */