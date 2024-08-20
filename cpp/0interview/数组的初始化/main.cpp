#include <iostream>

#define ARR_LEN 16

int global_arr1[ARR_LEN];
int global_arr2[ARR_LEN] {};

void local_var() {
    int local_arr1[ARR_LEN];
    int local_arr2[ARR_LEN] {};

    std::cout << "--- local var ---" << std::endl;
    for (int i = 0; i < ARR_LEN; ++i) {
        std::cout << local_arr1[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < ARR_LEN; ++i) {
        std::cout << local_arr2[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

class Node {
public:
    // Node() {};
    void mem_var() {
        std::cout << "--- mem var ---" << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << mem_arr1[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << mem_arr2[i] << " ";
        }
        std::cout << std::endl << std::endl;
    }
    void mem_local() {
        int mem_local_arr1[ARR_LEN];
        int mem_local_arr2[ARR_LEN] {};

        std::cout << "--- mem local var ---" << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << mem_local_arr1[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << mem_local_arr2[i] << " ";
        }
        std::cout << std::endl << std::endl;
    }
    static void static_mem_var() {
        std::cout << "--- static mem var ---" << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << static_mem_arr1[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << static_mem_arr2[i] << " ";
        }
        std::cout << std::endl << std::endl;
    }
    static void static_mem_local() {
        int static_mem_local_arr1[ARR_LEN];
        int static_mem_local_arr2[ARR_LEN] {};

        std::cout << "--- static mem local var ---" << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << static_mem_local_arr1[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < ARR_LEN; ++i) {
            std::cout << static_mem_local_arr2[i] << " ";
        }
        std::cout << std::endl << std::endl;
    }
private:
    int mem_arr1[ARR_LEN];
    int mem_arr2[ARR_LEN] {};

    static int static_mem_arr1[ARR_LEN];
    static int static_mem_arr2[ARR_LEN];
};

int Node::static_mem_arr1[ARR_LEN];
int Node::static_mem_arr2[ARR_LEN] {};

void testGlobalVarArray() {
    std::cout << "--- global var ---" << std::endl;
    for (int i = 0; i < ARR_LEN; ++i) {
        std::cout << global_arr1[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < ARR_LEN; ++i) {
        std::cout << global_arr2[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void testLoaclVarArray() {
    local_var();
}

void testMemVarArray() {
    Node().mem_var();
    // Node node;
    // node.mem_var();
}

void testMemLocalArray() {
    Node().mem_local();
}

void testStaticMemVarArray() {
    Node::static_mem_var();
}

void testStaticMemLocalArray() {
    Node::static_mem_local();
}

int main(int argc, char *argv[]) {
    testGlobalVarArray();
    testLoaclVarArray();
    testMemVarArray();
    testMemLocalArray();
    testStaticMemVarArray();
    testStaticMemLocalArray();
    return 0;
}