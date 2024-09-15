#define _CRT_SECURE_NO_WARNINGS
#include "stringhelp.h"
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

// Updated nextWhite function with assertions
int nextWhite(const char* str) {
    assert(str != NULL && "String pointer should not be NULL");
    int i, result = -1;
    for (i = 0; result < 0 && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\t') {
            result = i;
        }
    }
    return result < 0 ? i : result; // Line 18: Updated logic for determining the next whitespace index
}

// Updated isNumber function with assertions
int isNumber(const char* str, const int len) {
    assert(str != NULL && "String pointer should not be NULL");
    assert(len >= 0 && "Length should be non-negative");
    int result = 1;
    for (int i = 0; i < len && result; i++) { // Line 30: Updated loop condition to check length correctly
        if (!isdigit(str[i])) {
            result = 0;
        }
    }
    return result;
}

// Updated indexString function with assertions
struct StringIndex indexString(const char* str) {
    assert(str != NULL && "String pointer should not be NULL");
    struct StringIndex result = { {0}, {0}, {0}, 0, 0, 0 };
    char buf[MAX_WORD_SIZE + 1] = { 0 };
    int i, sp;
    strcpy(result.str, str);
    if (str[0] != '\0') {
        result.lineStarts[0] = 0;
        result.numLines = 1;
    }
    for (i = 0; str[i] != '\0'; i++) {
        while (str[i] != '\0' && isspace(str[i])) {
            if (str[i] == '\n') { // Line 47: Increment line starts only on newline characters
                result.lineStarts[result.numLines++] = i + 1;
            }
            i++;
        }
        for (sp = 0; str[sp + i] != '\0' && !isspace(str[sp + i]); sp++);
        if (isNumber(str + i, sp)) {
            result.numberStarts[result.numNumbers++] = i;
        } else {
            result.wordStarts[result.numWords++] = i;
        }
        i += sp - 1;
    }
    return result;
}

// Updated getWord function with assertions
void getWord(char word[], const struct StringIndex* idx, int wordNum) {
    assert(word != NULL && "Word pointer should not be NULL");
    assert(idx != NULL && "Index pointer should not be NULL");
    assert(wordNum >= 0 && wordNum < idx->numWords && "Word number out of bounds");
    int i, sp, start;
    word[0] = '\0';
    if (wordNum < idx->numWords && wordNum >= 0) {
        start = idx->wordStarts[wordNum];
        sp = nextWhite(idx->str + start);
        for (i = 0; i < sp; i++) { // Line 78: Ensure only word characters are copied
            word[i] = idx->str[start + i];
        }
        word[sp] = '\0';
    }
}

// Updated getNumber function with assertions
void getNumber(char word[], const struct StringIndex* idx, int numberNum) {
    assert(word != NULL && "Word pointer should not be NULL");
    assert(idx != NULL && "Index pointer should not be NULL");
    assert(numberNum >= 0 && numberNum < idx->numNumbers && "Number number out of bounds");
    int i, sp, start;
    word[0] = '\0';
    if (numberNum < idx->numNumbers && numberNum >= 0) {
        start = idx->numberStarts[numberNum];
        sp = nextWhite(idx->str + start);
        for (i = 0; i < sp; i++) { // Line 95: Ensure number characters are copied correctly
            word[i] = idx->str[start + i];
        }
        word[sp] = '\0';
    }
}
