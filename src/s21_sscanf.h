#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#include "s21_string.h"

#define SPECS_LIST "cdieEfgGosuxXpn"
#define INFINITY_DESIGN "inf"
#define NOT_NUMBER_DESIGN "nan"

#define CHAR_PERCENT (int)37
#define CHAR_SPACE (int)32
#define CHAR_STAR (int)42
#define CHAR_PLUS (int)43
#define CHAR_MINUS (int)45
#define CHAR_NULL (int)48
#define CHAR_NINE (int)57
#define CHAR_A (int)65
#define CHAR_A_SM (int)97
#define CHAR_Z (int)90
#define END_LINE (int)0
#define CHAR_DOT (int)46

#define INT_MINUS_ONE -1
#define INT_NULL 0
#define INT_ONE 1
#define INT_TWO 2
#define INT_OCT 8
#define INT_TEN 10
#define INT_HEX 16

#define CHAR_N (int)110
#define CHAR_L_SM (int)108
#define CHAR_L (int)76
#define CHAR_H_SM (int)104
#define CHAR_X (int)88
#define CHAR_X_SM (int)120
#define CHAR_E (int)69
#define CHAR_E_SM (int)101

typedef enum {
  spec_c,
  spec_d,
  spec_i,
  spec_e,
  spec_E,
  spec_f,
  spec_g,
  spec_G,
  spec_o,
  spec_s,
  spec_u,
  spec_x,
  spec_X,
  spec_p,
  spec_n,
  spec_unknown,
} sspecs;

typedef enum lens {
  len_none,
  len_h,
  len_l,
  len_L,
} lens;

typedef struct {
  sspecs spec;
  int width;
  lens len;
  s21_bool skip;
} specifier;

int s21_sscanf(const char *str, const char *format, ...);
s21_bool scan(specifier spec, char **str, va_list ap, int *negative_scan,
              const char *start);
specifier scan_specifier(char **format);
int scan_width(char **cast_format);
s21_bool is_digit(char symbol_is_digit, int base);
s21_size_t to_digit(char symbol_to_digit, int base);
char chr_lower(char symbol_is_lower);
s21_bool strstr_icase(char **str, char *substring);
s21_bool parse_string(specifier spec, char **str, va_list ap);
s21_bool parse_int(specifier spec, char **str, va_list ap);
s21_bool parse_based_uint(specifier spec, char **str, va_list ap, int base,
                          s21_bool number_sign);
s21_bool parse_uint(specifier spec, char **str, va_list ap,
                    s21_bool number_sign);
s21_bool parse_hex(specifier spec, char **str, va_list ap,
                   s21_bool number_sign);
s21_bool parse_oct(specifier spec, char **str, va_list ap,
                   s21_bool number_sign);
s21_bool parse_i_uint(specifier spec, char **str, va_list ap);
s21_bool parse_ptr(specifier spec, char **str, va_list ap);
s21_bool parse_float(specifier spec, char **str, va_list ap);
s21_bool scan_int(char **str, int width, long long *dest);
s21_bool scan_based_uint(char **str, int width, unsigned long long *dest,
                         int base, s21_bool number_sign);
s21_bool scan_float(char **str, int width, long double *dest);
s21_bool nan_inf(char **str, long double *dest);
long double s21_atof(char **str, int *width);
s21_bool scientific(char **str, int *width, long double *number_result);

#endif  // SRC_S21_SSCANF_H_