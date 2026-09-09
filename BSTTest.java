import java.util.*;

/**
 * Automated Unit Test Suite for Binary Search Tree Program
 * Run with: java BSTTest.java
 */
public class BSTTest {

    private static int testsPassed = 0;
    private static int testsFailed = 0;

    public static void main(String[] args) {
        System.out.println("==========================================================");
        System.out.println("          RUNNING AUTOMATED BST TEST SUITE                ");
        System.out.println("==========================================================\n");

        testEmptyArray();
        testSingleElement();
        testBalancedHeightProperty();
        testSequentialDegenerateCase();
        testInOrderProperty();
        testDuplicateHandling();
        testNegativeNumbers();
        testSearchExisting();
        testSearchMissing();
        testDynamicInsertion();

        System.out.println("\n==========================================================");
        System.out.println(" TEST RESULTS: " + testsPassed + " Passed, " + testsFailed + " Failed");
        System.out.println("==========================================================");

        if (testsFailed > 0) {
            System.exit(1);
        }
    }

    private static void assertTrue(String testName, boolean condition, String message) {
        if (condition) {
            System.out.println("  [PASS] " + testName);
            testsPassed++;
        } else {
            System.err.println("  [FAIL] " + testName + " -> " + message);
            testsFailed++;
        }
    }

    private static void assertEquals(String testName, Object expected, Object actual) {
        if (Objects.equals(expected, actual)) {
            System.out.println("  [PASS] " + testName);
            testsPassed++;
        } else {
            System.err.println("  [FAIL] " + testName + " -> Expected: " + expected + ", Got: " + actual);
            testsFailed++;
        }
    }

    // ----------------------------------------------------
    // Tests
    // ----------------------------------------------------

    private static void testEmptyArray() {
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(new int[]{});
        assertEquals("Empty Array: size is 0", 0, bst.size());
        assertEquals("Empty Array: height is 0", 0, bst.getHeight());
        assertTrue("Empty Array: root is null", bst.getRoot() == null, "Root should be null");
    }

    private static void testSingleElement() {
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(new int[]{42});
        assertEquals("Single Element: size is 1", 1, bst.size());
        assertEquals("Single Element: height is 1", 1, bst.getHeight());
        assertEquals("Single Element: min is 42", Integer.valueOf(42), bst.getMin());
        assertEquals("Single Element: max is 42", Integer.valueOf(42), bst.getMax());
        assertTrue("Single Element: is balanced", bst.isBalanced(), "Should be balanced");
    }

    private static void testBalancedHeightProperty() {
        // For N = 7, optimal height is floor(log2(7)) + 1 = 3
        int[] arr = {1, 2, 3, 4, 5, 6, 7};
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(arr);
        assertEquals("Balanced Tree: size is 7", 7, bst.size());
        assertEquals("Balanced Tree: optimal height is 3", 3, bst.getHeight());
        assertTrue("Balanced Tree: isBalanced() is true", bst.isBalanced(), "Tree should satisfy AVL balance");
    }

    private static void testSequentialDegenerateCase() {
        // Sorted input into sequential BST creates a linked list of height N
        int[] arr = {1, 2, 3, 4, 5, 6, 7};
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArraySequential(arr);
        assertEquals("Sequential Tree: height is 7 (linear stick)", 7, bst.getHeight());
        assertTrue("Sequential Tree: isBalanced() is false", !bst.isBalanced(), "Should NOT be balanced");
    }

    private static void testInOrderProperty() {
        // In-order traversal of a valid BST must ALWAYS be strictly sorted
        int[] arr = {65, 12, 89, 4, 38, 71, 99, 23};
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(arr);
        List<Integer> inOrder = bst.inOrderTraversal();

        boolean isSorted = true;
        for (int i = 1; i < inOrder.size(); i++) {
            if (inOrder.get(i) <= inOrder.get(i - 1)) {
                isSorted = false;
                break;
            }
        }
        assertTrue("BST Property: In-Order is strictly ascending", isSorted, "In-order traversal must be sorted");
    }

    private static void testDuplicateHandling() {
        // [10, 20, 10, 30, 20, 40] has 4 unique elements: 10, 20, 30, 40
        int[] arr = {10, 20, 10, 30, 20, 40};
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(arr);
        assertEquals("Duplicates: size is 4 unique keys", 4, bst.size());
        assertEquals("Duplicates: min is 10", Integer.valueOf(10), bst.getMin());
        assertEquals("Duplicates: max is 40", Integer.valueOf(40), bst.getMax());
    }

    private static void testNegativeNumbers() {
        int[] arr = {-50, 20, -10, 0, 35, -5};
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(arr);
        assertEquals("Negative numbers: min is -50", Integer.valueOf(-50), bst.getMin());
        assertEquals("Negative numbers: max is 35", Integer.valueOf(35), bst.getMax());
        assertEquals("Negative numbers: size is 6", 6, bst.size());
    }

    private static void testSearchExisting() {
        int[] arr = {50, 30, 70, 20, 40, 60, 80};
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(arr);
        Program.BinarySearchTree.SearchResult result = bst.search(40);
        assertTrue("Search: key 40 found", result.found, "Key 40 should be found");
        assertEquals("Search: path for 40", Arrays.asList(50, 30, 40), result.path);
        assertEquals("Search: comparisons count is 3", 3, result.comparisons);
    }

    private static void testSearchMissing() {
        int[] arr = {50, 30, 70, 20, 40, 60, 80};
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(arr);
        Program.BinarySearchTree.SearchResult result = bst.search(999);
        assertTrue("Search: key 999 not found", !result.found, "Key 999 should not be found");
        assertTrue("Search: visited nodes", result.comparisons > 0, "Should have performed comparisons");
    }

    private static void testDynamicInsertion() {
        Program.BinarySearchTree bst = Program.BinarySearchTree.fromArrayBalanced(new int[]{50, 30, 70});
        assertEquals("Dynamic Insert: initial size is 3", 3, bst.size());
        bst.insert(25);
        assertEquals("Dynamic Insert: size after insertion is 4", 4, bst.size());
        assertTrue("Dynamic Insert: 25 can be found", bst.search(25).found, "Key 25 should be found");
    }
}
