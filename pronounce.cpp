// Camryn Buonamassa
// CSCI135 Project 2
/* Pseudocode
1) Get input with cin in order to only take the first word
2) Check that all the characters inputted were either letters or apostrophes
3) Translate all letters to uppercase
4) Read through every line of the dictionary using getline and a while loop
   until you find a word spelled the same
6) Save the phonemes to a string variable
7) Output the pronounciation of the word
8) Create a function to save phonemes to an array to allow comparison of 
   individual phonemes
9) Search for words with the same number of phonemes in the same order
10) Search for words with one more phoneme than the original, inserted anywhere
    in the word
11) Search for words with one less phoneme than the original, removed from
    anywhere in the word
12) Search for words with the the same number of phonemes in the same order with
    one replaced/different from the original */

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
using namespace std;
// Prototypes
string filterWord(string word);
string readPhonemes(string filteredWord);
string findIdentical(string phonemes, string filteredWord);
string remove(string phonemes, string afterSpace, string word);
string add(string phonemes, string afterSpace, string word);
string replace(string phonemes, string afterSpace, string word);
int countPhonemes(string phonemes);
void splitPhonemes(string line, string array[], int& size);
void splitOnSpace(string s, string& before, string& after);
void decide(int count, string phonemes, string filteredWord);
// main() does as minimal work as possible; decide() calls add, remove, and replace
int main() {
  string word;
  // Initialize first word of user input to the variable "word"
  cin >> word;

  string filteredWord = filterWord(word);
  string phonemes = readPhonemes(filteredWord);
  // Ends the program if there are no phonemes 
  if (phonemes == "") {
    return 0;
  }
  string identical = findIdentical(phonemes, filteredWord);
  int count = countPhonemes(phonemes);
  decide(count, phonemes, filteredWord);
}
// Makes sure word only has letters or apostrophes
string filterWord(string word) {
  char letter;
  string filteredWord;
  // Checks every character of input word
  // Only letters and apostrophes allowed 
  for (int i = 0; i < word.length(); i++) {
    letter = word[i];
    // If ASCII value is 39 (') then add it to filteredword and check next character
    if ((int)letter == 39) {
      filteredWord += letter;
    // If character is uppercase, add to filterowrd and check next character
    } else if (isupper(letter)) {
      filteredWord += letter;
    // If character is lowercase, add to filterowrd and check next character
    } else if (islower(letter)) {
      letter = char((int)letter - 32);
      filteredWord += letter;
    // If character doesn't fit any of the above conditions, return a blank string
    } else {
      return "";
    }
  }
  // After checking every character, return the original word (now called filteredword)
  return filteredWord;
}
// Finds the filtered word in the dictionary and its phonemes
// Splits the word from the phonemes and returns the string of phonemes
string readPhonemes(string filteredWord) {
  // Initialize all necessary strings, booleans, and input streams
  bool found = false;
  string word;
  string phonemes;
  string beforeSpace;
  string afterSpace;
  ifstream library;
  library.open("cmudict.0.7a.txt");
  // Continue while we can still take in another word from dictionary
  while (library >> word) {
    // If the word we read is the same as the user input word, separate the word from the phonemes
    if (word == filteredWord) {
      found = true;
      getline(library, phonemes);
      splitOnSpace(phonemes, beforeSpace, afterSpace);
      splitOnSpace(afterSpace, beforeSpace, afterSpace);
      // Output the pronounciation of the found word
      cout << "Pronounciation: " << afterSpace << endl;
      cout << "" << endl;
      break;
    }
  }
  // If user input word doesn't match any word in dictionary, output "Not found"
  if (!found) {
    cout << "Not found" << endl;
    return "";
  }
  // Return the phonemes so we can use them in the other functions
  return afterSpace;
}
// Searches for any set of phonemes that match the original
// If found, returns the new word
string findIdentical(string phonemes, string filteredWord) {
  bool found = false;
  string word;
  string newPhonemes;
  string beforeSpace;
  string afterSpace;
  string identical;
  string allIdentical;
  ifstream library;

  library.open("cmudict.0.7a.txt");
  // Continue while we can still take in another word from dictionary
  while (library >> word) {
    getline(library, newPhonemes);
    // Read the new phonemes
    splitOnSpace(newPhonemes, beforeSpace, afterSpace);
    splitOnSpace(afterSpace, beforeSpace, afterSpace);
    // If the word is the same as the user input word, found is false 
    if (word == filteredWord) {
      found = false;
    // If the new phonemes are the same as the original, add the new word to identical
    } else if (afterSpace == phonemes) {
      found = true;
      string identical = filterWord(word);
      allIdentical += " ";
      allIdentical += identical;
    }
  }
  cout << "Identical: " << allIdentical << endl;
  // If found is false, identical is an empty string because there is no word with identical phonemes
  if (!found) {
    identical = "";
  }
  return identical;
}
// Called by decide() when the number of phonemes in the new word is one more
// than the original number of phonemes
// Searches for any words with same phonemes as original plus a new one inserted
// anywhere in original word
string add(string phonemes, string afterSpace, string word) {
  bool strike = false;
  int sizePho = 0;
  int sizeAft = 0;
  int counter = 0;
  string added;
  // Create two arrays to hold the separated original phonemes and the separated new phonemes
  string ogPhonemes[20];
  string newPhonemes[20];
  splitPhonemes(phonemes, ogPhonemes, sizePho);
  splitPhonemes(afterSpace, newPhonemes, sizeAft);
  // counter and strike allow us to compare the phonemes in a way where we can only have one mismatch
  for (int i = 0; i < sizeAft; i++) {
    if (ogPhonemes[i] != newPhonemes[counter]) {
      if (!strike) {
        strike = true;
        counter++;
        // If there is a second mismatch, return an empty string
        if (ogPhonemes[i] != newPhonemes[counter]) {
          return "";
        }
      } else {
        return "";
      }
    }
    counter++;
  }
  word += " ";
  return word;
}
// Called by deicde when the number of phonemes in the new word is one less than
// the original number of phonemes
// Searches for any words with same phonemes as original minus one of them
string remove(string phonemes, string afterSpace, string word) {
  return add(afterSpace, phonemes, word);
}
// Called by decide when the number of phonemes in the new word is equal to the original number of phonemes
// Compares each phoneme to the original, determining if there is only one difference
string replace(string phonemes, string afterSpace, string word) {
  int sizePho = 0;
  int sizeAft = 0;
  int strike = 0;
  string replaced;
  string ogPhonemes[20];
  string newPhonemes[20];
  splitPhonemes(phonemes, ogPhonemes, sizePho);
  splitPhonemes(afterSpace, newPhonemes, sizeAft);
  // There can only be one mismatch, but all other phonemes must be in the same place
  // This is why we can use one for loop to track one position variable
  for (int i = 0; i < sizePho; i++) {
    if (ogPhonemes[i] != newPhonemes[i]) {
      strike++;
    }
  }
  // If there are 0 or more than 1 mismatch, the word does not fit the conditions for replace phoneme
  // Return empty string
  if (strike != 1) {
    return "";
  // Otherwise, it must fit the conditions, so return the word or an empty string if the word happens to be ""
  } else {
    if (word == "") {
      return "";
    } else {
      word += " ";
      return word;
    }
  }
}
// Counts phonemes by adding 1 to the number of spaces between phonemes
int countPhonemes(string phonemes) {
  int count = 1;
  // Count all the spaces between the phonemes and add 1 to get number of phonemes
  // Useful for deciding which function (add remove replace) to call
  for (int i = 0; i < phonemes.length(); i++) {
    if (isspace(phonemes[i])) {
      count++;
    }
  }
  return count;
}
// Decides which function (add, remove, or replace) to call based on the number
// of phonemes in the new string of phonemes
void decide(int count, string phonemes, string filteredWord) {
  bool done = false;
  string beforeSpace;
  string afterSpace;
  string newPhonemes;
  string word;
  ifstream library;
  string replaced, removed, added;
  library.open("cmudict.0.7a.txt");
  // Continue while we can still take in another word from dictionary
  while (!done && library >> word) {
    string goodWord = filterWord(word);
    getline(library, newPhonemes);
    splitOnSpace(newPhonemes, beforeSpace, afterSpace);
    splitOnSpace(afterSpace, beforeSpace, afterSpace);
    int x = countPhonemes(afterSpace);
    // USes the number of phonemes to decide which fucntion to call
    // I made this function to keep main very minimal
    if (x == count && goodWord != filteredWord) {
      replaced += replace(phonemes, afterSpace, goodWord);
    } else if (x == count - 1) {
      removed += remove(phonemes, afterSpace, goodWord);
    } else if (x == count + 1) {
      added += add(phonemes, afterSpace, goodWord);
    } else {
      done = false;
    }
  }
  cout << "Add phoneme: " << added << endl;
  cout << "Remove phoneme: " << removed << endl;
  cout << "Replace phoneme: " << replaced << endl;
}
// Splits phonemes so they can be compared individually
void splitPhonemes(string line, string array[], int& size) {
  // Temporary string to hold phonemes
  string temp;
  // For the length of the line, push group of characters (single phoneme) 
  // to the array when a space is encountered
  for (int i = 0; i < line.length(); i++) { 
    if (line[i] == ' ' && temp != "") {
      array[size] = temp;
      temp = "";
      size++;
    } else {
      temp += line[i];
    }
  }
  if (temp != "") {
    array[size] = temp;
    size++;
  }
}
// Used to split words from phonemes due to the spaces in the dictionary
// Function provided by CS department
void splitOnSpace(string s, string& before, string& after) {  // reset strings
  before = "";
  after = "";
  // accumulate before space
  int i = 0;
  while (i < s.size() && not isspace(s[i])) {
    before += s[i];
    i++;
  }  // Skip the space
  i++;
  // Accumulate characters after space
  while (i < s.size()) {
    after += s[i];
    i++;
  }
}