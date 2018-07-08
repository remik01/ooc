// untit test for the ClassRectangle


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AbstractClassShape.h"
#include "ClassRectangle.h"

#include "CUnit/Basic.h"


static Rectangle *myrec = NULL;

// The suite initialization function.
int init_suite1(void)
{
    if (NULL == (myrec = Rectangles.get_rectangle(Rectangles.STANDARD)))
    {
        return -1;
    }
    else
    {
        myrec->set_width(myrec, 123)->set_height(myrec, 456);
        return 0;
    }
}

// The suite cleanup function.

int clean_suite1(void)
{
    Rectangles.cleanup();
    if (NULL != myrec)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void testGET_AREA(void)
{
    CU_ASSERT(56088 == myrec->get_area(myrec));
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
    if ((NULL == CU_add_test(pSuite, "test of get_area()", testGET_AREA)))
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