import json
import matplotlib.pyplot as plt
import os
import numpy as np

JSON_FILE = '../results.json'
IMG_DIR = 'img'
os.makedirs(IMG_DIR, exist_ok=True)

# Load Data (from JSON)
with open(JSON_FILE, 'r') as f:
    data = json.load(f)

benchmarks = {'BruteForce': {}, 'HeldKarp': {}, 'Greedy': {}}

for b in data['benchmarks']:
    name = b['name']
    if '/' not in name: continue

    algo_raw, n_str = name.split('/')
    algo = algo_raw.replace("BM_", "")
    n = int(n_str)

    # Convert ns to milliseconds for easier reading
    time_ms = b['real_time'] / 1e6
    
    # Filter out timeouts
    if time_ms > 0:
        benchmarks[algo][n] = time_ms

# Plot 1: All Algorithms
plt.figure(figsize=(10, 6))
styles = {
    'BruteForce': {'c': '#d62728', 'marker': 'x', 'label': 'Brute Force O(N!)'}, # Red
    'HeldKarp':   {'c': '#1f77b4', 'marker': 'o', 'label': 'Held-Karp O(N^2 2^N)'}, # Blue
    'Greedy':     {'c': '#2ca02c', 'marker': 's', 'label': 'Greedy O(N^2)'}  # Green
}

for algo, points in benchmarks.items():
    if not points: continue
    sorted_n = sorted(points.keys())
    times = [points[n] for n in sorted_n]
    
    # Filter out the "Timeout" points if they exist in JSON as 0
    clean_n = []
    clean_t = []
    for i, t in enumerate(times):
        if t > 0.0001: # minimal threshold
            clean_n.append(sorted_n[i])
            clean_t.append(t)
            
    plt.plot(clean_n, clean_t, **styles.get(algo, {}))

plt.yscale('log')
plt.title('Runtime Comparison: Brute Force vs Held-Karp vs Greedy')
plt.xlabel('Number of Nodes (N)')
plt.ylabel('Time (Milliseconds) - Log Scales')
plt.grid(True, which="both", ls="-", alpha=0.4)
plt.legend()
plt.tight_layout()
plt.savefig(f"{IMG_DIR}/plot_runtime_all.png", dpi=300)
plt.close()

# Held-Karp Zoom
plt.figure(figsize=(10, 6))
hk_points = benchmarks['HeldKarp']
hk_n = sorted([n for n in hk_points if n >= 10])
hk_t = [hk_points[n] for n in hk_n]

plt.plot(hk_n, hk_t, 'o-', color='#1f77b4', linewidth=2, label='Held-Karp')

plt.title('Held-Karp Algorithm (N=10...20)')
plt.xlabel('Number of Nodes (N)')
plt.ylabel('Time (Milliseconds)')
plt.grid(True, alpha=0.4)
plt.legend()
plt.tight_layout()
plt.savefig(f"{IMG_DIR}/plot_heldkarp_zoom.png", dpi=300)
plt.close()

# Greedy Accuracy
# Hardcoded from manual run
accuracy_data = [
    ('T01', 78.98), ('T02', 1.52), ('T03', 23.24), ('T04', 10.89),
    ('T05', 0), ('T08', 0.00), ('T09', 35.62), ('T10', 12.59),
    ('T13', 30.55), ('T14', 21.16), ('T17', 26.15), ('T20', 28.21),
    ('T22', 49.33), ('T23', 31.39), ('T25', 30.42)
]

labels = [x[0] for x in accuracy_data if x[1] > 0 or x[0]=='T08']
values = [x[1] for x in accuracy_data if x[1] > 0 or x[0]=='T08']

plt.figure(figsize=(10, 6))
bars = plt.bar(labels, values, color='#ff7f0e', edgecolor='black')

plt.title('Relative Error for Greedy Algorithm (vs Optimum)')
plt.xlabel('Test ID')
plt.ylabel('Error (%)')
plt.grid(axis='y', alpha=0.4)

# Add value labels on top
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval + 1, f'{yval:.1f}%', ha='center', va='bottom', fontsize=8)

plt.tight_layout()
plt.savefig(f"{IMG_DIR}/plot_greedy_error.png", dpi=300)
plt.close()

print("Graphics generated in img/")
