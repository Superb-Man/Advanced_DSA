def build_suffix_array(text):
    n = len(text)

    suffixes = sorted((text[i:], i) for i in range(n))
    suffix_array = [s[1] for s in suffixes]

    
    return suffix_array

def suffix_array_search(text, pattern, suffix_array):
    n = len(text)
    m = len(pattern)
    l, r = 0, n

    while l < r:
        mid = (l + r) // 2
        if pattern > text[suffix_array[mid]:]:
            l = mid + 1
        else:
            r = mid

    start = l
    r = n
    while l < r:
        mid = (l + r) // 2
        if pattern == text[suffix_array[mid]:suffix_array[mid]+m]:
            l = mid + 1
        else:
            r = mid

    return suffix_array[start:l]


def build_bwt(text, suffix_array):
    n = len(text)
    bwt = [''] * n
    for i in range(n):
        if suffix_array[i] == 0:
            bwt[i] = text[-1]
        else:
            bwt[i] = text[suffix_array[i] - 1]
    return ''.join(bwt)

class RankTable:
    def __init__(self, bwt, checkpoint_interval):
        self.bwt = bwt
        self.checkpoint_interval = checkpoint_interval
        self.rank = {}
        self.checkpoints = {}
        self.build_rank_table()

    def build_rank_table(self):
        n = len(self.bwt)
        unique_chars = set(self.bwt)
        self.rank = {char: [0] * (n + 1) for char in unique_chars}
        self.checkpoints = {char: [0] * ((n // self.checkpoint_interval) + 1) for char in unique_chars}

        for i in range(n):
            char = self.bwt[i]
            for c in self.rank:
                self.rank[c][i + 1] = self.rank[c][i]
            self.rank[char][i + 1] += 1

            if (i + 1) % self.checkpoint_interval == 0:
                checkpoint_index = (i + 1) // self.checkpoint_interval
                for c in self.checkpoints:
                    self.checkpoints[c][checkpoint_index] = self.rank[c][i + 1]

    def get_rank(self, char, index):
        if char not in self.rank:
            return 0
        checkpoint_index = index // self.checkpoint_interval
        checkpoint_rank = self.checkpoints[char][checkpoint_index]

        start = checkpoint_index * self.checkpoint_interval
        for i in range(start, index):
            if self.bwt[i] == char:
                checkpoint_rank += 1
        return checkpoint_rank

    def get_count(self, char):
        return self.rank[char][-1] if char in self.rank else 0

class FMIndex:
    def __init__(self, text, checkpoint_interval=4):
        self.text = text
        self.suffix_array = build_suffix_array(text)
        self.bwt = build_bwt(text, self.suffix_array)
        self.rank_table = RankTable(self.bwt, checkpoint_interval)
        self.c_table = self.build_c_table()

    def build_c_table(self):
        counts = {}
        total_count = 0
        for char in sorted(set(self.bwt)):
            counts[char] = total_count
            total_count += self.rank_table.get_count(char)
        return counts

    def find_pattern(self, pattern):
        m = len(pattern)
        l = 0
        r = len(self.text)
        for i in range(m - 1, -1, -1):
            char = pattern[i]
            l = self.c_table[char] + self.rank_table.get_rank(char, l)
            r = self.c_table[char] + self.rank_table.get_rank(char, r)
            if l >= r:
                return []
        return self.suffix_array[l:r]

if __name__ == "__main__":
    while True:
        text = input("Enter the text : ")
        text+= "$"

        fm_index = FMIndex(text)

        print("Suffix Array:", fm_index.suffix_array)
        print("BWT:", fm_index.bwt)

        pattern = input("Enter the pattern : ")
        
        # Suffix-array search :
        positions = suffix_array_search(text, pattern, fm_index.suffix_array)
        print(f"Pattern '{pattern}' found at positions:", positions)

        # FM index query : 
        positions = fm_index.find_pattern(pattern)
        print(f"Pattern '{pattern}' found at positions:", positions)
