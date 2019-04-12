#include <stdio.h>

void cEncrypt(char *plainText, int key);

int main(void) {

  int key = 1; // Single integer encryption key in the range [0,25]
  char plainText[100] = {"the number eight"}; // Plain text message to be manipulated


// Prints cipher text version of message
  cEncrypt(plainText, key);
  return 0;
}


// CAESAR ENCRYPTION
//
void cEncrypt(char *plainText, int key) {
  char cipherText;

  for (int index = 0; plainText[index] != '\0'; index++) {
    // Converts any lower case letters to upper case
    if ((int)plainText[index] <= 122 && (int)plainText[index] >= 97) {
      plainText[index] -= 32;
    }

  // Converts each plain text char into a cipher text char in message
    if ((int)plainText[index] >= 65 && (int)plainText[index] <= 90) {
      cipherText = ((int)plainText[index] - 65 + key) % 26 + 65;
    } else {
      cipherText = plainText[index];
    }

  printf("%c", cipherText);
  }
  printf("\n");
}
