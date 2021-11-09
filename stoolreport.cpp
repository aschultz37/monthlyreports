#include "stoolreport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void SR::StoolReport::importParser(string lineIn, SR::EntryData &fieldsOut){

}

int stoolMonthFilter(std::string month, std::string year){
    
}

SR::StoolReport::StoolReport(){

}

SR::StoolReport::~StoolReport(){
    for(int i = 0; i < filteredLines.length(); i++){
        delete filteredLines[i];
        filteredLines[i] = NULL;
    }
    for(int i = 0; i < sortedLines.length(); i++){
        delete sortedLines[i];
        sortedLines[i] = NULL;
    }
}