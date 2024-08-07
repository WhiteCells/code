#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/maximum-points-inside-the-square/
 */

class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        vector<int> min_point_radius(26, INT_MAX);
        int min_radius = INT_MAX;
        for (int i = 0; i < points.size(); ++i) {
            int x = points[i][0], y = points[i][1];
            int cur_radius = max(abs(x), abs(y));
            int c = s[i] - 'a';
            if (cur_radius < min_point_radius[c]) {
                min_radius = min(min_radius, cur_radius);
                min_point_radius[c] = min_radius;
            } else if (cur_radius < min_radius) {
                min_radius = cur_radius;
            }
        }
        int res = 0;
        for (const auto &radius : min_point_radius) {
            if (radius <= min_radius) {
                ++res;
            }
        }
        return res;
    }
};

class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        vector<int> min_point_radius(26, INT_MAX);
        int min_radius = INT_MAX;
        for (int i = 0; i < points.size(); ++i) {
            int x = points[i][0], y = points[i][1];
            int cur_radius = max(abs(x), abs(y));
            int c = s[i] - 'a';
            if (cur_radius < min_point_radius[c]) {
                min_radius = min(min_radius, min_point_radius[c]);
                min_point_radius[c] = cur_radius;
            } else if (cur_radius < min_radius) {
                min_radius = cur_radius;
            }
        }
        int res = 0;
        for (const auto &radius : min_point_radius) {
            if (radius < min_radius) {
                ++res;
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}