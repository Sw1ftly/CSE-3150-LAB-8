#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <memory>
#include <iostream>

using std::shared_ptr;
using std::weak_ptr;
using std::ostream;

template <typename T>
ostream &operator<<(ostream &os, const shared_ptr<T> &p) {
    return os << p.get() << " shared_ptr count: [" << p.use_count() << "]";
}

template <typename T>
ostream &operator<<(ostream &os, const weak_ptr<T> &p) {
    T *raw = nullptr;
    auto sp = p.lock();
    raw = sp ? sp.get() : nullptr;
    return os << raw << " weak_ptr to shared_ptr count: [" << (sp ? sp.use_count() : 0) << "]";
}

struct LinkedList {
public:
    struct Node {
        int data;
        shared_ptr<Node> next;
        Node(int data, shared_ptr<Node> next = nullptr) : data(data), next(next) {}
    };

    struct CopyNode {
        weak_ptr<Node> weak_node_ptr;
    };

    LinkedList();
    ~LinkedList();

    void build_node_list(int k);
    CopyNode* build_copyNodes_weak_ptrs();
    void delete_node_shared_ptr_list();
    void print_node_list_shared_ptrs();
    void print_node_array_weak_ptrs();

private:
    shared_ptr<Node> root;
    CopyNode* copyNodes;
    int nodeCount;
};

#endif 