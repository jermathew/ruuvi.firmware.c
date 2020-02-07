#include "unity.h"

#include "app_config.h"
#include "ruuvi_boards.h"
#include "ruuvi_driver_enabled_modules.h"
#include "ruuvi_library.h"

#include "main.h"
#include "semver.h"

#include "mock_ruuvi_driver_error.h"
#include "mock_ruuvi_interface_yield.h"
#include "mock_ruuvi_interface_watchdog.h"

semver_t current = {};
semver_t compare = {};

void setUp (void)
{
  rd_error_check_Ignore();
}

void tearDown (void)
{
    // Free allocated memory when we're done
    semver_free(&current);
    semver_free(&compare);
}

void test_main_setup(void)
{
    ri_watchdog_init_ExpectAndReturn(APP_WDT_INTERVAL_MS, &on_wdt, RD_SUCCESS);
    ri_yield_init_ExpectAndReturn(RD_SUCCESS);
    setup();
}

void test_main_loop(void)
{
    ri_yield_ExpectAndReturn(RD_SUCCESS);
    app_main();
}

void test_semver_boards(void)
{
    char operator[] = "^";
    semver_parse(RUUVI_BOARDS_SEMVER, &current);
    semver_parse(RUUVI_BOARDS_REQ, &compare);
    TEST_ASSERT(semver_satisfies(current, compare, operator));
}

void test_semver_drivers(void)
{
    char operator[] = "^";
    semver_parse(RUUVI_DRIVERS_SEMVER, &current);
    semver_parse(RUUVI_DRIVERS_REQ, &compare);
    TEST_ASSERT(semver_satisfies(current, compare, operator));
}

void test_semver_libraries(void)
{
    char operator[] = "^";
    semver_parse(RUUVI_LIBRARIES_SEMVER, &current);
    semver_parse(RUUVI_LIBRARIES_REQ, &compare);
    TEST_ASSERT(semver_satisfies(current, compare, operator));
}