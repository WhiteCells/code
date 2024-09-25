#include "../../head_file.h"

/*
problme:

url:
 */

class Solution
{
public:
    string clearDigits(string s)
    {
        int digits_num = 0;
        int n = s.size();
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] >= '0' && s[i] <= '9') {
                s.erase(i, 1);
                ++digits_num;
            }
            else {
                if (digits_num > 0) {
                    s.erase(i, 1);
                    --digits_num;
                }
            }
            std::cout << s << std::endl;
        }
        return s;
    }
};

int main()
{
    cout << Solution().clearDigits("a8f") << endl;
    return 0;
}