/**
 * @brief
 *  this function iterates and returns the minimal sequence
 */
char *retMinSeq();
/** 
 * @brief
 * this function receives a string and returns its gimatry value
*/
int gimatryValue(char *sequence);
/** @brief 
 * This function prints all the minimal sequences with the same gimatry value as the word received */
int minSeq(int gimatryVal);
/** @brief 
 * This function prints all the minimal sequences with the same gimatry values as the word received 
 * or all  the minimal sequences which reversed "atbash" have the same gimatry values as the word received.
 */
int atBash(char * word);
/** @brief
 * This function prints all the minimal sequences which are built by the same characters as the word received
 * and ignores to empty chars but still prints them 
 */
int minSeqWithEmpty(char *word);