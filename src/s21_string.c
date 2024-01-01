#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t count2 = 0;
  for (s21_size_t i = 0; str1[i]; i++) {
    s21_size_t count1 = 0;
    count1 = count2;
    for (s21_size_t j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) {
        count2++;
        break;
      }
    }
    if (count2 == count1) break;
  }
  return count2;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *tmp = (unsigned char *)str;
  unsigned char sym = (unsigned char)c;
  void *res = S21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (sym == *tmp) {
      res = tmp;
      break;
    }
    tmp++;
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *tmp1 = (unsigned char *)str1;
  unsigned char *tmp2 = (unsigned char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (*tmp2 != *tmp1) {
      result = *tmp1 - *tmp2;
      break;
    }
    tmp1++;
    tmp2++;
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *tmp1 = (char *)dest;
  const char *tmp2 = (char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    *tmp1++ = *tmp2++;
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *tmp = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    *tmp++ = (unsigned char)c;
  }
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest + s21_strlen(dest);
  while (*src != '\0') {
    *ptr++ = *src++;
  }
  *ptr = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest + s21_strlen(dest);
  while (*src != '\0' && n--) {
    *ptr++ = *src++;
  }
  *ptr = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  unsigned char *tmp = (unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  while (tmp[i] && tmp[i] != ch) ++i;
  return ch == tmp[i] ? (char *)tmp + i : S21_NULL;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && *str1 == *str2) str1++, str2++;
  return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  if (str1 && str2 && n > 0) {
    s21_size_t index = 0;
    while (index < n) {
      if (str1[index] == '\0' || str1[index] != str2[index]) {
        result = str1[index] - str2[index];
        break;
      }
      index++;
    }
  }
  return result;
}

char *s21_strcpy(char *str1, const char *str2) {
  if (str1 == S21_NULL) return S21_NULL;
  char *ptr = str1;
  while (*str2 != '\0') {
    *str1 = *str2;
    str1++;
    str2++;
  }
  *str1 = '\0';
  return ptr;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest == S21_NULL) return S21_NULL;
  char *ptr = dest;
  while (*src != '\0' && n--) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return ptr;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (*(str + length)) length++;
  return length;
}

char *s21_strrchr(const char *str, int c) {
  int match = 0;
  unsigned char *tmp = (unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  for (s21_size_t i = 0; i <= s21_strlen((const char *)tmp); i++) {
    if (ch == tmp[i]) match = i + 1;
  }
  return match ? (char *)&tmp[match - 1] : S21_NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t needle_len = s21_strlen(needle);
  int flag = 1;

  if (needle_len) {
    flag = 0;
    s21_size_t haystack_len = s21_strlen(haystack);
    while (haystack_len-- >= needle_len) {
      if (!s21_memcmp(haystack, needle, needle_len)) {
        flag = 1;
        break;
      }
      haystack++;
    }
  }
  return flag ? (char *)haystack : S21_NULL;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *tmp1 = (char *)str1;
  const char *tmp2 = (char *)str2;
  while (*str1) {
    int fail = 0;
    while (*str2) {
      if (*str1 == *str2) {
        fail = 1;
        break;
      }
      str2++;
    }
    if (fail) break;
    str1++;
    str2 = tmp2;
  }
  return str1 - tmp1;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *tmp = (char *)str2;
  int match = 0;
  while (*str1) {
    while (*str2) {
      if (*str1 == *str2) {
        match = 1;
        break;
      }
      str2++;
    }
    if (match) break;
    str1++;
    str2 = tmp;
  }
  return match ? (char *)str1 : S21_NULL;
}

char *s21_strerror(int errnum) {
  char *tmp;
  if (errnum < 0 || errnum >= ARRAY_SIZE) {
    long int i = 10, num = errnum;
    int count = 1;
    if (errnum < 0) num = -num;
    while (num >= i) {
      i *= 10;
      count++;
    }
    char symb[count + 2];
    if (errnum < 0) {
      symb[0] = 45;
      count++;
    }
    for (int j = ((errnum < 0) ? 1 : 0); j < count; j++) {
      int res = num / (i / 10);
      symb[j] = res + 48;
      i /= 10;
      num -= i * res;
    }
    symb[count] = '\0';
    static char err[512];
    s21_strcpy(err, "Unknown error");

#if defined(__APPLE__) || defined(__MACH__)
    s21_strcat(err, ": ");
#elif defined(__linux__)
    s21_strcat(err, " ");
#endif

    s21_strcat(err, symb);
    tmp = err;
  } else {
    tmp = (char *)s21_error[errnum];
  }
  return tmp;
}

char *s21_strtok(char *str, const char *delim) {
  static char *global = S21_NULL;
  if (str) global = str;
  if (global) {
    str = global + s21_strspn(global, delim);
    global = str + s21_strcspn(str, delim);
    if (*global != '\0') {
      *global = '\0';
      global++;
    }
  }
  return *str != '\0' ? str : S21_NULL;
}
