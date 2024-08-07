#include "../../head_file.h"

/*
ThroneInheritance t= new ThroneInheritance("king"); // 继承顺序：king
t.birth("king", "andy"); // 继承顺序：king > andy
t.birth("king", "bob"); // 继承顺序：king > andy > bob
t.birth("king", "catherine"); // 继承顺序：king > andy > bob > catherine
t.birth("andy", "matthew"); // 继承顺序：king > andy > matthew > bob > catherine
t.birth("bob", "alex"); // 继承顺序：king > andy > matthew > bob > alex > catherine
t.birth("bob", "asha"); // 继承顺序：king > andy > matthew > bob > alex > asha > catherine
t.getInheritanceOrder(); // 返回 ["king", "andy", "matthew", "bob", "alex", "asha", "catherine"]
t.death("bob"); // 继承顺序：king > andy > matthew > bob（已经去世）> alex > asha > catherine
t.getInheritanceOrder(); // 返回 ["king", "andy", "matthew", "alex", "asha", "catherine"]
 */

class ThroneInheritance {
public:
    ThroneInheritance(string kingName) : king_(kingName) {

    }

    void birth(string parentName, string childName) {
        mp_[parentName].push_back(childName);
    }

    void death(string name) {
        dead_.insert(name);
    }

    vector<string> getInheritanceOrder() {
        vector<string> res;

        function<void(const string &)> preOrder = [&](const string &parent) -> void {
            if (!dead_.count(parent)) {
                res.push_back(parent);
            }
            if (mp_.count(parent)) {
                for (const auto &child : mp_[parent]) {
                    preOrder(child);
                }
            }
        };

        preOrder(king_);
        return res;
    }

private:
    unordered_map<string, vector<string>> mp_;
    unordered_set<string> dead_;
    string king_;
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */

int main(int argc, char *argv[]) {

    return 0;
}