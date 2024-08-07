#include "../../head_file.h"

/*
problme: 2512. 奖励最顶尖的 K 名学生

给你两个字符串数组 positive_feedback 和 negative_feedback ，分别包含表示正面的和负面的词汇。不会 有单词同时是正面的和负面的。

一开始，每位学生分数为 0 。每个正面的单词会给学生的分数 加 3 分，每个负面的词会给学生的分数 减  1 分。

给你 n 个学生的评语，用一个下标从 0 开始的字符串数组 report 和一个下标从 0 开始的整数数组 student_id 表示，其中 student_id[i] 表示这名学生的 ID ，这名学生的评语是 report[i] 。每名学生的 ID 互不相同。

给你一个整数 k ，请你返回按照得分 从高到低 最顶尖的 k 名学生。如果有多名学生分数相同，ID 越小排名越前。


示例 1：

输入：positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is studious","the student is smart"], student_id = [1,2], k = 2
输出：[1,2]
解释：
两名学生都有 1 个正面词汇，都得到 3 分，学生 1 的 ID 更小所以排名更前。

示例 2：

输入：positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is not studious","the student is smart"], student_id = [1,2], k = 2
输出：[2,1]
解释：
- ID 为 1 的学生有 1 个正面词汇和 1 个负面词汇，所以得分为 3-1=2 分。
- ID 为 2 的学生有 1 个正面词汇，得分为 3 分。
学生 2 分数更高，所以返回 [2,1] 。

提示：

    1 <= positive_feedback.length, negative_feedback.length <= 104
    1 <= positive_feedback[i].length, negative_feedback[j].length <= 100
    positive_feedback[i] 和 negative_feedback[j] 都只包含小写英文字母。
    positive_feedback 和 negative_feedback 中不会有相同单词。
    n == report.length == student_id.length
    1 <= n <= 104
    report[i] 只包含小写英文字母和空格 ' ' 。
    report[i] 中连续单词之间有单个空格隔开。
    1 <= report[i].length <= 100
    1 <= student_id[i] <= 109
    student_id[i] 的值 互不相同 。
    1 <= k <= n

url: https://leetcode.cn/problems/reward-top-k-students/description/
 */

// time complexity: O(n)
// spatial complexity: O(n)
class Solution1 {
public:
    vector<int> topStudents(vector<string> &positive_feedback, vector<string> &negative_feedback, vector<string> &report, vector<int> &student_id, int k) {
        unordered_map<string, bool> positive, negative;
        for (const auto &p : positive_feedback) {
            positive[p] = true;
        }
        for (const auto &n : negative_feedback) {
            negative[n] = false;
        }
        int n = report.size();
        unordered_map<int, int> stu; // id : score
        for (int i = 0; i < n; ++i) {
            string word;
            report[i] += ' ';
            for (int j = 0; j < report[i].size(); ++j) {
                if (' ' == report[i][j]) {
                    stu[student_id[i]] += positive.count(word) ? 3 : negative.count(word) ? -1 : 0;
                    word.clear();
                }
                else {
                    word += report[i][j];
                }
            }
            // stu[student_id[i]] += positive.count(word) ? 3 : negative.count(word) ? -1 : 0;
        }
        vector<pair<int, int>> v(stu.begin(), stu.end());
        sort(v.begin(), v.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
            return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
        });
        vector<int> res;
        for (int i = 0; i < min(k, static_cast<int>(v.size())); ++i) { // 至少 k, 避免 k >= v.size()
            res.emplace_back(v[i].first);
        }
        return res;
    }
};

// 简单优化
class Solution2 {
public:
    vector<int> topStudents(vector<string> &positive_feedback, vector<string> &negative_feedback, vector<string> &report, vector<int> &student_id, int k) {
        unordered_map<string, int> feedback;
        for (const auto &positive : positive_feedback) {
            feedback[positive] = 3;
        }
        for (const auto &negative : negative_feedback) {
            feedback[negative] = -1;
        }
        int n = report.size();
        vector<pair<int, int>> v;
        for (int i = 0; i < n; ++i) {
            stringstream ss(report[i]); // stream 空格分隔
            string word;
            int score = 0;
            while (ss >> word) {
                if (feedback.count(word)) {
                    score += feedback[word];
                }
            }
            v.emplace_back(-score, student_id[i]);
        }
        sort(v.begin(), v.end());
        vector<int> res;
        for (int i = 0; i < min(k, (int)v.size()); ++i) {
            res.emplace_back(v[i].second);
        }
        return res;
    }
};

class Solution3 {
public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {
        unordered_map<string, int> mp;
        for (const auto &positive : positive_feedback) {
            mp[positive] = 3;
        }
        for (const auto &negative : negative_feedback) {
            mp[negative] = -1;
        }
        unordered_map<int, int> stu_mp; // id : score
        for (int i = 0; i < report.size(); ++i) {
            string word;
            stu_mp[student_id[i]] = 0;
            for (int j = 0; j < report[i].size(); ++j) {
                if (' ' == report[i][j]) {
                    if (mp.count(word)) {
                        stu_mp[student_id[i]] += mp[word];
                    }
                    word.clear();
                }
                word += report[i][j];
            }
            if (mp.count(word)) {
                stu_mp[student_id[i]] += mp[word];
            }
        }
        vector<pair<int, int>> vpair(stu_mp.begin(), stu_mp.end());
        sort(vpair.begin(), vpair.end(), [&](const pair<int, int> &p1, const pair<int, int> &p2){
            return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
        });
        vector<int> res;
        for (int i = 0; i < min(k, static_cast<int>(vpair.size())); ++i) {
            res.emplace_back(vpair[i].first);
        }
        return res;
    }
};

int main() {
    vector<string> positive_feedback { "smart", "brilliant", "studious" };
    vector<string> negative_feedback { "not" };
    vector<string> report { "this student is studious", "the student is smart" };
    vector<int> student_id { 1, 2 };
    int k = 2;
    vector<int> res = Solution2().topStudents(positive_feedback, negative_feedback, report, student_id, k);
    for (const auto &ele : res) {
        cout << ele << ' ';
    }
    cout << '\n';
    return 0;
}