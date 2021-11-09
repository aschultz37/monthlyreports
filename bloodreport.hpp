#include <string>
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
            
            std::vector <BR::EntryData*> const &getSortedLines(){ return sortedLines;}

            void importParser(std::string lineIn);
            int bloodMonthFilter(std::string month, std::string year);
        private:
            std::vector <BR::EntryData*> parsedLines;
            std::vector <BR::EntryData*> filteredLines;
            std::vector <BR::EntryData*> sortedLines;
    };
}