#include <stdio.h>

// Substitution cipher which takes encrypted text and a 26 letter key as input and returns the decrypted message
void sDecrypt(char *cipherText, char *key);\

int main() {

  // 26 character substitution key, A = C, B = D, C = E, D = ...
  char key[26] = {67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,65,66};
  // Encrypted message to be decrypted
  char cipherText[100] = {"VJKU OGUUCIG YKNN DG GPETARVGF"};

  sDecrypt(cipherText, key);
  return 0;
}

// Substitution cipher which takes encrypted text and a 26 letter key as input and returns the decrypted message
void sDecrypt(char *cipherText, char *key){

  char plainText;

  // Loops over each character in the encrypted message
  for(int i = 0; cipherText[i] != '\0'; i++){

    // If letter is lowercase -> convert to upper case (not necessary when decrypting)
    if ((int)cipherText[i] <= 122 && (int)cipherText[i] >= 97) {
      cipherText[i] -= 32;
    }

    // Matches
    if ((int)cipherText[i] >= 65 && (int)cipherText[i] <= 90) {
      for(int n = 0; n < 26; n++) {
        if(cipherText[i] == key[n]){
          plainText = n + 65;
        }
      }
    } else {
      plainText = cipherText[i];
    }

  printf("%c", plainText);
  }
  printf("\n");
}
