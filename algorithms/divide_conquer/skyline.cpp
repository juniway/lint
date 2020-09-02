#include <iostream>

struct Building {
    int left, ht, right;
};

class Strip {
    int left, ht;
public:
    Strip(int l = 0, int h = 0) :left(l), ht(h) {}
    friend class Skyline;
};

class Skyline {
public:
    Skyline ();
    // Skyline *Merge(Skyline *other);
    Skyline (int cap) {
        capacity = cap;
        arr = new Strip[cap];
        n = 0;
    }

    void append(Strip *st) {
        if (n > 0 && arr[n - 1].ht == st->ht) return;
        if (n > 0 && arr[n-1].left == st->left) {
            arr[n-1].ht = std::max(arr[n-1].ht, st->ht);
        }

        arr[n] = *st;
        n++;
    }

    void print() {
        for(int i = 0; i < n; i++) {
            std::cout << " (" << arr[i].left << ", " << arr[i].ht << "), ";
        }
    }


    Skyline *Merge(Skyline *other) {
        Skyline *res = new Skyline(n + other->n);
        int h1 = 0, h2 = 0;
        int i = 0, j = 0;
        while(i < n && j < other->n) {
            if (arr[i].left < other->arr[j].left) {
                int x1 = arr[i].left;
                h1 = arr[i].ht;

                int maxh = std::max(h1, h2);
                res->append(new Strip(x1, maxh));
                i++;
            }
            else {
                int x2 = other->arr[j].left;
                h2 = other->arr[j].ht;
                int maxh = std::max(h1, h2);
                res->append(new Strip(x2, maxh));
                j++;
            }
        }

        while (i < n) {
            res->append(&arr[i]);
            i++;
        }

        while (j < other->n) {
            res->append(&other->arr[j]);
            j++;
        }

        return res;
    }

    int count() {return n;}
    ~Skyline () {delete [] arr;}

private:
    Strip *arr;
    int capacity;
    int n;
};

Skyline* findSkyline(Building arr[], int l, int h) {
    if (l == h) {
        Skyline* res = new Skyline(2);
        res->append(new Strip(arr[l].left, arr[l].ht));
        res->append(new Strip(arr[l].right, 0));
        return res;
    }

    int mid = (l+h) / 2;
    Skyline* sl = findSkyline(arr, l, mid);
    Skyline* sr = findSkyline(arr, mid + 1, h);
    Skyline *res = sl->Merge(sr);

    delete sl;
    delete sr;

    return res;
}

int main(int argc, char *argv[]) {
    Building arr[] = {
        {1, 11, 5}, {2, 6, 7}, {3, 13, 9}
    };
    int n = sizeof (arr) / sizeof (arr[0]);

    Skyline *ptr = findSkyline(arr, 0, n - 1);
    ptr->print();
    return 0;
}
