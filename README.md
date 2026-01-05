# tsp-solution-study
A study for several solutions for the Travelling Salesman Problem

# Set up & Run the Google Benchmark

```bash
    chmod +x setup.sh
    ./setup.sh

    g++ src/*.cpp -O3 -I./include -I./benchmark/include -L./benchmark/build/src -lbenchmark -lpthread -o tsp_bench
    ./tsp_bench
```

# Testing

```bash
    # testing directory
    cd ./tests
```

## Create the reference & output files

```
    Note: The Held-Kerp Algorithm was used for generating the reference files.
```

```bash
    # ref
    g++ generate_refs.cpp ../src/held_karp_tsp.cpp -I ../include/ -o generate_refs
    ./generate_refs # the existing .ref files WILL be overwritten

    # out
    g++ generate_outs.cpp ../src/greedy_tsp.cpp -I ../include/ -o generate_outs
    ./generate_outs # the existing .out files WILL be overwritten
```

## Compare the results

```bash
    g++ compare_results.cpp -o compare_results
    ./compare_results # > compare_results.txt
```

```
    Note: The output of the command above can be redirected to a 'compare_results.txt' file (for better analysis).
    The name of the file is present in the '.gitignore' hidden file, thus it cannot be accidentally commited.
```