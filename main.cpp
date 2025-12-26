#include <BinarySearchTree.hpp>
#include <print>

void print_tree(const ds::BinarySearchTree<int>& tree) {
    tree.foreach([](const int& val) {
        std::print("{} ", val);
    });
    std::println("");
}

int main() {
    ds::BinarySearchTree<int> tree;

    tree.add(5);
    tree.add(11);
    tree.add(18);
    tree.add(-1);
    tree.add(4);
    tree.add(1);

    print_tree(tree);

    int& eleven = tree.find(11);

    std::println("eleven = {}", eleven);

    tree.foreach([](int& val) {
        val++;
        std::print("{} ", val);
    });
    std::println("");

    const int& zero = tree.min();
    const int& nineteen = tree.max();

    std::println("0 is {}", zero);
    std::println("19 is {}", nineteen);

    tree.foreach([&tree](const int& val) {
        if (!tree.is_present(val)) {
            std::println("Error!");
        }
    });

    std::println("Ascending order:");
    print_tree(tree);

    std::println("Descending order:");
    tree.foreach(
        [](const int& val){
            std::print("{} ", val);
        },
        ds::BstTraverseOrder::DESCENDING
    );
    std::println("");

    std::println("From root order:");
    tree.foreach(
        [](const int& val){
            std::print("{} ", val);
        },
        ds::BstTraverseOrder::FROM_ROOT
    );
    std::println("");

    tree.add(1);
    tree.add(1);
    tree.add(1);
    tree.add(1);
    tree.add(1);

    tree.add(19);
    tree.add(19);
    tree.add(19);
    tree.add(19);

    std::println("\nTrying to add duplicates:");
    print_tree(tree);

    return 0;
}