#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        int res = 0;
        for (int i = 0; i < startTime.size(); ++i) {
            if (queryTime >= startTime[i] && queryTime <= endTime[i]) {
                ++res;
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}