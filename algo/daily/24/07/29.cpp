#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    int calPoints(vector<string> &operations) {
        int res = 0;
        vector<int> v;
        for (size_t i = 0; i < operations.size(); ++i) {
            if (operations[i][0] == '-' || (operations[i][0] >= '0' && operations[i][0] <= '9')) {
                int num = stoi(operations[i]);
                res += num;
                v.push_back(num);
            } else if (operations[i] == "+") {
                int num = v[v.size() - 1] + v[v.size() - 2];
                res += num;
                v.push_back(num);
            } else if (operations[i] == "D") {
                int num = v[v.size() - 1] * 2;
                res += num;
                v.push_back(num);
            } else if (operations[i] == "C") {
                res -= v[v.size() - 1];
                v.pop_back();
            }
        }
        return res;
    }
};

int main() {
    vector<string> opt {"5","-2","4","C","D","9","+","+"};
    std::cout << Solution().calPoints(opt);
    return 0;
}