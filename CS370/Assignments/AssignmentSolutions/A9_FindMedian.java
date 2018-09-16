/*******************************************************************************
 * Name          : FindMedian.java
 * Author        : Brian S. Borowski
 * Version       : 1.1
 * Date          : April 4, 2016
 * Last modified : April 8, 2018 
 * Description   : Solution to HackerRank -> Data Structures -> Heap ->
 *                 Find the Running Median
 ******************************************************************************/
import java.util.Scanner;
import java.util.Comparator;
import java.util.PriorityQueue;

class MaxHeapComparator implements Comparator<Integer> {
    public int compare(Integer x, Integer y) {
        return y - x;
    }
}

public class FindMedian {
    static PriorityQueue<Integer> maxHeap, minHeap;

    /**
     * Computes mean without potential for overflow.
     */
    static float mean(int x, int y) {
        return x + (y - x) / 2.0f;
    }

    /**
     * Returns the next median after parsing value.
     */
    public static float computeMedian(int value, float median) {
        int sign = maxHeap.size() - minHeap.size();
        if (sign > 0) { // There are more elements in the max heap.
            if (value < median) { // The value belongs in the max heap.
                // Remove max from the max heap and insert into the min heap.
                minHeap.add(maxHeap.remove());
                // Add value to the max heap.
                maxHeap.add(value);
            } else {
                // The value belongs in the min heap.
                minHeap.add(value);
            }

            // Now both heaps should have an equal number of elements.
            median = mean(maxHeap.peek(), minHeap.peek());
        } else if (sign == 0) { // Both heaps are the same size.
            if (value < median) { // The value belongs in the max heap.
                maxHeap.add(value);
                median = maxHeap.peek();
            } else {
                // The value belongs in the min heap.
                minHeap.add(value);
                median = minHeap.peek();
            }
        } else { // There are more elements in the min heap.
            if (value < median) { // The value belongs in the max heap.
                maxHeap.add(value);
            } else {
                // Remove min from the min heap and insert into the max heap.
                maxHeap.add(minHeap.remove());
                // The value belongs in the min heap.
                minHeap.add(value);
            }

            // Now both heaps should have an equal number of elements.
            median = mean(maxHeap.peek(), minHeap.peek());
        }
        return median;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numIntegers = scanner.nextInt();
        float median = 0.0f;
        maxHeap = new PriorityQueue<Integer>(
            numIntegers, new MaxHeapComparator());
        minHeap  = new PriorityQueue<Integer>(numIntegers);

        for (int i = 0; i < numIntegers; i++) {
            median = computeMedian(scanner.nextInt(), median);
            System.out.printf("%.1f\n", median);
        }
        scanner.close();
    }
}
