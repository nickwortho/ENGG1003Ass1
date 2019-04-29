#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *caesarEncrypt(char inputMessage[], int key);
char *caesarDecrypt(char inputMessage[], int key);
char *substitutionEncrypt(char inputMessage[], char key[]);
char *substitutionDecrypt(char inputMessage[], char key[]);
void frequencyAnalysis(char inputMessage[]);

int main() {

  int mode;
  char inputMessage[501]; // message length cannot exceed 500 characters
  int caesarKey;
  char substitutionKey[27]; // rotated by 2

// FILE INPUT
  FILE *fp;

  fp = fopen("input.txt", "r"); //opens input file for reading
  if(fp != NULL) { // error check for missing file, locked file, etc.

    fseek(fp, 12, SEEK_SET); // moves file pointer position to after mode input instruction
    fscanf(fp, "%d", &mode); // gets mode character from input file and stores in mode
    printf("%d\n", mode);

    fseek(fp, 23, SEEK_CUR); // moves file pointer position to after message input instruction
    fgets(inputMessage, 500, fp); // gets message from input file and stores in inputMessage
    printf("%s", inputMessage);

    fseek(fp, 13, SEEK_CUR); // moves file pointer position to after key input instruction

    if (mode == 1 || mode == 2) { // if using Caesar cipher

      fscanf(fp, "%d", &caesarKey); // gets key from input file and stores in caesarKey
      printf("%d\n", caesarKey);

    } else if (mode == 3 || mode == 4) { // if using substitution cipher

      fgets(substitutionKey, 27, fp); // gets key from input file and stores in substitutionKey
      printf("%s\n", substitutionKey);

    }

  } else {
      return 0; // if file error triggered, exit program
  }

  fclose(fp);

// END FILE INPUT

/*
  printf("%s", inputMessage);

  fp = fopen("output.txt", "a");

  fputs(inputMessage, fp);

  fclose(fp);

  return 0;
*/

/*
!! Program function selection !!
1 = Encryption with Caesar cipher
2 = Decryption with Caesar cipher
3 = Encryption with Substitution cipher
4 = Decryption with Substitution cipher
*/

  switch(mode) {

    case 1: {
      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(caesarEncrypt(inputMessage, caesarKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;
    }

    case 2: {
      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(caesarDecrypt(inputMessage, caesarKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;
    }

    case 3: {
      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(substitutionEncrypt(inputMessage, substitutionKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;
    }

    case 4: {
      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(substitutionDecrypt(inputMessage, substitutionKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;
    }

    default: {
      return -1;
    }
  }

  return 0;

}

char *caesarEncrypt(char inputMessage[], int key) {

  char *outputMessage = malloc(501 * sizeof(char));

  for (int index = 0; inputMessage[index] != '\0'; index++) {
    // Converts any lower case letters to upper case
    if ((int)inputMessage[index] <= 122 && (int)inputMessage[index] >= 97) {
      inputMessage[index] -= 32;
    }

  // Converts each plain text char into a cipher text char in message
    if ((int)inputMessage[index] >= 65 && (int)inputMessage[index] <= 90) {
      outputMessage[index] = ((int)inputMessage[index] - 65 + key) % 26 + 65;
    } else {
      outputMessage[index] = inputMessage[index];
    }

  }
  return outputMessage;
}


char *caesarDecrypt(char inputMessage[], int key) {

  char *outputMessage = malloc(501 * sizeof(char));

  for (int index = 0; inputMessage[index] != '\0'; index++) {
    // Converts any lower case letters to upper case
    if ((int)inputMessage[index] <= 122 && (int)inputMessage[index] >= 97) {
      inputMessage[index] -= 32;
    }

  // Converts each cipher text char in cipherText into a plain text char
    if ((int)inputMessage[index] >= 65 && (int)inputMessage[index] <= 90) {
      outputMessage[index] = ((int)inputMessage[index] - 65 - key) % 26 + 65;
    } else {
      outputMessage[index] = inputMessage[index]; // If char not an upper case letter, ignore and print
    }
  }
  return outputMessage;
}

char *substitutionEncrypt(char inputMessage[], char key[]){

  char *outputMessage = malloc(501 * sizeof(char));

  for(int i = 0; inputMessage[i] != '\0'; i++){

    if ((int)inputMessage[i] <= 122 && (int)inputMessage[i] >= 97) {
      inputMessage[i] -= 32;
    }

    if ((int)inputMessage[i] >= 65 && (int)inputMessage[i] <= 90) {
      outputMessage[i] = key[inputMessage[i] - 65];
    } else {
      outputMessage[i] = inputMessage[i];
    }
  }
  return outputMessage;
}

char *substitutionDecrypt(char inputMessage[], char key[]){

  char *outputMessage = malloc(501 * sizeof(char));

  // Loops over each character in the encrypted message
  for(int i = 0; inputMessage[i] != '\0'; i++){

    // If letter is lowercase -> convert to upper case (not necessary when decrypting)
    if ((int)inputMessage[i] <= 122 && (int)inputMessage[i] >= 97) {
      inputMessage[i] -= 32;
    }

    // Matches
    if ((int)inputMessage[i] >= 65 && (int)inputMessage[i] <= 90) {
      for(int n = 0; n < 26; n++) {
        if(inputMessage[i] == key[n]){
          outputMessage[i] = n + 65;
        }
      }
    } else {
      outputMessage[i] = inputMessage[i];
    }
  }
  return outputMessage;
}

void frequencyAnalysis(char *inputMessage) { // Returns frequency of each letter in cipherText in alphabetical order

  int maxFreq;
  char maxLetter;
  char mostFreq[26] = {"ETAOINSHRDLCUMWFGYPBVKJXQZ"};
  char alphabet[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  char testKey[26] = {}; // possible key to be altered from frequency analysis
  int frequency[26] = {}; // Frequency array of letters in string
  int len = strlen(inputMessage); // Gets length of string


  for(int index = 0; index < len; index++) { // Loops through each letter in the string
    for(int letter = 65; letter <= 90; letter++) { // Loops through each letter of the alphabet
      int cipherChar = (int)inputMessage[index]; // Sets cipherChar to cipherText letter at index
      if(letter == cipherChar) { // If the letters match, correct letter identified and
        frequency[cipherChar - 65]++; //  frequency of said letter +1
        break;
      }
    }
  }

  for(int n = 0; n <= 25; n++) { // Prints frequency array to console
    printf("%d ", frequency[n]);
  }

  for(int n = 0; n <= 25; n++) { //n=0 is most freq, n=1 second most freq, etc...

    maxFreq = 0;

    for(int i = 0; i <= 25; i++) { // finds letter of string with greatest frequency
      if(frequency[i] >= maxFreq) { // if new letter has greater frequency than prev, replace
        maxFreq = frequency[i];
        maxLetter = i + 65; // converts into ASCII value for upper case letters
      }
    }

    for(int x = 0; x <= 25; x++) { //finds position of maxLetter in alphabet and sets maxLetter to same position in testKey
      if(alphabet[x] == mostFreq[n]) {
        testKey[x] = maxLetter;
        break;
      }
    }

    frequency[maxLetter - 65] = 0; //sets the most frequent letter's frequency to 0 to find 2nd most frequent
  }



  printf("\n");

  for(int n = 0; n <= 25; n++) { // Prints testKey array to console
    printf("%c ", testKey[n]);
  }
}
