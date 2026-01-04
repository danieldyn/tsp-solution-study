# tsp-solution-study
A study for several solutions for the Travelling Salesman Problem

```bash
    chmod +x setup.sh
    ./setup.sh
    g++ src/*.cpp -O3 -I./include -I./benchmark/include -L./benchmark/build/src -lbenchmark -lpthread -o tsp_bench
```