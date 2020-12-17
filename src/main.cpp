#include "json_model.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

/*int main()
{

    hse::model::json my_data = hse::model::generate_json(5);

    std::cout << my_data;
    
    
}*/

#include <benchmark/benchmark.h>
void save_data(const hse::model::json & data, std::size_t elements, std::size_t max_depth){
  std::ostringstream ss;
  ss << "data-" << elements << "-" << max_depth << ".dat";
  std::ofstream out (ss.str());
  out << data;
}

static void BM_json_output(benchmark::State& state) {
  std::size_t elements = state.range(0);
  std::size_t max_depth = state.range(1);
  hse::model::set_prng_seed(42);
  hse::model::json my_data = hse::model::generate_json(elements, max_depth);
  save_data(my_data, elements, max_depth);
  for (auto _ : state) {
    state.PauseTiming();
    std::ostringstream ss;
    state.ResumeTiming();
    ss << my_data;
    state.PauseTiming();
  }
}

// Register the function as a benchmark
BENCHMARK(BM_json_output)
    ->Args({10, 5})
    ->Args({50, 5})
    ->Args({100, 5})
    ->Args({500, 5})
    ->Args({1000, 5})
    ->Args({5000, 5})
    ->Args({10000, 5});

BENCHMARK_MAIN();


