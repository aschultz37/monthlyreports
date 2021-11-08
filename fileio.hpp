#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*This file handles general file I/O tasks across file formats*/


/*findFileLength: 
* Determines number of lines in a file (*lines)
* Return 1 if success
*/
int findFileLength(std::ifstream *inFile, int *fileLength){
    *fileLength = 0;
    std::string tmp;
    while(getline(*inFile, tmp)){
        (*fileLength)++;
    }
    return 1;
}

/*readFile: 
* Fills a string vector with lines from a file
* Return 1 if success
*/
int readFile(std::ifstream *inFile, std::vector <string> lineVec, int fileLength){
    for(int i = 0; i < fileLength; i++){
        string tmp;
        getline(*inFile, tmp);
        lineVec.push_back(tmp);
    }
    return 1;
}


/*writeFile:
* Writes a string vector to a file
* Return 1 if success, 0 if fail
*/
int writeFile(std::ofstream *outFile, std::vector <string> outAr, int fileLength){
    return 1;
}