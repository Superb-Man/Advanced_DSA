import pydot
import itertools
import imageio
import os

# Function to find the overlap between two strings
def overlap(a, b, min_length=1):
    start = 0
    while True:
        start = a.find(b[:min_length], start)
        if start == -1:
            return 0
        if b.startswith(a[start:]):
            return len(a) - start
        start += 1

def greedy_scs(seqs):
    steps = []
    while len(seqs) > 1:
        max_length = -1
        best_pair = (None, None)
        best_merged = None

        # Find the pair of sequences with maximum overlap
        for a, b in itertools.permutations(seqs, 2):
            ov = overlap(a, b)
            if ov > max_length:
                max_length = ov
                best_pair = (a, b)
                best_merged = a + b[ov:]

        steps.append(seqs[:])

        seqs.remove(best_pair[0])
        seqs.remove(best_pair[1])
        seqs.append(best_merged)

    steps.append(seqs[:])  # Final state
    return seqs[0], steps


if __name__ == '__main__':
    num = input("How many sequences : ")
    sequences = [] 
    for i in range(int(num)):
        sequences.append(input(f"Enter sequence {i} : "))

    scs, steps = greedy_scs(sequences)
    print(f"Shortest Common Superstring: {scs}")
    print(f"Steps : {steps}")

