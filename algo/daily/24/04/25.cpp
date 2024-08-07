#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int distanceTraveled(int mainTank, int additionalTank) {
        int cnt = 0, res = 0;
        while (mainTank > 0) {
            ++cnt;
            res += 10;
            --mainTank;
            if (cnt == 5 && additionalTank > 0) {
                mainTank += 1;
                additionalTank -= 1;
                cnt = 0;
            }
        }
        return res;
    }
};

int main() {
    std::cout << Solution().distanceTraveled(5, 10) << std::endl;
    return 0;
}