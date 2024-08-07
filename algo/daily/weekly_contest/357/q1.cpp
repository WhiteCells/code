#include <iostream>
#include <string>

using namespace std;

class Solution{
public:
    string finalString(string s){
        string ans;
        for(auto& c : s){
            if('i' == c){
                for(int i = 0; i < ans.size() / 2; ++i){
                    auto tmp = ans[i];
                    ans[i] = ans[ans.size() - 1 - i];
                    ans[ans.size() - 1 - i] = tmp;
                }
            }
            else{
                ans += c;
            }
        }
        return ans;
    }
};

int main(){
    string str = "poiinter";
    Solution s;
    cout << s.finalString(str) << '\n';
    return 0;
}