#include <stdio.h>
#include <stdlib.h>
# include <string.h>
#define WORD 30
#define TXT 1024
// read from a file here:
FILE *filePointer, *outPointer;

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
int minSeq(int gimatryVal,char * text){
    // iterate untill geting useless value and then check gimatry 
    // if equals then print, else throw the sequence and start again
    int index1=0, index2=0, wordIndex = 0, first =1;
    //printf("hello im minseq\n");
    char *word = (char *) calloc(sizeof(char), WORD);
    //printf("The text is : %s\n",text);
    int GimatryWordVal=0, currentCharVal = 0;
    while(text[index1] != '\0'|| text[index2] == '~'){
        currentCharVal = (int)text[index1];
        // get the next character that is not an empty char
        while((currentCharVal < 65 || (currentCharVal > 90 && currentCharVal < 97) || currentCharVal > 122)
         && text[index1] != '~'){
            index1+=1;
            currentCharVal = text[index1];
        }
        word[wordIndex++] = text[index1];
        if(text[index1] == '~') 
            break;
        if(65 <= currentCharVal && currentCharVal <= 90){
            GimatryWordVal += (currentCharVal -65 +1);
        }
        else if(97 <= currentCharVal && currentCharVal <= 122){
            GimatryWordVal += (currentCharVal - 97 +1);
        }
        // printf("The current character is : %c\n", text[index1]);
        // printf("The Current Gimatry Value is : %d\n", GimatryWordVal );
        index2 = index1 +1;
        // printf("text at index1 is : %c\n", text[index1]);
        // printf("text at index2 is : %c\n", text[index2]);
        while(text[index2] != '\0' && text[index2] != '~'){
            if(GimatryWordVal < gimatryVal){
               // increment gimatry value
                // printf("The current char is : %c\n", text[index2]);
                // printf("The gimatry value is : %d\n", GimatryWordVal);
                currentCharVal = (int)text[index2];
                //printf("The ascii value of the char is : %d", currentCharVal);
                if(65 <= currentCharVal && currentCharVal <= 90){
                    GimatryWordVal += (currentCharVal -65 +1);
                }
                else if(97 <= currentCharVal && currentCharVal <= 122){
                    GimatryWordVal += (currentCharVal - 97 +1);
                }
                word[wordIndex++] = text[index2];
            }
            //
            if(GimatryWordVal == gimatryVal){
                //printf("printing the word\n");
                if(first == 1){
                    fprintf(outPointer,"%s", word);first=0;
                }
                else
                    fprintf(outPointer,"~%s", word);
                free(word);
                word = (char *)calloc(sizeof(char), WORD);
                wordIndex=0;
                GimatryWordVal = 0;
                break;
            }
            if(GimatryWordVal > gimatryVal){
                // reset word
                free(word);
                word = (char *)calloc(sizeof(char), WORD);
                GimatryWordVal = 0;
                wordIndex = 0;
                break;
            }
            index2++;
        }
        
        index1++;
    }
    //word[0] = 's';
    free(word);
    //free(text);
    return 0;


}

int atBash(char * word, char * text){
    char c = word[0];
    int currentCharIndex=0;
    int wordLength = 0;
    int  index=0;
    while(c != '\0'){
        (wordLength)+=1;
        c = word[++index];
    }
    char * atbashWord = (char *) calloc(sizeof(char), (wordLength+1));
    char * reverseAtbashWord = (char *) calloc(sizeof(char), (wordLength+1));
    int currentIndex =0;
    int currCharValue;
    //init the atbash word
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
       // printf("current char is %d\n", word[currentIndex]);
        if(word[currentIndex] == '\0'){
            break;
        }
    }
    atbashWord[currentIndex] = '\0';
    currentIndex = 0; index = wordLength-1;
    //printf("getting the reverse atbash values, index is : %d\n",index);
    while(index >=0 ){
        //printf("The current char is : %c\n",atbashWord[index]);
        reverseAtbashWord[currentIndex++] = atbashWord[index--];
    }
    reverseAtbashWord[currentIndex] = '\0';
    //printf("Reverse atbash is : %s\n", reverseAtbashWord);
    char nextChar = text[currentCharIndex++];
    //printf("this char is : %c", nextChar);
    int index1=0,index2=0,first =1;

    while(nextChar != '~'){
       //printf("Current char is : %d\n", nextChar);
        if(nextChar != ' ' || nextChar != '\n' || nextChar != '\t'){
            if(nextChar == atbashWord[index1]){
                index1++;
            }
            else{
                index1 = 0;
            }
            if(nextChar == reverseAtbashWord[index2]){
                index2++;
            }
            else{
                index2 = 0;
            }
        }
        if(index1 == (wordLength)){
            if(first == 1){
                fprintf(outPointer,"%s",atbashWord);first = 0;
            }
            else{
                fprintf(outPointer,"~%s", atbashWord);
            }
        }
        if(index2 == (wordLength)){
            if(first == 1){
                fprintf(outPointer,"%s",reverseAtbashWord);first = 0;
            }
            else{
                fprintf(outPointer,"~%s", reverseAtbashWord);
            }
        }
        nextChar = text[currentCharIndex++];
    }
    free(atbashWord);
    free(reverseAtbashWord);
    return 0;
}

int minSeqWithEmpty(char *wordABC, char * text){
    //printf("received word : %s\n", wordABC);
    int currentCharIndex=0;
    int *asciWord = (int *) calloc(sizeof(int), 143), *asciNextSeq = (int *) calloc(sizeof(int), 143);
    char nextChar = wordABC[0];
    int charVal, wordLen=0, index=1;
    // init the word's asci value chart
    if(nextChar == '\0')
        return 0;
    while(nextChar != '\0'){
        charVal = (int) nextChar;
        if(charVal >= 33 && charVal <= 175){
            asciWord[charVal-33] +=1;
            wordLen+=1;
        }
        //printf("got nextChar of value of %c\n", nextChar);
        nextChar = wordABC[index++];
        
    }
    nextChar = text[currentCharIndex++];
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
        if(nextChar != ' ' && nextChar != '\n' && nextChar != '\t'){
            charVal = (int)nextChar;
            // printf("current char is : %c\n", nextChar);
            // printf("asciWord value at : %d, is : %d   ", charVal-33, asciWord[charVal-33]);
            // printf("asci value as aciNextSeq at %d, is : %d\n", charVal-33, asciNextSeq[charVal-33]);
            if(asciWord[charVal-33] > asciNextSeq[charVal-33]){
                // printf("asciWord at index %c, is : %d\n", charVal, asciWord[charVal-33]);
                // printf("asciNextSeq at index %c, is : %d\n ", charVal, asciNextSeq[charVal-33]);
                asciNextSeq[charVal-33] +=1;
                newSeq[index++] = nextChar;
                lenSeq+=1;
                //printf("incrementing value by 1 to %c\n",nextChar);
            }
            else{
                lenSeq = 0; index=0;
                //printf("reallocating memory of sequence's asci chart\n");
                free(asciNextSeq);
                asciNextSeq = (int *)calloc(sizeof(int), 88);
                //printf("reallocating memory of the sequence itself\n");
                free(newSeq);
                newSeq = (char *) calloc(sizeof(char), wordLen);
            }
        }
        if(lenSeq == wordLen){
            newSeq[index] = '\0';
            lenSeq = 0;
            if(first == 1){
                fprintf(outPointer,"%s", newSeq); first = 0 ;
            }
            else{
                fprintf(outPointer,"~%s", newSeq);
            }
            free(asciNextSeq);
            asciNextSeq = (int *)calloc(sizeof(int), 143);
        }
        nextChar = text[currentCharIndex++];
    }
    free(asciNextSeq);
    free(newSeq);
    return 0;
}

int main(int argc, char* argv[]){
    // init word
    filePointer = stdin;
    outPointer = stdout;
    char word[(WORD * sizeof(char))];
    char nextChar = fgetc(filePointer);
    char text[TXT], text1[TXT], text2[TXT];
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
    index = 0;
    nextChar = fgetc(filePointer);
    while(nextChar != '~'){
        text[index++] = nextChar;
        nextChar = fgetc(filePointer);
    }
    text[index] = '~';
    //printf(" The text received is : %s\n",text);
    strcpy(text1,text);
    strcpy(text2,text);
    int gimatryWord = 0;
    index = 0;
    int charVal;
    //printf("setting the word");
    do {
        charVal = (int) word[index++];
        if((charVal > 96 && charVal < 123)){
            // increment small letter
            gimatryWord += (charVal-96);
        }
        else if(charVal > 64 && charVal < 91){
            // increment big letter
            gimatryWord += (charVal - 64);
        }
    }while(word[index] != '\0');
    //printf("gimatry value of the word is : %d\n ", gimatryWord);
    //enter code here:
    //filePointer = fopen(argv[1],"r");
    fprintf(outPointer,"Gematria Sequences: ");
    minSeq(gimatryWord,text);
    //printf("%c",fgetc(filePointer));

    // reset to point to the first text char
    //filePointer = stdin;
    //while(fgetc(filePointer) != '\n'){};
    fprintf(outPointer,"\nAtbash Sequences: ");
    atBash(word,text1);

    //filePointer = stdin;
    //while(fgetc(filePointer) != '\n'){};
    fprintf(outPointer,"\nAnagram Sequences: ");
    minSeqWithEmpty(word,text2);

    fclose(filePointer);
    return 0;
}
