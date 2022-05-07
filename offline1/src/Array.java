import java.util.Random;
import java.util.Scanner;

@SuppressWarnings("unchecked")
public class Array<T extends Comparable<T>> {
    private static final int INIT_SIZE = 2;

    private T[] array;
    private int currentPos;

    public Array() {
        this.array = (T[]) new Comparable[INIT_SIZE];
        this.currentPos = 0;
    }

    public Array(int n) {
        this.array = (T[]) new Comparable[n];
        this.currentPos = 0;
    }

    public Array(T[] array) {
        this.array = (T[]) new Comparable[array.length];
        System.arraycopy(array, 0, this.array, 0, array.length);
        this.currentPos = array.length;
    }

    public T[] getArray() {
        return this.array;
    }

    public T getAnElement(int i) throws ArrayIndexOutOfBoundsException {
        return this.array[i];
    }

    public void add(T element) {
        if (this.currentPos == this.array.length) {
            resizeArray(this.array.length * 2);
        }
        this.array[this.currentPos++] = element;
    }

    public void add(int i, T element) throws ArrayIndexOutOfBoundsException {
        if (i > this.currentPos || i < 0) {
            throw new ArrayIndexOutOfBoundsException("Array index has to be between 0 and " + this.currentPos + ". Provided: " + i);
        }

        if (this.currentPos == this.array.length) {
            resizeArray(this.array.length * 2);
        }
        System.arraycopy(this.array, i, this.array, i + 1, this.currentPos - i);
        this.array[i] = element;
        this.currentPos++;
    }

    public void remove(T element) {
        for (int i = 0; i < this.array.length; i++) {
            if (this.array[i] != null && this.array[i].equals(element)) {
                this.array[i] = null;
            }
        }
        removeNulls();
    }

    private void removeNulls() {
        int swimAmount = 0;
        for (int i = 0; i < this.currentPos; i++) {
            if (this.array[i] == null) {
                swimAmount++;
                continue;
            }
            this.array[i - swimAmount] = this.array[i];
        }
        this.currentPos -= swimAmount;
    }

    public int[] findIndex(T element) {
        int occurrence = 0;
        for (T s : this.array) {
            if (s.compareTo(element) == 0) {
                occurrence++;
            }
        }

        int[] indices;
        if (occurrence > 0) {
            indices = new int[occurrence];
            int i = 0;
            for (T s : this.array) {
                if (s.compareTo(element) == 0) {
                    this.array[i++] = element;
                }
            }
        } else {
            indices = new int[0];
        }

        return indices;
    }

    // end exclusive
    public Array<T> subArray(int start, int end) throws ArrayIndexOutOfBoundsException {
        if (start > end || start < 0 || start >= this.currentPos || end > this.currentPos) {
            throw new ArrayIndexOutOfBoundsException("Sub Array interval has to be between 0 and " + this.currentPos);
        }

        int len = end - start;
        T[] subInternalArray = (T[]) new Comparable[len];
        System.arraycopy(this.array, start, subInternalArray, 0, len);
        return new Array<>(subInternalArray);
    }

    public void merge(T[] array1, T[] array2) {
        this.array = (T[]) new Comparable[array1.length + array2.length];

        int ptr1 = 0, ptr2 = 0;

        int mergePos = 0;
        while (mergePos < this.array.length) {
            if (ptr1 >= array1.length) {
                // if both ptr1 and ptr2 were out of bounds, loop would terminate, so
                // we need not check that case
                this.array[mergePos++] = array2[ptr2++];
            } else if (ptr2 >= array2.length) {
                this.array[mergePos++] = array1[ptr1++];
            } else if (array2[ptr2].compareTo(array1[ptr1]) < 0) {
                this.array[mergePos++] = array2[ptr2++];
            } else {
                this.array[mergePos++] = array1[ptr1++];
            }
        }
        this.currentPos = this.array.length;
    }

    public int length() {
        return this.currentPos;
    }

    public void resizeArray(int toSize) {
        T[] resizedArray = (T[]) new Comparable[toSize];
        System.arraycopy(this.array, 0, resizedArray, 0, this.array.length);
        this.array = resizedArray;
    }

    public boolean isEmpty() {
        return this.currentPos == 0;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder("\nArray Length: " + this.currentPos + "\n");
        stringBuilder.append("Array capacity: ").append(this.array.length).append("\n");
        stringBuilder.append("Content: [");
        for (int i = 0; i < this.currentPos; i++) {
            stringBuilder.append(this.array[i]).append(" at ").append(i);
            if (i < this.currentPos - 1) {
                stringBuilder.append(", ");
            }
        }
        stringBuilder.append("]").append("\n");
        return stringBuilder.toString();
    }

    // test client
    public static void main(String[] args) {
        Array<String> array = new Array<>();

        System.out.println(array);

        System.out.println("Enter inputs, 'quit' to quit: ");
        Scanner scanner = new Scanner(System.in);
        String input;
        while (!(input = scanner.nextLine()).equals("quit")) {
            array.add(input);
        }

        System.out.println(array);

        if (array.length() > 3) {
            System.out.println("Putting in 3:");
            array.add(3, "Put in 3");
        }

        System.out.println(array);

        System.out.println("Removing 'Put in 3'");
        array.remove("Put in 3");

        System.out.println(array);

        String[] s1 = {"a", "c", "g"};
        String[] s2 = {"b", "d", "e", "f"};

        array.merge(s1, s2);

        System.out.println(array);

        System.out.println("*****************int*****************");
        Array<Integer> integerArray = new Array<>(5);
        System.out.println(integerArray);

        Random random = new Random();

        for (int i = 0; i < 20; i++) {
            integerArray.add(random.nextInt());
        }

        System.out.println(integerArray);

        for (int i = 0; i < 5; i++) {
            int randIndex = random.nextInt(integerArray.length());
            int randElement = random.nextInt();
            System.out.println("Adding " + randElement + " at " + randIndex);
            integerArray.add(randIndex, randElement);
        }

        System.out.println(integerArray);

        for (int i = 0; i < 5; i++) {
            int randIndex = random.nextInt(integerArray.length());
            System.out.println("Removing " + integerArray.getAnElement(randIndex) +
                    " at " + randIndex);
            integerArray.remove(integerArray.getAnElement(randIndex));
        }

        System.out.println(integerArray);

        System.out.println("Sub-array from 1 to 15: ");
        System.out.println(integerArray.subArray(1, 15));
//        System.out.println(integerArray.subArray(1, 90)); // throws exception
    }
}
