#include "wdtranslator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../myclib/include/myclib.h"
#include "../myclib/str/str.h"

/* - UTILITY - */

static inline size_t wd_char_index(const_wd_char *const chr) {
  return (size_t)(chr - SORTED_WINGDINGS);
}

/* - IMPLEMENTATION - */

const_wd_char ascii_char_to_wd_char(const char ascii) {
  return (ascii >= ASCII_TO_WD_OFFSET) ? WINGDINGS[ascii - ASCII_TO_WD_OFFSET]
                                      : NULL;
}

string ascii_str_to_wd_str(const char *ascii_str) {
  string wd_output = string();
  while (*ascii_str != '\0') {
    const char CHR = *ascii_str;
    const char *const wd_char = ascii_char_to_wd_char(CHR);
    if (wd_char != NULL)
      string_append(wd_output, wd_char);
    else
      string_append(wd_output, CHR);
    ascii_str++;
  }
  return wd_output;
}

const_wd_char *search_sorted_wd(const_wd_char wd_char) {
  size_t min = 0;
  size_t max = ARR_LEN(WINGDINGS);
  while (min < max) {
    const size_t MID = (min + max) / 2;
    const int CMP_RESULT = strcmp(wd_char, SORTED_WINGDINGS[MID]);
    if (CMP_RESULT < 0)
      max = MID;
    else if (CMP_RESULT > 0)
      min = MID + 1;
    else
      return SORTED_WINGDINGS + MID;
  }
  return NULL;
}

bool is_substr_wd_candidate(const char *const substr) {
  if (IS_WD_BEGIN_BYTE(*substr)) {
    WD_SIZE substr_len = 0;
    while (substr_len < WDS_LARGE && substr[substr_len] != '\0')
      substr_len++;
    switch (substr_len) {
    case WDS_SMALL:
      return IS_SMALL_WD(substr);
    case WDS_MEDIUM:
      return IS_MEDIUM_WD(substr);
    case WDS_LARGE:
      return IS_LARGE_WD(substr);
    }
  }
  return false;
}

char wd_char_to_ascii_char(const_wd_char wd_char) {
  const_wd_char *const wd_char_pos = search_sorted_wd(wd_char);
  return (char)(wd_char_pos != NULL
                    ? SORTED_WD_TO_ASCII[wd_char_pos - SORTED_WINGDINGS]
                    : '\0');
}

string wd_str_to_ascii_str(const char *wd_str) {
  string ascii_str = string();
  size_t prev_index = 0;
  while (*wd_str != '\0') {
    if (is_substr_wd_candidate(wd_str)) {
      const_wd_char *const wd_char = search_sorted_wd(wd_str);
      const size_t WD_CHR_IDX = wd_char_index(wd_char);
      string_append_char(ascii_str, SORTED_WD_TO_ASCII[WD_CHR_IDX]);
      wd_str += WD_LEN_TYPE(*wd_char);
    } else {
      // If no Wingdings candidates were found, we can skip ahead by the largest
      // possible Wingdings character.
      for (size_t i = 0; i < WDS_LARGE && *wd_str != '\0'; i++, wd_str++)
        string_append_char(ascii_str, *wd_str);
    }
  }
  return ascii_str;
}
