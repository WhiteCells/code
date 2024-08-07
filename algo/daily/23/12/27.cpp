#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int isWinner(vector<int>& player1, vector<int>& player2) {
        int cnt = 0;
        for (int i = 0; i < player1.size(); ++i) {
            if (i == 1) {
                cnt += (player1[i - 1] == 10) ? 2 * player1[i] : player1[i];
                cnt -= (player2[i - 1] == 10) ? 2 * player2[i] : player2[i];
            }
            else if (i > 1) {
                cnt += (player1[i - 1] == 10 || player1[i - 2] == 10) ? 2 * player1[i] : player1[i];
                cnt -= (player2[i - 1] == 10 || player2[i - 2] == 10) ? 2 * player2[i] : player2[i];
            }
            else {
                cnt += player1[i];
                cnt -= player2[i];
            }
        }
        return cnt > 0 ? 1 : (cnt == 0 ? 0 : 2);
    }
};

int main() {
    
    return 0;
}