#include <locale.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myclib/include/myclib.h"
#include "myclib/str/str.h"
#include "wdtranslator/wdtranslator.h"

/* - CONVENIENCE MACROS - */

#define CONSTRUCT_KEYWORD_GROUP(action, ...)                  \
  (keyword_group) {                                           \
    .ACTION = (action),                                       \
    .NUM_KEYWORDS = ARR_LEN(((const char *[]){__VA_ARGS__})), \
    .KEYWORDS = (const char *[]){__VA_ARGS__},                \
  }

#define CONSTRUCT_WD_TRANSLATOR(translator_func, type) \
  ((wd_translator){.TRANSLATOR = (translator_func),    \
                   .NAME = STRINGIFY(translator_func), \
                   .TYPE = (type)})

/* - DEFINITIONS - */

#define UTF8_CHCP_CMD "chcp 65001"

/* - ENUMS - */

typedef enum : unsigned {
  TM_ASCII_TO_WD = 1,
  TM_WD_TO_ASCII = 2,
} translator_type;

typedef enum : unsigned {
  UA_NONE = 0,
  UA_EXIT = 1,
  UA_SWITCH = 2,
} user_action;

typedef enum : int {
  EC_STDIN_AT_EOF = 1,
  EC_STRING_CTOR_FAILURE = EC_STDIN_AT_EOF << 1,
} exit_code;

/* - TYPES - */

typedef struct {
  const char *const *const KEYWORDS;
  const size_t NUM_KEYWORDS;
  const user_action ACTION;
} keyword_group;

typedef void (*const translator_func)(const_string);

typedef struct {
  translator_func TRANSLATOR;
  const char *const NAME;
  const translator_type TYPE;
} wd_translator;

/* - TRANSLATOR DECLARATIONS - */

static void ascii_to_wd_translator(const_string);
static void wd_to_ascii_translator(const_string);

/* - CONSTANTS - */

static const keyword_group KEYWORDS[] = {
    CONSTRUCT_KEYWORD_GROUP(UA_EXIT, "!exit", "!quit"),
    CONSTRUCT_KEYWORD_GROUP(UA_SWITCH, "!switch", "!chg"),
};

static const wd_translator TRANSLATORS[] = {
    CONSTRUCT_WD_TRANSLATOR(ascii_to_wd_translator, TM_ASCII_TO_WD),
    CONSTRUCT_WD_TRANSLATOR(wd_to_ascii_translator, TM_WD_TO_ASCII),
};

/* - FUNCTION DECLARATIONS - */

static bool is_valid_translator_mode(translator_type);
static bool prompt_chcp_change(void);

/* - UTILITY - */

static inline void display_translators(void) {
  for (size_t i = 0; i < ARR_LEN(TRANSLATORS); i++)
    printf("%zu. %s\n", i + 1, TRANSLATORS[i].NAME);
  fflush(stdout);
}

static inline translator_type get_translator_option(void) {
  translator_type type;
  string buf = string_write_from_stream_(NULL, stdin, '\n');
  while (true) {
    if (sscanf(buf, "%u", &type) == 1)
      if (is_valid_translator_mode(type)) break;
    if (feof(stdin)) exit(EC_STDIN_AT_EOF);
    string_clear(buf);
    string_write_from_stream(buf, stdin, '\n');
  }
  string_delete(buf);
  return type;
}

static inline bool is_valid_translator_mode(const translator_type mode) {
  switch (mode) {
    case TM_ASCII_TO_WD:
    case TM_WD_TO_ASCII:
      return true;
  }
  return false;
}

static inline user_action is_user_action(const_string str) {
  for (size_t i = 0; i < ARR_LEN(KEYWORDS); i++) {
    const keyword_group *const group = KEYWORDS + i;
    for (size_t j = 0; i < group->NUM_KEYWORDS; j++)
      if (string_equals(str, group->KEYWORDS[j])) return group->ACTION;
  }
  return UA_NONE;
}

static inline void init(void) {
#ifdef _WIN32
  if (system(NULL) && prompt_chcp_change()) system(UTF8_CHCP_CMD);
#endif
  setlocale(LC_CTYPE, "en_US.UTF-8");
  setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
}

static inline const wd_translator *get_translator(translator_type type) {
  for (size_t i = 0; i < ARR_LEN(TRANSLATORS); i++) {
    if (type == TRANSLATORS[i].TYPE) return TRANSLATORS + i;
  }
  return NULL;
}

/* - PROMPTS - */

[[maybe_unused]]
static inline bool prompt_chcp_change(void) {
  puts("This program relies on UTF-8 encoding for full functionality.");
  puts("Querying current code page...");
  system("chcp");
  puts("Allow this program to run \"" UTF8_CHCP_CMD "\"?");
  return system("choice") == 1;  // `choice` returns `1` by default for `y`.
}

[[nodiscard]] static inline translator_type prompt_translator(void) {
  puts("Which translator would you like to use?");
  display_translators();
  return get_translator_option();
}

/* - TRANSLATORS - */

static void ascii_to_wd_translator(const_string input) {}

static void wd_to_ascii_translator(const_string input) {}

static inline void translator_intermediary(translator_type mode) {
  string buf = string_write_from_stream_(NULL, stdin, '\n');
  const user_action action = is_user_action(buf);
  switch (action) {
    case UA_NONE:
      
      break;
    case UA_EXIT:
      return;
    case UA_SWITCH:
      mode = prompt_translator();
  }
}

int main(void) {
  init();
  translator_intermediary(prompt_translator());
  return 0;
}
