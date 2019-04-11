#include <stdio.h>

int main() {

  // 26 character substitution key, offset of 2 (begins at C)
  char key[26] = {67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,65,66};
  char plainText[100] = {"ATTACK AT SUNSET"};
  char cipherText;

  for(int i = 0; plainText[i] != '\0'; i++){

    if ((int)plainText[i] <= 122 && (int)plainText[i] >= 97) {
      plainText[i] -= 32;
    }

    if ((int)plainText[i] >= 65 && (int)plainText[i] <= 90) {
      cipherText = key[plainText[i] - 65];
    } else {
      cipherText = plainText[i];
    }

    printf("%c", cipherText);
  }
  return 0;
}
