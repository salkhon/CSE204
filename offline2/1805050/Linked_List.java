import java.util.Random;
import java.util.Scanner;

public class Linked_List<T> {
    private Node head;
    private Node tail;
    private int numElem;

    public Linked_List() {
        this.numElem = 0;
    }

    public int size() {
        return this.numElem;
    }

    // adds to the last
    public void add(T item) {
        if (isEmpty()) {
            this.head = new Node(item, null, null);
            this.tail = head;
        } else {
            this.tail.next = new Node(item, null, this.tail);
            this.tail = this.tail.next;
        }
        this.numElem++;
    }

    public void add(int i, T item) throws IndexOutOfBoundsException {
        if (i < 0 || i > this.numElem) {
            throw new IndexOutOfBoundsException("List index has to be between 0 and " + this.numElem);
        }

        if (i == this.numElem) {
            // handles add last and empty list case
            add(item);
            return;
        }

        Node target = getNodeAt(i);

        Node node = new Node(item, target, target.prev);

        if (target.prev != null) {
            target.prev.next = node;
        } else {
            // add to index 0 of not empty list
            this.head = node;
        }
        target.prev = node;

        this.numElem++;
    }

    // assumes list is not empty and index < this.numEle
    private Node getNodeAt(int index) {
        Node current = this.head;
        int i = 0;
        while (i < index) {
            i++;
            current = current.next;
        }
        return current;
    }

    public T get(int i) {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("List is empty");
        }

        if (i < 0 || i >= this.numElem) {
            throw new IndexOutOfBoundsException("List index has to be between 0 and " + (this.numElem - 1));
        }

        return getNodeAt(i).value;
    }

    public T getFirstElement() {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("List is empty");
        }

        return this.head.value;
    }

    // gets and removes first element
    public T popFirstElement() {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("List is empty");
        }

        Node first = this.head;
        this.head = this.head.next;
        if (this.head != null) {
            this.head.prev = null;
        }

        this.numElem--;

        return first.value;
    }

    public T getLastElement() {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("List is empty");
        }

        return this.tail.value;
    }

    // gets and removes last element
    public T popLastElement() {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("List is empty");
        }

        Node last = this.tail;
        this.tail = this.tail.prev;
        if (this.tail != null) {
            this.tail.next = null;
        }

        this.numElem--;

        return last.value;
    }

    public void remove(int i) {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("List is empty");
        }

        if (i < 0 || i >= this.numElem) {
            throw new IndexOutOfBoundsException("List index has to be between 0 and " + (this.numElem - 1));
        }

        Node target = getNodeAt(i);

        removeNode(target);
    }

    public void remove(T item) {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("List is empty");
        }

        for (Node current = this.head; current != null; current = current.next) {
            if (current.value.equals(item)) {
                removeNode(current);
            }
        }
    }

    private void removeNode(Node target) {
        if (target.prev != null) {
            target.prev.next = target.next;
        } else {
            // first element of non empty list
            this.head = target.next;
        }

        if (target.next != null) {
            target.next.prev = target.prev;
        } else {
            // last element
            this.tail = target.prev;
        }
        this.numElem--;
    }

    public boolean isEmpty() {
        return this.head == null;
    }

    private class Node {
        public T value;
        public Node next;
        public Node prev;

        public Node(T value, Node next, Node prev) {
            this.value = value;
            this.next = next;
            this.prev = prev;
        }
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder("\nNumber of Elements: " + this.numElem + "\n");
        stringBuilder.append("[ ");
        int i = 0;
        for (Node current = this.head; current != null; current = current.next) {
            stringBuilder.append(current.value).append(" AT ").append(i++);
            if (current.next != null) {
                stringBuilder.append(", ");
            }
        }
        stringBuilder.append(" ]\n");
        return stringBuilder.toString();
    }

    // test client
    public static void main(String[] args) {
        Linked_List<String> linkedList = new Linked_List<>();

        Random random = new Random();

        for (int i = 0; i < 10; i++) {
            linkedList.add(String.valueOf(random.nextInt(100)));
        }

        Scanner scanner = new Scanner(System.in);

        boolean isQuit = false;
        while (!isQuit) {
            displayMenu();
            int op = scanner.nextInt();
            scanner.nextLine();

            int index;
            String value;
            switch (op) {
                case 1:
                    System.out.print("Enter value: ");
                    value = scanner.nextLine();
                    linkedList.add(value);
                    break;

                case 2:
                    System.out.print("Enter index and value: ");
                    index = scanner.nextInt();
                    value = scanner.nextLine();
                    linkedList.add(index, value);
                    break;

                case 3:
                    System.out.print("Enter index: ");
                    index = scanner.nextInt();
                    scanner.nextLine();
                    System.out.println(linkedList.get(index));
                    break;

                case 4:
                    System.out.println(linkedList.popFirstElement());
                    break;

                case 5:
                    System.out.println(linkedList.popLastElement());
                    break;

                case 6:
                    System.out.print("Enter index: ");
                    index = scanner.nextInt();
                    scanner.nextLine();
                    linkedList.remove(index);
                    break;

                case 7:
                    System.out.print("Enter index: ");
                    value = scanner.nextLine();
                    linkedList.remove(value);
                    break;

                default:
                    isQuit = true;
            }

            System.out.println(linkedList);
        }
    }

    public static void displayMenu() {
        System.out.println("Operations: ");
        System.out.println("1. Add to last");
        System.out.println("2. Add at index: ");
        System.out.println("3. Get from index");
        System.out.println("4. Pop first element");
        System.out.println("5. Pop last element");
        System.out.println("6. Remove from index");
        System.out.println("7. Remove value");
        System.out.println("Default: Quit");
        System.out.print("Enter option: ");
    }
}
