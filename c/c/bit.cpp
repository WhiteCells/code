#include <iostream>

/*
使用 char 1 byte = 8 bit
 */

#define ALGORITHM_DESIGN                0b00000001
#define COLLEGE_PHYSICS                 0b00000010
#define COLLEGE_ENGLISH                 0b00000100
#define COMPUTER_NETWORK                0b00001000
#define ELECTRONIC_TECHNOLOGY           0b00010000
#define COMPUTER_COMPOSITION            0b00100000
#define COMPUTER_OPERATING_SYSTEM       0b01000000
#define DATA_STRUCTURE_BUDGETING_METHOD 0b10000000


void SelectCourse(char *student, char course) {
    *student |= course;
}

void WithdrawalCourse(char *student, char course) {
    *student &= ~course;
}

bool QueryCourse(char *student, char course) {
    return *student & course;
}

void PrintSelectedCourse(char *student) {
    int mask = 1;
    for (int i = 0; i < 8; ++i, mask <<= 1) {
        int bit = *student & mask;
        switch (bit) {
            case ALGORITHM_DESIGN:
                std::cout << "ALGORITHM_DESIGN" << std::endl;
                break;
            case COLLEGE_PHYSICS:
                std::cout << "COLLEGE_PHYSICS" << std::endl;
                break;
            case COLLEGE_ENGLISH:
                std::cout << "COLLEGE_ENGLISH" << std::endl;
                break;
            case COMPUTER_NETWORK:
                std::cout << "COMPUTER_NETWORK" << std::endl;
                break;
            case ELECTRONIC_TECHNOLOGY:
                std::cout << "ELECTRONIC_TECHNOLOGY" << std::endl;
                break;
            case COMPUTER_COMPOSITION:
                std::cout << "COMPUTER_COMPOSITION" << std::endl;
                break;
            case COMPUTER_OPERATING_SYSTEM:
                std::cout << "COMPUTER_OPERATING_SYSTEM" << std::endl;
                break;
            case DATA_STRUCTURE_BUDGETING_METHOD:
                std::cout << "DATA_STRUCTURE_BUDGETING_METHOD" << std::endl;
                break;
            default:
                break;
        }
    }
}

int main() {
    char student = 0;
    SelectCourse(&student, ALGORITHM_DESIGN);
    SelectCourse(&student, COLLEGE_ENGLISH);
    SelectCourse(&student, COMPUTER_OPERATING_SYSTEM);
    SelectCourse(&student, ELECTRONIC_TECHNOLOGY);

    if (QueryCourse(&student, COLLEGE_ENGLISH)) {
        std::cout << "the student choose ELECTRONIC_TECHNOLOGY" << '\n';
    } else {
        std::cout << "students did not choose ELECTRONIC_TECHNOLOGY" << '\n';
    }

    WithdrawalCourse(&student, COLLEGE_ENGLISH);
    if (QueryCourse(&student, COLLEGE_ENGLISH)) {
        std::cout << "the student chose ELECTRONIC_TECHNOLOGY" << '\n';
    } else {
        std::cout << "student did not choose ELECTRONIC_TECHNOLOGY" << '\n';
    }
    PrintSelectedCourse(&student);
    return 0;
}