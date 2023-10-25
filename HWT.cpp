#include "tree.hpp"

int main() {
    tree::tree_RB<int> tr1;

    int a, b, c;
    std::cin >> a >> b >> c;
    tr1.add_node(a);
    tr1.add_node(b);
    tr1.add_node(c);

    tr1.print(c);

    return 0;
}