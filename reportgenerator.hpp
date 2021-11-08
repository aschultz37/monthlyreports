#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*reportgenerator.hpp
* This class assumes that an input .csv has standard format.
* The .csv should be a standard Blood Processing sheet from BTIL Biospecimens.
* This class can extract and manipulate entries from a given month/year combination.
* Results can be displayed to the terminal or written to a .txt file.
*/

namespace RG{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;
        std::string oncID;
        std::string studyID;
        std::string received;
        std::string date;
    };

    class ReportGenerator{
        public:
            RG::ReportGenerator();
            ~RG::ReportGenerator(){ //need to delete structs from filteredLines and sortedLines

            }
            
            void importCSV(std::string inFileName);              //imports lines from CSV and parses it into struct
            void displayReport();                                //prints resulting/sorted list to terminal
            void writeReport(std::string outFileName);           //writes the resulting/sorted list to txt file
            int filterMonth(std::string month, std::string year);//copies only lines from the correct month/yr into filteredLines; returns total # entries found
            int sort(int option);                                //sorts by option: 1) PN; 2) OncID; 3) Study ID; 4) Timepoint; 5) Date
        private:
            std::vector <std::string> fileLines;
            std::vector <RG::EntryData> filteredLines;
            std::vector <RG::EntryData> sortedLines;

            void importParser(std::string lineIn, RG::EntryData &fieldsOut);
            void pnSort();
            void oncSort();
            void studySort();
            void timeSort();
            void dateSort();
    };
}