#include <check.h>
#include <stdio.h>
#include <stdlib.h>

// libsolv
#include <solv/util.h>

// hawkey
#include "testsys.h"
#include "test_query.h"
#include "test_sack.h"

struct TestGlobals_s test_globals;

static void
init_test_globals(struct TestGlobals_s *tg, const char *repo_dir)
{
    tg->repo_dir = solv_strdup(repo_dir);
    tg->sack = NULL;
}

static void
free_test_globals(struct TestGlobals_s *tg)
{
    solv_free(tg->repo_dir);
}

int
main(int argc, const char **argv)
{
    int number_failed;

    if (argc != 2) {
	fprintf(stderr, "synopsis: %s <repo_directory>\n", argv[0]);
	exit(1);
    }
    init_test_globals(&test_globals, argv[1]);

    SRunner *sr = srunner_create(sack_suite());
    srunner_add_suite(sr, query_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    free_test_globals(&test_globals);
    return (number_failed == 0) ? 0 : 1;
}