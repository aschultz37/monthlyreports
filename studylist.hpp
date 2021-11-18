#include <string>
#include <vector>

namespace SL{
    //list of studies
    std::vector <std::string> studyNums = {"20028", 
                                        "17455", 
                                        "13325", 
                                        "18394", 
                                        "18634", 
                                        "20068", 
                                        "18617", 
                                        "20166", 
                                        "20153", 
                                        "20371", 
                                        "19672", 
                                        "93085"};
    //list of timepoints for each study (keyed to studyNums vector)
    std::vector <std::vector <std::string>> timepoints = {{"baseline", "c2d1", "c4d1", "eot", "recurrence"},
                                                        {"c1d1", "c1d8", "c1d15", "c3d1", "eot", "c7d1", "co-c1d1", "co-c1d15", "co-eot"},
                                                        {"s1", "s2", "s3", "s4", "s5"},
                                                        {"baseline", "pre-op", "post-op", "final 3 months hp", "recurrence"},
                                                        {"baseline", "1 year", "2 year", "3 year", "4 year", "5 year"},
                                                        {"baseline", "c2d1", "c4d1", "post-op", "eot", "recurrence"},
                                                        {"baseline", "on nac", "pre-op", "post-op"},
                                                        {"baseline", "c1d1", "c4d1", "c7d1", "c8d1", "c9d1", "c10d1", "c13d1", "c14d1", "c16d1", "c19d1", "c22d1", "c25d1", "eot"},
                                                        {"baseline", "c1d1", "c4d1", "c7d1", "c8d1", "c9d1", "c10d1", "c13d1", "c14d1", "c16d1", "c19d1", "c22d1", "c25d1", "eot"},
                                                        {"baseline", "c2d1", "c3d1", "c4d1", "c5d1", "c6d1", "pre-op", "eot", "recurrence"},
                                                        {},
                                                        {"s1", "s2", "s3", "s4", "s5"}};
}