#include "D:\distake\Coding\head_file.h"

// 优先队列

class MaxPQ {
private:
    // 存储元素的数组
    vector<int> pq;
    // 当前PQ中的元素个数
    int N;
public:
    // 构造函数
    MaxPQ(int capacity) {
        // 索引0不用，所以需要多分配一个空间
        pq.resize(capacity + 1);
        N = 0;
    }
    // 返回当前队列中最大元素
    int max() {
        return pq[1];
    }

    // 插入元素
    void insert(int e) {
        // 将要插入的元素添加到堆底的位置，然后上浮到正确位置
        ++N;
        // 先将新的元素添加到最后
        pq[N] = e;
        // 然后上浮到正确位置
        swim(N);

    }
    // 删除并返回当前数组中最大元素
    int delMax() {
        // 先将堆顶的元素A和堆底元素B位置对调，然后删除A，将B下沉到合适位置
        int max = pq[1];
        // 兑换
        exch(1, N);
        // 删除
        --N;
        // 下称
        sink(1);
        return max;
    }

    int parent(int root) {
        return root / 2;
    }
    int left(int root) {
        return root * 2;
    }
    int right(int root) {
        return root * 2 + 1;
    }
    // 上浮第k个元素，以维护最大堆性质
    void swim(int k)        // 定位为子节点
    {
        // 如果某个节点A比它的父节点大，那么对A上浮
        while (k > 1 && less(parent(k), k))  // k> 1才有父节点
        {
            cout << "swin: " << pq[k] << endl;
            // 交换序号为parent(k) 和 k 的值
            exch(parent(k), k);
            // 交换完后k位于父节点处
            k = parent(k);
        }
    }
    // 下沉第k个元素
    void sink(int k)        // 定位为父节点
    {
        // 如果某个节点A比它的子节点小，则对A下沉
        // 需要判断A与其两个子节点比较大小，判断A是否为最大值
        while (left(k) <= N) {
            // 先假设左节点为最大值
            int older = left(k);
            // 如果右节点存在，比较大小
            while (right(k) <= N && less(left(k), right(k))) {
                // 最大值为右节点
                older = right(k);
            }
            // 父节点与最大子节点进行比较
            if (less(older, k)) break;

            // 否则交换并下沉k节点
            cout << "sink: " << pq[k] << endl;
            exch(older, k);
            k = older;
        }
    }

    // 交换数组的两个元素
    void exch(int i, int j) {
        // cout << "i: " << i << " j: " << j << endl;
        int temp = pq[i];
        pq[i] = pq[j];
        pq[j] = temp;

    }

    // 比较pq[i]是否小于pq[j]
    bool less(int i, int j) {
        return pq[i] < pq[j];
    }
};

int main() {
    MaxPQ data(10);

    data.insert(2);
    data.insert(5);
    data.insert(6);
    data.insert(10);
    data.delMax();
    cout << data.max() << endl;
    return 0;
}
