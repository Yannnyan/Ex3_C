#include <stdio.h>
#include <stdlib.h>
#define WORD 30
#define TXT 1024
// read from a file here:
FILE *filePointer;

char *retMinSeq(){
    char * minseq;
    minseq = (char *)malloc(WORD*sizeof(char));
    char nextChar = fgetc(filePointer);
    int nextIndex=0;
    while(nextChar != '~' || nextChar != ' ' || nextChar != '\n' || nextChar != '\t'){
        minseq[nextIndex++] = nextChar;
        nextChar = fgetc(filePointer);
    }
    minseq[nextIndex] = '\0';
    return minseq;
}

int gimatryValue(char *sequence){
    if(sizeof(sequence) == 1){
        return 0;
    }
    char nextChar = sequence[0];
    int currentIndex = 1;
    int gimatryVal=0;
    int curCharVal;
    while(nextChar != '\0' && nextChar != '~'){
        curCharVal = (int)nextChar;
        if(97 <= curCharVal && curCharVal <= 122){
            gimatryVal += curCharVal-96;
        }
        else if(65 <= curCharVal && curCharVal <= 90){
            gimatryVal += curCharVal-64;
        }
        nextChar = sequence[currentIndex++];
    }
    //printf("word received is : %s\n", sequence);
    //printf("Value of read word is : %d\n", gimatryVal);
    return gimatryVal;
}
int minSeq(int gimatryVal){
    // iterate untill geting useless value and then check gimatry 
    // if equals then print, else throw the sequence and start again
    char nextChar = fgetc(filePointer);
    char *word;
    word = (char *) malloc(WORD *sizeof(char));
    int nextIndex = 0;
    int true = nextChar == '~' ? 0 : 1;
    int first = 1;
    //printf("true is : %d\n", true);
    while(true == 1){
        if(nextChar == '\n' || nextChar == '\t' || nextChar == ' ' || nextChar == '~'){
            if(nextChar == '~'){
                true = 0;
            }
            word[nextIndex] = '\0';
            //printf("word passed to gimatryValue is %s\n: ", (word));
            int gimatSeqVal = gimatryValue(word);
            if(gimatSeqVal == gimatryVal){
                if(first == 1){
                    printf("%s",word); first = 0 ;
                }
                else{
                    printf("~%s",word);
                }
            }
            nextIndex=0;
            word = (char *)realloc(word, WORD * sizeof(char));
        }
        else{
            //printf("current char is : %c\n",nextChar);
            word[nextIndex++] = nextChar;
        }
        nextChar = fgetc(filePointer);
    }
    free(word);
    //printf("ended minSeq\n");
    return 0;


}

int atBash(char * word){
    //printf("word receive is : %s\n", word );
    char c = word[0];
    int wordLength = 0;
    int  index=0;
    // get the word's length
    while(c != '\0'){
        wordLength+=1;
        c = word[++index];
    }
    //printf("The length of the word is : %d\n", wordLength);
    //printf("allocating memory for atbashWord\n");
    char * atbashWord = (char *) malloc((wordLength+1) * sizeof(char));
    //printf("allocating memory for reverseAtbashWord\n");
    char * reverseAtbashWord = (char *) malloc((wordLength+1) * sizeof(char));
    int currentIndex =0;
    int currCharValue;
    while(word[currentIndex] != '\0'){
        currCharValue = (int)word[currentIndex];
        if(97 <= currCharValue && currCharValue <= 122){
            atbashWord[currentIndex] = (char) (122 - (currCharValue - 97));
            currentIndex+=1;
            //printf("atbash is : %s\n", atbashWord);
        }
        else if(65 <= currCharValue && currCharValue <= 90){
            atbashWord[currentIndex] = (char) (90 - (currCharValue - 65));
            currentIndex+=1;
            //printf("atbash is : %s\n", atbashWord);
        }
    }
    atbashWord[currentIndex] = '\0';
    reverseAtbashWord[currentIndex] = '\0';
    currentIndex = wordLength - 1;
    index =0;
    while(atbashWord[index] != '\0'){
        reverseAtbashWord[currentIndex--] = atbashWord[index++];
    }
    //printf("reverse atbash is : %s\n", reverseAtbashWord);
    char nextChar = getc(filePointer);
    int index1=0,index2=0, first = 1;

    while(nextChar != '~'){
        if(nextChar != ' ' || nextChar != '\n' || nextChar != '\t'){
            if(nextChar == atbashWord[index1]){
                index1++;
               // printf("incrementing index1 by 1 for char : %c\n", nextChar);
            }
            else{
                index1 = 0;
                //printf("resetting index1 by 1 for char : %c\n", nextChar);
            }
            if(nextChar == reverseAtbashWord[index2]){
                index2++;
                //printf("incrementing index2 by 1 for char : %c\n", nextChar);
            }
            else{
                //printf("resetting index2 by 1 for char : %c\n", nextChar);
                index2 = 0;
            }
        }
        if(index1 == (wordLength)){
            if(first == 1){
                printf("%s",atbashWord);
                first =0;
            }
            else{
                printf("~%s",atbashWord);
            }
        }
        if(index2 == (wordLength)){
            if(first == 1){
                printf("%s",reverseAtbashWord);
                first =0;
            }
            else{
                printf("~%s",reverseAtbashWord);
            }
        }
        nextChar = getc(filePointer);
    }
    return 0;
}

int minSeqWithEmpty(char *wordABC){
    //printf("received word : %s\n", wordABC);
    int *asciWord = (int *) calloc(sizeof(int), 88), *asciNextSeq = (int *) calloc(sizeof(int), 88);
    char nextChar = wordABC[0];
    int charVal, wordLen=0, index=1;
    // init the word's asci value chart
    if(nextChar == '\0')
        return 0;
    while(nextChar != '\0'){
        charVal = (int) nextChar;
        if(charVal >= 40 && charVal <= 126){
            asciWord[charVal] +=1;
            wordLen+=1;
        }
        //printf("got nextChar of value of %c\n", nextChar);
        nextChar = wordABC[index++];
        
    }
    nextChar = fgetc(filePointer);
    //printf("allocating new memory\n");
    char *newSeq = (char *) malloc(wordLen * sizeof(char));
    //printf("allocated new memory space for the new minimal sequence\n");
    index =0;
    int lenSeq=0;
    int first = 1;
    // read the text and get the minimal sequences
    // test if the asci values of the minimal sequences equal to the
    // word's asci chart by making its own chart and just checking if 
    // the word's asci chart already has this character, print only if
    // the word's length is equal to the minimal sequence length
    while(nextChar != '~'){
        if(lenSeq == wordLen){
            newSeq[index] = '\0';
            lenSeq = 0;
            if(first == 1){
                printf("%s", newSeq); first = 0 ;
            }
            else{
                printf("~%s", newSeq);
            }
        }
        if(nextChar != ' ' && nextChar != '\n' && nextChar != '\t'){
            charVal = (int)nextChar;
            if(asciWord[charVal] > asciNextSeq[charVal]){
                //printf("asciWord at index %c, is : %d\n", charVal, asciWord[charVal]);
                //printf("asciNextSeq at index %c, is : %d\n ", charVal, asciNextSeq[charVal]);
                asciNextSeq[charVal] +=1;
                newSeq[index++] = nextChar;
                lenSeq+=1;
                //printf("incrementing value by 1 to %c\n",nextChar);
            }
            else{
                lenSeq = 0; index=0;
               // printf("reallocating memory of sequence's asci chart\n");
                free(asciNextSeq);
                asciNextSeq = (int *)calloc(sizeof(int), 88);
                //printf("reallocating memory of the sequence itself\n");
                free(newSeq);
                newSeq = (char *) calloc(sizeof(char), wordLen);
            }
        }
        else{
            newSeq[index++] = nextChar;
        }
        nextChar = fgetc(filePointer);
    }
    free(asciNextSeq);
    free(newSeq);
    return 0;
}

int main(int argc, char* argv[]){
    // init word
    if(argc == 2){filePointer = fopen(argv[1], "r");}
    else{
        return 1;
    }
    char word[(WORD * sizeof(char))];
    char nextChar = fgetc(filePointer);
    int index =0;
    while(nextChar != '\n' && nextChar != '~'){
        word[index++] = nextChar;
        nextChar = fgetc(filePointer);
    }
    word[index] = '\0';
    //printf("word receive is : %s\n",word);
    // print not valid if word[0] = '\0' if needed
    if(word[0] == '\0'){
        printf("cannot find word!");
        return 1;
    }
    //printf("%s", word);
    // calculate gimatric values of the word

    int gimatryWord = 0;
    index = 0;
    int charVal;
    do {
        charVal = (int) word[index++];
        if((charVal > 96 && charVal < 123)){
            // increment small letter
            gimatryWord += (charVal-96);
        }
        else if(charVal > 64 && charVal < 91){
            // increment big letter
            gimatryWord += (charVal - 65);
        }
    }while(word[index] != '\0');
    //printf("gimatry value of the word is : %d\n ", gimatryWord);
    //enter code here:
    printf("Gematria Sequences: ");
    minSeq(gimatryWord);

    // reset to point to the first text char
    filePointer = fopen(argv[1],"r");
    while(fgetc(filePointer) != '\n'){};
    printf("\nAtbash Sequences: ");
    atBash(word);

    filePointer = fopen(argv[1],"r");
    while(fgetc(filePointer) != '\n'){};
    printf("\nAnagram Sequences: ");
    minSeqWithEmpty(word);

    fclose(filePointer);
    return 0;
}
