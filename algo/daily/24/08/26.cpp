#include "../../head_file.h"

/*
problme:

url:
 */

// Definition for Employee.
class Employee
{
public:
    int id;
    int importance;
    vector<int> subordinates;
};

class Solution
{
public:
    int res = 0;
    int getImportance(vector<Employee *> employees, int id)
    {
        int res = 0;
        unordered_map<int, pair<int, vector<int>>> employee;
        vector<int> subid;
        for (const auto &e : employees) {
            employee[e->id] = {e->importance, e->subordinates};
            if (e->id == id) {
                res += e->importance;
                subid = e->subordinates;
            }
        }
        function<void(const vector<int> &)> dfs = [&](const vector<int> &subids) -> void {
            for (const auto &s : subids) {
                res += employee[s].first;
                dfs(employee[s].second);
            }
        };
        dfs(subid);
        return res;
    }
};

int main()
{

    return 0;
}