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
        std::string subjectID;
        std::string received;
        std::string date;
    };

    class ReportGenerator{
        public:
            ReportGenerator();
            ~ReportGenerator(){ //need to delete structs from filteredLines and sortedLines

            }
            
            void importCSV(std::string inFileName);
            void displayReport();
            void writeReport(std::string outFileName);
            int filterMonth(std::string month, std::string year);
            void sort(int option);
        private:
            std::vector <std::string> fileLines;
            std::vector <RG::EntryData> filteredLines;
            std::vector <RG::EntryData> sortedLines;

            void importParser(std::string lineIn, RG::EntryData &fieldsOut);
            void pnSort();
            void oncSort();
            void subjectSort();
            void timeSort();
            void dateSort();
            int dateCompare(std::string date1, std::string date2);
    };
}