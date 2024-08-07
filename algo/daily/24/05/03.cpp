#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    double average(vector<int>& salary) {
        sort(salary.begin(), salary.end());
        return (double)accumulate(salary.begin() + 1, salary.end() - 1, 0) / (salary.size() - 2);
    }
};

int main() {
    
    return 0;
}