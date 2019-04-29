/*
The following program implements various cryptographical functions.

The program will take an input message to be operated on  inputMessage  and output
the modified message  outputMessage  dependent on the function chosen.

All input is taken through the file  input.txt and all output is sent to the file  output.txt

The program has 5 different modes:
  1: Encryption using a Caesar (rotation) cipher
  2: Decryption using a Caesar (rotation) cipher with key known
  3: Encryption using a substitution cipher
  4: Decryption using a substitution cipher with key known
  5: Decryption using a substitution cipher with key NOT known

  NOTE: Mode 5 can be used for decryption using a Caesar cipher with key not known.

The user will select functionality by entering a mode, message, and key
(except for mode 5, in which case key should be left blank) into the input.txt file.
Mode should be either a single integer 1-5 when using a Caesar cipher, or a string of 26 unique letters
when using a substitution cipher. A single space should be left before entering mode and message, and key
should be input directly after the # character. The encrypted or decrypted message will be output to the
output.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KEYMAX 27
#define INPUTMAX 1001

char *caesarEncrypt(char inputMessage[], int key);
char *caesarDecrypt(char inputMessage[], int key);
char *substitutionEncrypt(char inputMessage[], char key[]);
char *substitutionDecrypt(char inputMessage[], char key[]);
char *frequencyAnalysisDecryption(char inputMessage[]);

int main() {

  int mode;
  char inputMessage[INPUTMAX]; // message length cannot exceed 500 characters
  int caesarKey; // value between 0-26 to rotate alphabet by
  char substitutionKey[KEYMAX]; // key cannot exceed 26 characters

// FILE INPUT
//
  FILE *fp;

  fp = fopen("input.txt", "r"); //opens input file for reading
  if(fp != NULL) { // error check for missing file, locked file, etc.

// mode input from file
    fseek(fp, 12, SEEK_SET); // moves file pointer position to after mode input instruction
    fscanf(fp, "%d", &mode); // gets mode character from input file and stores in mode
    printf("%d\n", mode);

    if (mode < 0 || mode > 5) { // error check for mode input

      return -1;

    }

// message input from file
    fseek(fp, 23, SEEK_CUR); // moves file pointer position to after message input instruction
    fgets(inputMessage, INPUTMAX-1, fp); // gets message from input file and stores in inputMessage
    printf("%s", inputMessage);

    fseek(fp, 13, SEEK_CUR); // moves file pointer position to after key input instruction

// key input from file
    if (mode == 1 || mode == 2) { // if using Caesar cipher

      fscanf(fp, "%d", &caesarKey); // gets key from input file and stores in caesarKey
      printf("%d\n", caesarKey);

      if (caesarKey < 0 || caesarKey > 26) { // error check for caesarKey input

        return -1;

      }

    } else if (mode == 3 || mode == 4) { // if using substitution cipher

      fgets(substitutionKey, KEYMAX, fp); // gets key from input file and stores in substitutionKey
      printf("%s\n", substitutionKey);

    } else {

      for(int i = 0; i < 26; i++) {

         substitutionKey[i] = frequencyAnalysisDecryption(inputMessage)[i];

      }

      printf("%s\n", substitutionKey);

    }

  } else {

      return 0; // if file error triggered, exit program

  }

  fclose(fp);

/*
!! Program function selection !!
1 = Encryption with Caesar cipher
2 = Decryption with Caesar cipher
3 = Encryption with Substitution cipher
4 = Decryption with Substitution cipher
5 = Decryption with either cipher and NO key given
*/

  switch(mode) {

    case 1: { // Encryption with Caesar cipher

      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(caesarEncrypt(inputMessage, caesarKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;

    }

    case 2: { // Decryption with Caesar cipher

      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(caesarDecrypt(inputMessage, caesarKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;

    }

    case 3: { // Encryption with Substitution cipher

      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(substitutionEncrypt(inputMessage, substitutionKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;

    }

    case 4: { // Decryption with Substitution cipher

      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(substitutionDecrypt(inputMessage, substitutionKey), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;

    }

    case 5: { // Decryption with Caesar cipher without key given



    }

    case 6: { // Decryption with Substitution cipher without key given

      fp = fopen("output.txt", "w"); //opens output.txt file for writing
      fprintf(fp, "Output message:\n");
      fputs(substitutionDecrypt(inputMessage, frequencyAnalysisDecryption(inputMessage)), fp); // writes outputMessage into output.txt file
      fclose(fp); // closes output.txt file for writing
      break;

    }

    default: {

      return -1;

    }
  }

  return 0;

}

// FUNCTIONS
//

/*
Caesar Cipher Encryption
Function:     Encrypts a block of plain text using a Caesar (rotation) cipher.
              Each letter in the plain text is shifted by a certain amount of letters defined
              by the key value.
IO:           Takes plain text message to be encrypted  inputMessage  and encryption key  caesarKey
              and outputs encrypted message  outputMessage
Restrictions: inputMessage must be a string of characters with a maximum length of 500.
              caesarKey must be a single integer such that 1 <= caesarKey <= 26.
*/

char *caesarEncrypt(char inputMessage[], int key) {

  char *outputMessage = malloc(strlen(inputMessage) * sizeof(char));

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

/*
Caesar Cipher Decryption
Function:     Decrypts a block of cipher text using a Caesar (rotation) cipher.
              Each letter in the cipher text is shifted by a certain amount of letters defined
              by the key value.
IO:           Takes cipher text message to be decrypted  inputMessage  and decryption key  caesarKey
              and outputs decrypted message  outputMessage
Restrictions: inputMessage must be a string of characters with a maximum length of 500.
              caesarKey must be a single integer such that 1 <= caesarKey <= 26.
*/

char *caesarDecrypt(char inputMessage[], int key) {

  char *outputMessage = malloc(strlen(inputMessage) * sizeof(char));

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

/*
Substitution Cipher Encryption
Function:     Encrypts a block of plain text using a substitution cipher.
              Each letter in the plain text is replaced by a specific unique letter defined by
              the same index in the key.
IO:           Takes plain text message to be encrypted  inputMessage  and encryption key  substitutionKey
              and outputs encrypted message  outputMessage
Restrictions: inputMessage must be a string of characters with a maximum length of 500.
              substitutionKey must be a string of exactly 26 unique letters.
*/

char *substitutionEncrypt(char inputMessage[], char key[]){

  char *outputMessage = malloc(strlen(inputMessage) * sizeof(char));

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

/*
Substitution Cipher Decryption
Function:     Decrypts a block of cipher text using a substitution cipher.
              Each letter in the cipher text is replaced by a specific unique letter defined by
              the same index in the key.
IO:           Takes cipher text message to be decrypted  inputMessage  and decryption key  substitutionKey
              and outputs decrypted message  outputMessage
Restrictions: inputMessage must be a string of characters with a maximum length of 500.
              substitutionKey must be a string of exactly 26 unique letters.
*/

char *substitutionDecrypt(char inputMessage[], char key[]){

  char *outputMessage = malloc(strlen(inputMessage) * sizeof(char));

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

/*
Frequency Analysis Decryption
Function:     Attempts to decrypt a block of cipher text using frequency analysis to generate a substitution key.
              Each letter in the cipher text is replaced by a specific unique letter defined by
              the same index in the key.
IO:           Takes cipher text message to be decrypted  inputMessage and outputs decrypted message  outputMessage
Restrictions: inputMessage must be a string of characters with a maximum length of 500.
*/

char *frequencyAnalysisDecryption(char *inputMessage) { // Returns frequency of each letter in inputMessage in alphabetical order

  int maxFreq;
  char maxLetter;
  char alphabet[KEYMAX] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  char stdFreqDistrib[KEYMAX] = {"ETAOINSHRDLCUMWFGYPBVKJXQZ"};
  int frequency[KEYMAX] = {}; // Frequency array of letters in string
  char *testKey = malloc(strlen(inputMessage) * sizeof(char)); // possible key to be altered from frequency analysis
  int len = strlen(inputMessage); // Gets length of string

// counts frequency of each letter in inputMessage
  for(int index = 0; index < len; index++) { // Loops through each letter in the string

    for(int letter = 65; letter <= 90; letter++) { // Loops through each letter of the alphabet

      int inputChar = (int)inputMessage[index]; // Sets inputChar to inputMessage letter at index

      if(letter == inputChar) { // If the letters match, correct letter identified

        frequency[inputChar - 65]++; //  frequency of said letter +1
        break;

      }
    }
  }

/*
  for(int n = 0; n <= 25; n++) { // Prints frequency array to console

    printf("%d ", frequency[n]);

  }
*/
// SORTING
  for(int n = 0; n <= 25; n++) { //n=0 is most freq, n=1 second most freq, etc...

    maxFreq = 0;

    for(int i = 0; i <= 25; i++) { // finds letter of string with greatest frequency

      if(frequency[i] > maxFreq) { // if current letter has greater frequency than prev, replace

        maxFreq = frequency[i];
        maxLetter = i + 65; // converts into ASCII value for upper case letters

      }
    }


    for(int x = 0; x <= 25; x++) { // (loops alphabet) finds position of maxLetter in alphabet and sets maxLetter to same position in testKey

      if(alphabet[x] == stdFreqDistrib[n]) { // if true then nth most frequent letter correctly identified

        testKey[x] = maxLetter; // current most frequent letter placed in testKey at correct position
        break;

      }
    }

    frequency[maxLetter - 65] = 0; //sets the most frequent letter's frequency to 0 to find 2nd most frequent
  }


  return testKey;

}
