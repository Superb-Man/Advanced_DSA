# Type: Knuth-Morris-Pratt Algorithm
# Description: Knuth-Morris-Pratt Algorithm for string matching
# Reference: Introduction to Algorithms, Cormen et al. (3rd
def kmpMatcher(text, pattern):
    n = len(text)
    m = len(pattern)
    pi = computePrefixFunction(pattern)
    q = 0
    for i in range(n):
        while q > 0 and pattern[q] != text[i]:
            q = pi[q - 1]
        if pattern[q] == text[i]:
            q += 1
        if q == m:
            print("Pattern occurs with shift", i - m + 1)
            q = pi[q - 1]


def computePrefixFunction(pattern):
    m = len(pattern)
    pi = [0] * m
    k = 0
    for q in range(1, m):
        while k > 0 and pattern[k] != pattern[q]:
            k = pi[k - 1]
        if pattern[k] == pattern[q]:
            k += 1
        pi[q] = k
    return pi


if __name__ == "__main__":

    while True:

        text = input("Enter the text: ")
        pattern = input("Enter the pattern: ")
        kmpMatcher(text, pattern)