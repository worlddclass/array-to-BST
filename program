import java.util.*;

/**
 * Binary Search Tree (BST) Generator & Visualizer
 *
 * This program takes an array of numbers and constructs a Binary Search Tree
 * using either:
 *   1. Balanced BST Construction: Sorts the array and recursively picks medians,
 *      guaranteeing an optimal O(log N) height.
 *   2. Sequential Insertion: Inserts elements one-by-one in original array order,
 *      preserving arrival order.
 *
 * Features:
 *   - Clean 2D ASCII Tree Visualizer (compatible with all terminals)
 *   - In-Order, Pre-Order, Post-Order, and Level-Order traversals
 *   - Search with step-by-step path tracing
 *   - Tree statistics: Height, Node Count, Min/Max, and Balance check
 *   - Interactive console & pre-configured demos
 */
public class Program {

    // ==========================================
    // 1. Tree Node Definition
    // ==========================================
    public static class TreeNode {
        public int val;
        public TreeNode left;
        public TreeNode right;

        public TreeNode(int val) {
            this.val = val;
            this.left = null;
            this.right = null;
        }
    }

    // ==========================================
    // 2. Binary Search Tree Implementation
    // ==========================================
    public static class BinarySearchTree {
        private TreeNode root;
        private final String buildMethod;

        public BinarySearchTree(String buildMethod) {
            this.root = null;
            this.buildMethod = buildMethod;
        }

        public TreeNode getRoot() {
            return root;
        }

        public String getBuildMethod() {
            return buildMethod;
        }

        // ------------------------------------------
        // Sequential Insertion (Original Order)
        // ------------------------------------------
        public static BinarySearchTree fromArraySequential(int[] array) {
            BinarySearchTree bst = new BinarySearchTree("Sequential Insertion (Original Order)");
            if (array == null || array.length == 0) return bst;

            for (int value : array) {
                bst.insert(value);
            }
            return bst;
        }

        public void insert(int value) {
            root = insertRec(root, value);
        }

        private TreeNode insertRec(TreeNode current, int value) {
            if (current == null) {
                return new TreeNode(value);
            }
            if (value < current.val) {
                current.left = insertRec(current.left, value);
            } else if (value > current.val) {
                current.right = insertRec(current.right, value);
            } else {
                // Duplicate values are skipped in standard BST
            }
            return current;
        }

        // ------------------------------------------
        // Balanced BST Construction (Optimal O(log N))
        // ------------------------------------------
        public static BinarySearchTree fromArrayBalanced(int[] array) {
            BinarySearchTree bst = new BinarySearchTree("Balanced BST (Optimal Minimal Height)");
            if (array == null || array.length == 0) return bst;

            // Remove duplicates and sort elements
            int[] uniqueSorted = Arrays.stream(array).distinct().sorted().toArray();
            bst.root = buildBalancedRec(uniqueSorted, 0, uniqueSorted.length - 1);
            return bst;
        }

        private static TreeNode buildBalancedRec(int[] sortedArr, int start, int end) {
            if (start > end) {
                return null;
            }
            // Pick median element as subtree root
            int mid = start + (end - start) / 2;
            TreeNode node = new TreeNode(sortedArr[mid]);

            node.left = buildBalancedRec(sortedArr, start, mid - 1);
            node.right = buildBalancedRec(sortedArr, mid + 1, end);

            return node;
        }

        // ------------------------------------------
        // Search with Path Trace
        // ------------------------------------------
        public static class SearchResult {
            public boolean found;
            public List<Integer> path = new ArrayList<>();
            public int comparisons = 0;
        }

        public SearchResult search(int key) {
            SearchResult res = new SearchResult();
            TreeNode curr = root;

            while (curr != null) {
                res.path.add(curr.val);
                res.comparisons++;
                if (key == curr.val) {
                    res.found = true;
                    return res;
                } else if (key < curr.val) {
                    curr = curr.left;
                } else {
                    curr = curr.right;
                }
            }
            res.found = false;
            return res;
        }

        // ------------------------------------------
        // Tree Statistics & Properties
        // ------------------------------------------
        public int getHeight() {
            return calculateHeight(root);
        }

        private int calculateHeight(TreeNode node) {
            if (node == null) return 0;
            return 1 + Math.max(calculateHeight(node.left), calculateHeight(node.right));
        }

        public int size() {
            return countNodes(root);
        }

        private int countNodes(TreeNode node) {
            if (node == null) return 0;
            return 1 + countNodes(node.left) + countNodes(node.right);
        }

        public Integer getMin() {
            if (root == null) return null;
            TreeNode curr = root;
            while (curr.left != null) curr = curr.left;
            return curr.val;
        }

        public Integer getMax() {
            if (root == null) return null;
            TreeNode curr = root;
            while (curr.right != null) curr = curr.right;
            return curr.val;
        }

        public boolean isBalanced() {
            return checkBalanced(root) != -1;
        }

        private int checkBalanced(TreeNode node) {
            if (node == null) return 0;
            int leftHeight = checkBalanced(node.left);
            if (leftHeight == -1) return -1;
            int rightHeight = checkBalanced(node.right);
            if (rightHeight == -1) return -1;

            if (Math.abs(leftHeight - rightHeight) > 1) return -1;
            return 1 + Math.max(leftHeight, rightHeight);
        }

        // ------------------------------------------
        // Traversals
        // ------------------------------------------
        public List<Integer> inOrderTraversal() {
            List<Integer> list = new ArrayList<>();
            inOrderRec(root, list);
            return list;
        }

        private void inOrderRec(TreeNode node, List<Integer> list) {
            if (node != null) {
                inOrderRec(node.left, list);
                list.add(node.val);
                inOrderRec(node.right, list);
            }
        }

        public List<Integer> preOrderTraversal() {
            List<Integer> list = new ArrayList<>();
            preOrderRec(root, list);
            return list;
        }

        private void preOrderRec(TreeNode node, List<Integer> list) {
            if (node != null) {
                list.add(node.val);
                preOrderRec(node.left, list);
                preOrderRec(node.right, list);
            }
        }

        public List<Integer> postOrderTraversal() {
            List<Integer> list = new ArrayList<>();
            postOrderRec(root, list);
            return list;
        }

        private void postOrderRec(TreeNode node, List<Integer> list) {
            if (node != null) {
                postOrderRec(node.left, list);
                postOrderRec(node.right, list);
                list.add(node.val);
            }
        }

        public List<List<Integer>> levelOrderTraversal() {
            List<List<Integer>> result = new ArrayList<>();
            if (root == null) return result;

            Queue<TreeNode> queue = new LinkedList<>();
            queue.add(root);

            while (!queue.isEmpty()) {
                int levelSize = queue.size();
                List<Integer> currentLevel = new ArrayList<>();
                for (int i = 0; i < levelSize; i++) {
                    TreeNode node = queue.poll();
                    currentLevel.add(node.val);
                    if (node.left != null) queue.add(node.left);
                    if (node.right != null) queue.add(node.right);
                }
                result.add(currentLevel);
            }
            return result;
        }

        // ------------------------------------------
        // Universal ASCII Tree Renderer
        // ------------------------------------------
        public void printTree() {
            if (root == null) {
                System.out.println("  (Tree is empty)");
                return;
            }
            printTreeRec(root, "", true, true);
        }

        private void printTreeRec(TreeNode node, String prefix, boolean isTail, boolean isRoot) {
            if (node == null) return;

            String branch = isRoot ? "-- " : (isTail ? "\\-- " : "|-- ");
            System.out.println(prefix + branch + "[" + node.val + "]");

            List<TreeNode> children = new ArrayList<>();
            List<String> labels = new ArrayList<>();

            if (node.left != null || node.right != null) {
                children.add(node.left);
                labels.add("L");
                children.add(node.right);
                labels.add("R");
            }

            for (int i = 0; i < children.size(); i++) {
                boolean childIsTail = (i == children.size() - 1);
                String childPrefix = prefix + (isRoot ? "    " : (isTail ? "    " : "|   "));
                TreeNode child = children.get(i);
                if (child != null) {
                    printNodeWithLabel(child, childPrefix, childIsTail, labels.get(i));
                } else {
                    String nullBranch = childIsTail ? "\\-- " : "|-- ";
                    System.out.println(childPrefix + nullBranch + "(" + labels.get(i) + ": null)");
                }
            }
        }

        private void printNodeWithLabel(TreeNode node, String prefix, boolean isTail, String label) {
            String branch = isTail ? "\\-- " : "|-- ";
            System.out.println(prefix + branch + "(" + label + ") [" + node.val + "]");

            List<TreeNode> children = new ArrayList<>();
            List<String> labels = new ArrayList<>();

            if (node.left != null || node.right != null) {
                children.add(node.left);
                labels.add("L");
                children.add(node.right);
                labels.add("R");
            }

            for (int i = 0; i < children.size(); i++) {
                boolean childIsTail = (i == children.size() - 1);
                String childPrefix = prefix + (isTail ? "    " : "|   ");
                TreeNode child = children.get(i);
                if (child != null) {
                    printNodeWithLabel(child, childPrefix, childIsTail, labels.get(i));
                } else {
                    String nullBranch = childIsTail ? "\\-- " : "|-- ";
                    System.out.println(childPrefix + nullBranch + "(" + labels.get(i) + ": null)");
                }
            }
        }

        public void printSummary() {
            System.out.println("+----------------------------------------------------------+");
            System.out.printf ("| Mode:        %-43s |%n", buildMethod);
            System.out.printf ("| Node Count:  %-43d |%n", size());
            System.out.printf ("| Tree Height: %-43d |%n", getHeight());
            System.out.printf ("| Min Value:   %-43s |%n", (getMin() != null ? getMin() : "N/A"));
            System.out.printf ("| Max Value:   %-43s |%n", (getMax() != null ? getMax() : "N/A"));
            System.out.printf ("| Balanced:    %-43s |%n", (isBalanced() ? "Yes (Height diff <= 1)" : "No (Skewed/Degenerate)"));
            System.out.println("+----------------------------------------------------------+");
            System.out.println("Traversals:");
            System.out.println("  * In-Order (Sorted):    " + inOrderTraversal());
            System.out.println("  * Pre-Order (Root 1st): " + preOrderTraversal());
            System.out.println("  * Post-Order:           " + postOrderTraversal());
            System.out.println("  * Level-Order (BFS):    " + levelOrderTraversal());
        }
    }

    // ==========================================
    // 3. User Interface & Main Entry Point
    // ==========================================
    public static void main(String[] args) {
        // If command-line arguments are provided, process them directly
        if (args != null && args.length > 0) {
            try {
                int[] cliArray = Arrays.stream(args).mapToInt(Integer::parseInt).toArray();
                System.out.println("==========================================================");
                System.out.println(" Processing input array from command line arguments: ");
                System.out.println(" Array: " + Arrays.toString(cliArray));
                System.out.println("==========================================================");
                displayComparison(cliArray);
                return;
            } catch (NumberFormatException e) {
                System.out.println("Warning: Non-integer arguments provided. Falling back to interactive menu.");
            }
        }

        Scanner scanner = new Scanner(System.in);
        while (true) {
            printHeader();
            System.out.println("1. Enter custom array (e.g. 50, 30, 70, 20, 40, 60, 80)");
            System.out.println("2. Demo 1: Sorted Array [1, 2, 3, 4, 5, 6, 7] (Sequential vs Balanced)");
            System.out.println("3. Demo 2: Arbitrary Array [55, 23, 89, 12, 38, 71, 99, 4, 19, 65]");
            System.out.println("4. Demo 3: Array with Duplicates [15, 10, 20, 10, 15, 25, 5, 30]");
            System.out.println("5. Exit");
            System.out.print("\nSelect an option (1-5): ");

            String input = scanner.nextLine().trim();
            if (input.equals("5") || input.equalsIgnoreCase("exit") || input.equalsIgnoreCase("q")) {
                System.out.println("\nGoodbye!");
                break;
            }

            switch (input) {
                case "1":
                    System.out.println("\nEnter numbers separated by spaces or commas:");
                    System.out.print("> ");
                    String line = scanner.nextLine().trim();
                    if (line.isEmpty()) {
                        System.out.println("Error: Empty input.");
                        break;
                    }
                    try {
                        int[] customArr = parseArray(line);
                        displayComparisonWithInteraction(customArr, scanner);
                    } catch (Exception e) {
                        System.out.println("Error parsing array: " + e.getMessage());
                    }
                    break;

                case "2":
                    System.out.println("\n--- DEMO 1: SORTED ARRAY ---");
                    System.out.println("Notice how sequential insertion creates a linked-list (height = 7),");
                    System.out.println("whereas balanced construction keeps height = 3 (optimal O(log N))!");
                    displayComparisonWithInteraction(new int[]{1, 2, 3, 4, 5, 6, 7}, scanner);
                    break;

                case "3":
                    System.out.println("\n--- DEMO 2: ARBITRARY ARRAY ---");
                    displayComparisonWithInteraction(new int[]{55, 23, 89, 12, 38, 71, 99, 4, 19, 65}, scanner);
                    break;

                case "4":
                    System.out.println("\n--- DEMO 3: ARRAY WITH DUPLICATES ---");
                    displayComparisonWithInteraction(new int[]{15, 10, 20, 10, 15, 25, 5, 30}, scanner);
                    break;

                default:
                    System.out.println("Invalid option, please try again.");
            }

            System.out.println("\nPress ENTER to continue to main menu...");
            scanner.nextLine();
        }
    }

    private static void printHeader() {
        System.out.println("\n==========================================================");
        System.out.println("       BINARY SEARCH TREE (BST) GENERATOR & VISUALIZER    ");
        System.out.println("==========================================================");
    }

    public static int[] parseArray(String line) {
        String[] tokens = line.split("[,\\s]+");
        List<Integer> list = new ArrayList<>();
        for (String t : tokens) {
            String trimmed = t.trim();
            if (!trimmed.isEmpty()) {
                list.add(Integer.parseInt(trimmed));
            }
        }
        int[] res = new int[list.size()];
        for (int i = 0; i < list.size(); i++) res[i] = list.get(i);
        return res;
    }

    public static void displayComparison(int[] array) {
        System.out.println("\nInput Array: " + Arrays.toString(array));
        System.out.println("Unique Element Count: " + Arrays.stream(array).distinct().count());

        // 1. Sequential Insertion Tree
        System.out.println("\n==========================================================");
        System.out.println(" MODE 1: SEQUENTIAL INSERTION (Preserves Arrival Order)");
        System.out.println("==========================================================");
        BinarySearchTree seqTree = BinarySearchTree.fromArraySequential(array);
        seqTree.printSummary();
        System.out.println("\nTree Visualization:");
        seqTree.printTree();

        // 2. Balanced Tree
        System.out.println("\n==========================================================");
        System.out.println(" MODE 2: BALANCED BST (Minimal Height, O(log N))");
        System.out.println("==========================================================");
        BinarySearchTree balancedTree = BinarySearchTree.fromArrayBalanced(array);
        balancedTree.printSummary();
        System.out.println("\nTree Visualization:");
        balancedTree.printTree();

        // Height comparison
        System.out.println("\n----------------------------------------------------------");
        System.out.println(" COMPARISON SUMMARY");
        System.out.println("----------------------------------------------------------");
        System.out.println(" Sequential Tree Height: " + seqTree.getHeight() + (seqTree.isBalanced() ? " (Balanced)" : " (Unbalanced)"));
        System.out.println(" Balanced Tree Height:   " + balancedTree.getHeight() + " (Optimal)");
        System.out.println("----------------------------------------------------------");
    }

    private static void displayComparisonWithInteraction(int[] array, Scanner scanner) {
        displayComparison(array);

        BinarySearchTree balancedTree = BinarySearchTree.fromArrayBalanced(array);
        BinarySearchTree seqTree = BinarySearchTree.fromArraySequential(array);

        while (true) {
            System.out.println("\nSub-menu for this tree:");
            System.out.println("  s) Search for a value (shows comparison path)");
            System.out.println("  i) Insert a new value");
            System.out.println("  b) Back to main menu");
            System.out.print("Your choice: ");
            String opt = scanner.nextLine().trim();

            if (opt.equalsIgnoreCase("b") || opt.isEmpty()) {
                break;
            } else if (opt.equalsIgnoreCase("s")) {
                System.out.print("Enter integer to search: ");
                try {
                    int val = Integer.parseInt(scanner.nextLine().trim());
                    BinarySearchTree.SearchResult rSeq = seqTree.search(val);
                    BinarySearchTree.SearchResult rBal = balancedTree.search(val);

                    System.out.println("\nSearch in Sequential Tree:");
                    System.out.println("  Found: " + rSeq.found);
                    System.out.println("  Path:  " + rSeq.path + " (Comparisons: " + rSeq.comparisons + ")");

                    System.out.println("Search in Balanced Tree:");
                    System.out.println("  Found: " + rBal.found);
                    System.out.println("  Path:  " + rBal.path + " (Comparisons: " + rBal.comparisons + ")");
                } catch (NumberFormatException e) {
                    System.out.println("Invalid integer.");
                }
            } else if (opt.equalsIgnoreCase("i")) {
                System.out.print("Enter integer to insert: ");
                try {
                    int val = Integer.parseInt(scanner.nextLine().trim());
                    seqTree.insert(val);
                    balancedTree.insert(val);
                    System.out.println("Inserted " + val + " into both trees!");
                    System.out.println("\nUpdated Balanced Tree:");
                    balancedTree.printTree();
                } catch (NumberFormatException e) {
                    System.out.println("Invalid integer.");
                }
            }
        }
    }
}
