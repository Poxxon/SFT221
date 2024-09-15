#pragma once
#ifndef MATHFUNCS_H
#define MATHFUNCS_H
#define MAX_LEN 100


struct Customer{
    char first[MAX_LEN];
    char last[MAX_LEN];
    char streetAdd[MAX_LEN];
    char city[MAX_LEN];
    char province[MAX_LEN];
    char postal[MAX_LEN];
};

void getString(const char *prompt, char *input, int maxLen);
int isValidPostalCode(const char *postalCode);
void formatPostalCode(char *postalCode);
void getPostalCode(const char *prompt, char *postalCode, int maxLen);
void getInfo(struct Customer *customer);

#endif