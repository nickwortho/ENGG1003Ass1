#include <stdio.h>
#include <string.h>

void freqAnalysis(char *cipherText); // Returns frequency of each letter in cipherText in alphabetical order

int main(void) {

  char cipherText[] = {"RCR VYE BGBX HBNX FHB FXNQBRV YM RNXFH IZNQEBCJ FHB PCJB? C FHYEQHF KYF. CF'J KYF N JFYXV FHB DBRC PYEZR FBZZ VYE. CF'J N JCFH ZBQBKR. RNXFH IZNQEBCJ PNJ N RNXA ZYXR YM FHB JCFH, JY IYPBXMEZ NKR JY PCJB HB LYEZR EJB FHB MYXLB FY CKMZEBKLB FHB OCRCLHZYXCNKJ FY LXBNFB ZCMB… HB HNR JELH N AKYPZBRQB YM FHB RNXA JCRB FHNF HB LYEZR BGBK ABBI FHB YKBJ HB LNXBR NWYEF MXYO RVCKQ. FHB RNXA JCRB YM FHB MYXLB CJ N INFHPNV FY ONKV NWCZCFCBJ JYOB LYKJCRBX FY WB EKKNFEXNZ. HB WBLNOB JY IYPBXMEZ… FHB YKZV FHCKQ HB PNJ NMXNCR YM PNJ ZYJCKQ HCJ IYPBX, PHCLH BGBKFENZZV, YM LYEXJB, HB RCR. EKMYXFEKNFBZV, HB FNEQHF HCJ NIIXBKFCLB BGBXVFHCKQ HB AKBP, FHBK HCJ NIIXBKFCLB ACZZBR HCO CK HCJ JZBBI. CXYKCL. HB LYEZR JNGB YFHBXJ MXYO RBNFH, WEF KYF HCOJBZM."}; // Cipher text message to be analysed

  freqAnalysis(cipherText);

  printf("\n");
  return 0;

}


void freqAnalysis(char *cipherText) { // Returns frequency of each letter in cipherText in alphabetical order

  int maxFreq;
  char maxLetter;
  char mostFreq[26] = {"ETAOINSHRDLCUMWFGYPBVKJXQZ"};
  char alphabet[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  char testKey[26] = {}; // possible key to be altered from frequency analysis
  int frequency[26] = {}; // Frequency array of letters in string
  int len = strlen(cipherText); // Gets length of string


  for(int index = 0; index < len; index++) { // Loops through each letter in the string
    for(int letter = 65; letter <= 90; letter++) { // Loops through each letter of the alphabet
      int cipherChar = (int)cipherText[index]; // Sets cipherChar to cipherText letter at index
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
