// http://int-e.eu/~bf3/squares/young.cc
// Tiling rectangles by minimal number of squares.
//
// Inspired by David Radcliffe.
// Author: Bertram Felgenhauer <int-e@gmx.de>
// Date: 2012-12-02
// Changes
// 2013-01-04: more fine-grained restart logic (e.g. young 160 159 < young.txt)
// 2013-03-05,06: refine 'search'; about 10x speedup for N=40

#include <cstdlib>
#include <iostream>
#include <sstream>

#define N 60

static const int verbose = 1;

typedef unsigned char byte;

struct valley {
    byte l;
    byte r;
    byte done;
    byte pad;
};

struct found {
    int level;
    found(int _level)
        : level(_level)
    {}
};

static valley valleys[N][128];
static byte log[N][2];

static void search(int level, int width, int bound);

// streamlined version of search() for the case width == bound
static void searchT(int level, int width)
{
    if (width == 0)
        throw found(level);

    for (int i = 0; i < width; i++) {
        if (valleys[level][i].l == valleys[level][i].r &&
            valleys[level][i].done < valleys[level][i].r)
        {
            byte w = valleys[level][i].l;
            for (int j = 0; j < i; j++) {
                valleys[level+1][j] = valleys[level][j];
                valleys[level+1][j].done =
                    std::min(valleys[level+1][j].l, valleys[level+1][j].r);
            }
            for (int j = i; j < width-1; j++)
                valleys[level+1][j] = valleys[level][j+1];
            log[level][0] = i+1;
            log[level][1] = w;
            if (i > 0)
                valleys[level+1][i-1].r += w;
            valleys[level+1][i].l += w;
            searchT(level+1, width-1);
        }
    }
}

// streamlined version of search() for width == bound-1
static void searchT1(int level, int width)
{
    if (width == 0)
        throw found(level);

    for (int i = 0; i < width; i++) {
        byte w = std::min(valleys[level][i].l, valleys[level][i].r);
        if (valleys[level][i].done < w) {
            for (int j = 0; j < i; j++) {
                valleys[level+1][j] = valleys[level][j];
                valleys[level+1][j].done =
                    std::min(valleys[level+1][j].l, valleys[level+1][j].r);
            }
            if (valleys[level][i].l == valleys[level][i].r) {
                if (i > 0)
                    valleys[level+1][i-1].r += w;
                valleys[level+1][i].l = valleys[level][i+1].l + w;
                valleys[level+1][i].r = valleys[level][i+1].r;
                valleys[level+1][i].done = valleys[level][i+1].done;
                for (int j = i+1; j < width-1; j++)
                    valleys[level+1][j] = valleys[level][j+1];
                log[level][0] = i+1;
                log[level][1] = w;
                searchT1(level+1, width-1);
            } else if (valleys[level][i].l == w) {
                if (i > 0)
                    valleys[level+1][i-1].r += w;
                valleys[level+1][i].l = valleys[level][i].l;
                valleys[level+1][i].r = valleys[level][i].r - w;
                valleys[level+1][i].done = 0;
                for (int j = i+1; j < width; j++)
                    valleys[level+1][j] = valleys[level][j];
                log[level][0] = i+1;
                log[level][1] = w;
                searchT(level+1, width);
            } else {
                valleys[level+1][i].l = valleys[level][i].l - w;
                valleys[level+1][i].r = valleys[level][i].r;
                valleys[level+1][i].done = 0;
                valleys[level+1][i+1].l = valleys[level][i+1].l + w;
                valleys[level+1][i+1].r = valleys[level][i+1].r;
                valleys[level+1][i+1].done = valleys[level][i+1].done;
                for (int j = i+2; j < width; j++)
                    valleys[level+1][j] = valleys[level][j];
                log[level][0] = i+1;
                log[level][1] = w;
                searchT(level+1, width);
            }
        }
    }
}

static void search(int level, int width, int bound)
{
    if (width == 0)
        throw found(level);

    if (width > bound)
        return;
    if (width == bound) {
        searchT(level, width);
        return;
    }
    if (width == bound-1) {
        searchT1(level, width);
        return;
    }

    for (int i = 0; i < width; i++) {
        byte w = std::min(valleys[level][i].l, valleys[level][i].r);
        byte w1 = valleys[level][i].done + 1;
        if (w1 <= w) {
            for (int j = 0; j < i; j++) {
                valleys[level+1][j] = valleys[level][j];
                valleys[level+1][j].done =
                    std::min(valleys[level][j].l, valleys[level][j].r);
            }
            if (w1 < w) {
                valleys[level+1][i].l = valleys[level][i].l - w1;
                valleys[level+1][i].r = w1;
                valleys[level+1][i].done = 0;
                valleys[level+1][i+1].l = w1;
                valleys[level+1][i+1].r = valleys[level][i].r - w1;
                valleys[level+1][i+1].done = 0;
                for (int j = i+1; j < width; j++)
                    valleys[level+1][j+1] = valleys[level][j];
                log[level][0] = i+1;
                for (;;) {
                    log[level][1] = w1;
                    search(level+1, width+1, bound-1);
                    if (++w1 >= w)
                        break;
                    valleys[level+1][i].l--;
                    valleys[level+1][i].r = w1;
                    valleys[level+1][i+1].l = w1;
                    valleys[level+1][i+1].r--;
                }
            }
            if (valleys[level][i].l == valleys[level][i].r) {
                if (i > 0)
                    valleys[level+1][i-1].r += w;
                valleys[level+1][i].l = valleys[level][i+1].l + w;
                valleys[level+1][i].r = valleys[level][i+1].r;
                valleys[level+1][i].done = valleys[level][i+1].done;
                for (int j = i+1; j < width-1; j++)
                    valleys[level+1][j] = valleys[level][j+1];
                log[level][0] = i+1;
                log[level][1] = w;
                search(level+1, width-1, bound-1);
            } else if (valleys[level][i].l == w) {
                if (i > 0)
                    valleys[level+1][i-1].r += w;
                valleys[level+1][i].l = valleys[level][i].l;
                valleys[level+1][i].r = valleys[level][i].r - w;
                valleys[level+1][i].done = 0;
                for (int j = i+1; j < width; j++)
                    valleys[level+1][j] = valleys[level][j];
                log[level][0] = i+1;
                log[level][1] = w;
                search(level+1, width, bound-1);
            } else {
                valleys[level+1][i].l = valleys[level][i].l - w;
                valleys[level+1][i].r = valleys[level][i].r;
                valleys[level+1][i].done = 0;
                valleys[level+1][i+1].l = valleys[level][i+1].l + w;
                valleys[level+1][i+1].r = valleys[level][i+1].r;
                valleys[level+1][i+1].done = valleys[level][i+1].done;
                for (int j = i+2; j < width; j++)
                    valleys[level+1][j] = valleys[level][j];
                log[level][0] = i+1;
                log[level][1] = w;
                search(level+1, width, bound-1);
            }
        }
    }
}

static int table[N][N];

int main(int argc, char **argv)
{
    int restartx = 1, restarty = 1;

    if (argc > 1) {
        restartx = std::atoi(argv[1]);
        if (argc > 2) {
            restarty = std::atoi(argv[2]);
        }
        if (restartx < 1 || restartx >= N ||
            restarty < 1 || restarty > restartx)
        {
            std::cerr << argv[0] << " [1.." << N-1
                      << " [1.." << N-1 << "]]" << std::endl;
            std::cerr << "e.g. " << argv[0] << " n < young.txt" << std::endl;
            std::exit(1);
        }
    }

    for (int x = 1; x <= restartx; x++) {
        for (int y = 1; y <= (x < restartx ? x : restarty-1); y++) {
            std::string reason, ignore;
            std::cin >> ignore >> ignore >> table[x][y] >> ignore;
            getline(std::cin, reason);
            std::cout << x << "," << y << " -> " << table[x][y]
                      << " :" << reason << std::endl;
            table[y][x] = table[x][y];
        }
    }

    for (int x = restartx; x < N; x++) {
        for (int y = (x == restartx ? restarty : 1); y <= x; y++) {
            std::string reason;
            if (x == y) {
                table[x][y] = 1;
                if (verbose)
                    std::cout << x << "," << y << " -> 1 : square" << std::endl;
                else
                    std::cout << 1 << std::endl;
                continue;
            }
            int bound = N;
            for (int d = y; d > 1; d--) {
                if (x % d == 0 && y % d == 0 && table[x/d][y/d] < bound) {
                    bound = table[x/d][y/d];
                    std::stringstream s;
                    s << "scale " << d;
                    reason = s.str();
                }
            }
            for (int h = 1; h < x; h++) {
                if (table[h][y] + table[x-h][y] < bound) {
                    bound = table[h][y] + table[x-h][y];
                    std::stringstream s;
                    s << "horizontal split at " << h;
                    reason = s.str();
                }
            }
            for (int v = 1; v < y; v++) {
                if (table[x][v] + table[x][y-v] < bound) {
                    bound = table[x][v] + table[x][y-v];
                    std::stringstream s;
                    s << "vertical split at " << v;
                    reason = s.str();
                }
            }
            valleys[0][0].l = x;
            valleys[0][0].r = y;
            valleys[0][0].done = 0;
            if (3*x < y*y)
                for (;;) {
                    try {
                        search(0, 1, bound-1);
                    } catch (found f) {
                        std::stringstream s;
                        bound = f.level;
                        s << "basic solution ";
                        for (int i = 0; i < bound; i++)
                            s << int(log[i][0]) << ":" << int(log[i][1]) << ",";
                        reason = s.str();
                        continue;
                    }
                    break;
                }
            if (verbose)
                std::cout << x << "," << y << " -> " << bound
                          << " : " << reason << std::endl;
            else
                std::cout << bound << ",";
            table[x][y] = table[y][x] = bound;
        }
    }
}
