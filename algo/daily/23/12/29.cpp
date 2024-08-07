#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int buyChoco(vector<int>& prices, int money) {
        int cost = INT_MAX;
        for (int i = 0; i < prices.size(); ++i) {
            for (int j = i + 1; j < prices.size(); ++j) {
                if (prices[i] + prices[j] <= money) {
                    cost = min(cost, (prices[i] + prices[j]));
                }
            }
        }
        return money - cost < 0 ? money : money - cost;
    }
};

int main() {
    vector<int> prices {1, 2, 2};
    int money = 3;
    cout << Solution().buyChoco(prices, money) << endl;
    return 0;
}