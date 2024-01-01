#ifndef S21_SPRINTF
#define S21_SPRINTF

#include "s21_string.h"

typedef struct Format {
  int check_accuracy;
  int right_offset;
  int accuracy_zv;
  int check_sharp;
  int check_width;
  int g_science;
  int width_zv;
  int accuracy;
  int use_exp;
  int g_spec;
  int width;
  int minus;
  int sharp;
  int space;
  char spec;
  int plus;
  int zero;
  int null;
  int l;
  int L;
  int h;
} Format;

typedef struct Var {
  int d;
  long l;
  char c;
  void *p;
  char *s;
  double f;
  long double ld;
  unsigned long ul;
} Var;

int s21_sprintf(char *str, const char *format, ...);
char *flags_reading(char *sym, Format *record, va_list factor);
char *width_reading(char *sym, Format *record, va_list factor, int *sum,
                    int *step);
char *accuracy_reading(char *sym, Format *record, va_list factor, int *sum,
                       int *step);
void pars_spec(Var args, const char *sym, char *str, va_list factor,
               Format *record);
void case_c(Format *record, va_list factor, Var args, char *tmp, char *str,
            int sign_minus, s21_size_t *len);
void case_s(Format *record, va_list factor, Var args, char *tmp, char *str,
            s21_size_t *len);
void case_whole_num(Format *record, char *tmp, char *str, int sign_minus,
                    s21_size_t *len);
void case_f_e_E(Format *record, va_list factor, Var args, char *tmp, char *str,
                int *sign_minus, s21_size_t *len);
void case_g_G(Format *record, va_list factor, Var args, char *str,
              int *sign_minus, s21_size_t *len);
void infinity_check(Format *record, char *str, s21_size_t *len,
                    const int *sign_minus);
void case_p(Var args, va_list factor, Format *record, char *tmp, char *str,
            unsigned long *num_u, int sign_minus, s21_size_t *len);
void init_unsign_case(unsigned long *var, va_list factor, Format *record,
                      unsigned long *num, char c);
char *init_d_case(Var *args, va_list factor, Format *record, long *num,
                  char *tmp, int *sign_minus);
int number_len(long double number, long double *num, long double *i);
char *number_to_string(const Format *record, long double number);
void transform_to_chars(const Format *record, int count, long double num,
                        char *symb);
char *number_to_oct_string(const Format *record, long double number);
char *number_to_hex_string(const Format *record, long double number);
char *double_to_string(long double number, Format *record);
void get_fract_part(Format *record, long double num, long double *whole,
                    long double *fract, long double *int_fract, int acc);
char *get_join_str(long double fract, int acc, char *fract_str, int count_whole,
                   int count_fract);
char *g_G_double_to_string(long double number, Format *record);
void get_g_G_fract_part(Format *record, long double *whole, long double number,
                        long double fract, long double *int_fract,
                        long double whole_fract, int *count_add_zero);
char *get_g_G_join_str(char *d_symb, const char *whole_str, char *fract_str,
                       long double whole, long double fract,
                       const Format *record, int count_add_zero,
                       long double int_fract);
char *double_to_string_science_g_G(long double number, Format *record);
char *number_to_science_notation(long double number, Format *record);
void add_left_spaces(const Format *record, s21_size_t len, char *str,
                     const char *x);
void add_right_spaces(const Format *record, s21_size_t len, char *str);
void add_plus_minus_space(char *str, s21_size_t *len, const char *tmp,
                          Format *record, int sign_minus);
void write_str(char *str, const char *tmp, const Format *record,
               s21_size_t len);

#endif  // S21_SPRINTF