#include <stdio.h>

void cDecrypt(char *cipherText, int key);

int main(void) {

  int key = 1; // Single integer decryption key in the range [0,25]
  char cipherText[100] = {"UIF OVNCFS FJHIU"}; // Cipher text message to be decrypted


// Prints decrypted version of cipherText
  cDecrypt(cipherText, key);
  return 0;
}


// CAESAR DECRYPTION
//
void cDecrypt(char *cipherText, int key) {
  char plainText;

  for (int index = 0; cipherText[index] != '\0'; index++) {
    // Converts any lower case letters to upper case
    if ((int)cipherText[index] <= 122 && (int)cipherText[index] >= 97) {
      cipherText[index] -= 32;
    }

  // Converts each cipher text char in cipherText into a plain text char
    if ((int)cipherText[index] >= 65 && (int)cipherText[index] <= 90) {
      plainText = ((int)cipherText[index] - 65 - key) % 26 + 65;
    } else {
      plainText = cipherText[index]; // If char not an upper case letter, ignore and print
    }

  printf("%c", plainText);
  }
  printf("\n");
}
