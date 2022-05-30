#ifndef _UTILS_H_
#define _UTILS_H_
uint8_t GetFileName(char* inputPath, char *receivedName);
uint32_t masrng(char* inputArr);
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);
void splitFileName(char* sourceFileName, char *fileName, char *fileExt);
#endif
