#include "../../head_file.h"

/*
problme: 2337. 移动片段得到字符串
给你两个字符串 start 和 target ，长度均为 n 。每个字符串 仅 由字符 'L'、'R' 和 '_' 组成，其中：
    字符 'L' 和 'R' 表示片段，其中片段 'L' 只有在其左侧直接存在一个 空位 时才能向 左 移动，而片段 'R' 只有在其右侧直接存在一个 空位 时才能向 右 移动。
    字符 '_' 表示可以被 任意 'L' 或 'R' 片段占据的空位。
如果在移动字符串 start 中的片段任意次之后可以得到字符串 target ，返回 true ；否则，返回 false 。
输入：start = "_L__R__R_", target = "L______RR"
输出：true
解释：可以从字符串 start 获得 target ，需要进行下面的移动：
- 将第一个片段向左移动一步，字符串现在变为 "L___R__R_" 。
- 将最后一个片段向右移动一步，字符串现在变为 "L___R___R" 。
- 将第二个片段向右移动散步，字符串现在变为 "L______RR" 。
可以从字符串 start 得到 target ，所以返回 true 。
输入：start = "_R", target = "R_"
输出：false
解释：字符串 start 中的片段只能向右移动，所以无法从字符串 start 得到 target 。
提示：
    n == start.length == target.length
    1 <= n <= 10^5
    start 和 target 由字符 'L'、'R' 和 '_' 组成
url: https://leetcode.cn/problems/move-pieces-to-obtain-a-string/
@Author: Eorys
@Date: 2023-08-21 07:15:08
@Last Modified by: Eorys
@Last Modified time: 2023-08-21 07:15:08
@Description:
*/

/*
如果 start 可以转化为 target:
1. 从左至右出现的 'L' 和 'R' 的顺序必须相同
2. start 中出现的 'L' 必须在 target 对应的 'L' 的右侧 ('L' 只能向左移动)，start 中出现的 'R' 必须在 target 对应的 'R' 的左侧 ('R' 只能向右移动)

运用双指针 i、j 同时遍历 start、target
指针指向 '_':
    跳过
指针都指向 'L' 或 'R' 时:
    字符为 'L':
        i < j  返回 false ('L' 只能向左移动)
    字符为 'R':
        i > j  返回 false ('R' 只能向右移动)
指针指向字符不相等:
    返回 false

最后要考虑 i、j 没有将 start、target 遍历完的情况，如果 start、target 中还有 'L' 或者 'R' 则 start 无法转换为 target
 */
class Solution {
public:
    bool canChange(string start, string target) {
        int i = 0, j = 0, n = start.size();
        while (i < n && j < n) {
            while (i < n && '_' == start[i]) {
                ++i;
            }
            while (j < n && '_' == target[j]) {
                ++j;
            }
            if (i < n && j < n) {
                if (start[i] != target[j]) {
                    return false;
                }
                // L 要在目标位置的右边，R 要在目标位置的左边
                else if ('L' == start[i] && i < j || 'R' == start[i] && i > j) {
                    return false;
                }
                ++i;
                ++j;
            }
        }
        while (i < n) {
            if (start[i] != '_') {
                return false;
            }
            ++i;
        }
        while (j < n) {
            if (target[j] != '_') {
                return false;
            }
            ++j;
        }
        return true;
    }
};

int main() {
    string start = "_L__R__R_";
    string target = "L______RR";
    Solution s;
    cout << s.canChange(start, target) << '\n';
    return 0;
}