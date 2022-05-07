import java.util.Scanner;

public class BinarySearchTree<T extends Comparable<T>> {
    private Node root;

    public BinarySearchTree() {
    }

    private int heightOfNode(Node node) {
        int height = 0;
        if (node != null) {
            height = node.heightOfSubtree;
        }
        return height;
    }

    private int subtreeSizeOfNode(Node node) {
        int size = 0;
        if (node != null) {
            size = node.subtreeSize;
        }
        return size;
    }

    private void updateNodeInformation(Node node) {
        if (node != null) {
            node.heightOfSubtree = Integer.max(heightOfNode(node.left), heightOfNode(node.right)) + 1;
            node.subtreeSize = subtreeSizeOfNode(node.left) + subtreeSizeOfNode(node.right) + 1;
        }
    }

    public void insertItem(T item) {
        this.root = insertItem(item, this.root);
    }

    private Node insertItem(T item, Node node) {
        if (node == null) {
            return new Node(item, null, null, 1, 1);
        }

        if (item.compareTo(node.value) < 0) {
            node.left = insertItem(item, node.left);
        } else if (item.compareTo(node.value) > 0) {
            node.right = insertItem(item, node.right);
        }

        updateNodeInformation(node);

        return node;
    }

    public void searchItem(T item) {
        boolean isFound = false;
        Node currentNode = this.root;
        while (currentNode != null && !isFound) {
            if (item.compareTo(currentNode.value) < 0) {
                currentNode = currentNode.left;
            } else if (item.compareTo(currentNode.value) > 0) {
                currentNode = currentNode.right;
            } else {
                isFound = true;
            }
        }

        System.out.println(item + " has " +
                (isFound ? "" : "not")
                + " been found.");

    }

    public T getInOrderSuccessor(T item) {
        Node currentNode = this.root;
        Node lowestSuccessor = null;
        while (currentNode != null) {
            if (item.compareTo(currentNode.value) < 0) {
                lowestSuccessor = currentNode;
                currentNode = currentNode.left;
            } else {
                currentNode = currentNode.right;
            }
        }
        return lowestSuccessor != null ?
                lowestSuccessor.value : null;
    }

    public T getInOrderPredecessor(T item) {
        Node currentNode = this.root;
        Node highestPredecessor = null;
        while (currentNode != null) {
            if (item.compareTo(currentNode.value) > 0) {
                highestPredecessor = currentNode;
                currentNode = currentNode.right;
            } else {
                currentNode = currentNode.left;
            }
        }
        return highestPredecessor != null ?
                highestPredecessor.value : null;
    }

    public void deleteItem(T item) {
        this.root = deleteItem(item, this.root);
        updateNodeInformation(this.root);
    }

    private Node deleteItem(T item, Node node) {
        if (node == null) {
            return null;
        }

        if (item.compareTo(node.value) < 0) {
            node.left = deleteItem(item, node.left);
        } else if (item.compareTo(node.value) > 0) {
            node.right = deleteItem(item, node.right);
        } else {
            Node replacement;
            if (node.right != null) {
                replacement = getMin(node.right);
                node.right = delMin(node.right);
                replacement.left = node.left;
                replacement.right = node.right;
            } else {
                replacement = node.left;
            }
            node = replacement;
        }

        updateNodeInformation(node);

        return node;
    }

    private Node delMin(Node node) {
        // initial node cannot be null
        if (node.left == null) {
            return node.right;
        }

        node.left = delMin(node.left);

        updateNodeInformation(node);

        return node;
    }

    public int getItemDepth(T item) {
        boolean isFound = false;
        Node current = this.root;
        int depth = 0;
        while (!isFound && current != null) {
            if (item.compareTo(current.value) < 0) {
                current = current.left;
                depth++;
            } else if (item.compareTo(current.value) > 0) {
                current = current.right;
                depth++;
            } else {
                depth++;
                isFound = true;
            }
        }

        return isFound ?
                depth : -1;
    }

    public T getMaxItem() {
        Node max = getMax(this.root);
        return max != null ?
                max.value : null;
    }

    private Node getMax(Node node) {
        Node current = node;
        if (current != null) {
            while (current.right != null) {
                current = current.right;
            }
        }
        return current;
    }

    public T getMinItem() {
        Node min = getMin(this.root);
        return min != null ?
                min.value : null;
    }

    private Node getMin(Node node) {
        Node current = node;
        if (current != null) {
            while (current.left != null) {
                current = current.left;
            }
        }
        return current;
    }

    public int getHeight(T item) {
        int height = -1;
        Node current = this.root;
        while (current != null) {
            if (item.compareTo(current.value) < 0) {
                current = current.left;
            } else if (item.compareTo(current.value) > 0) {
                current = current.right;
            } else {
                height = current.heightOfSubtree;
                break;
            }
        }
        return height;
    }

    public void printInOrder() {
        printInOrder(this.root);
    }

    private void printInOrder(Node node) {
        if (node != null) {
            printInOrder(node.left);
            System.out.print(node.value + " ");
            printInOrder(node.right);
        }
        if (node == this.root) {
            System.out.println();
        }
    }

    public void printPreOrder() {
        printPreOrder(this.root);
    }

    private void printPreOrder(Node node) {
        if (node != null) {
            System.out.print(node.value + " ");
            printPreOrder(node.left);
            printPreOrder(node.right);
        }
        if (node == this.root) {
            System.out.println();
        }
    }

    public void printPostOrder() {
        printPostOrder(this.root);
    }

    private void printPostOrder(Node node) {
        if (node != null) {
            printPostOrder(node.left);
            printPostOrder(node.right);
            System.out.print(node.value + " ");
        }
        if (node == this.root) {
            System.out.println();
        }
    }

    public int getSize() {
        int size = 0;
        if (this.root != null) {
            size = this.root.subtreeSize;
        }
        return size;
    }

    private class Node implements Comparable<Node> {
        public T value;
        public Node left;
        public Node right;
        public int heightOfSubtree;
        public int subtreeSize;

        public Node(T value, Node left, Node right, int heightOfSubtree, int subTreeSize) {
            this.value = value;
            this.left = left;
            this.right = right;
            this.heightOfSubtree = heightOfSubtree;
            this.subtreeSize = subTreeSize;
        }

        @Override
        public int compareTo(Node that) {
            return this.value.compareTo(that.value);
        }
    }


    public static void main(String[] args) {
        BinarySearchTree<Integer> integerBinarySearchTree = new BinarySearchTree<>();

        Scanner scanner = new Scanner(System.in);
        int option;
        int item;
        do {
            displayMenu();
            option = scanner.nextInt();
            scanner.nextLine();

            switch (option) {
                case 1:
                    item = getItem(scanner);
                    integerBinarySearchTree.insertItem(item);
                    break;
                case 2:
                    item = getItem(scanner);
                    integerBinarySearchTree.searchItem(item);
                    break;
                case 3:
                    item = getItem(scanner);
                    System.out.println("Inorder successor: " +
                            integerBinarySearchTree.getInOrderSuccessor(item));
                    break;
                case 4:
                    item = getItem(scanner);
                    System.out.println("Inorder predecessor: " +
                            integerBinarySearchTree.getInOrderPredecessor(item));
                    break;
                case 5:
                    item = getItem(scanner);
                    integerBinarySearchTree.deleteItem(item);
                    break;
                case 6:
                    item = getItem(scanner);
                    System.out.println("Item depth: " +
                            integerBinarySearchTree.getItemDepth(item));
                    break;
                case 7:
                    System.out.println("Max item: " + integerBinarySearchTree.getMaxItem());
                    break;
                case 8:
                    System.out.println("Min item: " + integerBinarySearchTree.getMinItem());
                    break;
                case 9:
                    item = getItem(scanner);
                    System.out.println("Height: " + integerBinarySearchTree.getHeight(item));
                    break;
                case 10:
                    integerBinarySearchTree.printInOrder();
                    break;
                case 11:
                    integerBinarySearchTree.printPreOrder();
                    break;
                case 12:
                    integerBinarySearchTree.printPostOrder();
                    break;
                case 13:
                    System.out.println("Size: " + integerBinarySearchTree.getSize());
                    break;
            }
        } while (option != 14);
    }

    private static void displayMenu() {
        System.out.println();
        System.out.println("1. Insert Item");
        System.out.println("2. Search Item");
        System.out.println("3. Get In Order Successor");
        System.out.println("4. Get In Order Predecessor");
        System.out.println("5. Delete Item");
        System.out.println("6. Get Item Depth");
        System.out.println("7. Get Max Item");
        System.out.println("8. Get Min Item");
        System.out.println("9. Get Height");
        System.out.println("10. Print In Order");
        System.out.println("11. Print Pre Order");
        System.out.println("12. Print Post Order");
        System.out.println("13. Get Size");
        System.out.println("14. Quit");

        System.out.print("Enter option: ");
    }

    private static int getItem(Scanner scanner) {
        System.out.print("Enter item: ");
        int item = scanner.nextInt();
        scanner.nextLine();
        return item;
    }
}
//    // test client
//    public static void main(String[] args) {
//        BinarySearchTree<Integer> integerBinarySearchTree = new BinarySearchTree<>();
//        Random random = new Random();
//        for (int i = 0; i < 50; i++) {
//            int r = random.nextInt(100);
//            integerBinarySearchTree.insertItem(r);
//            System.out.println("Inserted " + r + " at height " + integerBinarySearchTree.getHeight(r));
//            System.out.println("Depth: " + integerBinarySearchTree.getItemDepth(r));
//        }
//
//        for (int i = 0; i < 10; i++) {
//            int r = random.nextInt(100);
//            integerBinarySearchTree.deleteItem(r);
//        }
//
//        System.out.println("Inorder:");
//        integerBinarySearchTree.printInOrder();
//        System.out.println("Preorder");
//        integerBinarySearchTree.printPreOrder();
//        System.out.println("Postorder");
//        integerBinarySearchTree.printPostOrder();
//
//        for (int i = 0; i < 5; i++) {
//            int r = random.nextInt(100);
//            System.out.println("Successor of " + r + " : " + integerBinarySearchTree.getInOrderSuccessor(r));
//            System.out.println("Predecessor of " + r + " : " + integerBinarySearchTree.getInOrderPredecessor(r));
//        }
//
//        System.out.println("Min: " + integerBinarySearchTree.getMinItem());
//        System.out.println("Max: " + integerBinarySearchTree.getMaxItem());
//    }

