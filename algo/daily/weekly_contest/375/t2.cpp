#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<int> getGoodIndices(vector<vector<int>> &variables, int target) {
        vector<int> res;
        for (int i = 0; i < variables.size(); ++i) {
            int a = variables[i][0], b = variables[i][1],
                c = variables[i][2], m = variables[i][3];
            a %= 10;
            b %= 4;
            if (b == 0) {
                b = 4;
            }
            c %= m;
            if ((int)pow((int)pow(a, b) % 10, c) % m == target) {
                res.push_back(i);
            }
        }
        return res;
    }
};
int main() {
    // [2,3,3,10],[3,3,3,1],[6,1,1,4]], target = 2
    // vector<vector<int>> v {
    //     {2, 3, 3, 10},
    //     {3, 3, 3, 1},
    //     {6, 1, 1, 4},
    // };
    // int t = 2;

    // vector<vector<int>> v {
    //     {4, 4, 3, 2},
    // };
    // int t = 1;

    // vector<vector<int>> v {
    //     {4, 10, 5, 8},
    //     {8, 8, 9, 8},
    //     {7, 1, 5, 4},
    //     {8, 9, 2, 2},
    //     {2, 2, 8, 7},
    //     {6, 8, 10, 3},
    //     {6, 8, 4, 4},
    //     {5, 4, 10, 5},
    //     {3, 7, 8, 2},
    // };
    // int t = 1;

    // vector<vector<int>> v {
    //     {4, 10, 5, 8},
    //     {7, 7, 5, 8},
    //     {4, 8, 6, 2},
    //     {6, 3, 3, 2},
    // };
    // int t = 4;

    vector<vector<int>> v {
        // {4, 8, 6, 8},
        {2, 2, 2, 2},
    };
    int t = 0;
    auto res = Solution().getGoodIndices(v, t);
    for (auto i : res) {
        cout << i << " ";
    }
    return 0;
}