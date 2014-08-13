#ifndef THREAD_POOL_H
#define THREAD_POOL_H 


#include "NonCopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <memory>
#include <functional>
#include <vector>

class Thread;

class ThreadPool : private NonCopyable
{
    public:
        typedef std::function<void()> Task;

        ThreadPool(size_t queueSize, size_t poolSize);
        ~ThreadPool();
    
        void start(); //启动线程池new
        void stop();  //停止线程池
    
        void addTask(const Task &);
        Task getTask();
    private:
        void runInThread();  //线程池内线程的回调函数

        mutable MutexLock mutex_;
        Condition empty_;  
        Condition full_;
        size_t queueSize_;  //队列大小
        std::queue<Task> queue_;
        size_t poolSize_;  //线程池的大小
		std::vector<std::shared_ptr<Thread>> threads_;//new
        //PtrVector<Thread> threads_; origin
        bool isStarted_;  //线程池是否开启
};


#endif  /*THREAD_POOL_H*/
