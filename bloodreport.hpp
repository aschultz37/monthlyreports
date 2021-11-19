#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace BR{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;
        std::string oncID;
        std::string subjectID;
        std::string received;
        std::string date;
    };

    class BloodReport{
        public:
            BloodReport();
            ~BloodReport(); //delete structs from filteredLines and sortedLines
            
            std::vector <BR::EntryData*> const &getFilteredLines(){ return filteredLines;}
            std::vector <BR::EntryData*> const &getSortedLines(){ return sortedLines;}

            void pushSortedLines(BR::EntryData* input){ sortedLines.push_back(input);}

            void importParser(std::string lineIn);
            int bloodMonthFilter(int month, int year);
            void copytoSortBlood();
            void clearSort();
            void clearFiltered();
            void swapSortedLines(int index1, int index2);
        private:
            std::vector <BR::EntryData*> parsedLines;
            std::vector <BR::EntryData*> filteredLines;
            std::vector <BR::EntryData*> sortedLines;

            int extractMonth(std::string date);
            int extractYear(std::string date);
    };
}