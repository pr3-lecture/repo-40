#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int checkInputText(const char* input, const char* checkSet) {
    int found;
    
    for (int i = 0;i < strlen(input); i++){
        found = 0;
        for (int k = 0;k < strlen(checkSet); k++) {
            if(input[i] == checkSet[k]){
                found = 1;
            }
        }
        if(found == 0) {
            return 1;
        }
    }
    return 0;
}

int checkKey(KEY key){
    char* legalCharacters = KEY_CHARACTERS;
    int found;
    
    for (int i = 0;i < strlen(key.chars); i++){
        found = 0;
        for (int k = 0;k < strlen(legalCharacters); k++) {
            if(key.chars[i] == legalCharacters[k]){
                found = 1;
            }
        }
        if(found == 0) {
            return 1;
        }
    }
    return 0;
}

int xor (KEY key, const char* input, char* output) {
    if (key.type == 1) {
        int keyLength = strlen(key.chars);
        for (int i = 0; i < strlen(input); i++) {
            char charAtInput = input[i] - 'A' +1;
            char charAtKey = key.chars[i % keyLength] - 'A' +1;
            char outputChar = charAtInput ^ charAtKey;
            output[i] = outputChar + 'A' -1;
        }
        return 0;
    } else {
        *output = *input;
        return 0;
    }
}


int encrypt(KEY key, const char* input, char* output){
    if(strlen(key.chars) == 0){
        return E_KEY_TOO_SHORT;
    }
    
    if(checkKey(key)) {
        return E_KEY_ILLEGAL_CHAR;
    }
    
    if (checkInputText(input, MESSAGE_CHARACTERS)) {
        return E_MESSAGE_ILLEGAL_CHAR;
    }
    
    xor(key, input, output);
    
    return 0;
}

int decrypt(KEY key, const char* cypherText, char* output){
    if(strlen(key.chars) == 0){
        return E_KEY_TOO_SHORT;
    }
    
    if(checkKey(key)) {
        return E_KEY_ILLEGAL_CHAR;
    }
    
    if (checkInputText(cypherText, CYPHER_CHARACTERS)) {
        return E_CYPHER_ILLEGAL_CHAR;
    }
    
    xor(key, cypherText, output);
    
    return 0;
}

