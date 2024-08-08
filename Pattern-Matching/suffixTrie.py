class Node:
    def __init__(self, start=None, length=None):
        self.children = {}
        self.start = start
        self.length = length
        # self.index = None

class SuffixTrie:
    def __init__(self, text):
        self.text = text
        self.root = Node()
        self.build_suffix_trie()

    def build_suffix_trie(self):
        n = len(self.text)
        for i in range(n):
            current_node = self.root
            j = i
            while j < n:
                if self.text[j] not in current_node.children:
                    current_node.children[self.text[j]] = Node(start=j, length=n-j)
                    # current_node.children[self.text[j]].index = i
                    break
                child = current_node.children[self.text[j]]
                k = 0
                while k < child.length and j + k < n and self.text[child.start + k] == self.text[j + k]:
                    k += 1
                if k == child.length:
                    current_node = child
                    j += k
                else:
                    split_node = Node(start=child.start, length=k)
                    current_node.children[self.text[j]] = split_node
                    child.start += k
                    child.length -= k
                    split_node.children[self.text[child.start]] = child
                    split_node.children[self.text[j + k]] = Node(start=j + k, length=n - (j + k))
                    # split_node.children[self.text[j + k]].index = i
                    break
    
    def search(self, pattern):
        n = len(pattern)
        current_node = self.root
        i = 0
        while i < n:
            if pattern[i] not in current_node.children:
                return None
            child = current_node.children[pattern[i]]
            j = 0
            while j < child.length and i + j < n and pattern[i + j] == self.text[child.start + j]:
                j += 1
            if j == child.length:
                current_node = child
                i += j
            else:
                return None
        return current_node


    # generating dot files
    def generate_dot(self, filename="suffix_trie.dot"):
        dot_str = "digraph SuffixTrie {\n"
        dot_str += "  node [shape=circle, width=0.3, height=0.3, fontsize=10];\n"
        dot_str += "  node [width=0.3, height=0.3];\n"  # Smaller internal nodes
        
        node_counter = 0

        def add_edges(node, parent_name):
            nonlocal dot_str, node_counter
            node_name = f"node{node_counter}"
            node_counter += 1

            if len(node.children) == 0:
                dot_str += f'  "{node_name}" [label="", width=0.3, height=0.3, shape=point];\n'  # Larger leaf nodes
            else:
                dot_str += f'  "{node_name}" [label="", shape=circle];\n'
            
            if parent_name:
                if node.start is not None:
                    label = f'({node.start}, {node.length})'
                else:
                    label = ""
                dot_str += f'  "{parent_name}" -> "{node_name}" [label="{label}"];\n'
            
            for child in node.children.values():
                add_edges(child, node_name)

        add_edges(self.root, None)
        dot_str += "}\n"
        
        with open(filename, "w") as f:
            f.write(dot_str)

if __name__ == "__main__":

    while True:
        text = input("Enter the text : ")
        text+='$' 
        pattern = input("Enter the pattern : ")
        suffix_trie = SuffixTrie(text)
        suffix_trie.generate_dot()
        result = suffix_trie.search(pattern)
        if result:
            print("Pattern found")
        else:
            print("Pattern not found")
