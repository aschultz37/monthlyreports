#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace SR{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;
        std::string oncID;
        std::string subjectID;
        std::string stoolID;
        std::string received;
        std::string date;
    };

    class StoolReport{
        public:
            StoolReport();
            ~StoolReport(); //delete structs from filteredLines and sortedLines
           
            std::vector <SR::EntryData*> const &getFilteredLines(){ return filteredLines;}
            std::vector <SR::EntryData*> const &getSortedLines(){ return sortedLines;}
            std::vector <SR::EntryData*> const &getParsedLines(){ return parsedLines;}

            void pushSortedLines(SR::EntryData* input){ sortedLines.push_back(input);}

            void importParser(std::string lineIn);
            int stoolMonthFilter(int month, int year);
            void copytoSortStool();
            void clearSort();
            void clearFiltered();
            void swapSortedLines(int index1, int index2);
            bool isEmpty(int index);
        private:
            std::vector <SR::EntryData*> parsedLines;
            std::vector <SR::EntryData*> filteredLines;
            std::vector <SR::EntryData*> sortedLines;

            int extractMonth(std::string date);
            int extractYear(std::string date);
    };
}