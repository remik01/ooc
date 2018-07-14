// untit test for the main file "sort_shapes"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/Basic.h"

// load the file as modulino
// with disabled "main" function
#define DONT_HAVE_MAIN
#include "sort_shapes.c"

char *buffer = 0;
long length;

// The suite initialization function.
int init_suite1(void)
{
    mystdout = tmpfile();

    if (0 != run(0, NULL))
    {
        return -1;
    }

    if (mystdout)
    {
        fseek (mystdout, 0, SEEK_END);
        length = ftell (mystdout);
        fseek (mystdout, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, mystdout);
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -3;
    }

    if (buffer)
    {
        // printf("%s\n", buffer);
    }
    else
    {
        return -4;
    }

    return 0;
}

// The suite cleanup function.

int clean_suite1(void)
{
    free(buffer);
    buffer = NULL;

    fclose(mystdout);
    mystdout = NULL;

    if (NULL != NULL)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void testCHECK_RESULT(void)
{
    CU_ASSERT(NULL != strstr(buffer, "the singleton is: 36 x 34 = 1224"));
    CU_ASSERT(NULL != strstr(buffer, "237 x 253 = 59961"));
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test of results", testCHECK_RESULT)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}