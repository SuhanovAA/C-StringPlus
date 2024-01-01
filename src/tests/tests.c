#include <check.h>
#include <string.h>

#include "../s21_sprintf.h"
#include "../s21_sscanf.h"
#include "../s21_string.h"

#define LEN 100

typedef struct Fail {
  int str;
  int spr;
  int d;
  int s;
  int f;
  int c;
  int u;
  int o;
  int x;
  int X;
  int e;
  int E;
  int g;
  int G;
  int p;
  int scan;
  int str1;
} Fail;

// MEMCHR TEST
START_TEST(s21_test_memchr_check) {
  const char str[3][100] = {"Hello, how are you?", " ", ""};

  ck_assert_ptr_eq(s21_memchr(str[0], 'e', 20), memchr(str[0], 'e', 20));
  ck_assert_ptr_eq(s21_memchr(str[1], 'e', 20), memchr(str[1], 'e', 20));
  ck_assert_ptr_eq(s21_memchr(str[2], 'e', 20), memchr(str[2], 'e', 20));
  ck_assert_ptr_eq(s21_memchr(str[0], 'q', 20), memchr(str[0], 'q', 20));
  ck_assert_ptr_eq(s21_memchr(str[1], 'q', 20), memchr(str[1], 'q', 20));
  ck_assert_ptr_eq(s21_memchr(str[2], 'q', 20), memchr(str[2], 'q', 20));
  ck_assert_ptr_eq(s21_memchr(str[0], 'o', 5), memchr(str[0], 'o', 5));

  ck_assert_ptr_eq(s21_memchr(str[0], 'a', 2), memchr(str[0], 'a', 2));
  ck_assert_ptr_eq(s21_memchr(str[1], 'a', 2), memchr(str[1], 'a', 2));
  ck_assert_ptr_eq(s21_memchr(str[2], 'a', 2), memchr(str[2], 'a', 2));
  ck_assert_ptr_eq(s21_memchr(str[0], 'a', 0), memchr(str[0], 'a', 0));

  ck_assert_ptr_eq(s21_memchr(str[0], 115, 30), memchr(str[0], 115, 30));
}
END_TEST

// MEMCMP TEST
START_TEST(s21_test_memcmp_check) {
  const char str[5][100] = {"Hello, how are you?", "Hello, how are you?",
                            "Hello, Oow are you?", " ", ""};

  ck_assert_int_eq(s21_memcmp(str[0], str[1], 25), memcmp(str[0], str[1], 25));

  ck_assert_int_eq(memcmp(str[0], str[1], 25), 0);
  ck_assert_int_eq(s21_memcmp(str[0], str[1], 25), 0);

  ck_assert_int_gt(memcmp(str[0], str[2], 25), 0);
  ck_assert_int_gt(s21_memcmp(str[0], str[2], 25), 0);

  ck_assert_int_gt(memcmp(str[0], str[3], 25), 0);
  ck_assert_int_gt(s21_memcmp(str[0], str[3], 25), 0);

  ck_assert_int_gt(memcmp(str[0], str[4], 25), 0);
  ck_assert_int_gt(s21_memcmp(str[0], str[4], 25), 0);

  ck_assert_int_lt(memcmp(str[4], str[0], 25), 0);
  ck_assert_int_lt(s21_memcmp(str[4], str[0], 25), 0);

  ck_assert_int_eq(memcmp(str[0], str[1], 2), 0);
  ck_assert_int_eq(s21_memcmp(str[0], str[1], 2), 0);

  ck_assert_int_gt(memcmp(str[0], str[3], 2), 0);
  ck_assert_int_gt(s21_memcmp(str[0], str[3], 2), 0);

  ck_assert_int_eq(memcmp(str[0], str[1], 0), 0);
  ck_assert_int_eq(s21_memcmp(str[0], str[1], 0), 0);

  ck_assert_int_eq(memcmp(str[0], str[1], 0), 0);
  ck_assert_int_eq(s21_memcmp(str[0], str[1], 0), 0);
}
END_TEST

START_TEST(s21_memcmp_test) {
  char test1[] = "It's hard to be god";
  char test2[] = "Code like god";
  char test3[] = "\0";
  char test4[] = "Wanna\0 sleep";
  char test5[] = "Wanna\0 sleep";
  char test_8[] = "";
  char test_9[] = "";
  char test_10[] = "1";
  char test_11[] = "1";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 14) == 0,
                    memcmp(test1, test2, 14) == 0);
  ck_assert_uint_eq(s21_memcmp(test1, test3, 2) > 0,
                    memcmp(test1, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test2, test3, 2) > 0,
                    memcmp(test2, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test1, 9) > 0,
                    memcmp(test4, test1, 9) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test5, 7) == 0,
                    memcmp(test4, test5, 7) == 0);
  ck_assert_uint_eq(s21_memcmp(test_8, test_9, 1) == 0,
                    memcmp(test_8, test_9, 1) == 0);
  ck_assert_uint_eq(s21_memcmp(test_10, test_11, 1) == 0,
                    memcmp(test_10, test_11, 1) == 0);
}
END_TEST

// MEMCPY TEST
START_TEST(s21_test_memcpy_check) {
  char dest[100];
  const char *str2 = "wetwetr";
  const char *str3 = "Hello, How are you?ewfweertwtr";
  const char *str4 = " ";
  const char *str5 = "";
  ck_assert_ptr_eq(s21_memcpy(dest, str2, 20), memcpy(dest, str2, 20));
  ck_assert_ptr_eq(s21_memcpy(dest, str3, 33), memcpy(dest, str3, 33));
  ck_assert_ptr_eq(s21_memcpy(dest, str2, 4), memcpy(dest, str2, 4));
  ck_assert_ptr_eq(s21_memcpy(dest, str3, 2), memcpy(dest, str3, 2));

  ck_assert_str_eq(s21_memcpy(dest, str2, 12), memcpy(dest, str2, 12));
  ck_assert_str_eq(s21_memcpy(dest, str2, 3), memcpy(dest, str2, 3));
  ck_assert_str_eq(s21_memcpy(dest, str3, 2), memcpy(dest, str3, 2));
  ck_assert_str_eq(s21_memcpy(dest, str3, 8), memcpy(dest, str3, 8));
  ck_assert_str_eq(s21_memcpy(dest, str3, 0), memcpy(dest, str3, 0));

  ck_assert_str_eq(s21_memcpy(dest, str4, 8), memcpy(dest, str4, 8));
  ck_assert_str_eq(s21_memcpy(dest, str5, 8), memcpy(dest, str5, 8));
}
END_TEST

// MEMSET TEST
START_TEST(s21_test_memset_check) {
  char str[3][100] = {"Hello, how are you?", " ", ""};

  ck_assert_str_eq(s21_memset(str[0], 'e', 50), memset(str[0], 'e', 50));
  ck_assert_str_eq(s21_memset(str[0], 'e', 5), memset(str[0], 'e', 5));
  ck_assert_str_eq(s21_memset(str[0], 'e', 1), memset(str[0], 'e', 1));
  ck_assert_str_eq(s21_memset(str[0], 0, 1), memset(str[0], 0, 1));

  ck_assert_str_eq(s21_memset(str[1], 'e', 50), memset(str[1], 'e', 50));
  ck_assert_str_eq(s21_memset(str[1], 'e', 5), memset(str[1], 'e', 5));
  ck_assert_str_eq(s21_memset(str[2], 'e', 1), memset(str[2], 'e', 1));
  ck_assert_str_eq(s21_memset(str[2], 0, 1), memset(str[2], 0, 1));
}
END_TEST

// STRNCAT TEST
START_TEST(s21_test_strncat_check) {
  char str1[100] = "Hello, how are you?";
  const char str2[15] = "I am ok!";
  const char *str3 = " ";
  const char *str4 = "";
  char str5[100] = "";

  ck_assert_str_eq(s21_strncat(str1, str2, 2), strncat(str1, str2, 2));
  ck_assert_str_eq(s21_strncat(str1, str2, 0), strncat(str1, str2, 0));

  ck_assert_str_eq(s21_strncat(str1, str2, 20), strncat(str1, str2, 20));
  ck_assert_str_eq(s21_strncat(str1, str3, 20), strncat(str1, str3, 20));
  ck_assert_str_eq(s21_strncat(str1, str4, 20), strncat(str1, str4, 20));
  ck_assert_str_eq(s21_strncat(str5, str4, 20), strncat(str5, str4, 20));
}
END_TEST

// STRCHR TEST
START_TEST(s21_test_strchr_check) {
  char str[4][100] = {"Hello, how are you?", " ", "", "1234"};

  ck_assert_ptr_null(strchr(str[0], 's'));
  ck_assert_ptr_null(strchr(str[1], 's'));
  ck_assert_ptr_null(strchr(str[2], 's'));

  ck_assert_ptr_null(s21_strchr(str[0], 's'));
  ck_assert_ptr_null(s21_strchr(str[1], 's'));
  ck_assert_ptr_null(s21_strchr(str[2], 's'));

  ck_assert_str_eq(s21_strchr(str[0], 'e'), strchr(str[0], 'e'));
  ck_assert_str_eq(s21_strchr(str[0], '?'), strchr(str[0], '?'));
  ck_assert_str_eq(s21_strchr(str[0], '\0'), strchr(str[0], '\0'));
}
END_TEST

// STRRCHR TEST
START_TEST(s21_test_strrchr_check) {
  char str[4][100] = {"Hello, how are you?", " ", "", "1234"};

  ck_assert_ptr_null(strrchr(str[0], 's'));
  ck_assert_ptr_null(strrchr(str[1], 's'));
  ck_assert_ptr_null(strrchr(str[2], 's'));

  ck_assert_ptr_null(s21_strrchr(str[0], 's'));
  ck_assert_ptr_null(s21_strrchr(str[1], 's'));
  ck_assert_ptr_null(s21_strrchr(str[2], 's'));

  ck_assert_str_eq(s21_strrchr(str[0], 'e'), strrchr(str[0], 'e'));
  ck_assert_str_eq(s21_strrchr(str[0], '?'), strrchr(str[0], '?'));
  ck_assert_str_eq(s21_strrchr(str[0], '\0'), strrchr(str[0], '\0'));
}
END_TEST

// STRLEN TEST
START_TEST(s21_test_strlen_check) {
  char str[4][100] = {"Hello, how are you?", " ", "", "1234"};

  ck_assert_int_eq(s21_strlen(str[0]), strlen(str[0]));
  ck_assert_int_eq(s21_strlen(str[1]), strlen(str[1]));
  ck_assert_int_eq(s21_strlen(str[2]), strlen(str[2]));
  ck_assert_int_eq(s21_strlen(str[3]), strlen(str[3]));
}
END_TEST

// STRSPN TEST
START_TEST(s21_test_strspn_check) {
  char str[5][100] = {"Hello, how are you?", " ", "", "1234", "Hell"};

  ck_assert_int_eq(s21_strspn(str[0], str[1]), strspn(str[0], str[1]));
  ck_assert_int_eq(s21_strspn(str[0], str[2]), strspn(str[0], str[2]));
  ck_assert_int_eq(s21_strspn(str[0], str[3]), strspn(str[0], str[3]));
  ck_assert_int_eq(s21_strspn(str[0], str[4]), strspn(str[0], str[4]));
}
END_TEST

// STRCSPN TEST
START_TEST(s21_test_strcspn_check) {
  char str[6][100] = {"Hello, how are you?", " ", "", "1234", "Hell", "hau"};

  ck_assert_int_eq(s21_strcspn(str[0], str[1]), strcspn(str[0], str[1]));
  ck_assert_int_eq(s21_strcspn(str[0], str[2]), strcspn(str[0], str[2]));
  ck_assert_int_eq(s21_strcspn(str[0], str[3]), strcspn(str[0], str[3]));
  ck_assert_int_eq(s21_strcspn(str[0], str[4]), strcspn(str[0], str[4]));
  ck_assert_int_eq(s21_strcspn(str[0], str[5]), strcspn(str[0], str[5]));
}
END_TEST

// STRCAT TEST
START_TEST(s21_test_strcat_check) {
  char str[5][100] = {"Hello, how are you?", " ", "", "1234", "Hell"};

  ck_assert_str_eq(s21_strcat(str[0], str[1]), strcat(str[0], str[1]));
  ck_assert_str_eq(s21_strcat(str[0], str[2]), strcat(str[0], str[2]));
  ck_assert_str_eq(s21_strcat(str[0], str[3]), strcat(str[0], str[3]));

  ck_assert_str_eq(s21_strcat(str[0], str[4]), strcat(str[0], str[4]));
  ck_assert_str_eq(s21_strcat(str[1], str[4]), strcat(str[1], str[4]));
  ck_assert_str_eq(s21_strcat(str[2], str[4]), strcat(str[2], str[4]));
}
END_TEST

// STRCPY TEST
START_TEST(s21_test_strcpy_check) {
  char str[6][100] = {"Hello, how are you?", " ", "", "1234", "Hell", ""};

  ck_assert_str_eq(s21_strcpy(str[0], str[1]), strcpy(str[0], str[1]));
  ck_assert_str_eq(s21_strcpy(str[0], str[2]), strcpy(str[0], str[2]));
  ck_assert_str_eq(s21_strcpy(str[0], str[3]), strcpy(str[0], str[3]));
  ck_assert_str_eq(s21_strcpy(str[0], str[4]), strcpy(str[0], str[4]));

  ck_assert_str_eq(s21_strcpy(str[1], str[4]), strcpy(str[1], str[4]));
  ck_assert_str_eq(s21_strcpy(str[2], str[4]), strcpy(str[2], str[4]));
  ck_assert_str_eq(s21_strcpy(str[2], str[5]), strcpy(str[2], str[5]));
}
END_TEST

// STRNCPY TEST
START_TEST(s21_test_strncpy_check) {
  char str[5][100] = {"Hello, how are you?", " ", "", "1234", "Hell"};
  const s21_size_t size[5] = {0, 1, 2, 10, 50};

  ck_assert_str_eq(s21_strncpy(str[0], str[1], size[0]),
                   strncpy(str[0], str[1], size[0]));
  ck_assert_str_eq(s21_strncpy(str[0], str[2], size[1]),
                   strncpy(str[0], str[2], size[1]));
  ck_assert_str_eq(s21_strncpy(str[0], str[3], size[2]),
                   strncpy(str[0], str[3], size[2]));
  ck_assert_str_eq(s21_strncpy(str[0], str[4], size[3]),
                   strncpy(str[0], str[4], size[3]));

  ck_assert_str_eq(s21_strncpy(str[0], str[4], size[4]),
                   strncpy(str[0], str[4], size[4]));
  ck_assert_str_eq(s21_strncpy(str[2], str[4], size[4]),
                   strncpy(str[2], str[4], size[4]));
  ck_assert_str_eq(s21_strncpy(str[2], str[4], size[2]),
                   strncpy(str[2], str[4], size[2]));
  ck_assert_str_eq(s21_strncpy(str[2], str[4], size[0]),
                   strncpy(str[2], str[4], size[0]));
}
END_TEST

// STRCMP TEST
START_TEST(s21_test_strcmp_check) {
  char str[7][100] = {"Hello, how are you?", " ", "", "1234", "1234", "", " "};

  ck_assert_int_eq(s21_strcmp(str[0], str[1]), strcmp(str[0], str[1]));
  ck_assert_int_eq(s21_strcmp(str[1], str[3]), strcmp(str[1], str[3]));
  ck_assert_int_eq(s21_strcmp(str[2], str[1]), strcmp(str[2], str[1]));

  ck_assert_int_eq(s21_strcmp(str[3], str[4]), strcmp(str[3], str[4]));
  ck_assert_int_eq(s21_strcmp(str[2], str[5]), strcmp(str[2], str[5]));
  ck_assert_int_eq(s21_strcmp(str[1], str[6]), strcmp(str[1], str[6]));
}
END_TEST

// STRNCMP TEST
START_TEST(s21_test_strncmp_check) {
  char str[5][100] = {"Hello, how are you?", " ", "", "1234", "1234"};
  const s21_size_t size[5] = {0, 1, 2, 10, 50};

  ck_assert_int_eq(s21_strncmp(str[0], str[1], size[0]),
                   strncmp(str[0], str[1], size[0]));
  ck_assert_int_eq(s21_strncmp(str[0], str[1], size[1]),
                   strncmp(str[0], str[1], size[1]));
  ck_assert_int_eq(s21_strncmp(str[0], str[1], size[2]),
                   strncmp(str[0], str[1], size[2]));
  ck_assert_int_eq(s21_strncmp(str[0], str[1], size[3]),
                   strncmp(str[0], str[1], size[3]));
  ck_assert_int_eq(s21_strncmp(str[0], str[1], size[4]),
                   strncmp(str[0], str[1], size[4]));

  ck_assert_int_eq(s21_strncmp(str[1], str[3], size[3]),
                   strncmp(str[1], str[3], size[3]));
  ck_assert_int_eq(s21_strncmp(str[2], str[1], size[4]),
                   strncmp(str[2], str[1], size[4]));
  ck_assert_int_eq(s21_strncmp(str[3], str[4], size[2]),
                   strncmp(str[3], str[4], size[2]));
}
END_TEST

START_TEST(strncmp_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  s21_size_t n = 14;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_2) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, worldj";
  s21_size_t n = 14;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_3) {
  char s1[] = "";
  char s2[] = "";
  s21_size_t n = 1;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_4) {
  char s1[] = "f";
  char s2[] = "";
  s21_size_t n = 1;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_5) {
  char s1[] = "";
  char s2[] = "j";
  s21_size_t n = 1;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_6) {
  char s1[] = "1242434246364377659";
  char s2[] = "1242434246364377659";
  s21_size_t n = 19;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_7) {
  char s1[] = "1242434246364377659";
  char s2[] = "1242434246364377659";
  s21_size_t n = 2;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_8) {
  char s1[] = "g124243425";
  char s2[] = "124243424";
  s21_size_t n = 0;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_9) {
  char s1[] = "";
  char s2[] = "";
  s21_size_t n = 1;
  int n1 = strncmp(s1, s2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = s21_strncmp(s1, s2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

// STRPBRK TEST
START_TEST(s21_test_strpbrk_check) {
  char str[8][100] = {
      "Hello, how are you?", " ", "", "1234", "Hell", "how", ""};

  ck_assert_str_eq(s21_strpbrk(str[0], str[1]), strpbrk(str[0], str[1]));
  ck_assert_str_eq(s21_strpbrk(str[0], str[4]), strpbrk(str[0], str[4]));
  ck_assert_str_eq(s21_strpbrk(str[0], str[5]), strpbrk(str[0], str[5]));

  ck_assert_ptr_null(s21_strpbrk(str[0], str[2]));
  ck_assert_ptr_null(strpbrk(str[0], str[2]));
  ck_assert_ptr_null(s21_strpbrk(str[0], str[3]));
  ck_assert_ptr_null(strpbrk(str[0], str[3]));
  ck_assert_ptr_null(s21_strpbrk(str[2], str[5]));
  ck_assert_ptr_null(strpbrk(str[2], str[5]));

  ck_assert_ptr_null(s21_strpbrk(str[2], str[5]));
  ck_assert_ptr_null(strpbrk(str[6], str[6]));
}
END_TEST

// STRSTR TEST
START_TEST(s21_test_strstr_check) {
  char str[8][100] = {
      "Hello, how are you?", " ", "", "1234", "Hell", "how", ""};

  ck_assert_str_eq(s21_strstr(str[0], str[1]), strstr(str[0], str[1]));
  ck_assert_str_eq(s21_strstr(str[0], str[2]), strstr(str[0], str[2]));
  ck_assert_str_eq(s21_strstr(str[0], str[4]), strstr(str[0], str[4]));
  ck_assert_str_eq(s21_strstr(str[0], str[5]), strstr(str[0], str[5]));
  ck_assert_str_eq(s21_strstr(str[2], str[6]), strstr(str[2], str[6]));

  ck_assert_ptr_null(s21_strstr(str[0], str[3]));
  ck_assert_ptr_null(strstr(str[0], str[3]));
  ck_assert_ptr_null(s21_strstr(str[2], str[5]));
  ck_assert_ptr_null(strstr(str[2], str[5]));
}
END_TEST

START_TEST(strstr_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_2) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, P!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_3) {
  char s1[] = "Hello, world!";
  char s2[] = "!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_4) {
  char s1[] =
      "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!";
  char s2[] = "world";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_5) {
  char s1[] = "";
  char s2[] = "";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_6) {
  char s1[] = "Hello, world!";
  char s2[] = "";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_7) {
  char s1[] = "";
  char s2[] = "Hello, P!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_8) {
  char s1[] = "69917020";
  char s2[] = "0";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_9) {
  char s1[] = "69917020";
  char s2[] = "\0";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_10) {
  char s1[] = "69917020";
  char s2[] = "32859160 8v3489-74 tvc4y8719c n4[nqymu uv 4vm9cw";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_11) {
  char s1[] = "1   345 345 345 345 345";
  char s2[] = "345";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_12) {
  char s1[] = "sususususpicioussusususpicious";
  char s2[] = "susp";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_13) {
  char s1[] = "sus";
  char s2[] = "suspi";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

// STRERROR TEST
START_TEST(s21_test_strerror_check) {
  for (int i = -5; i < 138; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

// STRTOK TEST
START_TEST(s21_test_strtok_check) {
  char str[7][100] = {"Hello, how are you?", " ", "", "1234", "ewl", "how", ""};

  ck_assert_str_eq(s21_strtok(str[0], str[1]), strtok(str[0], str[1]));
  ck_assert_str_eq(s21_strtok(str[0], str[2]), strtok(str[0], str[2]));
  ck_assert_str_eq(s21_strtok(str[0], str[3]), strtok(str[0], str[3]));
  ck_assert_str_eq(s21_strtok(str[0], str[4]), strtok(str[0], str[4]));

  ck_assert_str_eq(s21_strtok(str[0], str[5]), strtok(str[0], str[5]));
  ck_assert_str_eq(s21_strtok(str[1], str[4]), strtok(str[1], str[4]));

  ck_assert_ptr_null(s21_strtok(str[2], str[5]));
  ck_assert_ptr_null(strtok(str[2], str[5]));
  ck_assert_ptr_null(s21_strtok(str[2], str[6]));
  ck_assert_ptr_null(strtok(str[2], str[6]));
}
END_TEST

// INSERT TEST
START_TEST(s21_test_insert_check) {
  char str[7][100] = {"Hello, how are you?", " ", "", "1234", "ewl", "how", ""};
  const s21_size_t index[3] = {0, 1, 11};

  void *insert_str = s21_insert(str[0], str[1], index[0]);
  ck_assert_str_eq(insert_str, " Hello, how are you?");
  if (insert_str) free(insert_str);

  insert_str = s21_insert(str[0], str[2], index[0]);
  ck_assert_str_eq(insert_str, "Hello, how are you?");
  if (insert_str) free(insert_str);

  insert_str = s21_insert(str[0], str[3], index[1]);
  ck_assert_str_eq(insert_str, "H1234ello, how are you?");
  if (insert_str) free(insert_str);

  insert_str = s21_insert(str[0], str[3], index[2]);
  ck_assert_str_eq(insert_str, "Hello, how 1234are you?");
  if (insert_str) free(insert_str);

  insert_str = s21_insert(str[2], str[6], index[0]);
  ck_assert_str_eq(insert_str, "");
  if (insert_str) free(insert_str);
}
END_TEST

START_TEST(test_insert_1) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char s4[] = "hello, hELLO, WORLD!world!";
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_3) {
  char *s1 = S21_NULL;
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_4) {
  char s1[30] = "abcdefghij";
  char s3[] = "\'I WAS HERE\'";
  char s4[] = "abc\'I WAS HERE\'defghij";
  s21_size_t num = 3;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_5) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = S21_NULL;
  s21_size_t num = 10;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_6) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char *s4 = S21_NULL;
  s21_size_t num = -1;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_7) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_8) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_9) {
  char s1[] = "wtf";
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_10) {
  char s1[] = "";
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s2, s4);
  if (s2) free(s2);
}
END_TEST

// TO_LOWER TEST
START_TEST(s21_test_to_lower_check) {
  char str[5][100] = {"Hello, hGGw1 are POou?", " ", "", "FFFFF", "sdfshgh"};

  void *to_lower_str = s21_to_lower(str[0]);
  ck_assert_str_eq(to_lower_str, "hello, hggw1 are poou?");
  if (to_lower_str) free(to_lower_str);

  to_lower_str = s21_to_lower(str[1]);
  ck_assert_str_eq(to_lower_str, " ");
  if (to_lower_str) free(to_lower_str);

  to_lower_str = s21_to_lower(str[2]);
  ck_assert_str_eq(to_lower_str, "");
  if (to_lower_str) free(to_lower_str);

  to_lower_str = s21_to_lower(str[3]);
  ck_assert_str_eq(to_lower_str, "fffff");
  if (to_lower_str) free(to_lower_str);

  to_lower_str = s21_to_lower(str[4]);
  ck_assert_str_eq(to_lower_str, "sdfshgh");
  if (to_lower_str) free(to_lower_str);
}
END_TEST

// TO_UPPER TEST
START_TEST(s21_test_to_upper_check) {
  char str[5][100] = {"Hello, hGGw1 are POou?", " ", "", "FFFFF", "sdfshgh"};

  void *to_upper_str = s21_to_upper(str[0]);
  ck_assert_str_eq(to_upper_str, "HELLO, HGGW1 ARE POOU?");
  if (to_upper_str) free(to_upper_str);

  to_upper_str = s21_to_upper(str[1]);
  ck_assert_str_eq(to_upper_str, " ");
  if (to_upper_str) free(to_upper_str);

  to_upper_str = s21_to_upper(str[2]);
  ck_assert_str_eq(to_upper_str, "");
  if (to_upper_str) free(to_upper_str);

  to_upper_str = s21_to_upper(str[3]);
  ck_assert_str_eq(to_upper_str, "FFFFF");
  if (to_upper_str) free(to_upper_str);

  to_upper_str = s21_to_upper(str[4]);
  ck_assert_str_eq(to_upper_str, "SDFSHGH");
  if (to_upper_str) free(to_upper_str);
}
END_TEST

// TRIM TEST
START_TEST(s21_test_trim_check) {
  char *result;
  char *banner = " \n   !* * *'\' Much Ado About Nothing * * '\'*  !\n";
  result = s21_trim(banner, " *!\n '\'");
  if (result) {
    ck_assert_str_eq(result, "Much Ado About Nothing");
    free(result);
  }

  char *banner2 = "xxx Hello, world! xxx ---";
  char *format_str = "x -";
  result = s21_trim(banner2, format_str);
  if (result) {
    ck_assert_str_eq(result, "Hello, world!");
    free(result);
  }

  char *empty_str = "";
  result = s21_trim(empty_str, S21_NULL);
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }

  char *empty_format = "";
  result = s21_trim(S21_NULL, empty_format);
  ck_assert(result == S21_NULL);

  result = s21_trim(banner, empty_format);
  if (result) {
    ck_assert_str_eq(result, "!* * *'' Much Ado About Nothing * * ''*  !");
    free(result);
  }

  result = s21_trim("banner \n", "\n");
  if (result) {
    ck_assert_str_eq(result, "banner ");
    free(result);
  }

  result = s21_trim(empty_str, " \n\0");
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }
}
END_TEST

START_TEST(test_trim_1) {
  char s1[30] = "-?hello, world!";
  char s3[] = "!?-";
  char s4[] = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_3) {
  char *s1 = S21_NULL;
  char s3[] = "";
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_4) {
  char s1[30] = "!!!abcdefghij!?!";
  char s3[] = "!?";
  char s4[] = "abcdefghij";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_5) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = "abc";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_6) {
  char s1[30] = "hello, world!";
  char s3[] = "?!";
  char *s4 = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_7) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_8) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_9) {
  char s1[] = " wtf ";
  char *s3 = S21_NULL;
  char *s4 = "wtf";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

// SPRINTF TEST
START_TEST(s21_test_sprintf_main_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, " "), sprintf(buffer2, " "));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%%%% %%"),
                   sprintf(buffer2, "%%%% %%"));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%*.*d_", 10, 15, 555),
                   sprintf(buffer2, "%*.*d_", 10, 15, 555));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "Hello%d %d", 5, 0),
                   sprintf(buffer2, "Hello%d %d", 5, 0));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "Hello%ld", 50000000000),
                   sprintf(buffer2, "Hello%ld", 50000000000));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "Hello%lu", (unsigned long)50000000000),
                   sprintf(buffer2, "Hello%lu", (unsigned long)50000000000));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%+d % d %#f %g", 5, 0, 5., 54545.),
                   sprintf(buffer2, "%+d % d %#f %g", 5, 0, 5., 54545.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#G %.4f", 5.7, 0.004),
                   sprintf(buffer2, "%#G %.4f", 5.7, 0.004));
  ck_assert_pstr_eq(buffer1, buffer2);

  const char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %#5.10g!";
  double num = 0.0000756589367;
  ck_assert_int_eq(sprintf(buffer1, str3, num, num, num, num, num),
                   s21_sprintf(buffer2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(buffer1, buffer2);

  const char *str4 = "test: %-+ 025.5g!\ntest: %- 020.4g!";
  num = -837564.4753366;
  ck_assert_int_eq(sprintf(buffer1, str4, num, num),
                   s21_sprintf(buffer2, str4, num, num));
  ck_assert_pstr_eq(buffer1, buffer2);
}

END_TEST

// SPRINTF_D TEST
START_TEST(s21_test_sprintf_d_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%d % 10d %-5d %010d %.5d %+d", 50, 40,
                               25874, 4, -875478, 54785),
                   sprintf(buffer2, "%d % 10d %-5d %010d %.5d %+d", 50, 40,
                           25874, 4, -875478, 54785));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.8d", 500),
                   sprintf(buffer2, "%.8d", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.d", 500),
                   sprintf(buffer2, "%.d", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%-30.8d", 500),
                   sprintf(buffer2, "%-30.8d", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%d", __INT_MAX__),
                   sprintf(buffer2, "%d", __INT_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.d", __INT_MAX__),
                   sprintf(buffer2, "%.d", __INT_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%d", -__INT_MAX__),
                   sprintf(buffer2, "%d", -__INT_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%d", 0), sprintf(buffer2, "%d", 0));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(
      s21_sprintf(buffer1, "%ld %ld %ld", 500, -5800L, 10000000000),
      sprintf(buffer2, "%ld %ld %ld", 500L, -5800L, 10000000000));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%ld", __LONG_MAX__),
                   sprintf(buffer2, "%ld", __LONG_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%ld", -__LONG_MAX__),
                   sprintf(buffer2, "%ld", -__LONG_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%hd %hd", (short)500, (short)-580),
                   sprintf(buffer2, "%hd %hd", (short)500, (short)-580));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(sprintf_1_signed) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %d Test";
  int val = -12;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three signed parameters
START_TEST(sprintf_2_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%d Test %d Test %d";
  int val = 012;
  int val2 = -017;
  int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%d Test %d Test %d";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_4_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%ld Test %ld Test %hd GOD %hd";
  long int val = 3088675747373646;
  long val2 = 33030030303;
  short int val3 = 22600;
  short val4 = -120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%3d Test %5d Test %10d";
  int val = -3015;
  int val2 = -11234;
  int val3 = -99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5d Test %.23d Test %3.d TEST %.d %.6d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -38;
  int val5 = -100;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5d Test %-.8d Test %-7d TEST %-.d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeroes
START_TEST(sprintf_8_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%0d Test %0.d Test %0.0d TEST %0d GOD %.d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  int val5 = -0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Pluses
START_TEST(sprintf_9_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%+d Test %+3.d Test %+5.7d TEST %+10d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zero vals
START_TEST(sprintf_10_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%d Test %3.d Test %5.7d TEST %10d %#d %-d %+d %.d % .d";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Spaces
START_TEST(sprintf_11_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d";
  int val = -32;
  int val2 = -8899;
  int val3 = -91918;
  int val4 = -32311;
  int val5 = -23;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Plus
START_TEST(sprintf_12_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%+d Test %+3.d Test %+5.7d TEST %+10d GOD %+.d";
  int val = -32;
  int val2 = -8899;
  int val3 = 91918;
  int val4 = -32311;
  int val5 = 3261;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Hash
START_TEST(sprintf_13_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%#d Test %#3d Test %#5.7d TEST %#.7d Oof %#.d";
  int val = -32;
  int val2 = 8899;
  int val3 = -91918;
  int val4 = 32311;
  int val5 = -8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// ZERO flag
START_TEST(sprintf_14_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%0d Test %06d Test %05.7d TEST %0.7d Oof %0.d";
  int val = -32;
  int val2 = 8899;
  int val3 = -91918;
  int val4 = -32311;
  int val5 = -8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Asterisk
START_TEST(sprintf_15_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%*d Test %-*d Test %*.*d TEST %.*d";
  int val = 32;
  int val2 = 8899;
  int val3 = -919;
  int val4 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Simple extra test
START_TEST(sprintf_16_signed) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%d";
  int val = 12;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_17_signed) {
  char str1[1024] = "";
  char str2[1024] = "";
  int val = -75;
  sprintf(str1, "Hello %d %023d", val, val);  // нет нулей перед числом(бонус)
  s21_sprintf(str2, "Hello %d %023d", val, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_signed) {
  char str1[300];
  char str2[300];
  char *str3 = "%ld Test %ld Test %hd GOD %hd tt %d tt %d";
  long int val = LONG_MAX;
  long val2 = LONG_MIN;
  short int val3 = SHRT_MAX;
  short val4 = SHRT_MIN;
  int val5 = INT_MAX;
  int val6 = INT_MIN;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5, val6),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5, val6));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_19_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%- d Test %- 15d sdasda %- 15d sdsad %- d";
  int val = -3231;
  int val2 = -3231;
  int val3 = 3231;
  int val4 = 3231;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// SPRINTF_U TEST
START_TEST(s21_test_sprintf_u_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%u", (unsigned)500),
                   sprintf(buffer2, "%u", (unsigned)500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.8u", (unsigned)500),
                   sprintf(buffer2, "%.8u", (unsigned)500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.u", (unsigned)500),
                   sprintf(buffer2, "%.u", (unsigned)500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%u", (unsigned)-500),
                   sprintf(buffer2, "%u", (unsigned)-500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%lu", (unsigned long)10000000000),
                   sprintf(buffer2, "%lu", (unsigned long)10000000000));

  ck_assert_int_eq(s21_sprintf(buffer1, "%lu", (unsigned long)-10000000000),
                   sprintf(buffer2, "%lu", (unsigned long)-10000000000));

  ck_assert_int_eq(s21_sprintf(buffer1, "%u", (unsigned)0),
                   sprintf(buffer2, "%u", (unsigned)0));

  ck_assert_int_eq(s21_sprintf(buffer1, "%hu", (unsigned short)50),
                   sprintf(buffer2, "%hu", (unsigned short)50));

  ck_assert_int_eq(s21_sprintf(buffer1, "%lu", (unsigned long)__LONG_MAX__ * 2),
                   sprintf(buffer2, "%lu", (unsigned long)__LONG_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(
      s21_sprintf(buffer1, "%lu", (unsigned long)-__LONG_MAX__ * 2),
      sprintf(buffer2, "%lu", (unsigned long)-__LONG_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%u", (unsigned)__INT_MAX__ * 2),
                   sprintf(buffer2, "%u", (unsigned)__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%u", (unsigned)-__INT_MAX__ * 2),
                   sprintf(buffer2, "%u", (unsigned)-__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// One parameter unsigned
START_TEST(sprintf_1_unsigned) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %u Test";
  unsigned int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three unsigned parameters
START_TEST(sprintf_2_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%u Test %u Test %u";
  unsigned int val = 012;
  unsigned int val2 = 017;
  unsigned int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%u Test %u Test %u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_4_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%lu Test %lu Test %hu GOD %hu";
  long unsigned int val = 3088675747373646;
  long unsigned val2 = 33030030303;
  unsigned short val3 = 22600;
  unsigned short val4 = 120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%3u Test %5u Test %10u";
  unsigned int val = 3015;
  unsigned int val2 = 01234;
  unsigned int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5u Test %.23u Test %3.u TEST %.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 38;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5u Test %-.8u Test %-7u TEST %-.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zerues
START_TEST(sprintf_8_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%0u Test %0.u Test %0.0u TEST %0u GOD %.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  unsigned int val5 = 0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeru vals
START_TEST(sprintf_10_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%u Test %3.u Test %5.7u TEST %10u %#u %-u %+u %.u % .u";
  unsigned int val = 0;
  sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Hash
START_TEST(sprintf_13_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%#u Test %#3u Test %#5.7u TEST %#.7u Ouf %#.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Asterisk
START_TEST(sprintf_15_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%*u Test %-*u Test %*.*u TEST %.*u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 919;
  unsigned int val4 = 32311;
  unsigned int ast = 2;
  unsigned int ast2 = 5;
  unsigned int ast3 = 4;
  unsigned int ast4 = 10;
  unsigned int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "fdsdsds %lu";
  unsigned long int val = ULONG_MAX;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// SPRINTF_O TEST
START_TEST(s21_test_sprintf_o_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%o", 500),
                   sprintf(buffer2, "%o", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#o", 500),
                   sprintf(buffer2, "%#o", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.8o", 500),
                   sprintf(buffer2, "%.8o", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.o", 500),
                   sprintf(buffer2, "%.o", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%o", 0), sprintf(buffer2, "%o", 0));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%o", -500),
                   sprintf(buffer2, "%o", -500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%ho", (unsigned short)50),
                   sprintf(buffer2, "%ho", (unsigned short)50));

  ck_assert_int_eq(s21_sprintf(buffer1, "%lo", (unsigned long)__LONG_MAX__ * 2),
                   sprintf(buffer2, "%lo", (unsigned long)__LONG_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%o", (unsigned)__INT_MAX__ * 2),
                   sprintf(buffer2, "%o", (unsigned)__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%o", (unsigned)-__INT_MAX__ * 2),
                   sprintf(buffer2, "%o", (unsigned)-__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_sX TEST
START_TEST(s21_test_sprintf_x_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%x", 500),
                   sprintf(buffer2, "%x", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#x", 500),
                   sprintf(buffer2, "%#x", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.8x", 500),
                   sprintf(buffer2, "%.8x", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.x", 500),
                   sprintf(buffer2, "%.x", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%x", 0), sprintf(buffer2, "%x", 0));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%x", -500),
                   sprintf(buffer2, "%x", -500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%hx", (unsigned short)50),
                   sprintf(buffer2, "%hx", (unsigned short)50));

  ck_assert_int_eq(s21_sprintf(buffer1, "%lx", (unsigned long)__LONG_MAX__ * 2),
                   sprintf(buffer2, "%lx", (unsigned long)__LONG_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(
      s21_sprintf(buffer1, "%lx", (unsigned long)-__LONG_MAX__ * 2),
      sprintf(buffer2, "%lx", (unsigned long)-__LONG_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%x", (unsigned)__INT_MAX__ * 2),
                   sprintf(buffer2, "%x", (unsigned)__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%x", (unsigned)-__INT_MAX__ * 2),
                   sprintf(buffer2, "%x", (unsigned)-__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_X TEST
START_TEST(s21_test_sprintf_X_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%X", 500),
                   sprintf(buffer2, "%X", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#X", 500),
                   sprintf(buffer2, "%#X", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.8X", 500),
                   sprintf(buffer2, "%.8X", 500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%X", 0), sprintf(buffer2, "%X", 0));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%X", -500),
                   sprintf(buffer2, "%X", -500));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%hX", (unsigned short)50),
                   sprintf(buffer2, "%hX", (unsigned short)50));

  ck_assert_int_eq(s21_sprintf(buffer1, "%lX", (unsigned long)__LONG_MAX__ * 2),
                   sprintf(buffer2, "%lX", (unsigned long)__LONG_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(
      s21_sprintf(buffer1, "%lX", (unsigned long)-__LONG_MAX__ * 2),
      sprintf(buffer2, "%lX", (unsigned long)-__LONG_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%X", (unsigned)__INT_MAX__ * 2),
                   sprintf(buffer2, "%X", (unsigned)__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%X", (unsigned)-__INT_MAX__ * 2),
                   sprintf(buffer2, "%X", (unsigned)-__INT_MAX__ * 2));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_C TEST
START_TEST(s21_test_sprintf_c_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  for (int i = 0; i < 256; i++) {
    ck_assert_int_eq(s21_sprintf(buffer1, "%c", i), sprintf(buffer2, "%c", i));
    ck_assert_pstr_eq(buffer1, buffer2);
  }

  ck_assert_int_eq(s21_sprintf(buffer1, "%-20c", 55),
                   sprintf(buffer2, "%-20c", 55));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(sprintf_1_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 9;
  int b = 10;
  int c = 17;
  int d = 66;
  int e = 124;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = -6;
  int b = -10;
  int c = -17;
  int d = -66;
  int e = -124;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 60;
  int b = 50;
  int c = 1744;
  int d = 386;
  int e = 257;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 60;
  int b = 50;
  int c = 1744;
  int d = 386;
  int e = 257;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// SPRINTF_S TEST
START_TEST(s21_test_sprintf_s_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%-20s", "Hello!"),
                   sprintf(buffer2, "%-20s", "Hello!"));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%20s", "Hello!"),
                   sprintf(buffer2, "%20s", "Hello!"));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%20.2s", "Hello!"),
                   sprintf(buffer2, "%20.2s", "Hello!"));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%20.20s", "Hello!"),
                   sprintf(buffer2, "%20.20s", "Hello!"));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%20.20s", ""),
                   sprintf(buffer2, "%20.20s", ""));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%20.s", ""),
                   sprintf(buffer2, "%20.s", ""));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(sprintf_1_string) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %s Test";
  char *val = "Why am I here?!";
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three string parameters
START_TEST(sprintf_2_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s Test %s Test %s";
  char *val = "I'm so tired";
  char *val2 = "Who invented this?";
  char *val3 = "This project gave me hemmoroids";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s Test %s Test %s";
  char *val = "Don't need this test";
  char *val2 = "Just for the kicks";
  char *val3 = "Lol";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%3s Test %5s Test %10s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore";
  char *val3 = "PPAP";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5s Test %.23s Test %3.s TEST %.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5s Test %-.8s Test %-7s TEST %-.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeroes
START_TEST(sprintf_8_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%0s Test %0.s Test %0.0s TEST %0s GOD %.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Pluses
START_TEST(sprintf_9_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%+s Test %+3.s Test %5.7s TEST %10s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "abcd";
  char *val4 = "I don't feel so good";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zero vals
START_TEST(sprintf_10_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%s Test %3.s Test %5.7s TEST %10s %#s %-s %+s %.s % .s";
  char *val = NULL;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Spaces
START_TEST(sprintf_11_string) {
  char str1[200];
  char str2[200];
  char *str3 = "% s Test % 3.s Test % 5.7s TEST % 10s GOD %.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Plus
START_TEST(sprintf_12_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%+s Test %+3.s Test %+5.7s TEST %+10s GOD %+.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Hash
START_TEST(sprintf_13_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%#s Test %#3s Test %#5.7s TEST %#.7s Oof %#.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// ZERO flag
// START_TEST(sprintf_14_string) {
//   char str1[200];
//   char str2[200];
//   char *str3 = "%0s Test %06s Test %05.7s TEST %0.7s Oof %0.s";
//   char *val = "WHAT IS THIS";
//   char *val2 = "idx";
//   char *val3 = "PPAP";
//   char *val4 = "I don't";
//   char *val5 = "What is lovin'?!";
//   ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
//                    s21_sprintf(str2, str3, val, val2, val3, val4, val5));
//   ck_assert_pstr_eq(str1, str2);
// }
// END_TEST

// Asterisk
START_TEST(sprintf_15_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%*s Test %-*s Test %*.*s TEST %.*s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s %s %s %% %d";
  char *val = "This";
  char *val2 = "\0";
  int val3 = 65;
  char *val4 = "string";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val4, val3),
                   s21_sprintf(str2, str3, val, val2, val4, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// SPRINTF_P TEST
START_TEST(s21_test_sprintf_p_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};
  char *str = "";

  ck_assert_int_eq(s21_sprintf(buffer1, "%p", str),
                   sprintf(buffer2, "%p", str));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%20p", str),
                   sprintf(buffer2, "%20p", str));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%p", S21_NULL),
                   sprintf(buffer2, "%p", S21_NULL));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_F TEST
START_TEST(s21_test_sprintf_f_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", 0.), sprintf(buffer2, "%f", 0.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", 1000.),
                   sprintf(buffer2, "%f", 1000.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", .0005),
                   sprintf(buffer2, "%f", .0005));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", .0001),
                   sprintf(buffer2, "%f", .0001));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", INFINITY),
                   sprintf(buffer2, "%f", INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", -INFINITY),
                   sprintf(buffer2, "%f", -INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", .000999999999999999),
                   sprintf(buffer2, "%f", .000999999999999999));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", 100.9999999),
                   sprintf(buffer2, "%f", 100.9999999));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.f", .000999999999999999),
                   sprintf(buffer2, "%.f", .000999999999999999));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.f", .999999999999999),
                   sprintf(buffer2, "%.f", .999999999999999));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.f", -.999999999999999),
                   sprintf(buffer2, "%.f", -.999999999999999));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", 1.000001),
                   sprintf(buffer2, "%f", 1.000001));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%+.10f", 1000.),
                   sprintf(buffer2, "%+.10f", 1000.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%08.10f", 1000.),
                   sprintf(buffer2, "%08.10f", 1000.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#.10f", 1000.),
                   sprintf(buffer2, "%#.10f", 1000.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%f", -1000.),
                   sprintf(buffer2, "%f", -1000.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Lf", 4587.789547L),
                   sprintf(buffer2, "%Lf", 4587.789547L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Lf", -8.89547L),
                   sprintf(buffer2, "%Lf", -8.89547L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Lf", 0.L),
                   sprintf(buffer2, "%Lf", 0.L));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_sE_TEST
START_TEST(s21_test_sprintf_e_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%e", 0.), sprintf(buffer2, "%e", 0.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%e", 0.00008),
                   sprintf(buffer2, "%e", 0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%e", -0.00008),
                   sprintf(buffer2, "%e", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.2e", -0.00008),
                   sprintf(buffer2, "%.2e", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.e", -0.00008),
                   sprintf(buffer2, "%.e", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#.e", -0.00008),
                   sprintf(buffer2, "%#.e", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12e", -0.00008777),
                   sprintf(buffer2, "%.12e", -0.00008777));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%e", 2e+145),
                   sprintf(buffer2, "%e", 2e+145));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Le", 2e+145L),
                   sprintf(buffer2, "%Le", 2e+145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Le", 2e-145L),
                   sprintf(buffer2, "%Le", 2e-145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12e", __DBL_MAX__),
                   sprintf(buffer2, "%.12e", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.6e", __DBL_MAX__),
                   sprintf(buffer2, "%.6e", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Le", __LDBL_MAX__),
                   sprintf(buffer2, "%Le", __LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Le", -__LDBL_MAX__),
                   sprintf(buffer2, "%Le", -__LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%e", INFINITY),
                   sprintf(buffer2, "%e", INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%e", -INFINITY),
                   sprintf(buffer2, "%e", -INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_E_TEST
START_TEST(s21_test_sprintf_E_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%E", 0.), sprintf(buffer2, "%E", 0.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%E", 0.00008),
                   sprintf(buffer2, "%E", 0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%E", -0.00008),
                   sprintf(buffer2, "%E", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.2E", -0.00008),
                   sprintf(buffer2, "%.2E", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.E", -0.00008),
                   sprintf(buffer2, "%.E", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#.E", -0.00008),
                   sprintf(buffer2, "%#.E", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12E", -0.00008777),
                   sprintf(buffer2, "%.12E", -0.00008777));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%E", 2e+145),
                   sprintf(buffer2, "%E", 2e+145));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LE", 2e+145L),
                   sprintf(buffer2, "%LE", 2e+145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LE", 2e-145L),
                   sprintf(buffer2, "%LE", 2e-145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12E", __DBL_MAX__),
                   sprintf(buffer2, "%.12E", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.6E", __DBL_MAX__),
                   sprintf(buffer2, "%.6E", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LE", __LDBL_MAX__),
                   sprintf(buffer2, "%LE", __LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LE", -__LDBL_MAX__),
                   sprintf(buffer2, "%LE", -__LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%E", INFINITY),
                   sprintf(buffer2, "%E", INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%E", -INFINITY),
                   sprintf(buffer2, "%E", -INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_g_TEST
START_TEST(s21_test_sprintf_g_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%g", 0.), sprintf(buffer2, "%g", 0.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%g", 0.00008),
                   sprintf(buffer2, "%g", 0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%g", -0.00008),
                   sprintf(buffer2, "%g", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.2g", -0.00008),
                   sprintf(buffer2, "%.2g", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.g", -0.00008),
                   sprintf(buffer2, "%.g", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.5g", 0.99999999),
                   sprintf(buffer2, "%.5g", 0.99999999));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#.5g", 1.1),
                   sprintf(buffer2, "%#.5g", 1.1));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%g", 10000200.),
                   sprintf(buffer2, "%g", 10000200.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#.g", -0.00008),
                   sprintf(buffer2, "%#.g", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12g", -0.00008777),
                   sprintf(buffer2, "%.12g", -0.00008777));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%g", 2e+145),
                   sprintf(buffer2, "%g", 2e+145));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Lg", 2e+145L),
                   sprintf(buffer2, "%Lg", 2e+145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Lg", 2e-145L),
                   sprintf(buffer2, "%Lg", 2e-145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12g", __DBL_MAX__),
                   sprintf(buffer2, "%.12g", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.6g", __DBL_MAX__),
                   sprintf(buffer2, "%.6g", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Lg", __LDBL_MAX__),
                   sprintf(buffer2, "%Lg", __LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%Lg", -__LDBL_MAX__),
                   sprintf(buffer2, "%Lg", -__LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%g", INFINITY),
                   sprintf(buffer2, "%g", INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%g", -INFINITY),
                   sprintf(buffer2, "%g", -INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

// SPRINTF_G_TEST
START_TEST(s21_test_sprintf_G_check) {
  char buffer1[200] = {0};
  char buffer2[200] = {0};

  ck_assert_int_eq(s21_sprintf(buffer1, "%G", 0.), sprintf(buffer2, "%G", 0.));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%G", 0.00008),
                   sprintf(buffer2, "%G", 0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%G", -0.00008),
                   sprintf(buffer2, "%G", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.2G", -0.00008),
                   sprintf(buffer2, "%.2G", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.G", -0.00008),
                   sprintf(buffer2, "%.G", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%#.G", -0.00008),
                   sprintf(buffer2, "%#.G", -0.00008));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12G", -0.00008777),
                   sprintf(buffer2, "%.12G", -0.00008777));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%G", 2e+145),
                   sprintf(buffer2, "%G", 2e+145));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LG", 2e+145L),
                   sprintf(buffer2, "%LG", 2e+145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LG", 2e-145L),
                   sprintf(buffer2, "%LG", 2e-145L));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.12G", __DBL_MAX__),
                   sprintf(buffer2, "%.12G", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%.6G", __DBL_MAX__),
                   sprintf(buffer2, "%.6G", __DBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LG", __LDBL_MAX__),
                   sprintf(buffer2, "%LG", __LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%LG", -__LDBL_MAX__),
                   sprintf(buffer2, "%LG", -__LDBL_MAX__));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%G", INFINITY),
                   sprintf(buffer2, "%G", INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);

  ck_assert_int_eq(s21_sprintf(buffer1, "%G", -INFINITY),
                   sprintf(buffer2, "%G", -INFINITY));
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_s21_sscanf) {
  int a = 0, b = 0, c = 0, d = 0;
  short sa = 0;
  short sb = 0;

  ck_assert_int_eq(s21_sscanf("123", "%a", &a), -1);
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("", "%d", &a), sscanf("", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf(" ", "%d", &a), sscanf(" ", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("123", "%d", &a), sscanf("123", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("123456", "%hd", &sa),
                   sscanf("123456", "%hd", &sb));
  ck_assert_int_eq(sa, sb);

  ck_assert_int_eq(s21_sscanf("98765", "%3d", &a), sscanf("98765", "%3d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("98765", "%3hd%d", &sa, &a),
                   sscanf("98765", "%3hd%d", &sb, &b));
  ck_assert_int_eq(sa, sb);
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("111%111", "%d%%%d", &a, &b),
                   sscanf("111%111", "%d%%%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("222%222", "%d %d", &a, &b),
                   sscanf("222%222", "%d %d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("333abcde333", "%dabcde%d", &a, &b),
                   sscanf("333abcde333", "%dabcde%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("44", "%1d %1d", &a, &b),
                   sscanf("44", "%1d %1d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf("4 4", "%d%d", &a, &b),
                   sscanf("4 4", "%d%d", &c, &d));
  ck_assert_int_eq(a, c);
  ck_assert_int_eq(b, d);

  ck_assert_int_eq(s21_sscanf(" ", "%%"), sscanf(" ", "%%"));

  ck_assert_int_eq(s21_sscanf("123", ""), 0);
  ck_assert_int_eq(s21_sscanf("123", "a"), sscanf("123", "a"));

  ck_assert_int_eq(s21_sscanf("123123", "%*3d%d", &a),
                   sscanf("123123", "%*3d%d", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_d) {
  short sa = 0, sb = 0, sc = 0, sd = 0;
  int a = 0, b = 0;
  long la = 0, lb = 0, lc = 0, ld = 0;

  ck_assert_int_eq(s21_sscanf("123456123", "%6hd%hd", &sa, &sb),
                   sscanf("123456123", "%6hd%hd", &sc, &sd));
  ck_assert_int_eq(sa, sc);
  ck_assert_int_eq(sb, sd);

  ck_assert_int_eq(s21_sscanf("12345678901", "%d", &a),
                   sscanf("12345678901", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901", "%d", &a),
                   sscanf("-12345678901", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901", "%ld", &la),
                   sscanf("-12345678901", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("12345678901234567890", "%ld", &la),
                   sscanf("12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("-12345678901234567890", "%ld", &la),
                   sscanf("-12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  lb = 0;
  ck_assert_int_eq(s21_sscanf("19223372036854775807", "%ld%ld", &la, &lb),
                   sscanf("19223372036854775807", "%ld%ld", &lc, &ld));
  ck_assert_int_eq(la, lc);
  ck_assert_int_eq(lb, ld);

  ck_assert_int_eq(s21_sscanf("12345678901234567890", "%d", &a),
                   sscanf("12345678901234567890", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-12345678901234567890", "%d", &a),
                   sscanf("-12345678901234567890", "%d", &b));
  ck_assert_int_eq(a, b);

  long long lla = 0, llb = 0, llc = 0, lld = 0;
  ck_assert_int_eq(s21_sscanf("123456789012345", "%lld", &lla),
                   sscanf("123456789012345", "%lld", &llb));
  ck_assert_int_eq(lla, llb);

  ck_assert_int_eq(
      s21_sscanf("-123456789012345678901", "%21lld%lld", &lla, &llb),
      sscanf("-123456789012345678901", "%21lld%lld", &llc, &lld));
  ck_assert_int_eq(lla, llc);
  ck_assert_int_eq(llb, lld);

  ck_assert_int_eq(s21_sscanf("987654321", "%lld", &lla),
                   sscanf("987654321", "%lld", &llb));
  ck_assert_int_eq(lla, llb);

  ck_assert_int_eq(s21_sscanf("abc", "%d", &a), sscanf("abc", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-abc", "%d", &a), sscanf("-abc", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("123", "%5d", &a), sscanf("123", "%5d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("++321", "%d", &a), sscanf("++321", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+321", "%d", &a), sscanf("+321", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+98765", "%*5d%d", &a),
                   sscanf("+98765", "%*5d%d", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_u) {
  unsigned int a = 0, b = 0;
  unsigned long la = 0, lb = 0;
  unsigned long long lla = 0, llb = 0;

  ck_assert_int_eq(s21_sscanf("3223476867342", "%u", &a),
                   sscanf("3223476867342", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("3223476867342", "%u", &a),
                   sscanf("3223476867342", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("7623476478263678234768", "%llu", &lla),
                   sscanf("7623476478263678234768", "%llu", &llb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("57632132323269778378215791", "%22llu", &lla),
                   sscanf("57632132323269778378215791", "%22llu", &llb));
  ck_assert_int_eq(la, lb);

  unsigned short sa = 0, sb = 0;
  ck_assert_int_eq(s21_sscanf("97853297", "%5hu%lu", &sa, &la),
                   sscanf("97853297", "%5hu%lu", &sb, &lb));
  ck_assert_int_eq(sa, sb);
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("263", "%5u", &a), sscanf("263", "%5u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-263", "%u", &a), sscanf("-263", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+263", "%u", &a), sscanf("+263", "%u", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+263", "%*2u%u", &a),
                   sscanf("+263", "%*2u%u", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_xX) {
  unsigned int a = 0, b = 0;

  ck_assert_int_eq(s21_sscanf("0x1234567890", "%x", &a),
                   sscanf("0x1234567890", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0X1234567890", "%x", &a),
                   sscanf("0X1234567890", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0x1abcdef", "%X", &a),
                   sscanf("0x1abcdef", "%X", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0X1ACDEF", "%X", &a),
                   sscanf("0X1ACDEF", "%X", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0x1aBcDeF", "%x", &a),
                   sscanf("0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("01aBcDeF", "%x", &a),
                   sscanf("01AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("01aBcDeF", "%X", &a),
                   sscanf("01AbCdEf", "%X", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("x1aBcDeF", "%x", &a),
                   sscanf("x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(s21_sscanf("X1aBcDeF", "%X", &a),
                   sscanf("X1AbCdEf", "%X", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-0x1aBcDeF", "%x", &a),
                   sscanf("-0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("++0x1aBcDeF", "%x", &a),
                   sscanf("++0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+0x1aBcDeF", "%x", &a),
                   sscanf("+0x1AbCdEf", "%x", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_o) {
  unsigned int a = 0, b = 0;

  ck_assert_int_eq(s21_sscanf("01234567", "%o", &a),
                   sscanf("01234567", "%o", &b));
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(s21_sscanf("21234567", "%o", &a),
                   sscanf("21234567", "%o", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-01234567", "%o", &a),
                   sscanf("-01234567", "%o", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0-1234567", "%o", &a),
                   sscanf("0-1234567", "%o", &b));

  a = 0, b = 0;
  ck_assert_int_eq(s21_sscanf("++01234567", "%o", &a),
                   sscanf("++01234567", "%o", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+01234567", "%o", &a),
                   sscanf("+01234567", "%o", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_i) {
  int a = 0, b = 0;

  ck_assert_int_eq(s21_sscanf("1234567890", "%i", &a),
                   sscanf("1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("01234567", "%i", &a),
                   sscanf("01234567", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0x1234567890", "%i", &a),
                   sscanf("0x1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-1234567890", "%i", &a),
                   sscanf("-1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-01234567", "%i", &a),
                   sscanf("-01234567", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-0x1234567890", "%i", &a),
                   sscanf("-0x1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("--1234567890", "%i", &a),
                   sscanf("--1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-0-1234567890", "%i", &a),
                   sscanf("-0-1234567890", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-0x-ab34567890", "%i", &a),
                   sscanf("-0x-ab34567890", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("123abcdef", "%i", &a),
                   sscanf("123abcdef", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("a123abcdef", "%i", &a),
                   sscanf("a123abcdef", "%i", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+0xfaf", "%i", &a), sscanf("+0xfaf", "%i", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_p) {
  void *a = NULL, *b = NULL;
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%p", &a),
                   sscanf("0x1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);

  ck_assert_int_eq(s21_sscanf("0xabc", "%p", &a), sscanf("0xabc", "%p", &b));
  ck_assert_ptr_eq(a, b);

  ck_assert_int_eq(s21_sscanf("1234567890", "%p", &a),
                   sscanf("1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);

  ck_assert_int_eq(s21_sscanf("-1234567890", "%p", &a),
                   sscanf("-1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+1234567890", "%p", &a),
                   sscanf("+1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_c) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(s21_sscanf("123", "%c", buf1), sscanf("123", "%c", buf2));
  ck_assert_int_eq(buf1[0], buf2[0]);

  ck_assert_int_eq(s21_sscanf("qwertyuiop", "%9c", buf1),
                   sscanf("qwertyuiop", "%9c", buf2));
  ck_assert_str_eq(buf1, buf2);

  ck_assert_int_eq(s21_sscanf("qwe", "%2c", buf1), sscanf("qwe", "%2c", buf2));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sscanf_s) {
  char buf1[100] = {0}, buf2[100] = {0};
  char buf3[100] = {0}, buf4[100] = {0};

  ck_assert_int_eq(s21_sscanf("1234567890", "%s", buf1),
                   sscanf("1234567890", "%s", buf2));
  ck_assert_str_eq(buf1, buf2);

  ck_assert_int_eq(s21_sscanf("abcdefghk", "%5s", buf1),
                   sscanf("abcdefghk", "%5s", buf2));
  ck_assert_str_eq(buf1, buf2);

  ck_assert_int_eq(s21_sscanf("", "%s", buf1), sscanf("", "%s", buf2));
  ck_assert_str_eq(buf1, buf2);

  ck_assert_int_eq(s21_sscanf("123 456", "%s %s", buf1, buf3),
                   sscanf("123 456", "%s %s", buf2, buf4));
  ck_assert_str_eq(buf1, buf2);
  ck_assert_str_eq(buf3, buf4);
}
END_TEST

START_TEST(test_sscanf_n) {
  char buf1[100] = {0}, buf2[100] = {0};
  int a = 0, b = 0;
  ck_assert_int_eq(s21_sscanf("1234567890", "%5s%n", buf1, &a),
                   sscanf("1234567890", "%5s%n", buf2, &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("", "%s%n", buf1, &a),
                   sscanf("", "%s%n", buf2, &b));
  ck_assert_int_eq(a, b);

  int i = 0, j = 0;
  ck_assert_int_eq(s21_sscanf("123456", "%*3d%d%n", &i, &a),
                   sscanf("123456", "%*3d%d%n", &j, &b));
  ck_assert_int_eq(a, b);
}
END_TEST

long double ldabs(long double x) { return x < 0 ? -x : x; }

s21_bool s21_float_eq(float a, float b) { return fabs(a - b) < 0.00001; }
s21_bool s21_double_eq(double a, double b) { return fabs(a - b) < 0.00001; }
s21_bool s21_ldouble_eq(long double a, long double b) {
  return ldabs(a - b) < 0.00001;
}

START_TEST(test_sscanf_f) {
  float a = 0, b = 0;
  double da = 0, db = 0;
  long double lda = 0, ldb = 0;
  ck_assert_int_eq(s21_sscanf("123.456", "%f", &a),
                   sscanf("123.456", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("123.456", "%lf", &da),
                   sscanf("123.456", "%lf", &db));
  ck_assert(s21_double_eq(da, db));

  ck_assert_int_eq(s21_sscanf("123.456", "%Lf", &lda),
                   sscanf("123.456", "%Lf", &ldb));
  ck_assert(s21_ldouble_eq(lda, ldb));

  ck_assert_int_eq(s21_sscanf("123.456", "%hf", &a),
                   sscanf("123.456", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("", "%f", &a), sscanf("", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("-", "%f", &a), sscanf("-", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("123.456", "%6f", &a),
                   sscanf("123.456", "%6f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf(".", "%f", &a), sscanf(".", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("abc", "%f", &a), sscanf("abc", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("123.", "%f", &a), sscanf("123.", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf(".123", "%f", &a), sscanf(".123", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("123.abc", "%f", &a),
                   sscanf("123.abc", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("222", "%f", &a), sscanf("222", "%f", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("abc", "%f", &a), sscanf("abc", "%f", &b));
  ck_assert(s21_float_eq(a, b));
}
END_TEST

START_TEST(test_sscanf_gG) {
  float a = 0, b = 0;
  float c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  float c2 = 0, d2 = 0, e2 = 0, f2 = 0;
  int res1 = 0, res2 = 0;

  ck_assert_int_eq(s21_sscanf("iNf", "%g", &a), sscanf("iNf", "%g", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));
  ck_assert_ldouble_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+inf", "%G", &a), sscanf("+inf", "%G", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));
  ck_assert_ldouble_eq(a, b);

  res1 = s21_sscanf("-inF     InF inF INF", "%G %G %G %G", &c1, &d1, &e1, &f1);
  res2 = sscanf("-inF     InF inF INF", "%G %G %G %G", &c2, &d2, &e2, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(e1, e2);
  ck_assert_ldouble_eq(f1, f2);
}
END_TEST

START_TEST(test_sscanf_eE) {
  float a = 0, b = 0;

  ck_assert_int_eq(s21_sscanf("nan", "%e", &a), sscanf("nan", "%e", &b));
  ck_assert(isnan(a));
  ck_assert(isnan(b));

  ck_assert_int_eq(s21_sscanf("-inf", "%E", &a), sscanf("-inf", "%E", &b));
  ck_assert(isinf(a));
  ck_assert(isinf(b));

  ck_assert_int_eq(s21_sscanf("1.23e-4", "%e", &a),
                   sscanf("1.23e-4", "%e", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("1.23e4", "%e", &a), sscanf("1.23e4", "%e", &b));
  ck_assert(s21_float_eq(a, b));

  ck_assert_int_eq(s21_sscanf("1.23E10", "%6E", &a),
                   sscanf("1.23E10", "%6E", &b));
  ck_assert(s21_float_eq(a, b));
}
END_TEST

// MAIN PART
Suite *s21_sprintf_suit(void) {
  Suite *suite_sprintf = suite_create("s21_sprintf");
  TCase *tcase_sprintf = tcase_create("s21_sprintf_tcase");

  tcase_add_test(tcase_sprintf, s21_test_sprintf_main_check);

  suite_add_tcase(suite_sprintf, tcase_sprintf);
  return suite_sprintf;
}

Suite *s21_sprintf_d_suit(void) {
  Suite *suite = suite_create("s21_sprintf_d");
  TCase *tcase = tcase_create("s21_sprintf_d_tcase");

  tcase_add_test(tcase, s21_test_sprintf_d_check);
  tcase_add_test(tcase, sprintf_1_signed);
  tcase_add_test(tcase, sprintf_2_signed);
  tcase_add_test(tcase, sprintf_3_signed);
  tcase_add_test(tcase, sprintf_4_signed);
  tcase_add_test(tcase, sprintf_5_signed);
  tcase_add_test(tcase, sprintf_6_signed);
  tcase_add_test(tcase, sprintf_7_signed);
  tcase_add_test(tcase, sprintf_8_signed);
  tcase_add_test(tcase, sprintf_9_signed);
  tcase_add_test(tcase, sprintf_10_signed);
  tcase_add_test(tcase, sprintf_11_signed);
  tcase_add_test(tcase, sprintf_12_signed);
  tcase_add_test(tcase, sprintf_13_signed);
  tcase_add_test(tcase, sprintf_14_signed);
  tcase_add_test(tcase, sprintf_15_signed);
  tcase_add_test(tcase, sprintf_16_signed);
  tcase_add_test(tcase, sprintf_17_signed);
  tcase_add_test(tcase, sprintf_18_signed);
  tcase_add_test(tcase, sprintf_19_signed);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_u_suit(void) {
  Suite *suite = suite_create("s21_sprintf_u");
  TCase *tcase = tcase_create("s21_sprintf_u_tcase");

  tcase_add_test(tcase, s21_test_sprintf_u_check);
  tcase_add_test(tcase, sprintf_1_unsigned);
  tcase_add_test(tcase, sprintf_2_unsigned);
  tcase_add_test(tcase, sprintf_3_unsigned);
  tcase_add_test(tcase, sprintf_4_unsigned);
  tcase_add_test(tcase, sprintf_5_unsigned);
  tcase_add_test(tcase, sprintf_6_unsigned);
  tcase_add_test(tcase, sprintf_7_unsigned);
  tcase_add_test(tcase, sprintf_8_unsigned);
  tcase_add_test(tcase, sprintf_10_unsigned);
  tcase_add_test(tcase, sprintf_13_unsigned);
  tcase_add_test(tcase, sprintf_15_unsigned);
  tcase_add_test(tcase, sprintf_16_unsigned);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_o_suit(void) {
  Suite *suite = suite_create("s21_sprintf_o");
  TCase *tcase = tcase_create("s21_sprintf_o_tcase");

  tcase_add_test(tcase, s21_test_sprintf_o_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_x_suit(void) {
  Suite *suite = suite_create("s21_sprintf_x");
  TCase *tcase = tcase_create("s21_sprintf_x_tcase");

  tcase_add_test(tcase, s21_test_sprintf_x_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_X_suit(void) {
  Suite *suite = suite_create("s21_sprintf_X");
  TCase *tcase = tcase_create("s21_sprintf_X_tcase");

  tcase_add_test(tcase, s21_test_sprintf_X_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_c_suit(void) {
  Suite *suite = suite_create("s21_sprintf_c");
  TCase *tcase = tcase_create("s21_sprintf_c_tcase");

  tcase_add_test(tcase, s21_test_sprintf_c_check);
  tcase_add_test(tcase, sprintf_1_c);
  tcase_add_test(tcase, sprintf_2_c);
  tcase_add_test(tcase, sprintf_3_c);
  tcase_add_test(tcase, sprintf_4_c);
  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_s_suit(void) {
  Suite *suite = suite_create("s21_sprintf_s");
  TCase *tcase = tcase_create("s21_sprintf_s_tcase");

  tcase_add_test(tcase, s21_test_sprintf_s_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_p_suit(void) {
  Suite *suite = suite_create("s21_sprintf_p");
  TCase *tcase = tcase_create("s21_sprintf_p_tcase");

  tcase_add_test(tcase, s21_test_sprintf_p_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_f_suit(void) {
  Suite *suite = suite_create("s21_sprintf_f");
  TCase *tcase = tcase_create("s21_sprintf_f_tcase");

  tcase_add_test(tcase, s21_test_sprintf_f_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_e_suit(void) {
  Suite *suite = suite_create("s21_sprintf_e");
  TCase *tcase = tcase_create("s21_sprintf_e_tcase");

  tcase_add_test(tcase, s21_test_sprintf_e_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_E_suit(void) {
  Suite *suite = suite_create("s21_sprintf_E");
  TCase *tcase = tcase_create("s21_sprintf_E_tcase");

  tcase_add_test(tcase, s21_test_sprintf_E_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_g_suit(void) {
  Suite *suite = suite_create("s21_sprintf_g");
  TCase *tcase = tcase_create("s21_sprintf_g_tcase");

  tcase_add_test(tcase, s21_test_sprintf_g_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_sprintf_G_suit(void) {
  Suite *suite = suite_create("s21_sprintf_G");
  TCase *tcase = tcase_create("s21_sprintf_G_tcase");

  tcase_add_test(tcase, s21_test_sprintf_G_check);

  suite_add_tcase(suite, tcase);
  return suite;
}

Suite *s21_string_suit(void) {
  Suite *suite_string = suite_create("s21_string");
  TCase *tcase_string = tcase_create("s21_string_tcase");

  tcase_add_test(tcase_string, s21_test_memchr_check);
  tcase_add_test(tcase_string, s21_test_memcmp_check);
  tcase_add_test(tcase_string, s21_test_memcpy_check);
  tcase_add_test(tcase_string, s21_test_memset_check);
  tcase_add_test(tcase_string, s21_memcmp_test);

  tcase_add_test(tcase_string, s21_test_strncat_check);
  tcase_add_test(tcase_string, s21_test_strchr_check);
  tcase_add_test(tcase_string, s21_test_strrchr_check);
  tcase_add_test(tcase_string, s21_test_strlen_check);

  tcase_add_test(tcase_string, s21_test_strspn_check);
  tcase_add_test(tcase_string, s21_test_strcspn_check);
  tcase_add_test(tcase_string, s21_test_strcat_check);
  tcase_add_test(tcase_string, s21_test_strcpy_check);

  tcase_add_test(tcase_string, s21_test_strncpy_check);
  tcase_add_test(tcase_string, s21_test_strcmp_check);
  tcase_add_test(tcase_string, s21_test_strncmp_check);
  tcase_add_test(tcase_string, s21_test_strcpy_check);

  tcase_add_test(tcase_string, s21_test_strpbrk_check);
  tcase_add_test(tcase_string, s21_test_strstr_check);
  tcase_add_test(tcase_string, s21_test_strerror_check);
  tcase_add_test(tcase_string, s21_test_strtok_check);

  tcase_add_test(tcase_string, strstr_1);
  tcase_add_test(tcase_string, strstr_2);
  tcase_add_test(tcase_string, strstr_3);
  tcase_add_test(tcase_string, strstr_4);
  tcase_add_test(tcase_string, strstr_5);
  tcase_add_test(tcase_string, strstr_6);
  tcase_add_test(tcase_string, strstr_7);
  tcase_add_test(tcase_string, strstr_8);
  tcase_add_test(tcase_string, strstr_9);
  tcase_add_test(tcase_string, strstr_10);
  tcase_add_test(tcase_string, strstr_11);
  tcase_add_test(tcase_string, strstr_12);
  tcase_add_test(tcase_string, strstr_13);

  tcase_add_test(tcase_string, strncmp_1);
  tcase_add_test(tcase_string, strncmp_2);
  tcase_add_test(tcase_string, strncmp_3);
  tcase_add_test(tcase_string, strncmp_4);
  tcase_add_test(tcase_string, strncmp_5);
  tcase_add_test(tcase_string, strncmp_6);
  tcase_add_test(tcase_string, strncmp_7);
  tcase_add_test(tcase_string, strncmp_8);
  tcase_add_test(tcase_string, strncmp_9);

  tcase_add_test(tcase_string, s21_test_insert_check);
  tcase_add_test(tcase_string, test_insert_1);
  tcase_add_test(tcase_string, test_insert_2);
  tcase_add_test(tcase_string, test_insert_3);
  tcase_add_test(tcase_string, test_insert_4);
  tcase_add_test(tcase_string, test_insert_5);
  tcase_add_test(tcase_string, test_insert_6);
  tcase_add_test(tcase_string, test_insert_7);
  tcase_add_test(tcase_string, test_insert_8);
  tcase_add_test(tcase_string, test_insert_9);
  tcase_add_test(tcase_string, test_insert_10);
  tcase_add_test(tcase_string, s21_test_to_lower_check);
  tcase_add_test(tcase_string, s21_test_to_upper_check);
  tcase_add_test(tcase_string, s21_test_trim_check);
  tcase_add_test(tcase_string, test_trim_1);
  tcase_add_test(tcase_string, test_trim_2);
  tcase_add_test(tcase_string, test_trim_3);
  tcase_add_test(tcase_string, test_trim_4);
  tcase_add_test(tcase_string, test_trim_5);
  tcase_add_test(tcase_string, test_trim_6);
  tcase_add_test(tcase_string, test_trim_7);
  tcase_add_test(tcase_string, test_trim_8);
  tcase_add_test(tcase_string, test_trim_9);

  suite_add_tcase(suite_string, tcase_string);
  return suite_string;
}

Suite *test_sprintf_string(void) {
  Suite *suite = suite_create("S21_SPRINTF_STRING");
  TCase *tc = tcase_create("sprintf_tc");

  tcase_add_test(tc, sprintf_1_string);
  tcase_add_test(tc, sprintf_2_string);
  tcase_add_test(tc, sprintf_3_string);
  tcase_add_test(tc, sprintf_5_string);
  tcase_add_test(tc, sprintf_6_string);
  tcase_add_test(tc, sprintf_7_string);
  tcase_add_test(tc, sprintf_8_string);
  tcase_add_test(tc, sprintf_9_string);
  tcase_add_test(tc, sprintf_10_string);
  tcase_add_test(tc, sprintf_11_string);
  tcase_add_test(tc, sprintf_12_string);
  tcase_add_test(tc, sprintf_13_string);
  // tcase_add_test(tc, sprintf_14_string);
  tcase_add_test(tc, sprintf_15_string);
  tcase_add_test(tc, sprintf_16_string);

  suite_add_tcase(suite, tc);
  return suite;
}

Suite *s21_sscanf_suite(void) {
  Suite *suite = suite_create("s21_sscanf");
  TCase *tcase_core = tcase_create("s21_sscanf_tcase");

  tcase_add_test(tcase_core, test_s21_sscanf);
  tcase_add_test(tcase_core, test_sscanf_d);
  tcase_add_test(tcase_core, test_sscanf_u);
  tcase_add_test(tcase_core, test_sscanf_xX);
  tcase_add_test(tcase_core, test_sscanf_o);
  tcase_add_test(tcase_core, test_sscanf_i);
  tcase_add_test(tcase_core, test_sscanf_p);
  tcase_add_test(tcase_core, test_sscanf_c);
  tcase_add_test(tcase_core, test_sscanf_s);
  tcase_add_test(tcase_core, test_sscanf_n);
  tcase_add_test(tcase_core, test_sscanf_f);
  tcase_add_test(tcase_core, test_sscanf_gG);
  tcase_add_test(tcase_core, test_sscanf_eE);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Fail f = {0};

  Suite *suite_string = s21_string_suit();
  Suite *suite_sprintf = s21_sprintf_suit();
  Suite *suite_sprintf_d = s21_sprintf_d_suit();
  Suite *suite_sprintf_u = s21_sprintf_u_suit();
  Suite *suite_sprintf_o = s21_sprintf_o_suit();
  Suite *suite_sprintf_x = s21_sprintf_x_suit();
  Suite *suite_sprintf_X = s21_sprintf_X_suit();
  Suite *suite_sprintf_c = s21_sprintf_c_suit();
  Suite *suite_sprintf_s = s21_sprintf_s_suit();
  Suite *suite_sprintf_p = s21_sprintf_p_suit();
  Suite *suite_sprintf_f = s21_sprintf_f_suit();
  Suite *suite_sprintf_e = s21_sprintf_e_suit();
  Suite *suite_sprintf_E = s21_sprintf_E_suit();
  Suite *suite_sprintf_g = s21_sprintf_g_suit();
  Suite *suite_sprintf_G = s21_sprintf_G_suit();
  Suite *suite_sscanf = s21_sscanf_suite();
  Suite *suite_sprintf_str = test_sprintf_string();

  SRunner *suite_runner_string = srunner_create(suite_string);
  SRunner *suite_runner_sprintf = srunner_create(suite_sprintf);
  SRunner *suite_runner_sprintf_d = srunner_create(suite_sprintf_d);
  SRunner *suite_runner_sprintf_u = srunner_create(suite_sprintf_u);
  SRunner *suite_runner_sprintf_o = srunner_create(suite_sprintf_o);
  SRunner *suite_runner_sprintf_x = srunner_create(suite_sprintf_x);
  SRunner *suite_runner_sprintf_X = srunner_create(suite_sprintf_X);
  SRunner *suite_runner_sprintf_c = srunner_create(suite_sprintf_c);
  SRunner *suite_runner_sprintf_s = srunner_create(suite_sprintf_s);
  SRunner *suite_runner_sprintf_p = srunner_create(suite_sprintf_p);
  SRunner *suite_runner_sprintf_f = srunner_create(suite_sprintf_f);
  SRunner *suite_runner_sprintf_e = srunner_create(suite_sprintf_e);
  SRunner *suite_runner_sprintf_E = srunner_create(suite_sprintf_E);
  SRunner *suite_runner_sprintf_g = srunner_create(suite_sprintf_g);
  SRunner *suite_runner_sprintf_G = srunner_create(suite_sprintf_G);
  SRunner *suite_runner_sscanf = srunner_create(suite_sscanf);
  SRunner *suite_runner_sprintf_str = srunner_create(suite_sprintf_str);

  srunner_set_fork_status(suite_runner_string, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_d, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_u, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_o, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_x, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_X, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_c, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_s, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_p, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_f, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_e, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_E, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_g, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_G, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sscanf, CK_NOFORK);
  srunner_set_fork_status(suite_runner_sprintf_str, CK_NOFORK);

  srunner_run_all(suite_runner_string, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_d, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_u, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_o, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_x, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_X, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_c, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_s, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_p, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_f, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_e, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_E, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_g, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_G, CK_NORMAL);
  srunner_run_all(suite_runner_sscanf, CK_NORMAL);
  srunner_run_all(suite_runner_sprintf_str, CK_NORMAL);

  f.str = srunner_ntests_failed(suite_runner_string);
  f.spr = srunner_ntests_failed(suite_runner_sprintf);
  f.d = srunner_ntests_failed(suite_runner_sprintf_d);
  f.u = srunner_ntests_failed(suite_runner_sprintf_u);
  f.o = srunner_ntests_failed(suite_runner_sprintf_o);
  f.x = srunner_ntests_failed(suite_runner_sprintf_x);
  f.X = srunner_ntests_failed(suite_runner_sprintf_X);
  f.c = srunner_ntests_failed(suite_runner_sprintf_c);
  f.s = srunner_ntests_failed(suite_runner_sprintf_s);
  f.p = srunner_ntests_failed(suite_runner_sprintf_p);
  f.f = srunner_ntests_failed(suite_runner_sprintf_f);
  f.e = srunner_ntests_failed(suite_runner_sprintf_e);
  f.E = srunner_ntests_failed(suite_runner_sprintf_E);
  f.g = srunner_ntests_failed(suite_runner_sprintf_g);
  f.G = srunner_ntests_failed(suite_runner_sprintf_G);
  f.scan = srunner_ntests_failed(suite_runner_sscanf);
  f.str1 = srunner_ntests_failed(suite_runner_sprintf_str);

  srunner_free(suite_runner_string);
  srunner_free(suite_runner_sprintf);
  srunner_free(suite_runner_sprintf_d);
  srunner_free(suite_runner_sprintf_u);
  srunner_free(suite_runner_sprintf_o);
  srunner_free(suite_runner_sprintf_x);
  srunner_free(suite_runner_sprintf_X);
  srunner_free(suite_runner_sprintf_c);
  srunner_free(suite_runner_sprintf_s);
  srunner_free(suite_runner_sprintf_p);
  srunner_free(suite_runner_sprintf_f);
  srunner_free(suite_runner_sprintf_e);
  srunner_free(suite_runner_sprintf_E);
  srunner_free(suite_runner_sprintf_g);
  srunner_free(suite_runner_sprintf_G);
  srunner_free(suite_runner_sscanf);
  srunner_free(suite_runner_sprintf_str);

  return (f.str || f.spr || f.d || f.u || f.o || f.x || f.X || f.c || f.s ||
          f.p || f.f || f.e || f.E || f.g || f.G || f.scan || f.str1)
             ? EXIT_FAILURE
             : EXIT_SUCCESS;
}
