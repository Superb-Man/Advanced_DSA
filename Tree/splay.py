import random
import string

class Node:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.left = None
        self.right = None

class SplayTree:
    def __init__(self):
        self.root = None

    # Right rotation
    def _rotate_right(self, node):
        temp = node.left
        node.left = temp.right
        temp.right = node
        return temp

    # Left rotation
    def _rotate_left(self, node):
        temp = node.right
        node.right = temp.left
        temp.left = node
        return temp

    # Splay operation
    def _splay(self, node, key):
        if node is None or node.key == key:
            return node

        # Key is in the left subtree
        if key < node.key:
            if node.left is None:
                return node

            # Zig-Zig (Left Left Case)
            if key < node.left.key:
                node.left.left = self._splay(node.left.left, key)
                node = self._rotate_right(node)

            # Zig-Zag (Left Right Case)
            elif key > node.left.key:
                node.left.right = self._splay(node.left.right, key)
                if node.left.right is not None:
                    node.left = self._rotate_left(node.left)

            # Zig
            return self._rotate_right(node) if node.left else node

        # Key is in the right subtree
        else:
            if node.right is None:
                return node

            # Zig-Zig (Right Right Case)
            if key > node.right.key:
                node.right.right = self._splay(node.right.right, key)
                node = self._rotate_left(node)

            # Zig-Zag (Right Left Case)
            elif key < node.right.key:
                node.right.left = self._splay(node.right.left, key)
                if node.right.left is not None:
                    node.right = self._rotate_right(node.right)

            # Zig
            return self._rotate_left(node) if node.right else node

    # Insert a node
    def insert(self, key, val):
        key = int(key)  # Ensure key is an integer
        if not isinstance(val, (int, float, str)):
            raise ValueError("Invalid insert")

        if self.root is None:
            self.root = Node(key, val)
            return

        self.root = self._splay(self.root, key)

        if self.root.key == key:
            self.root.val = val
            return

        node = Node(key, val)
        if key < self.root.key:
            node.left = self.root.left
            node.right = self.root
            self.root.left = None
        else:
            node.right = self.root.right
            node.left = self.root
            self.root.right = None

        self.root = node

    # Remove a node
    def remove(self, key):
        key = int(key)  # Ensure key is an integer
        if self.root is None:
            return

        self.root = self._splay(self.root, key)
        if self.root.key != key:
            return

        if self.root.left is None:
            self.root = self.root.right
        else:
            temp = self.root.right
            self.root = self.root.left
            self.root = self._splay(self.root, key)
            self.root.right = temp

    # Search for a node
    def search(self, key):
        key = int(key)  # Ensure key is an integer
        if self.root is None:
            return None

        self.root = self._splay(self.root, key)
        return self.root if self.root.key == key else None

    # Find minimum node
    def min(self, node=None):
        current = node if node else self.root
        while current and current.left:
            current = current.left
        return current

    # Find maximum node
    def max(self, node=None):
        current = node if node else self.root
        while current and current.right:
            current = current.right
        return current

    # In-order traversal
    def in_order(self, node, func):
        if node:
            self.in_order(node.left, func)
            func(node)
            self.in_order(node.right, func)

    # Check if the tree contains a key
    def contains(self, key):
        key = int(key)  # Ensure key is an integer
        def _contains(node):
            if not node:
                return False
            if node.key == key:
                return True
            return _contains(node.left) or _contains(node.right)

        return _contains(self.root)
    
    def clear(self):
        self.root = None

    def _print_tree(self, node, indent="", position="root"):
        if node is not None:
            print(f"{indent}[{position}]- {node.key}: {node.val}")
            indent += "   "
            self._print_tree(node.left, indent, "left")
            self._print_tree(node.right, indent, "right")

    def print_tree(self):
        if self.root is None:
            print("The tree is empty.")
        else:
            self._print_tree(self.root)      

def random_string(length):
    return ''.join(random.choices(string.ascii_letters, k=length))

if __name__ == "__main__":

    tree = SplayTree()

    # Insert some nodes randomly
    for i in range(20):
        # Generate random string
        tree.insert(random.randint(1, 100), random_string(5))
    
    tree.print_tree()
    
    while True:
        inp = input("Enter a command (insert, remove, search, min, max, print, contains, exit): ")
        if inp == "exit":
            break
        elif inp == "insert":
            key = int(input("Enter key: "))
            val = input("Enter value: ")
            tree.insert(key, val)
        elif inp == "remove":
            key = int(input("Enter key: "))
            tree.remove(key)
        elif inp == "search":
            key = int(input("Enter key: "))
            result = tree.search(key)
            if result:
                print(result.val)
            else:
                print("Key not found")
        elif inp == "min":
            min_node = tree.min()
            if min_node:
                print(min_node.key)
            else:
                print("The tree is empty.")
        elif inp == "max":
            max_node = tree.max()
            if max_node:
                print(max_node.key)
            else:
                print("The tree is empty.")
        elif inp == "contains":
            key = int(input("Enter key: "))
            print(tree.contains(key))
        elif inp == "print":
            tree.print_tree()
