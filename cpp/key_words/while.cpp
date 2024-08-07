//https://ac.nowcoder.com/acm/contest/60282/B
// int main() {
//     string s;
//     cin >> s;
//     int i = 0, j = s.size() - 1, cnt = 0;
//     while (i++ < j--) {
//         if ('?' == s[i] && '?' == s[j]) {
//             cnt += 26;
//         }
//         else if ('?' == s[i] || '?' == s[j]) {
//             cnt += 1;
//         }
//         else {
//             return 0;
//         }
//     }
//     if ('?' == s[s.size() / 2]) {
//         cnt += 26;
//     }
//     cout << cnt;
//     return 0;
// }