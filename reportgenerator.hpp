#include <iostream>
#include <fstream>
#include "bloodreport.hpp"
#include "tissuereport.hpp"
#include "stoolreport.hpp"

/*reportgenerator.hpp
* This class assumes that an input .csv has standard format.
* The .csv should be a standard Blood Processing sheet from BTIL Biospecimens.
* This class can extract and manipulate entries from a given month/year combination.
* Results can be displayed to the terminal or written to a .txt file.
*/

namespace RG{
    struct ReportSheets{ //blood, tissue, and stool sheets for each report

    };

    class ReportGenerator{
        public:
            ReportGenerator();
            ~ReportGenerator();
            
            void importCSV(std::string inFileName, int fileType);
            void displayReport(int fileType);
            void writeReport(std::string outFileName, int fileType);
            int filterMonth(std::string month, std::string year, int fileType);
            void sort(int option, int fileType);
        private:
            std::vector <std::string> fileLines;
            
            void pnSort();
            void oncSort();
            void subjectSort();
            void timeSort();
            void dateSort();
            int dateCompare(std::string date1, std::string date2);
    };
}