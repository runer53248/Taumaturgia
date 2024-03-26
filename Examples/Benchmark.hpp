#pragma once
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std::chrono_literals;
using namespace std::chrono;

constinit size_t repetition = 10'000;

template <typename FUN>
struct Benchmark {
    Benchmark(FUN&& fun) noexcept
        : fun{std::move(fun)} {}

    template <typename... Args>
    auto operator()(Args&&... args) {
        using time_type = nanoseconds;
        auto begin_value = time_type{0};
        std::vector<time_type> times;
        times.reserve(repetition);

        steady_clock::time_point start;
        steady_clock::time_point finish;

        std::invoke_result_t<FUN, Args...> result;
        time_type duration;

        auto repeat_fun = [&]() {
            start = steady_clock::now();
            result = fun(std::forward<Args>(args)...);
            finish = steady_clock::now();
            duration = duration_cast<time_type>(finish - start);
        };

        repeat_fun();
        std::cout << "first run duration: " << duration << '\n';
        repeat_fun();
        std::cout << "second run duration: " << duration << '\n';

        for (size_t i = 0; i < repetition; ++i) {
            repeat_fun();
            times.push_back(duration);
        }

        repeat_fun();
        times.push_back(duration);
        std::cout << "last run duration: " << duration << '\n';

        auto dur_aprox = std::accumulate(times.begin(), times.end(), begin_value);
        dur_aprox /= static_cast<int>(repetition);

        std::cout << "dur_aprox: " << dur_aprox << " (after repeat: " << repetition << " times)\n";
        return result;
    }

    FUN fun;
};
