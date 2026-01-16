# Travlling Salesman Problem Study

A study for several solutions for the Travelling Salesman Problem.

## Environment Setup

From the repository's root:

```bash
    chmod +x setup.sh
    ./setup.sh
```

## Running the Benchmark

Look inside the `run_benchmark.sh` file to choose the number of benchmarking rounds before continuing.

From the repository's root:

- If you want the results printed to the terminal in human readable format:

```bash
    chmod +x run_benchmark.sh
    ./run_benchmark.sh
```

- If you want to store them inside the root of the project in the `results.json` file:

```bash
    chmod +x run_benchmark.sh
    ./run_benchmark.sh json
```

## Verifying Correctness

From the repository's root:

```bash
    chmod +x run_check.sh
    ./run_check.sh > check_results.txt
    cat check_results.txt
```
