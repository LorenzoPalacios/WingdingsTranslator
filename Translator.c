#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "MyBasics.h"

#define NUM_WINGDINGS (94)
// The maximum size of one Wingdings "character" in bytes 
// (they're represented as strings, so this includes a null terminator)
#define MAX_WINGDINGS_CHAR_SIZE (sizeof(wingdings) / NUM_WINGDING_CHARS)

#define CODE_ENGLISH_TO_WINGDINGS (0)
#define CODE_WINGDINGS_TO_ENGLISH (1)

#define FILENAME_OUTPUT "out.txt"

// Preferably keep the below keywords unique enough so that they won't
// interfere with normal input when the translator picks up input.
// Regular words like "exit" could be legitimate user input for instance.

#define EXIT_KEYWORD "!exit"
#define EXIT_STATUS_CODE (0)

#define CHANGE_TRANSLATOR_KEYWORD "!chg"
#define CHANGE_TRANSLATOR_STATUS_CODE (1)

// ASCII mapped to their respective Wingding representation.
// Used to translate from ASCII to Wingdings.
static const char *wingdings[] = {
    // Symbols 1 (!, ", #, $, %, &, ', (, ), *, +, ',' , -, ., /) (15 total)
    "✏︎", "✂︎", "✁︎", "👓︎", "🕭︎", "🕮︎", "🕯︎", "🕿︎", "✆︎", "🖂︎", "🖃︎", "📪︎",
    "📫︎", "📬︎", "📭︎",

    // Numerical characters (0-9) (10 total)
    "📁︎", "📂︎", "📄︎", "🗏︎", "🗐︎", "🗄︎", "⌛︎", "🖮︎", "🖰︎", "🖲︎",

    // Symbols 2 (:, ;, <, =, >, ?, @) (7 total)
    // '@' has no Wingdings equivalent; it's just here for the sake of compatibility
    "🖳︎", "🖴︎", "🖫︎", "🖬︎", "✇︎", "✍︎", "@",

    // Uppercase alphabetical characters (A-Z) (26 total)
    "✌︎", "👌︎", "👍︎", "👎︎", "☜︎", "☞︎", "☝︎", "☟︎", "✋︎", "☺︎", "😐︎", "☹︎",
    "💣︎", "☠︎", "⚐︎", "🏱︎", "✈︎", "☼︎", "💧︎", "❄︎", "🕆︎", "✞︎", "🕈︎", "✠︎",
    "✡︎", "☪︎",

    // Symbols 3 ([, \, ], ^, _, `) (6 total)
    "☯︎", "ॐ︎", "☸︎", "☸︎", "♈︎", "♉︎",

    // Lowercase alphabetical characters (a-z) (26 total)
    "♋︎", "♌︎", "♍︎", "♎︎", "♏︎", "♐︎", "♑︎", "♒︎", "♓︎", "🙰", "🙵", "●︎",
    "❍︎", "■︎", "□︎", "◻︎", "❑︎", "❒︎", "⬧︎", "⧫︎", "◆︎", "❖︎", "⬥︎", "⌧︎",
    "⍓︎", "⌘︎",

    // Symbols 4 ({, |, }, ~) (4 total)
    "❀︎", "✿︎", "❝︎", "❞︎"};

static FILE *output_file = NULL;

/*
 * Container function for the translation loop
 * This function will prompt the user for English characters to be converted
 * into their respective Wingdings counterpart(s)
 * If no equivalent exists, the entered character will remain in the output.
 *
 * If EXIT_KEYWORD or CHANGE_TRANSLATOR_KEYWORD are entered, this function will
 * terminate its translation loop and return the respective status code.
 */
int translate_eng_to_wingdings(void)
{
    printf(
        "The selected translator is English-to-Wingdings\n"
        "Enter \"%s\" to quit, or \"%s\" to switch translators\n",
        EXIT_KEYWORD, CHANGE_TRANSLATOR_KEYWORD);
    while (1)
    {
        char *input = NULL;
        printf("Enter English here: ");

        getStrStdin(&input, UINT_MAX);

        if (input == NULL)
            continue;
        if (strcasecmp(input, EXIT_KEYWORD) == 0)
            return EXIT_STATUS_CODE;
        if (strcasecmp(input, CHANGE_TRANSLATOR_KEYWORD) == 0)
            return CHANGE_TRANSLATOR_STATUS_CODE;
    }
}

/*
 * Container function for the translation loop
 * This function will prompt the user for Wingdings characters to be converted
 * into English characters, if possible.
 * If no equivalent exists, the entered character will remain in the output.
 *
 * If EXIT_KEYWORD or CHANGE_TRANSLATOR_KEYWORD are entered, this function will
 * terminate the translation loop and return the respective status code.
 */
int translate_wingdings_to_eng(void)
{
    printf(
        "The selected translator is Wingdings-to-English\n"
        "Enter \"%s\" to quit, or \"%s\" to switch translators\n",
        EXIT_KEYWORD, CHANGE_TRANSLATOR_KEYWORD);
    while (1)
    {
        char *input = NULL;
        printf("Enter Wingdings here: ");
        getStrStdin(&input, 1000);

        if (input == NULL)
            continue;
        if (strcasecmp(input, EXIT_KEYWORD) == 0)
            return EXIT_STATUS_CODE;
        if (strcasecmp(input, CHANGE_TRANSLATOR_KEYWORD) == 0)
            return CHANGE_TRANSLATOR_STATUS_CODE;
    }
}
/*
 * Prompts the user for whether they want to translate from English to Wingdings, or from
 * Wingdings to English.
 * In the case of the former, this function returns CODE_ENGLISH_TO_WINGDINGSS.
 * In the case of the latter, this function returns CODE_WINGDINGS_TO_ENGLISH.
 *
 * If the user inputs something invalid, the function will prompt the user again until they input
 * something valid.
 */
int prompt_user_for_use_case(void)
{
    puts("What would you like to translate?");
    puts("0. Translate English-to-Wingdings");
    puts("1. Translate Wingdings-to-English");

    int user_choice = charToInt(getchar());

    while (user_choice != CODE_ENGLISH_TO_WINGDINGS && user_choice != CODE_WINGDINGS_TO_ENGLISH)
    {
        // fseeking to the end to discard any other input since we're only looking for a single
        // digit
        fseek(stdin, 0, SEEK_END);
        puts("Enter a valid option (0 or 1)");
        user_choice = charToInt(getchar());
    }
    return user_choice;
}

int main(void)
{
    puts(wingdings[9]);
    fopen_s(&output_file, FILENAME_OUTPUT, "rw");
    puts("Welcome to the Wingdings \"translator\"!\n");
    int user_choice = prompt_user_for_use_case();

    while (user_choice)
    {
        const int return_status = user_choice ? translate_eng_to_wingdings() : translate_wingdings_to_eng();
        if (return_status == EXIT_STATUS_CODE)
            return 0;
        else
            user_choice = prompt_user_for_use_case();
    }

    return 0;
}
