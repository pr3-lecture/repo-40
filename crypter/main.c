#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int main(int argc, char* argv[]) {
    if(argc == 1) {
        printf("Keine Parameter \n");
    }
    
    KEY key = {1, argv[1]};
    char input[255];
    int returnValue;
    
    if (argc == 2) {
        printf("Bitte Nachricht eingeben: \n");
        fgets(input, 255, stdin);
        input[strlen(input) - 1] = '\0';
    }
    
    if(argc == 3) {
        FILE* inputFile = fopen(argv[2], "r");
        
        if(input == NULL) {
            fprintf(stderr, "Fehler: Datei %s nicht gefunden", argv[2]);
            exit(1);
        }
        
        fgets(input, 254, inputFile);
        input[strlen(input) - 1] = '\0';
        
    }
    
    char output[BUFSIZ];
    if(strcmp(argv[0], "encrypt") == 0) {
        returnValue = encrypt(key, input, output);
    } else if (strstr(argv[0], "decrypt")) {
        returnValue = decrypt(key, input, output);
    }
    printf("%s \n", output);
    
    switch(returnValue) {
        case E_KEY_TOO_SHORT:
            fprintf(stderr, "Key zu kurz"); break;
        case E_KEY_ILLEGAL_CHAR:
            fprintf(stderr, "Ungültige Zeichen in Key");break;
        case E_MESSAGE_ILLEGAL_CHAR:
            fprintf(stderr, "Ungültige Zeichen in Nachricht"); break;
        case E_CYPHER_ILLEGAL_CHAR:
            fprintf(stderr, "Ungültige Zeichen in verschlüsseltem Text"); break;
        default: return returnValue;
    }
    
}

