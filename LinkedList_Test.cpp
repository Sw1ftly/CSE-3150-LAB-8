#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LinkedList.h"

TEST_CASE("Testing LinkedList with shared_ptr and weak_ptr") {
    LinkedList list;
    list.build_node_list(5);
    list.build_copyNodes_weak_ptrs();

    SUBCASE("Check initial weak_ptr validity") {
        for (int i = 0; i < 5; ++i) {
            auto sp = list.build_copyNodes_weak_ptrs()[i].weak_node_ptr.lock();
            CHECK(sp != nullptr);
        }
    }

    SUBCASE("Weak pointers should be invalidated after deleting shared_ptrs") {
        list.delete_node_shared_ptr_list();
        for (int i = 0; i < 5; ++i) {
            auto sp = list.build_copyNodes_weak_ptrs()[i].weak_node_ptr.lock();
            CHECK(sp == nullptr);
        }
    }
}