#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <memory>
#include <string>

// ==========================================
// 1. Tree Node Definition
// ==========================================
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ==========================================
// 2. Binary Search Tree Class
// ==========================================
class BinarySearchTree {
private:
    TreeNode* root;
    std::string buildMethod;

    TreeNode* insertRec(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        if (val < node->val) {
            node->left = insertRec(node->left, val);
        } else if (val > node->val) {
            node->right = insertRec(node->right, val);
        }
        return node;
    }

    static TreeNode* buildBalancedRec(const std::vector<int>& sortedArr, int start, int end) {
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        TreeNode* node = new TreeNode(sortedArr[mid]);
        node->left = buildBalancedRec(sortedArr, start, mid - 1);
        node->right = buildBalancedRec(sortedArr, mid + 1, end);
        return node;
    }

    int calcHeight(TreeNode* node) const {
        if (!node) return 0;
        return 1 + std::max(calcHeight(node->left), calcHeight(node->right));
    }

    int countNodes(TreeNode* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int checkBalanced(TreeNode* node) const {
        if (!node) return 0;
        int lh = checkBalanced(node->left);
        if (lh == -1) return -1;
        int rh = checkBalanced(node->right);
        if (rh == -1) return -1;
        if (std::abs(lh - rh) > 1) return -1;
        return 1 + std::max(lh, rh);
    }

    void inOrderRec(TreeNode* node, std::vector<int>& out) const {
        if (!node) return;
        inOrderRec(node->left, out);
        out.push_back(node->val);
        inOrderRec(node->right, out);
    }

    void preOrderRec(TreeNode* node, std::vector<int>& out) const {
        if (!node) return;
        out.push_back(node->val);
        preOrderRec(node->left, out);
        preOrderRec(node->right, out);
    }

    void postOrderRec(TreeNode* node, std::vector<int>& out) const {
        if (!node) return;
        postOrderRec(node->left, out);
        postOrderRec(node->right, out);
        out.push_back(node->val);
    }

    void printTreeRec(TreeNode* node, const std::string& prefix, bool isTail, bool isRoot) const {
        if (!node) return;
        std::string branch = isRoot ? "── " : (isTail ? "└── " : "├── ");
        std::cout << prefix << branch << "[" << node->val << "]\n";

        std::vector<std::pair<TreeNode*, std::string>> children;
        if (node->left || node->right) {
            children.push_back({node->left, "L"});
            children.push_back({node->right, "R"});
        }

        for (size_t i = 0; i < children.size(); ++i) {
            bool childIsTail = (i == children.size() - 1);
            std::string childPrefix = prefix + (isRoot ? "    " : (isTail ? "    " : "│   "));
            TreeNode* child = children[i].first;
            std::string label = children[i].second;
            if (child) {
                printNodeWithLabel(child, childPrefix, childIsTail, label);
            } else {
                std::string nullBranch = childIsTail ? "└── " : "├── ";
                std::cout << childPrefix << nullBranch << "(" << label << ": null)\n";
            }
        }
    }

    void printNodeWithLabel(TreeNode* node, const std::string& prefix, bool isTail, const std::string& label) const {
        std::string branch = isTail ? "└── " : "├── ";
        std::cout << prefix << branch << "(" << label << ") [" << node->val << "]\n";

        std::vector<std::pair<TreeNode*, std::string>> children;
        if (node->left || node->right) {
            children.push_back({node->left, "L"});
            children.push_back({node->right, "R"});
        }

        for (size_t i = 0; i < children.size(); ++i) {
            bool childIsTail = (i == children.size() - 1);
            std::string childPrefix = prefix + (isTail ? "    " : "│   ");
            TreeNode* child = children[i].first;
            std::string l = children[i].second;
            if (child) {
                printNodeWithLabel(child, childPrefix, childIsTail, l);
            } else {
                std::string nullBranch = childIsTail ? "└── " : "├── ";
                std::cout << childPrefix << nullBranch << "(" << l << ": null)\n";
            }
        }
    }

    void destroyTree(TreeNode* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BinarySearchTree(const std::string& method) : root(nullptr), buildMethod(method) {}

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(int val) {
        root = insertRec(root, val);
    }

    static BinarySearchTree* fromArraySequential(const std::vector<int>& arr) {
        auto* bst = new BinarySearchTree("Sequential Insertion (Original Order)");
        for (int v : arr) {
            bst->insert(v);
        }
        return bst;
    }

    static BinarySearchTree* fromArrayBalanced(const std::vector<int>& arr) {
        auto* bst = new BinarySearchTree("Balanced BST (Optimal Minimal Height)");
        if (arr.empty()) return bst;

        std::vector<int> uniqueSorted = arr;
        std::sort(uniqueSorted.begin(), uniqueSorted.end());
        uniqueSorted.erase(std::unique(uniqueSorted.begin(), uniqueSorted.end()), uniqueSorted.end());

        bst->root = buildBalancedRec(uniqueSorted, 0, static_cast<int>(uniqueSorted.size()) - 1);
        return bst;
    }

    struct SearchResult {
        bool found = false;
        std::vector<int> path;
        int comparisons = 0;
    };

    SearchResult search(int key) const {
        SearchResult res;
        TreeNode* curr = root;
        while (curr) {
            res.path.push_back(curr->val);
            res.comparisons++;
            if (key == curr->val) {
                res.found = true;
                return res;
            } else if (key < curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return res;
    }

    int getHeight() const { return calcHeight(root); }
    int size() const { return countNodes(root); }
    bool isBalanced() const { return checkBalanced(root) != -1; }

    std::vector<int> inOrder() const {
        std::vector<int> res;
        inOrderRec(root, res);
        return res;
    }

    std::vector<int> preOrder() const {
        std::vector<int> res;
        preOrderRec(root, res);
        return res;
    }

    std::vector<int> postOrder() const {
        std::vector<int> res;
        postOrderRec(root, res);
        return res;
    }

    std::vector<std::vector<int>> levelOrder() const {
        std::vector<std::vector<int>> res;
        if (!root) return res;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            std::vector<int> lvl;
            for (int i = 0; i < sz; ++i) {
                TreeNode* curr = q.front();
                q.pop();
                lvl.push_back(curr->val);
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            res.push_back(lvl);
        }
        return res;
    }

    void printTree() const {
        if (!root) {
            std::cout << "  (Tree is empty)\n";
            return;
        }
        printTreeRec(root, "", true, true);
    }

    void printSummary() const {
        std::cout << "┌────────────────────────────────────────────────────────┐\n";
        std::cout << "│ Mode:        " << buildMethod << "\n";
        std::cout << "│ Node Count:  " << size() << "\n";
        std::cout << "│ Tree Height: " << getHeight() << "\n";
        std::cout << "│ Balanced:    " << (isBalanced() ? "Yes (Height diff <= 1)" : "No (Skewed/Degenerate)") << "\n";
        std::cout << "└────────────────────────────────────────────────────────┘\n";
        
        auto printVec = [](const std::string& name, const std::vector<int>& v) {
            std::cout << "  • " << name << ": [";
            for (size_t i = 0; i < v.size(); ++i) {
                std::cout << v[i] << (i + 1 < v.size() ? ", " : "");
            }
            std::cout << "]\n";
        };

        std::cout << "Traversals:\n";
        printVec("In-Order (Sorted)   ", inOrder());
        printVec("Pre-Order (Root 1st)", preOrder());
        printVec("Post-Order          ", postOrder());
    }
};

// ==========================================
// 3. Main Function
// ==========================================
int main(int argc, char* argv[]) {
    std::vector<int> arr;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            arr.push_back(std::stoi(argv[i]));
        }
    } else {
        arr = {50, 30, 70, 20, 40, 60, 80};
    }

    std::cout << "==========================================================\n";
    std::cout << " Input Array: [";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << (i + 1 < arr.size() ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "==========================================================\n\n";

    std::unique_ptr<BinarySearchTree> seqTree(BinarySearchTree::fromArraySequential(arr));
    std::cout << "MODE 1: SEQUENTIAL INSERTION\n";
    seqTree->printSummary();
    std::cout << "\nTree Visualization:\n";
    seqTree->printTree();

    std::cout << "\n==========================================================\n";
    std::unique_ptr<BinarySearchTree> balTree(BinarySearchTree::fromArrayBalanced(arr));
    std::cout << "MODE 2: BALANCED BST (O(log N))\n";
    balTree->printSummary();
    std::cout << "\nTree Visualization:\n";
    balTree->printTree();

    return 0;
}
