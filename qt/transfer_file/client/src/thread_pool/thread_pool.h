#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QFunctionPointer>
#include <atomic>
#include <functional>

class ThreadPool : QObject
{
    Q_OBJECT

    using Task = std::function<void()>;
    using AtomicBool = std::atomic_bool;

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

public:
    static ThreadPool &getInstance();
    void enqueueTask(const Task &&task);
    void stop();

private:
    ThreadPool(int thread_count = QThread::idealThreadCount());
    ~ThreadPool();

    void workerThread();

    QVector<QThread *> threads_;
    QQueue<Task> tasks_que_;
    QMutex que_mtx_;
    QWaitCondition que_condition_;
    AtomicBool stop_;
};

#endif // _THREAD_POOL_H_