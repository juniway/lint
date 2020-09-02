#include <iostream>

struct Item {
    int value, weight;
    Item(int v, int w) : value(v), weight(w){}
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// greedy approach
double knapsackFractional(int W, Item a[], int n) {
    std::sort(a, a+n, cmp);
    int curWeight = 0;
    double finalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (curWeight + a[i].weight <= W) {
            curWeight += a[i].weight;
            finalValue += a[i].value;
        } else {
            int remain = W - curWeight;
            finalValue += a[i].value;
            break;
        }
    }

    return finalValue;
}

void testKnapsackFractional() {
    int W = 50;
    Item a[] = {
        {60, 10},
        {100, 21},
        {120, 30},
    };

    int n = (sizeof a) / sizeof a[0];
    int res = knapsackFractional(W, a, n);
    std::cout << res << std::endl;
}

int main(int argc, char *argv[]) {
    testKnapsackFractional();
    return 0;
}
