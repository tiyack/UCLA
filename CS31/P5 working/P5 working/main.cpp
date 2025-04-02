//
//  main.cpp
//  P5 working
//
//  Created by Tiya Chokhani on 11/5/22.
//

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int MAXWORDLEN = 6;
//have set this to 9 for now bc loop is running through the whole thing
const int MAXWORDS = 12/*000*/;

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);
bool validProbeWord (const char ListWords[][MAXWORDLEN+1], const char inputWord [], char probeWord [], int numWords);
void countForGoldAndSilver (char probeW[], const char rightWord []);

int main() {
    char words1[MAXWORDS][MAXWORDLEN+1] = {"assert", "balm", "baby", "toys", "doorss", "biam", "ablmt", "balls", "balms", "egret", "albums", "exit"};
//    int rounds;
//    cout << "How many rounds do you want to play? ";
//    cin >> rounds;
//    cin.ignore(10000, '\n');
//
//    if (rounds < 0){
//        cout << "The number of rounds must be positive." << endl;
//        return 1;
//    }
//    for (int i = 0; i < rounds; i++){
//        cout << endl;
//        cout << "Round " << (i + 1) << endl;
        //need to say how long the word is
        playOneRound(words1, 12, 0);
//    }
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
    char inputLine[50];
    while (strcmp(probe, words[wordnum]) != 0){
        do {
            cout << "Probe word: ";
            cin.getline(inputLine, 50);
        } while (!validProbeWord(words, inputLine, probe, nWords));
        
        //right answer is words[wordnum]
        //create a function count silver and gold
        countForGoldAndSilver(probe, words[wordnum]);
        score++;
        cerr << "Score is " << score <<  endl;
    }
    return score;
}
        

bool validProbeWord (const char ListWords[][MAXWORDLEN+1], const char inputWord [], char probeWord[], int numWords){

    //checking that its 4-6 chars
//    cerr << strlen(inputWord) << endl;
    size_t inputLen = strlen(inputWord);
//    cerr << inputLen << endl;
    if(inputLen < 4 || inputLen > 6){ //if more than 6 or less than 4
        cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
//        cerr << "Needs to restart. ENDHERE1" <<endl;
        return false;
    }
    
//    cerr << "Valid number of characters inputted." << endl;
    strncpy(probeWord, inputWord, 6);
//    cerr << "Copying to probeWord: " << probeWord << endl;
    probeWord[6] = '\0';
    
    //checking for lowercase aplha
    bool validWord = true;
    for (int i = 0; probeWord[i] != '\0'; i++){
        if (!isalpha(probeWord[i])){
            validWord = false;
//            cerr << "Here" << i;
            break;
        }
        if (!islower(probeWord[i])){
            validWord = false;
//            cerr << "Here" << i;
            break;
        }
    } //break ends here
    if(!validWord){
        cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
//        cerr << "Needs to restart2. ENDHERE" <<endl;
        return false;
    }
//    else
//        cerr << "Valid characters" << endl;
    
    //need to check that its a valid word from the array
    bool match = false;
    for (int i = 0; i < numWords; i++){
//        cerr << "i is " << i << endl;
        if(strcmp(ListWords[i], probeWord) == 0){
            match = true;
//            cerr << "There's a matching word" << endl;
            break;
        }
    }
    if(!match){
        cout << "I don't know that word." << endl;
//        cerr << "Needs to restart. ENDHERE" <<endl;
        return false;
    }
    return true;
}

void countForGoldAndSilver (char probeW[], const char rightWord []){
    cerr << "Input is " << probeW << " Answer is " << rightWord << endl;
    
    int goldCount = 0;
    int silverCount = 0;
    int probeLen = strlen(probeW);
    int rightWordLen = strlen(rightWord);
    char rightWordCopy[7];
    strcpy(rightWordCopy, rightWord);
    if (strcmp(probeW, rightWord) != 0){
        for (int i = 0; i < probeLen; i++){
            for (int j = 0; j < rightWordLen; j++){
                if (probeW[i] == rightWordCopy[j]){
                    cerr << probeW[i] << "=" << rightWordCopy[j] << endl;
                    if (j == i){
                        rightWordCopy[j] = 'Z';
                        probeW[i] = 'K';
                        goldCount++;
                        cerr << j << "=" << i << endl;
                        cerr << "gold added" << endl;
                    }
                    else{
                        rightWordCopy[j] = 'Z';
                        probeW[i] = 'K';
                        silverCount++;
                        cerr << "silver added" << endl;
                    }
                }
            }
        }
        cout << "Golds: " << goldCount << ", Silvers: " << silverCount << endl;
    }
}

    
    
    
    
    
    
    
    
    
    
    
    
//    int notGoldIndx[7];
//    int indx = 0;
//
//    if (strcmp(probeW, rightWord) != 0){
//        //GOLD
//        for (int i = 0; probeW[i] != '\0' && rightWord[i] != '\0'; i++){
//            if (probeW[i] == rightWord[i]){
////                cerr << probeW[i] << " Matches" << endl;
//                goldCount++;
////                cerr << "goldCount = " << goldCount << endl;
//            }
//            else{ //adding all the indexes that arent gold to an array
//                notGoldIndx[indx] = i;
//                indx++;
////                cerr <<  "notGoldIndx at " << indx-1 << " is " << notGoldIndx[indx-1] << endl;
//            }
//        }
//
//        //ask about these
//        int probeLen = strlen(probeW);
//        int rightWordLen = strlen(rightWord);
//        int silverCount = 0;
//        // int secondIndx[7];
//        char rightWordCopy[7];
//        strcpy(rightWordCopy, rightWord);
//
//        if (probeLen > rightWordLen){
////            cerr << "ProbeLen > rightWordLen" << endl;
//            for (int i = rightWordLen; i < probeLen; i++){
//                notGoldIndx[indx] = i;
//                indx++;
////                cerr <<  "notGoldIndx at " << indx-1 << " is " << notGoldIndx[indx-1] << endl;
//            }
//            //SILVER
//            for (int i = 0; i < indx; i++){ //to loop the indx of array
////                cerr << "Checking "<< probeW[notGoldIndx[i]] << endl; //these are the remianing chars that could be silver
//                for (int j = 0; notGoldIndx[j] < rightWordLen; j++){
//                    if(probeW[notGoldIndx[i]] == rightWordCopy[notGoldIndx[j]]){
////                        cerr << probeW[notGoldIndx[i]] << " = " << rightWordCopy[notGoldIndx[j]] << endl;
//                        silverCount++;
//                        rightWordCopy[notGoldIndx[j]] = 'Z';
//  //                      cerr << "rightWordCopy at " << notGoldIndx[j] << " is " << rightWordCopy[notGoldIndx[j]] << endl;
//                        break;
//                    }
//                }
//            }
//        }
//        else if (probeLen < rightWordLen){
//            for (int i = probeLen; i < rightWordLen; i++){
//                notGoldIndx[indx] = i;
//                indx++;
////                cerr <<  "notGoldIndx at " << indx-1 << " is " << notGoldIndx[indx-1] << endl;
//            }
//            //SILVER
////            cerr << "Indx: " << indx << endl;
//            for (int i = 0; notGoldIndx[i] < probeLen; i++){ //condition here is wrong
////                cerr << "Checking "<< probeW[notGoldIndx[i]] << endl; //these are the remianing chars that could be silver
//                for (int j = 0; j < indx; j++){
//                    if(probeW[notGoldIndx[i]] == rightWordCopy[notGoldIndx[j]]){
////                        cerr << probeW[notGoldIndx[i]] << " = " << rightWordCopy[notGoldIndx[j]] << endl;
//                        silverCount++;
//                        rightWordCopy[notGoldIndx[j]] = 'Z';
////                        cerr << "Does it break?" << endl;
//                        break;
//                    }
//                }
//            }
//        }
//        else{
//            //SILVER if equal
//            for (int i = 0; i < indx; i++){ //to loop the indx of array
////                cerr << probeW[notGoldIndx[i]] << endl; //these are the remianing chars that could be silver
//                for (int j = 0; j < indx; j++){
//                    if(probeW[notGoldIndx[i]] == rightWord[notGoldIndx[j]]){
////                        cerr << probeW[notGoldIndx[i]] << " = " << rightWord[notGoldIndx[j]] << endl;
//                        silverCount++;
//                        rightWordCopy[notGoldIndx[j]] = 'Z';
//                        break;
//                    }
//                }
//            }
//        }
//        cout << "Golds: " << goldCount << ", Silvers: " << silverCount << endl;
//    }
//}


//}


//void countForGoldAndSilver (char probeW[], const char rightWord []){
//    cerr << "Input is " << probeW << " Answer is " << rightWord << endl;
//    int goldCount = 0;
//    int notGoldIndx[7];
//    int indx = 0;
//
//    if (strcmp(probeW, rightWord) != 0){
//        //GOLD
//        for (int i = 0; probeW[i] != '\0' && rightWord[i] != '\0'; i++){
//            if (probeW[i] == rightWord[i]){
////                cerr << probeW[i] << " Matches" << endl;
//                goldCount++;
////                cerr << "goldCount = " << goldCount << endl;
//            }
//            else{ //adding all the indexes that arent gold to an array
//                notGoldIndx[indx] = i;
//                indx++;
////                cerr <<  "notGoldIndx at " << indx-1 << " is " << notGoldIndx[indx-1] << endl;
//            }
//        }
//
//        //ask about these
//        int probeLen = strlen(probeW);
//        int rightWordLen = strlen(rightWord);
//        int silverCount = 0;
//        // int secondIndx[7];
//        char rightWordCopy[7];
//        strcpy(rightWordCopy, rightWord);
//
//        if (probeLen > rightWordLen){
////            cerr << "ProbeLen > rightWordLen" << endl;
//            for (int i = rightWordLen; i < probeLen; i++){
//                notGoldIndx[indx] = i;
//                indx++;
////                cerr <<  "notGoldIndx at " << indx-1 << " is " << notGoldIndx[indx-1] << endl;
//            }
//            //SILVER
//            for (int i = 0; i < indx; i++){ //to loop the indx of array
////                cerr << "Checking "<< probeW[notGoldIndx[i]] << endl; //these are the remianing chars that could be silver
//                for (int j = 0; notGoldIndx[j] < rightWordLen; j++){
//                    if(probeW[notGoldIndx[i]] == rightWordCopy[notGoldIndx[j]]){
////                        cerr << probeW[notGoldIndx[i]] << " = " << rightWordCopy[notGoldIndx[j]] << endl;
//                        silverCount++;
//                        rightWordCopy[notGoldIndx[j]] = 'Z';
//  //                      cerr << "rightWordCopy at " << notGoldIndx[j] << " is " << rightWordCopy[notGoldIndx[j]] << endl;
//                        break;
//                    }
//                }
//            }
//        }
//        else if (probeLen < rightWordLen){
//            for (int i = probeLen; i < rightWordLen; i++){
//                notGoldIndx[indx] = i;
//                indx++;
////                cerr <<  "notGoldIndx at " << indx-1 << " is " << notGoldIndx[indx-1] << endl;
//            }
//            //SILVER
////            cerr << "Indx: " << indx << endl;
//            for (int i = 0; notGoldIndx[i] < probeLen; i++){ //condition here is wrong
////                cerr << "Checking "<< probeW[notGoldIndx[i]] << endl; //these are the remianing chars that could be silver
//                for (int j = 0; j < indx; j++){
//                    if(probeW[notGoldIndx[i]] == rightWordCopy[notGoldIndx[j]]){
////                        cerr << probeW[notGoldIndx[i]] << " = " << rightWordCopy[notGoldIndx[j]] << endl;
//                        silverCount++;
//                        rightWordCopy[notGoldIndx[j]] = 'Z';
////                        cerr << "Does it break?" << endl;
//                        break;
//                    }
//                }
//            }
//        }
//        else{
//            //SILVER if equal
//            for (int i = 0; i < indx; i++){ //to loop the indx of array
////                cerr << probeW[notGoldIndx[i]] << endl; //these are the remianing chars that could be silver
//                for (int j = 0; j < indx; j++){
//                    if(probeW[notGoldIndx[i]] == rightWord[notGoldIndx[j]]){
////                        cerr << probeW[notGoldIndx[i]] << " = " << rightWord[notGoldIndx[j]] << endl;
//                        silverCount++;
//                        rightWordCopy[notGoldIndx[j]] = 'Z';
//                        break;
//                    }
//                }
//            }
//        }
//        cout << "Golds: " << goldCount << ", Silvers: " << silverCount << endl;
//    }
//}
