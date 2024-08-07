#include <iostream>

using namespace std;

// cpu 抽象类
class CPU {
public:
    virtual void calculator() = 0; // cpu 计算纯虚函数
};

// gpu 抽象类
class GPU {
public:
    virtual void display() = 0; // gpu 显示纯虚函数
};

// memory 抽象类
class MEM {
public:
    virtual void sterage() = 0; // memory 存储纯虚函数
};

// 继承 CPU 的子类，重写父类纯虚函数
class Intel_CPU :public CPU {
public:
    // 重写
    virtual void calculator() {
        cout << "Inter_CPU" << endl;
    }
};

// 继承 GPU 的子类，重写父类纯虚函数
class Intel_GPU :public GPU {
public:
    // 重写
    virtual void display() {
        cout << "Inter_GPU" << endl;
    }
};

// 继承 MEM 的子类，重写父类纯虚函数
class Intel_MEM : public MEM {
public:
    // 重写
    virtual void sterage() {
        cout << "Inter_MEM" << endl;
    }
};

class AMD_CPU : public CPU {
public:
    // 重写
    virtual void calculator() {
        cout << "AMD_CPU" << endl;
    }
};

class AMD_GPU : public GPU {
public:
    // 重写
    virtual void dispaly() {
        cout << "AMD_GPU" << endl;
    }
};

class AMD_MEM :public MEM {
public:
    // 重写
    virtual void sterage() {
        cout << "AMD_MEM" << endl;
    }
};

// computer类
class Computer {
public:
    // 构造
    Computer(CPU *cpu, GPU *gpu, MEM *mem) {
        this->m_cpu = cpu;
        this->m_gpu = gpu;
        this->m_mem = mem;
    }
    // 拼装函数
    void work() {
        this->m_cpu->calculator();
        this->m_gpu->display();
        this->m_mem->sterage();
    }
    // 析构
    ~Computer() {
        if (m_cpu != NULL) {
            delete this->m_cpu;
            this->m_cpu = NULL;
        }
        if (m_gpu != NULL) {
            delete this->m_gpu;
            this->m_gpu = NULL;
        }
        if (m_mem != NULL) {
            delete this->m_mem;
            this->m_mem = NULL;
        }
    }
private:
    CPU *m_cpu;
    GPU *m_gpu;
    MEM *m_mem;
};

void test() {
    // 堆区创建配件
    CPU *IntelCPU = new Intel_CPU;
    GPU *IntelGPU = new Intel_GPU;
    MEM *AMDMEM   = new AMD_MEM;
    // 实例化 Computer 对象，传入指针
    Computer *computer = new Computer(IntelCPU, IntelGPU, AMDMEM);
    // 调用对象成员函数
    computer->work();
    // 销毁堆区数据
    delete computer;
}

int main() {
    test();
    return 0;
}