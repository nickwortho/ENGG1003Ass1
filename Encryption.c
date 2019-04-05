#include <stdio.h>
#include <string.h>

char msgEncrypt(char message[], int key);

int main() {

  char x;
  //int key = 1; // Single integer encryption key in the range [0,25]
  //int index;
  //char message[] = {"ATTACK AT SUNRISE"}; // Plain text message to be manipulated

  x = msgEncrypt("the number eight", 1);


// Prints cipher text version of message
  printf("%c\n", x);
  return 0;
}


// CAESAR ENCRYPTION
//
char msgEncrypt(char message[], int key) {

    for (int index = 0; index < 17; index++) {

  // Converts any lower case letters to upper case
      if (message[index] <= 122 && message[index] >= 97) {
        message[index] -= 32;
      }

  // Converts each plain text char into a cipher text char in message
      if (message[index] >= 65 && message[index] <= 90) {
        message[index] = ((message[index] + key - 65) % 26 + 65);
      }
    }
  return *message;
}
