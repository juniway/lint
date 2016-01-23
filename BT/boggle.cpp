// Analysis:
Unless you need to (e.g., for homework) don't use recursion for this.
Instead, pre-process your word list into equivalents with the letters sorted. 
Build a multimap from sorted letters to the words you can represent with a group of letters.
When the player picks out a proposed work, take the letters, sort them, look that up in your map, 
and see if one of the results matches what they entered. That'll essentially always be such a 
small number of entries that you can do a simple string comparison for each.
Another possibility would be to build your word list into a trie. This will definitely be more work. 
It will almost certainly save memory, and probably make lookups minutely faster as well 
-- but unless you're going to run a boggle web site so the computer is going to play 
against thousands of people at once, that's unlikely to matter.

// http://stackoverflow.com/questions/4313971/how-can-i-find-words-in-matrix-of-letters/4314056#4314056
Better Solution:
build a search tree for the dictionary (one level per letter)
for each position in the grid, start searching through the index, 
one character at a time, and proceed in each allowed direction 
until there are no entries left in the index, or you hit a grid boundary

The most appropriate solution depends a lot on the constraints you expect to be dealing with. 
How large is your dictionary? How large is your crossword.
I'd suggest taking a look at Suffix trees. 
You can insert all the dictionary words into one. 
Then search the suffix tree for the rows, columns and diagonals. 
For the rows, start a search from the root of the tree for the first letter in each row 
and iterate through the tree as you pass through the row. Do the same from right to left if necessary. 
Similar story for columns and diagonals.
Tree construction is O(N) and consumes O(N) space, where N is the size of your dictionary in characters. 
Searching will then take O(PQ) time, where your crossword is of size PxQ. 
Giving an overall runtime of O(N+PQ) and space of O(N).
The thing is, though, suffix trees are a pain to implement. They really are. 
So you might prefer settling for a simple Trie, which will give you a total runtime of O(N+PQ(max(P,Q)).

// http://www.danvk.org/wp/2007-02-04/moving-boggle-to-c/
// http://stackoverflow.com/questions/746082/how-to-find-list-of-possible-words-from-a-letter-matrix-boggle-solver
// http://www.cs.northwestern.edu/academics/courses/311/hw/boggle.html
// https://github.com/AnthonyB28/BoggleSolverCpp
// https://github.com/machineboy2045/fast-boggle-solver
// #include <ext/hash_set>
#include <string>
// using namespace __gnu_cxx; // for hash_set
using namespace std;       // for string
 
class Boggler {
public:
    Boggler();
    int LoadDictionary(const char* filename);
    int Score(const char* letters);
     
private:
    bool ParseBoard(const char* lets);
    void Solve(int x, int y, const string& sofar);
     
    hash_set<string> words_;
    hash_set<string> stems_;
    hash_set<string> found_;
    string bd_[4][4];
    bool prev_[4][4];
    int score_;
};

void Boggler::Solve(int x, int y, const string& sofar) {
    prev_[x][y] = true;
    string wd = sofar + bd_[x][y];
    if (words_.find(wd) != words_.end()) {
        if (found_.find(wd) == found_.end()) {
            found_.insert(wd);
            score_ += kWordScores[wd.size()];
        }
    }
     
    for (int dx=-1; dx<=1; ++dx) {
        int cx = x + dx;
        if (cx<0 || cx>3) continue;
        for (int dy=-1; dy<=1; ++dy) {
            int cy = y + dy;
            if (cy<0 || cy>3) continue;
            if (prev_[cx][cy]) continue;
            if (stems_.find(wd) != stems_.end())
                Solve(cx, cy, wd);
        }
    }
     
    prev_[x][y] = false;
}

int Boggler::Score(const char* letters) {
    if (!ParseBoard(letters)) return -1;
 
    score_ = 0;
    for (int i=0; i<16; ++i)
        Solve(i/4, i%4, "");
    found_.clear();
    return score_;
}


int main(int argc, char** argv) {
    Boggler b;
    int words = b.LoadDictionary("c:\\tmp\\dict.dat");
    cout << "Loaded " << words << " words." << endl;
    cout << "b.Score(abcd...) => " << b.Score("a b c d e f g h i j k l m n o p") << " == 18?" << endl;
    cout << "b.Score(qu...) => " << b.Score("t c e e v w h b t s t u qu a a e") << " == 94?" << endl;
    cout << "b.Score(catd...) => " << b.Score("c a t d l i n e m a r o p e t s") << " == 2338?" << endl;
}

int main(int argc, char** argv) {
    Boggler b;
    b.LoadDictionary("c:\\tmp\\dict.dat");
 
    char linebuf[256];
    while (cin.getline(linebuf, 256)) {
        cout << b.Score(linebuf) << endl;
    }
}

// a java implementation using trie
// https://www.cs.duke.edu/courses/cps100/fall12/Recitations/Recitation11.html