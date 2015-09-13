#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <google/cmockery.h>

#include "hmap.h"

// If unit testing is enabled override assert with mock_assert().
#if UNIT_TESTING
extern void mock_assert(const int result, const char* const expression, 
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif // UNIT_TESTING

void insert_get_test(void **state) {
    Hashmap *hm = hm_new();
    assert_true(hm_insert(hm, "test", "test2"));
    char *res = hm_get(hm, "test");
    assert_true(res != NULL);
    assert_string_equal(res, "test2");
}

void insert_override_test(void **state) {
    Hashmap *hm = hm_new();
    assert_true(hm_insert(hm, "test", "test_2"));
    assert_false(hm_insert(hm, "test", "test_2"));
}

void insert_has_key_test(void **state) {
    Hashmap *hm = hm_new();
    assert_true(hm_insert(hm, "test", "test2"));
    assert_true(hm_has_key(hm, "test"));

    assert_false(hm_has_key(hm, "some random test"));
}

void insert_delete_test(void **state) {
    Hashmap *hm = hm_new();
    assert_true(hm_insert(hm, "test", "test2"));
    assert_true(hm_delete(hm, "test"));
    assert_false(hm_delete(hm, "test"));
}

void double_hm_test(void **state) {
    Hashmap *hm1 = hm_new();
    Hashmap *hm2 = hm_new();

    assert_true(hm_insert(hm1, "my_test", "test2"));
    assert_true(hm_insert(hm2, "my_test", "yet_another_test"));

    char *res1 = hm_get(hm1, "my_test");
    char *res2 = hm_get(hm2, "my_test");
    assert_true(res1 != NULL);
    assert_true(res2 != NULL);

    assert_string_equal(res1, "test2");
    assert_string_equal(res2, "yet_another_test");
}

void multi_insert_test(void **state) {
    char *word_list[12][2] = {
        {"test", "test2"},
        {"kale", "garlic"},
        {"sour", "patch"},
        {"longboat", "dragon"},
        {"final", "fantasy"},
        {"cute", "ladies"},
        {"!!!!", "?????"},
        {"groovy", "tubular"},
        {"goobby", "dolan"},
        {" ", "  "},
        {"nahhhhh b", "lolz cats"},
        {"totes", "mah goats"}
    };

    char *res;

    Hashmap *hm = hm_new_size(8);
    for (int i = 0; i < sizeof(word_list) / sizeof(word_list[0]); i++) {
        hm_insert(hm, word_list[i][0], word_list[i][1]);
    }
    for (int i = 0; i < sizeof(word_list) / sizeof(word_list[0]); i++) {
        res = hm_get(hm, word_list[i][0]);
        assert_true(res != NULL);
        assert_string_equal(res, word_list[i][1]);
    }
}

int main(int argc, char *argv[]) {
    const UnitTest tests[] = {
        unit_test(insert_get_test),
        unit_test(insert_override_test),
        unit_test(insert_has_key_test),
        unit_test(insert_delete_test),
        unit_test(double_hm_test),
        unit_test(multi_insert_test)
    };
    return run_tests(tests);
}

