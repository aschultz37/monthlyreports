#include "stoolreport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void SR::StoolReport::importParser(string lineIn, SR::EntryData &fieldsOut){

}

/*stoolMonthFilter
* Filters parsedLines by month and year, putting valid entries into filteredLines
* Returns the number of entries in that month/year
*/
int SR::StoolReport::stoolMonthFilter(int month, int year){
    int counter = 0;
    for(int i = 0; i < parsedLines.length(); i++){
        if(extractMonth(parsedLines.at(i)->date) == month && extractYear(parsedLines.at(i)->date) == year){
            filteredLines.push_back(parsedLines.at(i));
            counter++;
        }
    }
    return counter;
}

/*extractMonth
* Returns the month (as an integer) as extracted from a date (string) of format m/d/y
*/
int SR::StoolReport::extractMonth(string date){
    char delimiter = '/'; 
    int i = 0; string month = "";
    while(date[i] != delimiter){ month.append(date[i++]);}
    return stoi(month);
}

/*extractYear
* Returns the year (as an integer) as extracted from a date (string) of format m/d/y
*/
int SR::StoolReport::extractYear(string date){
    char delimiter = '/'; 
    int i = 0; string year = "";
    while(date[i++] != delimiter){} //thru month
    i++; //skip /
    while(date[i++] != delimiter){} //thru day
    i++; //skip /
    while(date[i] < date.length()){ year.append(date[i++]);}
    return stoi(year);
}

SR::StoolReport::StoolReport(){

}

SR::StoolReport::~StoolReport(){
    for(int i = 0; i < parsedLines.length(); i++){
        delete parsedLines[i];
        parsedLines[i] = NULL;
    }
    for(int i = 0; i < filteredLines.length(); i++){
        delete filteredLines[i];
        filteredLines[i] = NULL;
    }
    for(int i = 0; i < sortedLines.length(); i++){
        delete sortedLines[i];
        sortedLines[i] = NULL;
    }
}