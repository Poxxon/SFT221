#include "mathfuncs.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void getString(const char *prompt, char *input, int maxLen){
    printf("%s", prompt);
    fgets(input, maxLen, stdin);
    if(input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0'; //to remove any newline if there is at the end of a string
    }
    while(strlen(input) == 0) {
        printf("Invalid Entry: %s", prompt);
        fgets(input, maxLen, stdin);
        if(input[strlen(input) - 1] == '\n'){
            input[strlen(input) - 1] = '\0';
        }
    }
}


int isValidPostalCode(const char *postalCode){
    int length = strlen(postalCode);

    if (length != 7) {
        return 0;
    }

    if (!isalpha(postalCode[0]) || !isdigit(postalCode[1]) || !isalpha(postalCode[2]) || 
        postalCode[3] != ' ' || !isdigit(postalCode[4]) || !isalpha(postalCode[5]) || !isdigit(postalCode[6])) {
        return 0;
    }

    return 1;
}


void formatPostalCode(char *postalCode) {
    for (int i = 0; i < strlen(postalCode); i++) {
        postalCode[i] = toupper(postalCode[i]);
    }
}


void getPostalCode(const char *prompt, char *postalCode, int maxLen){
    printf("%s", prompt);
    fgets(postalCode, maxLen, stdin);
    if (postalCode[strlen(postalCode) - 1] == '\n') {
        postalCode[strlen(postalCode) - 1] = '\0';
    }

    while (!isValidPostalCode(postalCode)) {
        printf("Invalid Entry: %s", prompt);
        fgets(postalCode, maxLen, stdin);
        if (postalCode[strlen(postalCode) - 1] == '\n') {
            postalCode[strlen(postalCode) - 1] = '\0';
        }
    }
    formatPostalCode(postalCode);
}


void getInfo(struct Customer *customer){
    getString("Enter your first name: ", customer->first, MAX_LEN);
    getString("Enter your last name: ", customer->last, MAX_LEN);
    getString("Enter your street address: ", customer->streetAdd, MAX_LEN);
    getString("Enter your city: ", customer->city, MAX_LEN);
    getString("Enter your province: ", customer->province,MAX_LEN);
    getPostalCode("Enter your postal code: ", customer->postal, MAX_LEN);
}


