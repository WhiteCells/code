#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        long long cnt = 12, n = 2, edge = 2;
        while (cnt < neededApples) {
            cnt += pow(n++, 2) * 12;
            edge += 2;
        }
        return edge * 4;
    }
};

int main() {
    cout << Solution().minimumPerimeter(2784381467700) << endl; // 70896
    cout << Solution().minimumPerimeter(1000000000) << endl; // 5040
    cout << Solution().minimumPerimeter(13) << endl; // 16
    cout << Solution().minimumPerimeter(15) << endl; // 16
    return 0;
}