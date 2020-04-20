//
// Created by dmitri on 09.04.2020.
//

#include <thread>

#include "thread_guard.h"
namespace advanced_thread {

//
// Joining thread
//
    joining_thread::joining_thread(std::thread t_) noexcept: t(std::move(t_)){}
    joining_thread::joining_thread(advanced_thread::joining_thread && other) noexcept : t(std::move(other.t)){}
    joining_thread::~joining_thread() noexcept { if_joinable(); }

    void joining_thread::if_joinable() {
        if (joinable())
            join();
    }

    joining_thread & joining_thread::operator=(std::thread t_) noexcept{
        if_joinable();
        t = std::move(t_);
        return *this;
    }

    joining_thread & joining_thread::operator=(joining_thread && other) noexcept {
        if_joinable();
        t = std::move(other.t);
        return *this;
    }

    bool joining_thread::joinable() const noexcept { return t.joinable(); }
    void joining_thread::join() { t.join(); }
    void joining_thread::detach() { t.detach(); }

    void joining_thread::swap(joining_thread & other) noexcept { t.swap(other.t); }

    std::thread::id joining_thread::get_id() const noexcept { return t.get_id(); }

    std::thread & joining_thread::as_thread() noexcept { return t; }
    const std::thread & joining_thread::as_thread() const noexcept { return t; }
}