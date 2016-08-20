#include <stdint.h>
#include <check.h>
#include "roman.h"

/* CASE: simple-addition */
START_TEST(first_test)
{
    
}
END_TEST

/* Set up the tests, cases, and suite to be run for this unit */
Suite* roman_suite(void)
{
    Suite* s;
    TCase* c;
    s = suite_create("roman");
    
    c = tcase_create("simple_addition");
    tcase_add_test(c, first_test);
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