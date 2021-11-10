#include "reportgenerator.hpp"

using namespace std;

/*importCSV
* Imports lines from CSV and parses it into struct
* Types: 1 = blood, 2 = tissue, 3 = stool
* Requires type of file (blood, tissue, stool) and file name
*/
void RG::ReportGenerator::importCSV(string inFileName, int infileType){
    filetype = infileType;
    ifstream infile; infile.open(inFileName);
    string tmp = "";
    while(getline(infile, tmp)){
        fileLines.push_back(tmp);
    }
    //now need to parse it depending on filetype
    if(filetype == RG::filetypes::blood){
        for(int i = 0; i < fileLines.size(); i++){
            sheets->bloodreport*.importParser(fileLines.at(i));
        }
    }
    else if(filetype == RG::filetypes::tissue){
        for(int i = 0; i < fileLines.size(); i++){
            sheets->tissuereport*.importParser(fileLines.at(i));
        }
    }
    else if(filetype == RG::filetypes::stool){
        for(int i = 0; i < fileLines.size(); i++){
            sheets->stoolreport*.importParser(fileLines.at(i));
        }
    }
}

/*filterMonth
* Copies only lines from the correct month/yr into filteredLines
* Returns total # entries found
*/
int RG::ReportGenerator::filterMonth(int month, int year, int infileType){
    if(filetype == RG::filetypes::blood){
        return sheets->bloodreport*.bloodMonthFilter(month, year);
    }
    else if(filetype == RG::filetypes::tissue){
        return sheets->tissuereport*.tissueMonthFilter(month, year);
    }
    else if(filetype == RG::filetypes::stool){
        return sheets->stoolreport*.stoolMonthFilter(month, year);
    }
    return -1;
}

/*displayReport
* Prints resulting/sorted list to terminal
*/
void RG::ReportGenerator::displayReport(){
    if(filetype == RG::filetypes::blood){
        for(int i = 0; i < sheets->bloodreport*.getSortedLines().size()){
            cout << sheets->bloodreport*.getSortedLines().at(i) << '\n';
        }
    }
    else if(filetype == RG::filetypes::tissue){
        for(int i = 0; i < sheets->tissuereport*.getSortedLines().size()){
            cout << sheets->tissuereport*.getSortedLines().at(i) << '\n';
        }
    }
    else if(filetype == RG::filetypes::stool){
        for(int i = 0; i < sheets->stoolreport*.getSortedLines().size()){
            cout << sheets->stoolreport*.getSortedLines().at(i) << '\n';
        }
    }
}

/*writeReport
* Writes the resulting/sorted list to txt file
*/
void RG::ReportGenerator::writeReport(std::string outFileName){
    ofstream outfile; outfile.open(outFileName);
    if(filetype == RG::filetypes::blood){
        for(int i = 0; i < sheets->bloodreport*.getSortedLines().size()){
            outfile << sheets->bloodreport*.getSortedLines().at(i) << '\n';
        }
    }
    else if(filetype == RG::filetypes::tissue){
        for(int i = 0; i < sheets->tissuereport*.getSortedLines().size()){
            outfile << sheets->tissuereport*.getSortedLines().at(i) << '\n';
        }
    }
    else if(filetype == RG::filetypes::stool){
        for(int i = 0; i < sheets->stoolreport*.getSortedLines().size()){
            outfile << sheets->stoolreport*.getSortedLines().at(i) << '\n';
        }
    }
    outfile.close();
}

/*sort
* Sorts by option: 1) PN; 2) OncID; 3) Subject ID; 4) Timepoint; 5) Date
*/
void RG::ReportGenerator::sort(int option){
    switch (option){
        case 1:
            pnSort();
            break;
        case 2:
            oncSort();
            break;
        case 3:
            subjectSort();
            break;
        case 4:
            timeSort();
            break;
        case 5:
            dateSort();
            break;
    }
}

/*pnSort
* Sorts alphabetically by PN
*/
void RG::ReportGenerator::pnSort(){

}

/*oncSort
* Sorts numerically by Onc ID
*/
void RG::ReportGenerator::oncSort(){

}

/*subjectSort
* Sorts numerically by Subject ID
*/
void RG::ReportGenerator::subjectSort(){

}

/*timeSort
* Sorts from lowest timepoint to highest timepoint
*/
void RG::ReportGenerator::timeSort(){

}
/*dateSort
* Sorts from oldest date to most recent date
*/
void RG::ReportGenerator::dateSort(){
    if(filetype == RG::filetypes::blood){
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->bloodreport*.getFilteredLines().size(); i++){
            sheets->bloodreport*.pushSortedLines(sheets->bloodreport*.getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->bloodreport*.getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->bloodreport*.getSortedLines.size(); j++){
                if(dateCompare(sheets->bloodreport*.getSortedLines.at(j), sheets->bloodreport*.getSortedLines.at(min)) == -1){
                    min = j;
                }
                bloodswap(sheets->bloodreport*.editSortedLines().at(i), sheets->bloodreport*.editSortedLines().at(min));
            }
        }
    }
    else if(filetype == RG::filetypes::tissue){
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->tissuereport*.getFilteredLines().size(); i++){
            sheets->tissuereport*.pushSortedLines(sheets->tissuereport*.getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->tissuereport*.getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->tissuereport*.getSortedLines.size(); j++){
                if(dateCompare(sheets->tissuereport*.getSortedLines.at(j), sheets->tissuereport*.getSortedLines.at(min)) == -1){
                    min = j;
                }
                tissueswap(sheets->tissuereport*.editSortedLines().at(i), sheets->tissuereport*.editSortedLines().at(min));
            }
        }
    }
    else if(filetype == RG::filetypes::stool){
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->stoolreport*.getFilteredLines().size(); i++){
            sheets->stoolreport*.pushSortedLines(sheets->stoolreport*.getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->stoolreport*.getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->stoolreport*.getSortedLines.size(); j++){
                if(dateCompare(sheets->stoolreport*.getSortedLines.at(j), sheets->stoolreport*.getSortedLines.at(min)) == -1){
                    min = j;
                }
                stoolswap(sheets->stoolreport*.editSortedLines().at(i), sheets->stoolreport*.editSortedLines().at(min));
            }
        }
    }
}

/*dateCompare
* Compares two dates formatted as mm/dd/yyyy, m/d/yyyy, mm/d/yyyy, or m/dd/yyyy
* Returns 1 if date1 > date2, 0 if =, -1 if date1 < date2
*/
int RG::ReportGenerator::dateCompare(string date1, string date2){
    int month1, day1, year1; //number of digits in each field of date1
    month1 = day1 = year1 = 0;
    int i = 0;
    while(date1[i++] != '/'){ month1++;}
    while(date1[i++] != '/'){ day1++;}
    for(int j = i; j < date1.length(); j++){ year1++;}

    int month2, day2, year2; //number of digits in each field of date2
    month2 = day2 = year2 = 0;
    i = 0;
    while(date2[i++] != '/'){ month2++;}
    while(date2[i++] != '/'){ day2++;}
    for(int j = i; j < date2.length(); j++){ year2++;}

    //convert the fields of each date to int for easier comparison
    int month1val = stoi(date1.substr(0,month1));
    int day1val = stoi(date1.substr(month1+1,month1+1+day1));
    int year1val = stoi(date1.substr(month1+1+day1+1,date1.length()));

    int month2val = stoi(date2.substr(0,month2));
    int day2val = stoi(date2.substr(month2+1,month2+1+day2));
    int year2val = stoi(date2.substr(month2+1+day2+1,date2.length()));

    //compare years
    if(year1val > year2val) return 1;
    if(year1val < year2val) return -1;
    //i.e. years are ==, compare months
    if(month1val > month2val) return 1;
    if(month1val < month2val) return -1;
    //i.e. months & years are ==, compare days
    if(day1val > day2val) return 1;
    if(day1val < day2val) return -1;
    //i.e. months, years, & days are ==
    return 0;
}

void RG::ReportGenerator::bloodSwap(BR::EntryData* &entry1, BR::EntryData* &entry2){
    BR::EntryData* tempentry = entry1;
    entry1 = entry2;
    entry2 = tempentry;
}

void RG::ReportGenerator::tissueSwap(TR::EntryData &entry1, TR::EntryData &entry2){
    TR::EntryData* tempentry = entry1;
    entry1 = entry2;
    entry2 = tempentry;
}

void RG::ReportGenerator::stoolSwap(SR::EntryData &entry1, SR::EntryData &entry2){
    SR::EntryData* tempentry = entry1;
    entry1 = entry2;
    entry2 = tempentry;
}

RG::ReportGenerator::ReportGenerator(){
    sheets = new RG::ReportSheets;
    sheets->bloodreport = new BR::BloodReport;
    sheets->tissuereport = new TR::TissueReport;
    sheets->stoolreport = new SR::StoolReport;
}

RG::ReportGenerator::~ReportGenerator(){
    delete sheets->bloodreport; sheets->bloodreport = NULL;
    delete sheets->tissuereport; sheets->tissuereport = NULL;
    delete sheets->stoolreport; sheets->stoolreport = NULL;
    delete sheets; sheets = NULL;
}