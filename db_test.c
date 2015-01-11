#include <string.h>
#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"
#include "treedb.h"
#include <stdlib.h>
#include <stdio.h>


int init_suite_2(void){
  return 0;
}

int clean_suite_2(void){
  return 0;
}

char *key;
char *val;

void testmakeTree(void){
  Tree test = NULL;
  key = "B";
  val = "2";
  test = makeTree(key, val, test);
  puts(test->key);
  puts(test->value);
  CU_ASSERT(*test->key == *key);
  CU_ASSERT(strcmp(test->value,val) == 0);
}

void testfindKey(void){
  Tree test = NULL;
  key = "A";
  val = "1";
  test = makeTree(key, val, test);
  Tree temp = NULL;
  temp = findKey(test, key);
  CU_ASSERT_TRUE(*temp->key == *key);
  CU_ASSERT_TRUE(*temp->value == *val);
}

void testupdateValue(void){
  Tree test = NULL;
  key = "A";
  val = "1";
  test = makeTree(key, val, test);
  val = "28";
  test = updateValue(key, val, test);
  CU_ASSERT(strcmp("28", test->value) == 0);
}

void testinsertEntry(void){
  Tree test = NULL;
  key = "A";
  val = "1";
  test = makeTree(key, val, test);
  key = "B";
  val = "3";
  test = insertEntry(key, val, test);
  CU_ASSERT(*test->right->key == *key);
  CU_ASSERT(*test->right->value == *val);
}

void testmaxValue(void){
  Tree test = NULL;
  key = "A";
  val = "1";
  test = makeTree(key, val, test);
  key = "B";
  test = makeTree(key, val, test);
  Tree temp = NULL;
  temp = maxValue(test);
  CU_ASSERT(*temp->key == *key);
}

void testminValue(void){
  Tree test = NULL;
  key = "C";
  val = "1";
  test = makeTree(key, val, test);
  key = "A";
  test = makeTree(key, val, test);
  Tree temp = NULL;
  temp = minValue(test);
  CU_ASSERT(*temp->key == *key);
}

void testdelete(void){
  Tree test = NULL;
  key = "E";
  val = "1";
  test = makeTree(key, val, test);
  key = "F";
  test = makeTree(key, val, test);
  key = "B";
  test = makeTree(key, val, test);
  delete(key, test);
  CU_ASSERT(test->left == NULL);
  key = "E";
  delete(key, test);
  CU_ASSERT(test->right == NULL);
  key = "E";
  test = makeTree(key, val, test);
  key = "G";
  test = makeTree(key, val, test);
  key = "F";
  delete(key,test);
  //  puts(test->right->key);
  CU_ASSERT(test->right == NULL);
}

int main()
{
  CU_pSuite pSuite2 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(pSuite2, "test of makeTree()", testmakeTree)) ||
    (NULL == CU_add_test(pSuite2, "test of findKey()", testfindKey)) ||
    (NULL == CU_add_test(pSuite2, "test of updateValue()", testupdateValue)) ||
    (NULL == CU_add_test(pSuite2, "test of insertEntry()", testinsertEntry)) ||
    (NULL == CU_add_test(pSuite2, "test of maxValue()", testmaxValue)) ||
    (NULL == CU_add_test(pSuite2, "test of minValue()", testminValue)) ||
    (NULL == CU_add_test(pSuite2, "test of delete()", testdelete)) 
  )
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
