#include "s21_string.h"

int left_side(const char *src, const char *trim_chars, int last) {
  int res = 0;
  int size = s21_strlen(trim_chars);
  for (int i = 0; i < size; i++) {
    if (src[last] == trim_chars[i]) res = 1;
  }
  return res;
}

int right_side(const char *src, const char *trim_chars, int last) {
  int res = 0;
  last--;
  int size = s21_strlen(trim_chars);
  for (int i = 0; i < size; i++) {
    if (src[last] == trim_chars[i]) res = 1;
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *arr = S21_NULL;
  if (src) {
    if (trim_chars && trim_chars[0]) {
      arr = calloc(s21_strlen(src) + 1, sizeof(char));
      s21_size_t begin = 0, last = s21_strlen(src);
      while (left_side(src, trim_chars, begin)) {
        begin++;
      }
      if (begin != last) {
        while (right_side(src, trim_chars, last)) last--;
      } else {
        arr[0] = '\0';
      }
      for (int i = 0; begin < last; i++) {
        arr[i] = src[begin];
        begin++;
      }
    } else {
      arr = s21_trim(src, "\t\n ");
    }
  }
  return arr;
}

void *s21_to_lower(const char *str) {
  char *copy_str = S21_NULL;
  if (str) {
    s21_size_t len = s21_strlen(str);
    copy_str = calloc(len + 2, 1);
    if (copy_str) {
      for (s21_size_t i = 0; i <= len; i++) {
        if (str[i] > 64 && str[i] < 91)
          copy_str[i] = str[i] + 32;
        else
          copy_str[i] = str[i];
      }
      copy_str[len] = '\0';
    }
  }
  return (void *)copy_str;
}

void *s21_to_upper(const char *str) {
  char *copy_str = S21_NULL;
  if (str) {
    s21_size_t len = s21_strlen(str);
    copy_str = calloc(len + 2, 1);
    if (copy_str) {
      for (s21_size_t i = 0; i <= len; i++) {
        if (str[i] > 96 && str[i] < 123)
          copy_str[i] = str[i] - 32;
        else
          copy_str[i] = str[i];
      }
      copy_str[len] = '\0';
    }
  }
  return (void *)copy_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int err = 0;
  char *new_string = S21_NULL;
  if (src && str && start_index <= (s21_strlen(src))) {
    new_string =
        (char *)calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    if (new_string == S21_NULL) err = 1;

    s21_size_t i = 0;
    for (; i < start_index; i++) new_string[i] = src[i];

    s21_size_t end = i;
    for (s21_size_t j = 0; j < s21_strlen(str); j++, i++) {
      new_string[i] = str[j];
    }
    for (; end < s21_strlen(src); end++, i++) {
      new_string[i] = src[end];
    }
    new_string[s21_strlen(new_string)] = '\0';
  } else {
    err = 1;
  }
  return err ? S21_NULL : (void *)new_string;
}
