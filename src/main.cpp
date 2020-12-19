#include "json_model.hpp"
#include "CustomDriver.hpp"
#include "json_parser.tab.hpp"

#include <iostream>
#include <sstream>
#include <fstream>


int main()
{

    hse::model::json my_data = hse::model::generate_json(5);
    std::ostringstream os;
    os << my_data;
    std::istringstream ss (os.str());
    hse::model::CustomDriver fuck;
    fuck.parse(ss);
    std::cout << fuck.result;
    
}

/*
#include <benchmark/benchmark.h>
void save_data(const hse::model::json & data, std::size_t elements, std::size_t max_depth){
  std::ostringstream ss;
  ss << "data-" << elements << "-" << max_depth << ".dat";
  std::ofstream out (ss.str());
  out << data;
}

std::istringstream load_data(std::size_t elements, std::size_t max_depth){
  std::ostringstream filename;
  filename << "data-" << elements << "-" << max_depth << ".dat";
  std::ifstream file (filename.str());
  std::string data_raw;
  std::string line;
      while ( getline (file, line) )
      {
          data_raw += line+'\n';
      }
  std::istringstream data (data_raw);
  return data;
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

static void BM_json_parse(benchmark::State& state) {
  std::size_t elements = state.range(0);
  std::size_t max_depth = state.range(1);

  for (auto _ : state) {
    state.PauseTiming();
    std::istringstream ss = load_data(elements, max_depth);
    hse::model::CustomDriver drv;

    state.ResumeTiming();
    drv.parse(ss);
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

BENCHMARK(BM_json_parse)
    ->Args({10, 5})
    ->Args({50, 5})
    ->Args({100, 5})
    ->Args({500, 5})
    ->Args({1000, 5})
    ->Args({5000, 5})
    ->Args({10000, 5});

BENCHMARK_MAIN();




*/
