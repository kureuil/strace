#include <stddef.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void
test_zappy(void **state)
{
  (void) state;
}

const struct CMUnitTest g_tests[] = {
  cmocka_unit_test(test_zappy),
};

int
main()
{
  return cmocka_run_group_tests(g_tests, NULL, NULL);
}
