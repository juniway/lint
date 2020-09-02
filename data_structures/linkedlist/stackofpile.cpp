#include <vector>
using namespace std;

class StackOfPlates {
public:
    StackOfPlates(int cap) {
        stackSize = cap;
    }

    void push(int val) {
        if (stackSize <= 0) return;
        if (stacks.empty() || stacks.back().size() >= stackSize) {
            stacks.push_back({val});
        } else {
            stacks.back().push_back(val);
        }
    }

    int pop() {
        if (stacks.empty()) return -1;
        int topVal = stacks.back().back();
        stacks.back().pop_back();
        if (stacks.back().empty())
            stacks.pop_back();
        return topVal;
    }

    int popAt(int index) {
        if (stacks.empty()) return -1;
        if (index < stacks.size()) {
            if (!stacks[index].empty()) {
                int val = stacks[index].back();
                stacks[index].pop_back();
                if (stacks[index].empty())
                    stacks.erase(stacks.begin() + index);
                return val;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
private:
    vector<vector<int>> stacks;
    int stackSize;
};
