#ifndef WD_TRANSLATOR
#define WD_TRANSLATOR

#include <limits.h>
#include <stddef.h>

#include "../myclib/include/myclib.h"
#include "../myclib/str/str.h"

/* - DEFINITIONS - */

#define IS_WD_BEGIN_BYTE(chr)                                                  \
  ((WD_BEGIN_BYTE)(chr) == WD_BEGIN_1 || (WD_BEGIN_BYTE)(chr) == WD_BEGIN_2 || \
   (WD_BEGIN_BYTE)(chr) == WD_BEGIN_3)

#define IS_SMALL_WD(wd_chr)                                                    \
  ((byte)(wd_chr)[WDS_SMALL - 2] == WDSCB_1 &&                                 \
   (byte)(wd_chr)[WDS_SMALL - 3] == WDSCB_2)

#define IS_MEDIUM_WD(wd_chr)                                                   \
  ((byte)(wd_chr)[WDS_MEDIUM - 2] == WDCB_1 &&                                 \
   (byte)(wd_chr)[WDS_MEDIUM - 3] == WDCB_2)

#define IS_LARGE_WD(wd_chr)                                                    \
  ((byte)(wd_chr)[WDS_LARGE - 2] == WDCB_1 &&                                  \
   (byte)(wd_chr)[WDS_LARGE - 3] == WDCB_2)

#define WD_LEN_TYPE(wd_chr)                                                    \
  (IS_SMALL_WD(wd_chr)    ? WDS_SMALL                                          \
   : IS_MEDIUM_WD(wd_chr) ? WDS_MEDIUM                                         \
   : IS_LARGE_WD(wd_chr)  ? WDS_LARGE                                          \
                          : 0)

/* - ENUMS - */

typedef enum : byte {
  WD_BEGIN_1 = 226,
  WD_BEGIN_2 = 240, // 🙰 and 🙵
  WD_BEGIN_3 = 224, // ॐ︎
} WD_BEGIN_BYTE;

// These bytes are selected for their lack of collisions with other Wingdings
// characters (i.e., they do not appear multiple times or in different positions
// for any given Wingdings).
typedef enum : byte {
  WDCB_1 = 184, // A common second-to-last byte.
  WDCB_2 = 239, // A common third-to-last byte.
} WD_COMMON_BYTE;

typedef enum : byte {
  WDSCB_1 = 153, // For 🙰 and 🙵, this is the common second-to-last byte.
  WDSCB_2 = 159, // For 🙰 and 🙵, this is the common third-to-last byte.
} WD_SPECIAL_COMMON_BYTE;

typedef enum : size_t {
  WDS_SMALL = sizeof("🙰") - 1,
  WDS_MEDIUM = sizeof("✏︎") - 1,
  WDS_LARGE = sizeof("👓︎") - 1,
} WD_SIZE;

/* - TYPES - */

typedef char *wd_array[];
typedef const char *const const_wd_array[];

typedef char *wd_char;
typedef const char *const const_wd_char;

/* - CONSTANTS - */

/*
 * Subtract an ASCII character by this value when indexing `wingdings` to get an
 * index to its Wingdings counterpart. Likewise, add this value to a valid index
 * of `wingdings` to get its ASCII equivalent.
 *
 * ### Example:
 * Consider the ASCII character `'d'`, whose ASCII value is `100`. `'d'`
 * corresponds to the '♎︎' Wingdings, which is stored at `wingdings[68]`.
 * The corresponding Wingdings for `'d'` can be found within `wingdings` like
 * so: `wingdings['d' - ASCII_TO_WD_OFFSET]`
 */
#define ASCII_TO_WD_OFFSET (char)(CHAR_MAX - NUM_WINGDINGS)

#define NUM_WINGDINGS ARR_LEN(WINGDINGS)

static const_wd_array WINGDINGS = {
    // Symbols 1 (!, ", #, $, %, &, ', (, ), *, +, ',' , -, ., /)
    // (15 listed)
    "✏︎",  // !
    "✂︎",  // "
    "✁︎",  // #
    "👓︎", // $
    "🕭︎", // %
    "🕮︎", // &
    "🕯︎", // '
    "🕿︎", // (
    "✆︎",  // )
    "🖂︎", // *
    "🖃︎", // +
    "📪︎", // ,
    "📫︎", // -
    "📬︎", // .
    "📭︎", // /

    // Numerical characters (0-9) (10 listed | 25 total Wingdings)
    "📁︎", // 0
    "📂︎", // 1
    "📄︎", // 2
    "🗏︎", // 3
    "🗐︎", // 4
    "🗄︎", // 5
    "⌛︎", // 6
    "🖮︎", // 7
    "🖰︎", // 8
    "🖲︎", // 9

    // Symbols 2 (:, ;, <, =, >, ?, @) (7 listed | 32 total Wingdings)
    // '@' has no Wingdings equivalent; it is present for compatibility.
    "🖳︎", // :
    "🖴︎", // ;
    "🖫︎", // <
    "🖬︎", // =
    "✇︎",  // >
    "✍︎",  // ?
    "@",  // @

    // Uppercase alphabetical characters (A-Z) (26 listed | 58 total
    // Wingdings)
    "✌︎",  // A
    "👌︎", // B
    "👍︎", // C
    "👎︎", // D
    "☜︎",  // E
    "☞︎",  // F
    "☝︎",  // G
    "☟︎",  // H
    "✋︎", // I
    "☺︎",  // J
    "😐︎", // K
    "☹︎",  // L
    "💣︎", // M
    "☠︎",  // N
    "⚐︎",  // O
    "🏱︎", // P
    "✈︎",  // Q
    "☼︎",  // R
    "💧︎", // S
    "❄︎",  // T
    "🕆︎", // U
    "✞︎",  // V
    "🕈︎", // W
    "✠︎",  // X
    "✡︎",  // Y
    "☪︎",  // Z

    // Symbols 3 ([, \, ], ^, _, `) (6 listed | 64 total Wingdings)
    "☯︎",  // [
    "ॐ︎",  // (backslash)
    "☸︎",  // ]
    "♈︎", // ^
    "♉︎", // _
    "♊︎", // `

    // Lowercase alphabetical characters (a-z)
    // (26 listed | 90 total Wingdings)
    "♋︎", // a
    "♌︎", // b
    "♍︎", // c
    "♎︎", // d
    "♏︎", // e
    "♐︎", // f
    "♑︎", // g
    "♒︎", // h
    "♓︎", // i
    "🙰",  // j
    "🙵",  // k
    "●︎",  // l
    "❍︎",  // m
    "■︎",  // n
    "□︎",  // o
    "◻︎",  // p
    "❑︎",  // q
    "❒︎",  // r
    "⬧︎",  // s
    "⧫︎",  // t
    "◆︎",  // u
    "❖︎",  // v
    "⬥︎",  // w
    "⌧︎",  // x
    "⍓︎",  // y
    "⌘︎",  // z

    // Symbols 4 ({, |, }, ~) (4 listed | 94 total Wingdings)
    "❀︎", // {
    "✿︎", // |
    "❝︎", // }
    "❞︎", // ~
};

static const_wd_array SORTED_WINGDINGS = {
    "@",  "ॐ︎",  "⌘︎",  "⌛︎", "⌧︎",  "⍓︎",  "■︎",  "□︎",  "◆︎",  "●︎",  "◻︎",  "☜︎",
    "☝︎",  "☞︎",  "☟︎",  "☠︎",  "☪︎",  "☯︎",  "☸︎",  "☸︎",  "☹︎",  "☺︎",  "☼︎",  "♈︎",
    "♉︎", "♋︎", "♌︎", "♍︎", "♎︎", "♏︎", "♐︎", "♑︎", "♒︎", "♓︎", "⚐︎",  "✁︎",
    "✂︎",  "✆︎",  "✇︎",  "✈︎",  "✋︎", "✌︎",  "✍︎",  "✏︎",  "✞︎",  "✠︎",  "✡︎",  "✿︎",
    "❀︎",  "❄︎",  "❍︎",  "❑︎",  "❒︎",  "❖︎",  "❝︎",  "❞︎",  "⧫︎",  "⬥︎",  "⬧︎",  "🏱︎",
    "👌︎", "👍︎", "👎︎", "👓︎", "💣︎", "💧︎", "📁︎", "📂︎", "📄︎", "📪︎", "📫︎", "📬︎",
    "📭︎", "🕆︎", "🕈︎", "🕭︎", "🕮︎", "🕯︎", "🕿︎", "🖂︎", "🖃︎", "🖫︎", "🖬︎", "🖮︎",
    "🖰︎", "🖲︎", "🖳︎", "🖴︎", "🗄︎", "🗏︎", "🗐︎", "😐︎", "🙰",  "🙵",
};

/*
 * Since `sorted_wingdings` does not have the same indexing as `wingdings`, the
 * indexing trick with `ASCII_WINGDINGS_OFFSET` will not work.
 *
 * In light of this, below is a character array where each element corresponds
 * to `sorted_wingdings`.
 *
 * (I know ']' is repeated. It's probably a mistake I made early on when
 * compiling all the Wingdings here.)
 */
static const char SORTED_WD_TO_ASCII[] = {
    '@', '\\', 'z', '6', 'x', 'y', 'n', 'o',  'u', 'l', 'p', 'E', 'G', 'F',
    'H', 'N',  'Z', '[', ']', ']', 'L', 'J',  'R', '^', '_', 'a', 'b', 'c',
    'd', 'e',  'f', 'g', 'h', 'i', 'O', '#',  '"', ')', '>', 'Q', 'I', 'A',
    '?', '!',  'V', 'X', 'Y', '|', '{', 'T',  'm', 'q', 'r', 'v', '}', '~',
    't', 'w',  's', 'P', 'B', 'C', 'D', '$',  'M', 'S', '0', '1', '2', ',',
    '-', '.',  '/', 'U', 'W', '%', '&', '\'', '(', '*', '+', '<', '=', '7',
    '8', '9',  ':', ';', '5', '3', '4', 'K',  'j', 'k'};

/* - FUNCTIONS - */

const_wd_char ascii_char_to_wd_char(char ascii);

[[nodiscard]]
string ascii_str_to_wd_str(const char *ascii);

bool is_substr_wd_candidate(const char *);

const_wd_char *search_sorted_wd(const_wd_char);

[[nodiscard]]
string wd_str_to_ascii_str(const char *wd_str);

char wd_char_to_ascii_char(const_wd_char);

#endif
