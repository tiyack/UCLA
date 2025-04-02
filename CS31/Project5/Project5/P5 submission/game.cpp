//
//  main.cpp
//  Project5
//
//  Created by Tiya Chokhani on 11/5/22.
//
#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;

const int MAXWORDS = 9000;
char words1[MAXWORDS][MAXWORDLEN+1];
char inputLine[50];
char probe[7];


const char WORDFILENAME[] = "/Users/tiyachokhani/Desktop/CS31/Project5/Project5/wordList.txt";
    // Windows users:  Use / instead of \ for pathname separators.

bool validProbeWord (const char ListWords[][MAXWORDLEN+1], const char inputWord [], char probeWord[], int numWords);
void countForGoldAndSilver (char probeW[], const char rightWord []);

bool checkRightAnswer (const char input[], const char rightAns[]);

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);

//const char wordList[MAXWORDS][MAXWORDLEN+1];

int main()
{
    char listOfWords[MAXWORDS][MAXWORDLEN+1];
    int n = getWords(listOfWords, MAXWORDS, WORDFILENAME); //fills up the array
//    cerr << "getWords found the file, and loaded " << n  << " words." << endl;
    
    if (n < 1){
        cout << "No words were loaded, so I can't play the game." << endl;
        return 1;
    }
    
    int rounds;
    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    cin.ignore(10000, '\n');

    if (rounds < 0){
        cout << "The number of rounds must be positive." << endl;
        return 1;
    }
    
    int numTries = 0;
    const int maxRounds = 1000;
    int scores [maxRounds];
    double total = 0;
    cout.setf(ios::fixed);
    cout.precision(2);
    
    for (int i = 1; i <= rounds; i++){ //for every round
        cout << endl;
        cout << "Round " << (i) << endl;
        int rand = randInt(0, n - 1); //generates a random number
        //int rand = 1;
        cout << "The hidden word is " << strlen(listOfWords[rand])
        << " letters long." << endl;
        numTries = playOneRound(listOfWords, n, rand);
        if (numTries == -1)
            return 2;
        if (numTries > 1)
            cout << "You got it in " << numTries << " tries." << endl;
        if (numTries == 1)
            cout << "You got it in " << numTries << " try." << endl;
        
        scores[i-1] = numTries; //creates an array to store the scores
        int max = numTries, min = numTries; //sets max and min as numTries
        for (int k = 0; k < i; k++){
            if (scores[k] < min)
                min = scores[k];
            if (scores[k] > max)
                max = scores[k];
        }
        total += numTries;
        cout << "Average: " << static_cast<double>(total)/i << ", minimum: " << min << ", maximum: " << max << endl;
    }
    
}

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum){

    // nWords represents the number of words in the array 'words'
    //words[wordnum] is the random word we have to check against
    int score = 0;
    if (nWords < 0 || wordnum < 0 || wordnum >= nWords){
        cerr << "Needs to return -1" << endl; //return -1;
        return -1;
    }
    
    char probe[MAXWORDLEN+1] = "";
    char inputLine[102];

    while (!checkRightAnswer(probe, words[wordnum])){ //to check that its not the right answer
        do { //repeatedly will ask for probe word if invalid one given
            cout << "Probe word: ";
            cin.getline(inputLine, 100);
        } while (!validProbeWord(words, inputLine, probe, nWords));
        
        //right answer is words[wordnum]
        countForGoldAndSilver(probe, words[wordnum]);
        score++;
    }
    return score;
}

void countForGoldAndSilver (char probeW[], const char rightWord []){
//    cerr << "Input is " << probeW << " Answer is " << rightWord << endl;
    
    int goldCount = 0;
    int silverCount = 0;
    size_t probeLen = strlen(probeW);
    size_t rightWordLen = strlen(rightWord);
    
    char rightWordCopy[7];
    strcpy(rightWordCopy, rightWord); //creating a copy of rightWord

    if (!checkRightAnswer(probeW, rightWord)){
        for (int i = 0; i < probeLen; i++){
            for (int j = 0; j < rightWordLen; j++){
                if (probeW[i] == rightWordCopy[j]){
                    if (j == i){
                        rightWordCopy[j] = 'Z';
                        probeW[i] = 'K';
                        goldCount++;
                    }
                    else{
                        rightWordCopy[j] = 'Z';
                        probeW[i] = 'K';
                        silverCount++;
                     //   cerr << "silver added" << endl;
                    }
                }
            }
        }
        cout << "Golds: " << goldCount << ", Silvers: " << silverCount << endl;
    }
}


bool validProbeWord (const char ListWords[][MAXWORDLEN+1], const char inputWord [], char probeWord[], int numWords){

    //checking that its 4-6 chars
    size_t inputLen = strlen(inputWord);
    if(inputLen < 4 || inputLen > 6){ //if more than 6 or less than 4
        cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
        return false;
    }
    
    strncpy(probeWord, inputWord, 6);
    probeWord[6] = '\0';
    
    //checking for lowercase aplha
    bool validWord = true;
    for (int i = 0; probeWord[i] != '\0'; i++){
        if (!isalpha(probeWord[i]) || probeWord[i] == ' '){
            validWord = false;
            break;
        }
        if (!islower(probeWord[i])){
            validWord = false;
            break;
        }
    } //break ends here
    if(!validWord){
        cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
        return false;
    }
    
    //need to check that its a valid word from the array
    bool match = false;
    for (int i = 0; i < numWords; i++){
        if(strcmp(ListWords[i], probeWord) == 0){
            match = true;
            break;
        }
    }
    if(!match){
        cout << "I don't know that word." << endl;
        return false;
    }
    return true;
}

bool checkRightAnswer (const char input[], const char rightAns[]){
    size_t inputLen = strlen(input);
    size_t rightAnsLen = strlen(rightAns);
    bool match = true;
    
    //cerr << "Running Check Right answer " << endl;
    //cerr << "Input is " << input << " right Ans is " << rightAns << endl;
    if (inputLen == rightAnsLen){ //check for same length
        for (int i = 0; i < inputLen; i++){
            if (input[i] != rightAns[i]){
                match = false;
                break;
            }
        }
        if(match) //all chars are the same
            return true;
    }
    return false;
}

