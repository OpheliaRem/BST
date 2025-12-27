#include <BinarySearchTree.hpp>
#include <print>
#include <stdexcept>
#include <vector>

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

    tree.remove(6);

    std::println("\nTrying to remove root:");
    tree.foreach(
        [](const int& val){
            std::print("{} ", val);
        },
        ds::BstTraverseOrder::FROM_ROOT
    );
    std::println("");

    std::println("\nTrying to remove all the elements one by one:");
    std::vector<int> values;
    tree.foreach(
        [&values](const int& val) {
            values.push_back(val);
        }
    );

    for (int val : values) {
        print_tree(tree);
        tree.remove(val);
    }
    print_tree(tree);

    if (!tree.is_empty()) {
        std::println("size = {}", tree.get_size());
        throw std::logic_error("Something is wrong with the algorithm");
    }

    return 0;
}