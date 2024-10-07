#include "thread_pool.h"
#include <QDebug>

ThreadPool &ThreadPool::getInstance()
{
    static ThreadPool thread_pool;
    return thread_pool;
}

void ThreadPool::enqueueTask(const Task &&task)
{
    if (stop_) {
        qDebug() << "thread pool stop";
        return;
    }
    {
        QMutexLocker locker(&que_mtx_);
        tasks_que_.enqueue(task);
    }
    que_condition_.wakeOne();
}

void ThreadPool::stop()
{
    stop_ = true;
    que_condition_.wakeAll();
}

ThreadPool::ThreadPool(int thread_count) :
    stop_(false)
{
    qDebug() << thread_count;
    for (int i = 0; i < thread_count; ++i) {
        QThread *thread = new QThread(this);
        threads_.append(thread);
        this->connect(thread, &QThread::started, this, [this]() {
            workerThread();
        });
        thread->start();
    }
}

ThreadPool::~ThreadPool()
{
    {
        QMutexLocker locker(&que_mtx_);
        stop_ = true;
        que_condition_.wakeAll();
    }

    for (QThread *thread : threads_) {
        thread->quit();
        thread->wait();
        delete thread;
        qDebug() << "recycle thread";
    }
}

void ThreadPool::workerThread()
{
    while (true) {
        Task task;
        {
            QMutexLocker locker(&que_mtx_);
            while (tasks_que_.empty() && !stop_) {
                que_condition_.wait(&que_mtx_);
            }
            if (stop_ && tasks_que_.empty()) {
                break;
            }
            task = tasks_que_.dequeue();
        }
        task();
        qDebug() << "task finished";
    }
}