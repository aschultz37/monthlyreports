#include "bloodreport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void BR::BloodReport::importParser(string lineIn, BR::EntryData &fieldsOut){

}

BR::BloodReport::BloodReport(){

}

BR::BloodReport::~BloodReport(){
    for(int i = 0; i < filteredLines.length(); i++){
        delete filteredLines[i];
        filteredLines[i] = NULL;
    }
    for(int i = 0; i < sortedLines.length(); i++){
        delete sortedLines[i];
        sortedLines[i] = NULL;
    }
}