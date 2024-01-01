#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  *str = '\0';
  int a = 0;
  va_list factor;
  va_start(factor, format);
  for (char *sym = (char *)format; *sym; sym++) {
    Var args = {0};
    int flag_double_percent = 0;
    if (*sym == '%' && *(sym + 1) == '%') {
      s21_strcat(str, "%");
      flag_double_percent = 1;
      sym += 1;
    }
    if (*sym != '%') {
      char tmp[2];
      tmp[0] = *sym;
      tmp[1] = '\0';
      s21_strcat(str, tmp);
      continue;
    }
    if (!flag_double_percent) {
      Format record = {0};
      sym = flags_reading(sym, &record, factor);
      pars_spec(args, sym, str, factor, &record);
    }
  }
  va_end(factor);
  a = (int)s21_strlen(str);
  return a ? a : 1;
}

char *flags_reading(char *sym, Format *record, va_list factor) {
  int sum_w = 0, step_w = 0, sum_a = 0, step_a = 0;
  while (sym) {
    switch (*sym) {
      case 'L':
        record->L = 1;
        break;
      case 'l':
        record->l = 1;
        break;
      case 'h':
        record->h = 1;
        break;
      case '#':
        record->sharp = 1;
        break;
      case '-':
        record->minus = 1;
        break;
      case '+':
        record->plus = 1;
        break;
      case ' ':
        record->space = 1;
        break;
      default:
        break;
    }
    if (!record->check_accuracy)
      sym = width_reading(sym, record, factor, &sum_w, &step_w);
    if (*sym == '.') record->check_accuracy = 1;
    if (record->check_accuracy)
      sym = accuracy_reading(sym, record, factor, &sum_a, &step_a);

    if (*sym == 's' || *sym == 'd' || *sym == 'f' || *sym == 'e' ||
        *sym == 'x' || *sym == 'i' || *sym == 'c' || *sym == 'E' ||
        *sym == 'g' || *sym == 'G' || *sym == 'o' || *sym == 'u' ||
        *sym == 'X' || *sym == 'p')
      break;
    sym++;
  }
  if (!record->width_zv) record->width = sum_w;
  if (!record->accuracy_zv) record->accuracy = sum_a;
  return sym;
}

char *width_reading(char *sym, Format *record, va_list factor, int *sum,
                    int *step) {
  if ((*sym > 47 && *sym < 58) || *sym == '*') {
    if (!record->check_width && *sym == '0') {
      record->zero = 1;
    } else {
      if (*sym == '*') {
        record->width = va_arg(factor, int);
        record->width_zv = 1;
      } else {
        int num = *sym - 48;
        *sum = *sum * pow(10, *step) + num;
        *step = 1;
      }
    }
    record->check_width = 1;
  }
  return sym;
}

char *accuracy_reading(char *sym, Format *record, va_list factor, int *sum,
                       int *step) {
  if ((*sym > 47 && *sym < 58) || *sym == '*') {
    if (*sym == '*') {
      record->accuracy = va_arg(factor, int);
      record->accuracy_zv = 1;
    } else {
      int num = *sym - 48;
      *sum = *sum * pow(10, *step) + num;
      *step = 1;
    }
  }
  return sym;
}

void pars_spec(Var args, const char *sym, char *str, va_list factor,
               Format *record) {
  int sign_minus = 0;
  char *tmp = 0;
  s21_size_t len;
  long num;
  unsigned long num_u;
  switch (*sym) {
    case 'd':
      tmp = init_d_case(&args, factor, record, &num, tmp, &sign_minus);
      if (tmp) case_whole_num(record, tmp, str, sign_minus, &len);
      break;
    case 'u':
      init_unsign_case(&args.ul, factor, record, &num_u, 'u');
      tmp = number_to_string(record, num_u);
      if (tmp) case_whole_num(record, tmp, str, sign_minus, &len);
      break;
    case 'o':
      init_unsign_case(&args.ul, factor, record, &num_u, 'o');
      tmp = number_to_oct_string(record, num_u);
      if (tmp) case_whole_num(record, tmp, str, sign_minus, &len);
      break;
    case 'x':
      init_unsign_case(&args.ul, factor, record, &num_u, 'x');
      tmp = number_to_hex_string(record, num_u);
      if (tmp) case_whole_num(record, tmp, str, sign_minus, &len);
      break;
    case 'X':
      init_unsign_case(&args.ul, factor, record, &num_u, 'X');
      tmp = number_to_hex_string(record, num_u);
      if (tmp) case_whole_num(record, tmp, str, sign_minus, &len);
      break;
    case 'p':
      case_p(args, factor, record, tmp, str, &num_u, sign_minus, &len);
      break;
    case 'c':
      case_c(record, factor, args, tmp, str, sign_minus, &len);
      break;
    case 's':
      case_s(record, factor, args, tmp, str, &len);
      break;
    case 'f':
      record->spec = 'f';
      case_f_e_E(record, factor, args, tmp, str, &sign_minus, &len);
      break;
    case 'e':
      record->spec = 'e';
      case_f_e_E(record, factor, args, tmp, str, &sign_minus, &len);
      break;
    case 'E':
      record->spec = 'E';
      case_f_e_E(record, factor, args, tmp, str, &sign_minus, &len);
      break;
    case 'g':
      record->spec = 'g';
      case_g_G(record, factor, args, str, &sign_minus, &len);
      break;
    case 'G':
      record->spec = 'G';
      case_g_G(record, factor, args, str, &sign_minus, &len);
      break;
    default:
      break;
  }
}

void case_c(Format *record, va_list factor, Var args, char *tmp, char *str,
            int sign_minus, s21_size_t *len) {
  record->spec = 'c';
  args.c = va_arg(factor, int);
  tmp = calloc(2, 1);
  if (tmp) {
    tmp[0] = args.c;
    if (args.c) tmp[1] = '\0';
    add_plus_minus_space(str, len, tmp, record, sign_minus);
    write_str(str, tmp, record, *len);
    free(tmp);
  }
}

void case_s(Format *record, va_list factor, Var args, char *tmp, char *str,
            s21_size_t *len) {
  record->spec = 's';
  char n[] = "(null)";
  args.s = va_arg(factor, char *);
  if (args.s)
    *len = s21_strlen(args.s);
  else
    *len = s21_strlen(n);
  tmp = calloc(*len + 1, 1);
  if (tmp) {
    if (args.s)
      s21_strcpy(tmp, args.s);
    else
      s21_strcpy(tmp, n);

    if (record->accuracy < (int)*len && record->check_accuracy) {
      tmp[record->accuracy] = '\0';
    }
    *len = s21_strlen(tmp);
    add_left_spaces(record, *len, str, " ");
    write_str(str, tmp, record, *len);
    free(tmp);
  }
}

void case_whole_num(Format *record, char *tmp, char *str, int sign_minus,
                    s21_size_t *len) {
  int check = record->accuracy;
  if (!record->check_accuracy || !record->accuracy) check = 1;

  add_plus_minus_space(str, len, tmp, record, sign_minus);
  for (; check > (int)s21_strlen(tmp); check--) s21_strcat(str, "0");
  if (!record->accuracy && record->check_accuracy && *tmp == '0')
    s21_strcpy(tmp, record->width ? " " : "");
  write_str(str, tmp, record, *len);
  if (tmp) free(tmp);
}

void case_f_e_E(Format *record, va_list factor, Var args, char *tmp, char *str,
                int *sign_minus, s21_size_t *len) {
  long double num;
  if (!record->check_accuracy) record->accuracy = 6;
  if (record->L) {
    args.ld = va_arg(factor, long double);
    num = args.ld;
  } else {
    args.f = va_arg(factor, double);
    num = args.f;
  }
  if (num < 0) *sign_minus = 1;
  if (fabsl(num) == INFINITY) {
    infinity_check(record, str, len, sign_minus);
  } else {
    if (record->spec == 'f')
      tmp = double_to_string(num, record);
    else
      tmp = number_to_science_notation(num, record);

    if (tmp) {
      add_plus_minus_space(str, len, tmp, record, *sign_minus);
      write_str(str, tmp, record, *len);
      free(tmp);
    }
  }
}

void case_g_G(Format *record, va_list factor, Var args, char *str,
              int *sign_minus, s21_size_t *len) {
  long double num;
  if (record->spec == 'g' || record->spec == 'G') record->g_spec = 1;
  if (!record->check_accuracy) record->accuracy = 6;
  if (record->L) {
    args.ld = va_arg(factor, long double);
    num = args.ld;
  } else {
    args.f = va_arg(factor, double);
    num = args.f;
  }
  if (num < 0) *sign_minus = 1;
  if (fabsl(num) == INFINITY) {
    infinity_check(record, str, len, sign_minus);
  } else {
    char *tmp_e;
    tmp_e = number_to_science_notation(num, record);
    char *tmp_f;
    tmp_f = g_G_double_to_string(num, record);
    if (tmp_e) {
      if (tmp_f) {
        const char *ch = record->use_exp ? tmp_e : tmp_f;

        add_plus_minus_space(str, len, ch, record, *sign_minus);
        write_str(str, ch, record, *len);

        free(tmp_f);
      }
      free(tmp_e);
    }
  }
}

void infinity_check(Format *record, char *str, s21_size_t *len,
                    const int *sign_minus) {
  char inf_str[4];
  if (record->spec == 'G' || record->spec == 'E')
    s21_strcpy(inf_str, "INF");
  else
    s21_strcpy(inf_str, "inf");
  add_plus_minus_space(str, len, inf_str, record, *sign_minus);
  write_str(str, inf_str, record, *len);
}

void case_p(Var args, va_list factor, Format *record, char *tmp, char *str,
            unsigned long *num_u, int sign_minus, s21_size_t *len) {
  record->sharp = 1, record->check_sharp = 1;
  args.p = va_arg(factor, void *);
  record->spec = 'p';
  if (!args.p) record->null = 1;
  *num_u = (unsigned long)args.p;
  tmp = number_to_hex_string(record, *num_u);
  case_whole_num(record, tmp, str, sign_minus, len);
}

void init_unsign_case(unsigned long *var, va_list factor, Format *record,
                      unsigned long *num, char c) {
  record->spec = c;
  *var = va_arg(factor, unsigned long);
  if (record->l)
    *num = *var;
  else
    *num = record->h ? (unsigned short)*var : (unsigned)*var;
}

char *init_d_case(Var *args, va_list factor, Format *record, long *num,
                  char *tmp, int *sign_minus) {
  record->spec = 'd';
  if (record->l) {
    args->l = va_arg(factor, long);
    *num = args->l;
  } else {
    args->d = va_arg(factor, int);
    *num = record->h ? (short)args->d : args->d;
  }
  if (*num < 0) *sign_minus = 1;
  tmp = number_to_string(record, *num);
  return tmp;
}

int number_len(long double number, long double *num, long double *i) {
  int count = 1;
  if (number < 0) *num = -*num;
  while (*num >= *i) {
    *i *= 10;
    count++;
  }
  return count;
}

char *number_to_string(const Format *record, long double number) {
  long double i = 10., num = number;
  int count = number_len(number, &num, &i);

  char *symb = calloc(count + record->accuracy + 5, 1);
  if (symb) {
    for (int j = 0; j < count; j++) {
      int res = num / (i / 10);
      symb[j] = res + 48;
      i /= 10;
      num -= i * res;
    }
    symb[count] = '\0';
  }
  return symb;
}

void transform_to_chars(const Format *record, int count, long double num,
                        char *symb) {
  char tmp_str[count + 5];
  unsigned long res = num;
  for (int j = 0;; j++) {
    long ost;
    if (record->spec == 'o') {
      ost = res % 8;
      tmp_str[j] = ost + 48;
      res /= 8;
    } else {
      ost = res % 16;
      if (ost < 10)
        tmp_str[j] = ost + 48;
      else
        tmp_str[j] = (record->spec == 'X') ? ost + 55 : ost + 87;
      res /= 16;
    }
    if (!res) {
      tmp_str[j + 1] = '\0';
      break;
    }
  }
  int l = s21_strlen(tmp_str);
  for (int j = 0; j < l; j++) {
    symb[j] = tmp_str[l - 1 - j];
  }
  symb[l] = '\0';
}

char *number_to_oct_string(const Format *record, long double number) {
  long double i = 10., num = number;
  int count = number_len(number, &num, &i);
  char *symb = calloc(count + 5, 1);

  if (symb) transform_to_chars(record, count, num, symb);
  return symb;
}

char *number_to_hex_string(const Format *record, long double number) {
  long double i = 10, num = number;
  int count = number_len(number, &num, &i);
  char *symb = calloc(count + 5, 1);

  if (symb) transform_to_chars(record, count, num, symb);
  return symb;
}

char *double_to_string(long double number, Format *record) {
  char *d_symb = S21_NULL;
  long double whole, fract = 0, int_fract, num = fabsl(number);
  int count_add_zero = 0;
  if (!record->accuracy) num = round(fabsl(number));

  get_fract_part(record, num, &whole, &fract, &int_fract, record->accuracy);

  if (fract) {
    while (int_fract * pow(10, count_add_zero + 1) < pow(10, record->accuracy))
      count_add_zero++;
  }

  char *whole_str = number_to_string(record, whole);
  char *fract_str = number_to_string(record, int_fract);
  if (whole_str) {
    if (fract_str) {
      int count_whole = s21_strlen(whole_str);
      int count_fract = s21_strlen(fract_str);
      d_symb = get_join_str(fract, record->accuracy, fract_str, count_whole,
                            count_fract);
      if (d_symb) {
        s21_strcpy(d_symb, whole_str);
        if (record->accuracy || record->sharp) s21_strcat(d_symb, ".");
        if (record->accuracy <= count_add_zero)
          count_add_zero = record->accuracy - 1;
        char *fract_str_tmp = fract_str;
        if (record->right_offset) fract_str_tmp++;
        while (count_add_zero-- > 0) s21_strcat(d_symb, "0");
        if (record->accuracy) s21_strcat(d_symb, fract_str_tmp);
      }
      free(fract_str);
    }
    free(whole_str);
  }
  return d_symb;
}

void get_fract_part(Format *record, long double num, long double *whole,
                    long double *fract, long double *int_fract, int acc) {
  *fract = modfl(num, whole);
  *int_fract = roundl(*fract * pow(10, acc));

  if (*int_fract == pow(10, acc)) {
    *whole += 1;
    record->right_offset = 1;
  }
}

char *get_join_str(long double fract, int acc, char *fract_str, int count_whole,
                   int count_fract) {
  char *d_symb;
  if (!fract) {
    for (int i = 0; i < acc - 1; i++) fract_str[i + 1] = '0';
    fract_str[acc] = '\0';
  }
  int count = count_whole + count_fract + acc;
  d_symb = calloc(count + 50, 1);
  return d_symb;
}

char *g_G_double_to_string(long double number, Format *record) {
  char *d_symb = S21_NULL;
  long double whole, fract, int_fract = 0, num = fabsl(number), whole_fract = 0;
  int count_add_zero = 0;

  if (!record->accuracy) record->accuracy = 1;
  fract = modfl(num, &whole);
  get_g_G_fract_part(record, &whole, number, fract, &int_fract, whole_fract,
                     &count_add_zero);
  char *whole_str = number_to_string(record, whole);
  char *fract_str = number_to_string(record, int_fract);
  if (whole_str) {
    if (fract_str) {
      d_symb = get_g_G_join_str(d_symb, whole_str, fract_str, whole, fract,
                                record, count_add_zero, int_fract);
      free(fract_str);
    }
    free(whole_str);
  }
  return d_symb;
}

void get_g_G_fract_part(Format *record, long double *whole, long double number,
                        long double fract, long double *int_fract,
                        long double whole_fract, int *count_add_zero) {
  char *whole_len_mess = number_to_string(record, *whole);
  int whole_len = whole_len_mess ? s21_strlen(whole_len_mess) : 1;
  if (whole_len_mess) free(whole_len_mess);
  if (whole_len == record->accuracy) *whole = roundl(fabsl(number));

  if (fract) {
    if (*whole) {
      *int_fract = roundl(fract * pow(10, record->accuracy - whole_len));
    } else {
      long double tmp_fract = fract;
      int i = 0;
      while (tmp_fract < pow(10, record->accuracy - 1)) {
        tmp_fract *= 10;
        i++;
      }
      *int_fract = roundl(fract * pow(10, i));
    }
    if (*int_fract == pow(10, record->accuracy)) {
      *whole += 1;
      record->right_offset = 1;
    }
    while (!modfl((*int_fract / 10), &whole_fract) && *int_fract != 0) {
      *int_fract /= 10;
    }
  }

  if (*int_fract) {
    while (fract * pow(10, *count_add_zero + 1) < 1.L) {
      *count_add_zero += 1;
      if (*count_add_zero > record->accuracy + 10) break;
    }
    if (fract * pow(10, *count_add_zero) != 1.0 && *int_fract == 1.)
      *count_add_zero -= 1;
  }
}

char *get_g_G_join_str(char *d_symb, const char *whole_str, char *fract_str,
                       long double whole, long double fract,
                       const Format *record, int count_add_zero,
                       long double int_fract) {
  int count_whole = s21_strlen(whole_str);
  int count_fract = s21_strlen(fract_str);
  char *fract_str_tmp = fract_str;
  if (record->right_offset) fract_str_tmp++;

  int count = count_whole + count_fract + record->accuracy;
  d_symb = calloc(count + 50, 1);
  if (d_symb) {
    int zero = count_add_zero;
    s21_strcpy(d_symb, whole_str);
    if (whole) {
      if (record->sharp || (int_fract && *fract_str_tmp)) {
        s21_strcat(d_symb, ".");
        while (zero-- > 0) s21_strcat(d_symb, "0");
        count -= record->accuracy;
        s21_strcat(d_symb, fract_str_tmp);
        while (count++ < record->accuracy) s21_strcat(d_symb, "0");
      }
    } else {
      if (fract || record->sharp) {
        s21_strcat(d_symb, ".");
        while (zero-- > 0) s21_strcat(d_symb, "0");
        s21_strcat(d_symb, fract_str);
        if (record->sharp) {
          while (count_fract++ < record->accuracy) s21_strcat(d_symb, "0");
        }
      }
    }
  }
  return d_symb;
}

char *double_to_string_science_g_G(long double number, Format *record) {
  char *d_symb = S21_NULL;
  int count_add_zero = 0;
  int local_acc = record->accuracy;
  long double whole, fract, int_fract, num = fabsl(number), whole_fract;
  if (local_acc) local_acc -= 1;
  if (!local_acc) num = roundl(fabsl(number));

  get_fract_part(record, num, &whole, &fract, &int_fract, local_acc);

  if (int_fract) {
    while (!modfl((int_fract / 10), &whole_fract) && int_fract != 0) {
      int_fract /= 10;
      local_acc -= 1;
    }
    while (int_fract * pow(10, count_add_zero + 1) < pow(10, local_acc))
      count_add_zero++;
  }
  char *whole_str = number_to_string(record, whole);
  char *fract_str = number_to_string(record, int_fract);
  if (whole_str) {
    if (fract_str) {
      int count_whole = s21_strlen(whole_str);
      int count_fract = s21_strlen(fract_str);
      d_symb =
          get_join_str(fract, local_acc, fract_str, count_whole, count_fract);
      if (d_symb) {
        s21_strcpy(d_symb, whole_str);
        if ((int_fract && local_acc) || record->sharp) {
          s21_strcat(d_symb, ".");
          char *fract_str_tmp = fract_str;
          if (record->right_offset) fract_str_tmp++;
          while (count_add_zero-- > 0) s21_strcat(d_symb, "0");
          if (local_acc) s21_strcat(d_symb, fract_str_tmp);
        }
        if (record->sharp) {
          int d_symb_len = s21_strlen(d_symb) - 1;
          while (d_symb_len++ < record->accuracy) s21_strcat(d_symb, "0");
        }
      }
      free(fract_str);
    }
    free(whole_str);
  }
  return d_symb;
}

char *number_to_science_notation(long double number, Format *record) {
  int exponent = 0, exp_minus = 0;
  long double num = number;
  while (num >= 10.0 || num <= -10.0) num /= 10.0, exponent++;
  while (num < 1.0 && num > -1.0 && num != 0.) num *= 10.0, exponent--;
  if (exponent < -4 || exponent >= record->accuracy) record->g_science = 1;
  if (exponent < 0) exp_minus = 1;

  char *science_str;
  if (record->g_spec) {
    if (record->g_science) record->use_exp = 1;
    science_str = double_to_string_science_g_G(num, record);
  } else
    science_str = double_to_string(num, record);

  if (science_str) {
    char *exp_str_without_zero = number_to_string(record, exponent);
    if (exp_str_without_zero) {
      int l = s21_strlen(exp_str_without_zero);
      char exp_str[l + 5];
      if (l == 1) {
        exp_str[0] = exp_minus ? '-' : '+';
        exp_str[1] = '0';
        exp_str[2] = '\0';
      } else {
        exp_str[0] = exp_minus ? '-' : '+';
        exp_str[1] = '\0';
      }
      s21_strcat(exp_str, exp_str_without_zero);
      free(exp_str_without_zero);

      int new_length = s21_strlen(exp_str) + s21_strlen(science_str) + 50;
      char *check_realloc = realloc(science_str, new_length);
      if (check_realloc) {
        science_str = check_realloc;
        s21_strcat(science_str,
                   ((record->spec == 'e' || record->spec == 'g') ? "e" : "E"));
        s21_strcat(science_str, exp_str);
      }
    }
  }
  return science_str;
}

void add_left_spaces(const Format *record, s21_size_t len, char *str,
                     const char *x) {
  if (!record->minus) {
    int spaces_count = record->width > (int)len ? record->width - len : 0;
    for (int i = spaces_count; i > 0; i--) {
      s21_strcat(str, x);
    }
  }
}

void add_right_spaces(const Format *record, s21_size_t len, char *str) {
  if (record->minus) {
    int spaces_count;
    if (record->width > (int)len)
      spaces_count = record->width - len;
    else
      spaces_count = 0;
    for (int i = spaces_count; i > 0; i--) s21_strcat(str, " ");
  }
}

void add_plus_minus_space(char *str, s21_size_t *len, const char *tmp,
                          Format *record, int sign_minus) {
  if (record->sharp &&
      (record->spec == 'o' || record->spec == 'x' || record->spec == 'X'))
    record->check_sharp = 1;

  *len = s21_strlen(tmp);
  if (record->spec == 'd' || record->spec == 'u' || record->spec == 'o' ||
      record->spec == 'x' || record->spec == 'X') {
    int check = record->accuracy;
    for (; check > (int)s21_strlen(tmp); check--) *len += 1;
  }
  if (sign_minus || record->plus || record->space) *len += 1;
  if (record->sharp && *tmp != '0') {
    if (record->spec == 'o') *len += 1;
    if (record->spec == 'x' || record->spec == 'p' || record->spec == 'X')
      *len += 2;
  }
  if (!record->zero) add_left_spaces(record, *len, str, " ");
  if (sign_minus) {
    s21_strcat(str, "-");
  } else if (record->plus) {
    if (record->spec != 'u') s21_strcat(str, "+");
  } else if (record->space) {
    if (record->spec != 'u') s21_strcat(str, " ");
  }
  if (record->sharp && *tmp != '0') {
    if (record->spec == 'o')
      s21_strcat(str, "0");
    else if (record->spec == 'x' || record->spec == 'p')
      s21_strcat(str, "0x");
    else if (record->spec == 'X')
      s21_strcat(str, "0X");
  }
  if (record->zero) add_left_spaces(record, *len, str, "0");
}

void write_str(char *str, const char *tmp, const Format *record,
               s21_size_t len) {
#if defined(__APPLE__) || defined(__MACH__)
  const char null_nil[] = "0x0";
#elif defined(__linux__)
  const char null_nil[] = "(nil)";
#endif

  s21_strcat(str, !record->null ? tmp : null_nil);
  add_right_spaces(record, len, str);
}
