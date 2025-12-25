#include <BinarySearchTree.hpp>
#include <print>

int main() {
    ds::BinarySearchTree<int> tree;

    tree.add(5);
    tree.add(11);
    tree.add(18);
    tree.add(-1);
    tree.add(4);
    tree.add(1);

    tree.foreach([](const int& val) {
        std::print("{} ", val);
    });
    std::println("");

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
    tree.foreach(
        [](const int& val){
            std::print("{} ", val);
        },
        ds::BstTraverseOrder::ASCENDING
    );
    std::println("");

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

    return 0;
}