#include "wdtranslator.h"

#include <stdlib.h>
#include <string.h>

#include "../myclib/include/myclib.h"
#include "../myclib/str/str.h"

/* - UTILITY - */

static inline size_t wd_char_index(const_wd_char *const chr) {
  return (size_t)(chr - WINGDINGS);
}

/* - IMPLEMENTATION - */

const_wd_char ascii_char_to_wd_char(const char ascii) {
  return (ascii > ASCII_TO_WD_OFFSET) ? WINGDINGS[ascii - ASCII_TO_WD_OFFSET]
                                      : NULL;
}

string ascii_str_to_wd_str(const char *ascii_str) {
  string wd_output = string_init(STR_DEFAULT_CAPACITY);
  while (*ascii_str != '\0') {
    const char CHR = *ascii_str;
    const char *const wd_char = ascii_char_to_wd_char(CHR);
    if (wd_char != NULL)
      string_append_raw_str(wd_output, wd_char);
    else
      string_append_char(wd_output, CHR);
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

const_wd_char *search_for_wd(const char *const wd_cand) {
  switch ((WD_BEGIN_BYTE)*wd_cand) {
  case WD_BEGIN_1:
  case WD_BEGIN_2: {
    char wingdings_container[WDS_LARGE];
    size_t wd_length;
    if (IS_SMALL_WD(wd_cand))
      wd_length = WDS_SMALL;
    else if (IS_MEDIUM_WD(wd_cand))
      wd_length = WDS_MEDIUM;
    else if (IS_LARGE_WD(wd_cand))
      wd_length = WDS_LARGE;
    else
      break;
    strncpy(wingdings_container, wd_cand, wd_length - 1);
    wingdings_container[wd_length] = '\0';
    return search_sorted_wd(wingdings_container);
  }
  }
  return NULL;
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
    const_wd_char *const wd_char = search_for_wd(wd_str);
    if (wd_char != NULL) {
      const size_t CUR_INDEX = wd_char_index(wd_char);
      string_append_char(ascii_str, SORTED_WD_TO_ASCII[CUR_INDEX]);
      wd_str += CUR_INDEX - prev_index;
      prev_index = CUR_INDEX;
    } else {
      string_append_char(ascii_str, *wd_str);
      wd_str++;
    }
  }
  return ascii_str;
}
