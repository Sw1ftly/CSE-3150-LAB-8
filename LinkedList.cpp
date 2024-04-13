#include "LinkedList.h"
#include <vector>

LinkedList::LinkedList() : root(nullptr), copyNodes(nullptr), nodeCount(0) {}

LinkedList::~LinkedList() {
    delete_node_shared_ptr_list();
    if (copyNodes) {
        delete[] copyNodes;
    }
}

void LinkedList::build_node_list(int k) {
    for (int i = 0; i < k; ++i) {
        root = std::make_shared<Node>(i, root);
    }
    nodeCount = k;
}

LinkedList::CopyNode* LinkedList::build_copyNodes_weak_ptrs() {
    if (nodeCount == 0) return nullptr;
    copyNodes = new CopyNode[nodeCount];
    shared_ptr<Node> current = root;
    int index = 0;
    while (current != nullptr) {
        copyNodes[index++].weak_node_ptr = current;
        current = current->next;
    }
    return copyNodes;
}

void LinkedList::delete_node_shared_ptr_list() {
    root = nullptr;
}

void LinkedList::print_node_list_shared_ptrs() {
    shared_ptr<Node> current = root;
    while (current != nullptr) {
        std::cout << "Node value: " << current->data << ", " << current << std::endl;
        current = current->next;
    }
}

void LinkedList::print_node_array_weak_ptrs() {
    for (int i = 0; i < nodeCount; ++i) {
        std::cout << "CopyNode " << i << ": " << copyNodes[i].weak_node_ptr << std::endl;
    }
}

/*

int main() {
    LinkedList list;
    list.build_node_list(5);
    std::cout << "Original list using shared_ptrs:\n";
    list.print_node_list_shared_ptrs();

    list.build_copyNodes_weak_ptrs();
    std::cout << "\nCopyNodes using weak_ptrs (before deletion):\n";
    list.print_node_array_weak_ptrs();

    
    list.delete_node_shared_ptr_list();
    std::cout << "\nCopyNodes using weak_ptrs (after deletion):\n";
    list.print_node_array_weak_ptrs();

    return 0;
}
*/