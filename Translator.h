// - Header Guards End -
#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef _INC_TRANSLATOR
#define _INC_TRANSLATOR
#endif

// - Header Guards End -

#define NUM_WINGDINGS (sizeof(wingdings) / sizeof(*wingdings))

#define WINGDINGS_CHAR_MAX_SIZE (sizeof(*wingdings))

/*
 * This is the offset between a standard ASCII char's value and its corresponding Wingdings character.
 *
 * Subtract a char by this value when indexing wingdings[] to get its Wingdings counterpart, or
 * add this value to a valid index within wingdings[] to get that particular Wingdings' char equivalent.
 *
 * An example: Consider the char 'd', ASCII value 100. 'd' corresponds to '♎︎', index 68.
 * If you have only the value of 'd', you can find its corresponding Wingdings via
 * "wingdings['d' - ASCII_WINGDINGS_OFFSET]".
 */
#define ASCII_WINGDINGS_OFFSET (CHAR_MAX - NUM_WINGDINGS)

#define CODE_ENGLISH_TO_WINGDINGS (0)
#define CODE_WINGDINGS_TO_ENGLISH (1)

#define WINGDINGS_TO_ENG_OUTPUT_FILENAME "WingdingsToEnglish.txt"
#define ENG_TO_WINGDINGS_OUTPUT_FILENAME "EnglishToWingdings.txt"

#define WINGDINGS_OUTPUT output_files[0]

#define SHOULD_CLEAR_OUTPUT_FILES (1)

// The maximum number of bytes to read from one line of input.
#define MAX_BYTE_READS (4096)

// Preferably keep the below keywords unique enough so that they won't
// interfere with normal input when the translator picks up input.
// Regular words like "exit" could be legitimate user input for instance.

#define EXIT_KEYWORD "!exit"
#define EXIT_STATUS_CODE (10)

#define CHANGE_TRANSLATOR_KEYWORD "!chg"
#define CHANGE_TRANSLATOR_STATUS_CODE (11)

#define CASE_SENSITIVE_KEYWORDS 0

// ASCII characters mapped to their respective Wingdings representation.
static const char *const wingdings[] = {
    // Symbols 1 (!, ", #, $, %, &, ', (, ), *, +, ',' , -, ., /) (15 total)
    "✏︎", "✂︎", "✁︎", "👓︎", "🕭︎", "🕮︎", "🕯︎", "🕿︎", "✆︎", "🖂︎", "🖃︎", "📪︎",
    "📫︎", "📬︎", "📭︎",

    // Numerical characters (0-9) (10 total | 25 total Wingdings)
    "📁︎", "📂︎", "📄︎", "🗏︎", "🗐︎", "🗄︎", "⌛︎", "🖮︎", "🖰︎", "🖲︎",

    // Symbols 2 (:, ;, <, =, >, ?, @) (7 total | 32 total Wingdings)
    // '@' has no Wingdings equivalent - it's here only for the sake of compatibility
    "🖳︎", "🖴︎", "🖫︎", "🖬︎", "✇︎", "✍︎", "@",

    // Uppercase alphabetical characters (A-Z) (26 total | 58 total Wingdings)
    "✌︎", "👌︎", "👍︎", "👎︎", "☜︎", "☞︎", "☝︎", "☟︎", "✋︎", "☺︎", "😐︎", "☹︎",
    "💣︎", "☠︎", "⚐︎", "🏱︎", "✈︎", "☼︎", "💧︎", "❄︎", "🕆︎", "✞︎", "🕈︎", "✠︎",
    "✡︎", "☪︎",

    // Symbols 3 ([, \, ], ^, _, `) (6 total | 64 total Wingdings)
    "☯︎", "ॐ︎", "☸︎", "☸︎", "♈︎", "♉︎",

    // Lowercase alphabetical characters (a-z) (26 total | 90 total Wingdings)
    "♋︎", "♌︎", "♍︎", "♎︎", "♏︎", "♐︎", "♑︎", "♒︎", "♓︎", "🙰", "🙵", "●︎",
    "❍︎", "■︎", "□︎", "◻︎", "❑︎", "❒︎", "⬧︎", "⧫︎", "◆︎", "❖︎", "⬥︎", "⌧︎",
    "⍓︎", "⌘︎",

    // Symbols 4 ({, |, }, ~) (4 total | 94 total Wingdings)
    "❀︎", "✿︎", "❝︎", "❞︎"};

/*
 * Sorted with stdlib's qsort() with a comparator function of:
 *
 * int cmp(const void *const a, const void *const b)
 * {
 *   const char *const *char_a = a;
 *   const char *const *char_b = b;
 *   return strcmp(*char_a, *char_b);
 * }
 *
 */
static const char *const sorted_wingdings[] = {
    "@", "ॐ︎", "⌘︎", "⌛︎", "⌧︎", "⍓︎", "■︎", "□︎", "◆︎", "●︎", "◻︎", "☜︎",
    "☝︎", "☞︎", "☟︎", "☠︎", "☪︎", "☯︎", "☸︎", "☸︎", "☹︎", "☺︎", "☼︎", "♈︎",
    "♉︎", "♋︎", "♌︎", "♍︎", "♎︎", "♏︎", "♐︎", "♑︎", "♒︎", "♓︎", "⚐︎", "✁︎",
    "✂︎", "✆︎", "✇︎", "✈︎", "✋︎", "✌︎", "✍︎", "✏︎", "✞︎", "✠︎", "✡︎", "✿︎",
    "❀︎", "❄︎", "❍︎", "❑︎", "❒︎", "❖︎", "❝︎", "❞︎", "⧫︎", "⬥︎", "⬧︎", "🏱︎",
    "👌︎", "👍︎", "👎︎", "👓︎", "💣︎", "💧︎", "📁︎", "📂︎", "📄︎", "📪︎", "📫︎", "📬︎",
    "📭︎", "🕆︎", "🕈︎", "🕭︎", "🕮︎", "🕯︎", "🕿︎", "🖂︎", "🖃︎", "🖫︎", "🖬︎", "🖮︎",
    "🖰︎", "🖲︎", "🖳︎", "🖴︎", "🗄︎", "🗏︎", "🗐︎", "😐︎", "🙰", "🙵"};

// output_files[0] is the WINGDINGS OUTPUT FILE (ASCII-to-Wingdings conversion)
static FILE *output_files[] = {NULL};

// Returns 0 if the output files were opened successfully.
// Returns 1 otherwise.
int open_output_files(void)
{
    if (SHOULD_CLEAR_OUTPUT_FILES)
    {
        fopen_s(&WINGDINGS_OUTPUT, ENG_TO_WINGDINGS_OUTPUT_FILENAME, "w");
    }
    else
    {
        fopen_s(&WINGDINGS_OUTPUT, ENG_TO_WINGDINGS_OUTPUT_FILENAME, "a");
    }

    if (!WINGDINGS_OUTPUT)
    {
        fputs("Could not open output file (" ENG_TO_WINGDINGS_OUTPUT_FILENAME ")\n", stderr);
        return 1;
    }

    return 0;
}

/* - Functions to translate from ASCII to Wingdings and vice versa - */

char *ascii_str_to_wingdings(const char *const ascii_str, const size_t ascii_strlen);

char wingdings_char_to_ascii_char(const char *const _wingdings_char);

char *wingdings_to_ascii_str(const char *wingdings_to_translate);
