#include <stdio.h>
#include <stdlib.h>
#define WORD 30;
#define TXT 1024;
// read from a file here:
FILE *filePointer = fopen(argv[0], 'r');

int main(int* argc, int* argv[]){
    // init word
    char word[(WORD* 4)];
    char nextChar = fgetc;
    int index =0;
    while(nextChar != "\n" && nextChar != EOF){
        word[index++] = nextChar;
    }
    word[index] = '\0'
    // print not valid if word[0] = '\0' if needed
    if(word[0] == '\0'){
        printf("cannot find word!");
        return;
    }
    // calculate gimatric values of the word
    int gimatryWord = 0;
    int[52] abc;
    index = 0;
    int charVal;
    do {
        charVal = (int) word[index++];
        if((charVal > 96 && charVal < 123)){
            // increment small letter
            abc[charVal - 97] +=1;
            gimatryWord += (charVal-96);
        }
        if(charVal > 64 && charVal < 91){
            // increment big letter
            abc[charVal -65 + 26] +=1;
            gimatryWord += (charVal - 65);
        }
        abc[nextChar]+=1;
    }while(word[index] != '\0');
    // enter code here:
    minSeq(gimatryWord);
    atBash(gimatryWord);
    minSeqWithEmpty(abc);
    return 0;
}
int minSeq(int gimatryVal){
    


}

int atbash(int gimatryVal){

}

int minSeqWithEmpty(int *wordABC){



}