#include <stdio.h>
#include <string.h>

void freqAnalysis(char *cipherText); // Returns frequency of each letter in cipherText in alphabetical order

int main(void) {

  char cipherText[100] = {"ABCDEFGAABCCDDDZHJKAHSDC"}; // Cipher text message to be analysed

  freqAnalysis(cipherText);

  printf("\n");
  return 0;

}


void freqAnalysis(char *cipherText) { // Returns frequency of each letter in cipherText in alphabetical order

  int maxFreq = 0;
  char maxLetter;
  int frequency[26] = {}; // Frequency array of letters in string
  int len = strlen(cipherText); // Gets length of string

  for(int index = 0; index < len; index++) { // Loops through each letter in the string
    for(char letter = 65; letter <= 90; letter++) { // Loops through each letter of the alphabet
      int element = (int)cipherText[index]; // Sets element to letter at index
      if((int)letter == element) { // If the letters match, correct letter identified and
        frequency[element - 65]++; //  frequency of said letter +1
        break;
      }
    }
  }

  // finds letter of string with greatest frequency
  for(int i = 0; i <= 25; i++){
    if(frequency[i] > maxFreq){
      maxFreq = frequency[i];
      maxLetter = i + 65;
    }
  }

  printf("%d %c\n", maxFreq, maxLetter);

  for(int n = 0; n <= 25; n++) { // Prints frequency array to console
    printf("%d ", frequency[n]);
  }
}
