#include <iostream>
#include "csv.h"

int main(){
    io::CSVReader<6> in("example.csv");
    in.read_header(io::ignore_extra_column, "studentId", "hw1", "hw2", "hw3", "midterm", "finalexam");
    std::string studentId; int hw1, hw2, hw3, midterm, finalexam;
    while(in.read_row(studentId, hw1, hw2, hw3, midterm, finalexam)) {
        std::cout << studentId << ", " 
                    << hw1 << ", " 
                    << hw2 << ", " 
                    << hw3 << ", " 
                    << midterm << ". " 
                    << finalexam << std::endl;
    }
}
