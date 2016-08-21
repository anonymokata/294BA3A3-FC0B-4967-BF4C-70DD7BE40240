#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <check.h>
#include "roman.h"

/* CASE: simple-addition */
START_TEST(add_I_plus_I)
{
    const char* result = roman_add("I","I");
    
    ck_assert_ptr_ne(0, result);
    ck_assert_str_eq("II", result);
    
    free((void*)result);
}
END_TEST

/* CASE: handle errors */
START_TEST(null_inputs_should_return_null)
{
    const char* result;
    
    result = roman_add(0,"I");
    ck_assert_ptr_eq(0, result);
    
    result = roman_add("I", 0);
    ck_assert_ptr_eq(0, result);
    
    result = roman_add(0,0);
    ck_assert_ptr_eq(0, result);
}
END_TEST

START_TEST(empty_inputs_should_return_null)
{
    const char* result;
    
    result = roman_add("", "I");
    ck_assert_ptr_eq(0, result);
    
    result = roman_add("I", "");
    ck_assert_ptr_eq(0, result);
    
    result = roman_add("", "");
    ck_assert_ptr_eq(0, result);
}
END_TEST

/* Set up the tests, cases, and suite to be run for this unit */
Suite* roman_suite(void)
{
    Suite* s;
    TCase* c;
    s = suite_create("roman");
    
    c = tcase_create("simple_addition");
    tcase_add_test(c, add_I_plus_I);
    suite_add_tcase(s, c);
    
    c = tcase_create("handle_errors");
    tcase_add_test(c, null_inputs_should_return_null);
    tcase_add_test(c, empty_inputs_should_return_null);
    suite_add_tcase(s, c);
    
    return s;
}

/* Our main function runner takes no arguments and it always runs all tests */
int main(void) 
{
    int failures;
    Suite* s;
    SRunner* r;
    
    s = roman_suite();
    r = srunner_create(s);
    
    srunner_run_all(r, CK_NORMAL);
    failures = srunner_ntests_failed(r);
    srunner_free(r);
    
    return failures;
}