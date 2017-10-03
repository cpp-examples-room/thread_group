#ifndef THREAD_GROUP_HPP
#define THREAD_GROUP_HPP

#include <list>
#include <memory>
#include <mutex>
#include <thread>

namespace tds {
    class Thread_group {
    public:
        Thread_group() = default;

        Thread_group(Thread_group const& rhs) = delete;
        Thread_group(Thread_group&& rhs) = default;
        Thread_group& operator=(Thread_group const& rhs) = delete;
        Thread_group& operator=(Thread_group&& rhs) = default;

        ~Thread_group() {
            for(auto t: threads_) {
                delete t;
            }
        }

        template<typename F, typename... Args>
        std::thread* create_thread(F thread_func, Args... args) {
            auto new_thread = std::make_unique<std::thread>(thread_func, args...);
            std::lock_guard<std::mutex> lock_g(mutex_);
            threads_.push_back(new_thread.get());
            return new_thread.release();
        }

        void remove_thread(std::thread *thread) {
            if (thread) {
                std::lock_guard<std::mutex> lock_g(mutex_);
                auto t = std::find(threads_.begin(), threads_.end(), thread);
                if (t != threads_.end()) {
                    threads_.erase(t);
                }
            }
        }

        void join_all() {
            /* A deadlock will happen if this->threads_ contains this thread. */
            for(auto t: threads_) {
                if (t->joinable()) { t->join(); }
            }
        }

        std::size_t size() const {
            std::lock_guard<std::mutex> lock_g(mutex_);
            return threads_.size();
        }

    private:
        std::list<std::thread*> threads_;
        mutable std::mutex mutex_;
    };
}

#endif
