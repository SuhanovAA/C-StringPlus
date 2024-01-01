#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int return_result = *str ? INT_NULL : INT_MINUS_ONE;
  va_list ap;
  va_start(ap, format);

  char *cast_str = (char *)str;
  char *start = cast_str;
  char *cast_format = (char *)format;
  while (*cast_str && *cast_format && return_result != INT_MINUS_ONE) {
    if (*cast_format == CHAR_PERCENT) {
      cast_format++;
      if (*cast_format != CHAR_PERCENT) {
        specifier spec = scan_specifier(&cast_format);
        return_result += scan(spec, &cast_str, ap, &return_result, start);
      } else {
        if (*cast_str == CHAR_PERCENT) {
          cast_str++;
          cast_format++;
        } else {
          return_result = INT_MINUS_ONE;
        }
      }
    } else {
      if (*cast_str == *cast_format) {
        cast_str++;
        cast_format++;
      } else if (*cast_format == CHAR_SPACE) {
        cast_format++;
      } else {
        break;
      }
    }
  }
  if (*cast_format == CHAR_PERCENT && *(cast_format + 1) == CHAR_N) {
    *va_arg(ap, long int *) = cast_str - start;
  }

  va_end(ap);

  return return_result;
}

s21_bool scan(specifier spec, char **str, va_list ap, int *negative_scan,
              const char *start) {
  s21_bool return_result = S21_FALSE;
  while (**str == CHAR_SPACE) {
    (*str)++;
  }
  if (**str) {
    switch (spec.spec) {
      case spec_unknown:
        *negative_scan = INT_MINUS_ONE;
        break;
      case spec_c:
      case spec_s:
        return_result = parse_string(spec, str, ap);
        break;
      case spec_d:
        return_result = parse_int(spec, str, ap);
        break;
      case spec_i:
        return_result = parse_i_uint(spec, str, ap);
        break;
      case spec_e:
      case spec_G:
      case spec_E:
      case spec_f:
      case spec_g:
        return_result = parse_float(spec, str, ap);
        break;
      case spec_o:
        return_result = parse_oct(spec, str, ap, S21_FALSE);
        break;
      case spec_u:
        return_result = parse_uint(spec, str, ap, S21_FALSE);
        break;
      case spec_x:
      case spec_X:
        return_result = parse_hex(spec, str, ap, S21_FALSE);
        break;
      case spec_p:
        return_result = parse_ptr(spec, str, ap);
        break;
      case spec_n:
        *va_arg(ap, long int *) = *str - start;
        break;
      default:
        *negative_scan = INT_MINUS_ONE;
        break;
    }
  } else {
    *negative_scan = INT_MINUS_ONE;
  }
  return return_result;
}

specifier scan_specifier(char **format) {
  specifier pass_spec_line = {INT_NULL};
  if (**format == CHAR_STAR) {
    pass_spec_line.skip = S21_TRUE;
    (*format)++;
  }

  if (is_digit(**format, INT_TEN)) {
    pass_spec_line.width = scan_width(format);
  }

  if (**format == CHAR_L_SM) {
    pass_spec_line.len = len_l;
    (*format)++;
    if (**format == CHAR_L_SM) {
      pass_spec_line.len = len_L;
      (*format)++;
    }
  } else if (**format == CHAR_H_SM) {
    pass_spec_line.len = len_h;
    (*format)++;
  } else if (**format == CHAR_L) {
    pass_spec_line.len = len_L;
    (*format)++;
  } else {
    pass_spec_line.len = len_none;
  }
  const char *spec_str = SPECS_LIST;
  char *pos = s21_strchr(spec_str, **format);
  if (pos) {
    pass_spec_line.spec = (sspecs)(pos - spec_str);
  } else {
    pass_spec_line.spec = spec_unknown;
  }
  (*format)++;
  return pass_spec_line;
}

int scan_width(char **cast_format) {
  int return_result = INT_NULL;
  while (is_digit(**cast_format, INT_TEN)) {
    return_result = return_result * INT_TEN + (**cast_format - CHAR_NULL);
    (*cast_format)++;
  }
  return return_result;
}

s21_bool is_digit(char symbol_is_digit, int base) {
  s21_bool return_result;
  if (base <= INT_TEN) {
    return_result =
        symbol_is_digit >= CHAR_NULL && symbol_is_digit < CHAR_NULL + base;
  } else {
    return_result =
        (symbol_is_digit >= CHAR_NULL && symbol_is_digit <= CHAR_NINE) ||
        (symbol_is_digit >= CHAR_A &&
         symbol_is_digit < CHAR_A + base - INT_TEN) ||
        (symbol_is_digit >= CHAR_A_SM &&
         symbol_is_digit < CHAR_A_SM + base - INT_TEN);
  }
  return return_result;
}

s21_size_t to_digit(char symbol_to_digit, int base) {
  s21_size_t return_result = INT_NULL;
  if (base <= INT_TEN) {
    return_result = symbol_to_digit - CHAR_NULL;
  } else {
    if (symbol_to_digit <= CHAR_NINE) {
      return_result = symbol_to_digit - CHAR_NULL;
    } else if (symbol_to_digit <= CHAR_A + base - INT_TEN) {
      return_result = symbol_to_digit - CHAR_A + INT_TEN;
    } else {
      return_result = symbol_to_digit - CHAR_A_SM + INT_TEN;
    }
  }
  return return_result;
}

char chr_lower(char symbol_is_lower) {
  if (symbol_is_lower >= CHAR_A && symbol_is_lower <= CHAR_Z) {
    symbol_is_lower += CHAR_A_SM - CHAR_A;
  }
  return symbol_is_lower;
}

s21_bool strstr_icase(char **str, char *substring) {
  s21_bool return_result = S21_FALSE;
  char *symbol_position = *str;
  while (*symbol_position &&
         chr_lower(*symbol_position) == chr_lower(*substring)) {
    symbol_position++;
    substring++;
  }
  if (*substring == END_LINE) {
    *str = symbol_position;
    return_result = S21_TRUE;
  }
  return return_result;
}

s21_bool parse_string(specifier spec, char **str, va_list ap) {
  s21_bool return_result = S21_FALSE;
  char *d = va_arg(ap, char *);
  if (spec.width == INT_NULL) {
    if (spec.spec == spec_c) {
      spec.width = INT_ONE;
    } else {
      spec.width = S21_INT_MAX;
    }
  }
  while (**str && spec.width > INT_NULL && **str != CHAR_SPACE) {
    *d++ = **str;
    (*str)++;
    spec.width--;
  }
  if (spec.spec == spec_s) {
    *d = END_LINE;
  }
  return_result = S21_TRUE;

  return return_result;
}

s21_bool parse_int(specifier spec, char **str, va_list ap) {
  long long number_result = INT_NULL;
  s21_bool return_result = scan_int(str, spec.width, &number_result);
  return_result &= !spec.skip;
  if (return_result) {
    switch (spec.len) {
      case len_none:
        *(va_arg(ap, int *)) = (int)number_result;
        break;
      case len_h:
        *(va_arg(ap, short *)) = (short)number_result;
        break;
      case len_l:
        *(va_arg(ap, long *)) = (long)number_result;
        break;
      case len_L:
        *(va_arg(ap, long long *)) = (long long)number_result;
        break;
    }
  }
  return return_result;
}

s21_bool parse_based_uint(specifier spec, char **str, va_list ap, int base,
                          s21_bool number_sign) {
  unsigned long long number_result = INT_NULL;
  s21_bool return_result =
      scan_based_uint(str, spec.width, &number_result, base, number_sign) ||
      number_sign;
  return_result &= !spec.skip;
  if (return_result) {
    switch (spec.len) {
      case len_none:
        *(va_arg(ap, unsigned int *)) = (unsigned int)number_result;
        break;
      case len_h:
        *(va_arg(ap, unsigned short *)) = (unsigned short)number_result;
        break;
      case len_l:
        *(va_arg(ap, unsigned long *)) = (unsigned long)number_result;
        break;
      case len_L:
        *(va_arg(ap, unsigned long long *)) = (unsigned long long)number_result;
        break;
    }
  }
  return return_result;
}

s21_bool parse_uint(specifier spec, char **str, va_list ap,
                    s21_bool number_sign) {
  s21_bool return_result = S21_FALSE;
  s21_bool flag = S21_TRUE;
  if (**str == CHAR_MINUS) {
    if (!number_sign) {
      (*str)++;
      spec.width--;
      number_sign = S21_TRUE;
    } else {
      flag = S21_FALSE;
    }
  } else if (**str == CHAR_PLUS) {
    (*str)++;
    spec.width--;
  }
  if (flag) {
    return_result |= parse_based_uint(spec, str, ap, INT_TEN, number_sign);
  }
  return return_result;
}

s21_bool parse_hex(specifier spec, char **str, va_list ap,
                   s21_bool number_sign) {
  s21_bool return_result = number_sign;
  if (**str == CHAR_MINUS && !number_sign) {
    (*str)++;
    spec.width--;
    number_sign = S21_TRUE;
  } else if (**str == CHAR_PLUS) {
    (*str)++;
    spec.width--;
  }
  if (**str == CHAR_NULL &&
      ((*(*str + INT_ONE) == CHAR_X_SM) || *(*str + INT_ONE) == CHAR_X)) {
    *str += INT_TWO;
    return_result |= S21_TRUE;
  }
  return_result |= parse_based_uint(spec, str, ap, INT_HEX, number_sign);
  return return_result;
}

s21_bool parse_oct(specifier spec, char **str, va_list ap,
                   s21_bool number_sign) {
  s21_bool return_result = number_sign;
  if (**str == CHAR_MINUS && !number_sign) {
    number_sign = S21_TRUE;
    (*str)++;
    spec.width--;
  } else if (**str == CHAR_PLUS) {
    (*str)++;
    spec.width--;
  }
  if (**str == CHAR_NULL) {
    (*str)++;
    spec.width--;
    return_result |= S21_TRUE;
  }
  return_result |= parse_based_uint(spec, str, ap, INT_OCT, number_sign);
  return return_result;
}

s21_bool parse_i_uint(specifier spec, char **str, va_list ap) {
  s21_bool number_sign = S21_FALSE;
  if (**str == CHAR_MINUS) {
    number_sign = S21_TRUE;
    (*str)++;
    spec.width--;
  } else if (**str == CHAR_PLUS) {
    (*str)++;
    spec.width--;
  }
  s21_bool return_result = S21_FALSE;
  if (**str == CHAR_NULL) {
    (*str)++;
    if (**str == CHAR_X_SM) {
      (*str)++;
      return_result = parse_hex(spec, str, ap, number_sign);
    } else {
      return_result = parse_oct(spec, str, ap, number_sign);
    }
  } else {
    return_result = parse_uint(spec, str, ap, number_sign);
  }
  return return_result;
}

s21_bool parse_ptr(specifier spec, char **str, va_list ap) {
  spec.len = len_l;
  return parse_hex(spec, str, ap, S21_FALSE);
}

s21_bool parse_float(specifier spec, char **str, va_list ap) {
  s21_bool return_result = S21_FALSE;
  if (spec.width == INT_NULL) {
    spec.width = S21_INT_MAX;
  }
  long double double_result = INT_NULL;
  return_result = scan_float(str, spec.width, &double_result);
  return_result &= !spec.skip;
  if (return_result) {
    switch (spec.len) {
      case len_none:
        *(va_arg(ap, float *)) = (float)double_result;
        break;
      case len_h:
        *(va_arg(ap, float *)) = (float)double_result;
        break;
      case len_l:
        *(va_arg(ap, double *)) = (double)double_result;
        break;
      case len_L:
        *(va_arg(ap, long double *)) = double_result;
        break;
    }
  }
  return return_result;
}

s21_bool scan_int(char **str, int width, long long *dest) {
  s21_bool flag = S21_FALSE, find = S21_FALSE, number_sign = S21_FALSE;
  if (width == INT_NULL) {
    width = S21_INT_MAX;
  }
  long long number_result = INT_NULL;
  if (**str == CHAR_MINUS) {
    number_sign = S21_TRUE;
    (*str)++;
    width--;
  } else if (**str == CHAR_PLUS) {
    (*str)++;
    width--;
  }
  if (is_digit(**str, INT_TEN)) {
    find = S21_TRUE;
  } else if (number_sign) {
    (*str)--;
  }
  if (find) {
    while (is_digit(**str, INT_TEN) && width--) {
      if (number_result > (S21_LLONG_MAX - (**str - CHAR_NULL)) / INT_TEN) {
        find = S21_FALSE;
        flag = S21_TRUE;
        number_result = S21_LLONG_MAX;
        if (number_sign) {
          number_result = -number_result - INT_ONE;
        }
        while (**str && width--) {
          (*str)++;
        }
        break;
      }
      number_result = number_result * INT_TEN + (**str - CHAR_NULL);
      (*str)++;
    }
  }
  if (find && number_sign) {
    number_result = -number_result;
  }
  if (find || flag) {
    *dest = number_result;
  }
  return find || flag;
}

s21_bool scan_based_uint(char **str, int width, unsigned long long *dest,
                         int base, s21_bool number_sign) {
  s21_bool return_result = S21_FALSE;
  if (width == INT_NULL) width = S21_INT_MAX;
  if (is_digit(**str, base)) {
    return_result = S21_TRUE;
  }
  if (return_result) {
    unsigned long long number_result = INT_NULL;
    while (is_digit(**str, base) && width--) {
      if (number_result > (S21_ULLONG_MAX - to_digit(**str, base)) / base) {
        number_result = S21_ULLONG_MAX;
        while (**str && width--) (*str)++;
      } else {
        number_result = number_result * base + to_digit(**str, base);
        (*str)++;
      }
    }
    if (number_sign) number_result = -number_result;
    *dest = number_result;
  }
  return return_result;
}

s21_bool scan_float(char **str, int width, long double *dest) {
  s21_bool return_result = S21_FALSE;
  s21_bool number_sign = S21_FALSE;
  long double number_result = INT_NULL;
  if (**str == CHAR_MINUS) {
    number_sign = S21_TRUE;
    (*str)++;
    width--;
  } else if (**str == CHAR_PLUS) {
    (*str)++;
    width--;
  }
  if (nan_inf(str, &number_result)) {
    return_result = S21_TRUE;
  } else if (is_digit(**str, INT_TEN) || **str == CHAR_DOT) {
    return_result = S21_TRUE;
    if (**str == CHAR_DOT) {
      return_result = S21_FALSE;
      if (is_digit(*(*str + INT_ONE), INT_TEN)) {
        return_result = S21_TRUE;
      }
    }
    number_result = s21_atof(str, &width);
    scientific(str, &width, &number_result);
  } else if (number_sign) {
    (*str)--;
  }
  if (return_result) {
    if (number_sign) number_result = -number_result;
    *dest = number_result;
  }
  return return_result;
}

s21_bool nan_inf(char **str, long double *dest) {
  s21_bool return_result = S21_FALSE;
  if (strstr_icase(str, NOT_NUMBER_DESIGN)) {
    return_result = S21_TRUE;
    *dest = NAN;
  } else if (strstr_icase(str, INFINITY_DESIGN)) {
    return_result = S21_TRUE;
    *dest = INFINITY;
  }
  return return_result;
}

long double s21_atof(char **str, int *width) {
  long double return_result = INT_NULL;
  while (is_digit(**str, INT_TEN) && width) {
    return_result = return_result * INT_TEN + (**str - CHAR_NULL);
    (*str)++;
    (*width)--;
  }
  if (**str == CHAR_DOT) {
    (*str)++;
    (*width)--;
    long double frac_coef = INT_ONE;
    int frac_width = INT_NULL;
    while (is_digit(*(*str + frac_width), INT_TEN) && (*width)--) frac_width++;
    while (frac_width--) {
      frac_coef /= INT_TEN;
      return_result += frac_coef * (**str - CHAR_NULL);
      (*str)++;
    }
  }
  return return_result;
}

s21_bool scientific(char **str, int *width, long double *number_result) {
  long long exp = INT_NULL;
  s21_bool return_result = S21_FALSE;

  if (**str == CHAR_E_SM || **str == CHAR_E) {
    (*str)++;
    (*width)--;
    return_result = scan_int(str, *width, &exp);
  }

  *number_result *= pow(INT_TEN, exp);
  return return_result;
}