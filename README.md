# Binary Search Tree (BST) Generator & Visualizer

A console application and educational tool that constructs, analyzes, and visualizes Binary Search Trees (BST) from numerical arrays.

The program highlights the structural and algorithmic differences between **Sequential Insertion** (which can degenerate into an $O(N)$ linked list) and **Balanced Construction** (which guarantees optimal $O(\log N)$ height).

---

## 📋 Features

- **Dual Construction Algorithms**:
  - **Balanced BST (`fromArrayBalanced`)**: Deduplicates and sorts the array, then recursively picks medians via divide-and-conquer to build an optimal tree with minimal height $\lfloor\log_2 N\rfloor + 1$.
  - **Sequential Insertion (`fromArraySequential`)**: Inserts values one-by-one in their original arrival order.
- **Universal 2D ASCII Tree Visualizer**:
  - Renders a clean hierarchical tree diagram in the terminal with explicit Left `(L)` and Right `(R)` branch indicators and null pointers.
  - Compatible across all operating systems and console encodings.
- **Comprehensive Traversals**:
  - **In-Order**: Prints sorted keys (verifying the BST property).
  - **Pre-Order**: Root-first traversal.
  - **Post-Order**: Bottom-up traversal.
  - **Level-Order (BFS)**: Breadth-first level-by-level inspection.
- **Tree Analytics & Metrics**:
  - Tree height and node count.
  - Minimum and maximum key values.
  - AVL height-balance status ($|\text{height}_L - \text{height}_R| \le 1$).
- **Search with Step-by-Step Path Tracing**:
  - Displays every node visited during search and reports the exact number of comparisons made.
- **Dynamic Tree Operations**:
  - Allows inserting new nodes into active trees with instant visual re-rendering.

---

## 🌲 Visual Demonstration

### Sorted Array Input: `[1, 2, 3, 4, 5, 6, 7]`

#### Mode 1: Sequential Insertion (Degenerate $O(N)$ Tree)
When elements arrive in sorted order, standard sequential insertion forms a linear chain:

```text
-- [1]
    \-- (R) [2]
        \-- (R) [3]
            \-- (R) [4]
                \-- (R) [5]
                    \-- (R) [6]
                        \-- (R) [7]

Tree Height: 7 | Balanced: No (Skewed)
```

#### Mode 2: Balanced BST (Optimal $O(\log N)$ Tree)
By selecting the median element recursively as the root, the tree remains perfectly balanced:

```text
-- [4]
    |-- (L) [2]
    |   |-- (L) [1]
    |   \-- (R) [3]
    \-- (R) [6]
        |-- (L) [5]
        \-- (R) [7]

Tree Height: 3 | Balanced: Yes (Optimal)
```

---

## ⚡ Complexity Comparison

| Metric / Operation | Sequential BST (Unsorted) | Sequential BST (Sorted/Worst Case) | Balanced BST (Optimal) |
| :--- | :---: | :---: | :---: |
| **Construction Time** | $O(N \log N)$ avg | $O(N^2)$ | $O(N \log N)$ |
| **Tree Height** | $O(\log N)$ avg | $O(N)$ (Degenerate) | $O(\log N)$ (Guaranteed) |
| **Search Time** | $O(\log N)$ avg | $O(N)$ | $O(\log N)$ |
| **Space Complexity** | $O(N)$ | $O(N)$ | $O(N)$ |

---

## 🚀 Getting Started

### Prerequisites

- **Java Development Kit (JDK) 11+** (JDK 17 or JDK 21 recommended)
- Optional: C++ compiler (`g++` or `clang++`) if running the companion C++ version.

---

### Running the Java Program

You can run `Program.java` directly using single-file source code execution:

#### 1. Interactive Menu Mode
Provides an interactive menu for custom arrays, preloaded demos, searching, and inserting:

```bash
java Program.java
```

#### 2. Direct CLI Mode
Pass numbers directly as arguments to immediately generate and compare both trees:

```bash
java Program.java 50 30 70 20 40 60 80
```

#### 3. Compile & Run
If compiling manually:

```bash
# Compile
javac Program.java

# Run
java Program 50 30 70 20 40 60 80
```

---

### Running the Automated Test Suite

A standalone unit test suite is included to verify all algorithms, edge cases, and traversals:

```bash
java BSTTest.java
```

---

### Running the Companion C++ Program (Optional)

```bash
# Compile
g++ -std=c++17 bst_app.cpp -o bst_app

# Run with arguments
./bst_app 50 30 70 20 40 60 80
```

---

## 📂 Project Structure

```text
├── Program.java     # Main Java program with BST logic, visualizer, and CLI
├── BSTTest.java     # Automated unit test suite (28 test assertions)
├── bst_app.cpp      # Companion modern C++ implementation
├── .gitignore       # Git ignore rules for compiled classes and binaries
└── README.md        # Documentation and usage guide
```

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
