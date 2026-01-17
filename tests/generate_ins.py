import random
import os

# Configuration
NUM_TESTS = 25
OUTPUT_DIR = "./"
MAX_COST = 1000000

def generate_test_case(test_id):
    if test_id <= 10:
        n = random.randint(3, 10) # Small tests for Brute Force
    elif test_id <= 20:
        n = random.randint(11, 18) # Medium tests for Held-Karp
    else:
        n = random.randint(19, 20) # Large tests

    # Generate all possible edges for an undirected graph of N nodes
    possible_edges = []
    for i in range(n):
        for j in range(i + 1, n):
            cost = random.randint(1, MAX_COST)
            possible_edges.append((i, j, cost))

    # Shuffle the edge pool
    random.shuffle(possible_edges)

    # A Hamiltonian cycle can exist only if M >= N
    min_m = n
    max_m = len(possible_edges)
    m = random.randint(min_m, max_m)

    selected_edges = possible_edges[:m]

    # Write to file
    filename = f"in/test{test_id:02d}.in"
    filepath = os.path.join(OUTPUT_DIR, filename)

    with open(filepath, "w") as f:
        # First line: N M
        f.write(f"{n} {m}\n")
        # Next M lines: X Y C
        for u, v, cost in selected_edges:
            f.write(f"{u} {v} {cost}\n")

    print(f"Created {filename}: N={n}, M={m}")

def main():
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    print(f"Generating {NUM_TESTS} tests in format (N M / X Y C)...")
    for i in range(1, NUM_TESTS + 1):
        generate_test_case(i)
    print("\nSuccess!")

if __name__ == "__main__":
    main()
