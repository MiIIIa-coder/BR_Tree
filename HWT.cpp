#include "tree.hpp"

bool comp_int(int n1, int n2) {
    return n1 > n2;
}

int main() {
    tree::tree_RB<int> tr1(comp_int);

    int a, b, c, d, e;
    std::cin >> a >> b >> c >> d >> e;
    tr1.insert(a);
    tr1.insert(b);
    tr1.insert(c);
    tr1.insert(d);
    tr1.insert(e);

    tr1.print(c);

    return 0;
}