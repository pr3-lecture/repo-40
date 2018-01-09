#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int tests_run = 0;
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)




static char* keyTooShort() {
  KEY key = {1, ""};
  const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char output[BUFSIZ];
  int result = encrypt(key, input, output);
  mu_assert("Key zu kurz", result == E_KEY_TOO_SHORT);

  return 0;
}

static char* illegalKeyChars() {
  KEY key = {1, "-.,/&"};
  const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char output[BUFSIZ];
  int result = encrypt(key, input, output);
  mu_assert("Ungültige Zeichen in Key", result == E_KEY_ILLEGAL_CHAR);

  return 0;
}

static char* illegalInputChars() {
  KEY key = {1, "TPERULES"};
  const char* input = "asd328347&&$$";
  char output[BUFSIZ];
  int result = encrypt(key, input, output);
  mu_assert("Ungültige Zeichen in Nachricht", result == E_MESSAGE_ILLEGAL_CHAR);

  return 0;
}

static char* illegalCypherChars() {
  KEY key = {1, "TPERULES"};
  const char* input = "asd1234";
  char output[BUFSIZ];
  int result = decrypt(key, input, output);
  mu_assert("Ungültige Zeichen in verschlüsseltem Text", result == E_CYPHER_ILLEGAL_CHAR);

  return 0;
}

static char* testEncrypt() {
  KEY key = {1, "TPERULES"};
  const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char output[BUFSIZ];
  encrypt(key, input, output);
  mu_assert("encrypt output error ", strcmp(output, "URFVPJB[]ZN^XBJCEBVF@ZRKMJ")==0);

  return 0;
}

static char* testDecrypt() {
  KEY key = {1, "TPERULES"};
  const char* input = "URFVPJB[]ZN^XBJCEBVF@ZRKMJ";
  char output[BUFSIZ];
  encrypt(key, input, output);
  mu_assert("decrypt output error ", strcmp(output, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")==0);

  return 0;

}

static char* allTests() {
  mu_run_test(keyTooShort);
  mu_run_test(illegalKeyChars);
  mu_run_test(illegalInputChars);
  mu_run_test(illegalCypherChars);
  mu_run_test(testEncrypt);
  mu_run_test(testDecrypt);

  /* weitere Tests */
  return 0;
}

int main() {
  char *result = allTests();

  if (result != 0) printf("%s\n", result);
  else             printf("ALL TESTS PASSED\n");

  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
