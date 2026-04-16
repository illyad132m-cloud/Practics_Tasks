#include <iostream>
#include <fstream> 
#include <string> 
#include <map>    
#include <windows.h>

using namespace std;

int main() {
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cout << "Error: Create file input.txt next to the program!" << endl;
        return 1;
    }

    string text = "";
    string line;
    while (getline(inputFile, line)) {
        text += line + " ";
    }
    inputFile.close();
    map<char, int> lettersCount;

    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c != ' ' && c != '.' && c != ',' && c != '!' && c != '?') {
            lettersCount[c]++;
        }
    }

    char bestChar = ' ';
    int maxCount = 0;
    for (auto pair : lettersCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second; 
            bestChar = pair.first;
        }
    }
    string currentWord = "";
    string bestWord = "";
    int maxInWord = 0;
    int currentInWord = 0;

    for (int i = 0; i < text.length(); i++) {
        char c = text[i];

        if (c == ' ' || c == '.' || c == ',' || c == '!' || c == '?') {

            if (currentInWord > maxInWord) {
                maxInWord = currentInWord;
                bestWord = currentWord;
            }
            currentWord = "";
            currentInWord = 0;

        }
        else {
            currentWord += c;
            if (c == bestChar) {
                currentInWord++; 
            }
        }
    }

    ofstream outputFile("output.txt"); 

    if (!outputFile.is_open()) {
        cout << "Error: Could not create output.txt file" << endl;
        return 1;
    }
    outputFile << "Most frequent character: '" << bestChar << "'" << endl;
    outputFile << "It appears in the text " << maxCount << " times." << endl;
    outputFile << "-----------------------------------" << endl;
    outputFile << "Word with the most occurrences of this character: " << bestWord << endl;
    outputFile << "Number of '" << bestChar << "' in this word: " << maxInWord << endl;

    outputFile.close();


    cout << "Done! Most frequent character: '" << bestChar << "'" << endl;
    cout << "Results saved in output.txt file" << endl;

    return 0;
}