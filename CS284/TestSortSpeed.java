import java.util.Random;
import java.util.function.Consumer;
import java.util.Arrays;

public class TestSortSpeed
{
    public static final int MAX_NUM_GENERATED = 5000;
    public static final int TEST_RUNS = 10;

    private static long timeAverageSort(Integer[] arr, Consumer<Integer[]> sortAlgo, int testRuns)
    {
        long totalSpeed = 0;
        for (int i = 0; i < testRuns; ++i)
        {
            Integer[] tmpArr = arr;
            long startTime = System.nanoTime();
            sortAlgo.accept(arr);
            long endTime = System.nanoTime();
            totalSpeed += endTime - startTime;
        }
        return totalSpeed / testRuns;
    }

    private static Integer[] createArray(String arrType, int arrSize)
    {
        arrType = arrType.toLowerCase();

        if (arrType == "ordered")
        {
            Integer[] arr = new Integer[arrSize];
            for (int i = 0; i < arrSize; ++i)
            {
                arr[i] = i;
            }
            return arr;
        }
        if (arrType == "random")
        {
            Integer[] arr = new Integer[arrSize];
            Random randInt = new Random();
            for (int i = 0; i < arrSize; ++i)
            {
                arr[i] = randInt.nextInt(MAX_NUM_GENERATED);
            }
            return arr;
        }
        if (arrType == "reverse")
        {
            Integer[] arr = new Integer[arrSize];
            for (int i = 0; i < arrSize; ++i)
            {
                arr[arrSize - i - 1] = i;
            }
            return arr;
        }
        return null;
    }

    public static void testSort(Consumer<Integer[]> sortAlgo, int arrLen)
    {
        Integer[] orderedTestArray = createArray("ordered", arrLen);
        Integer[] reverseOrderedTestArray = createArray("reverse", arrLen);
        Integer[] randomTestArray = createArray("random", arrLen);

        System.out.printf("%8d nanoseconds on average to sort an ordered array of %d elements over %d runs.\n", timeAverageSort(orderedTestArray, sortAlgo, TEST_RUNS), arrLen, TEST_RUNS);
        System.out.printf("%8d nanoseconds on average to sort a reverse ordered array of %d elements over %d runs.\n", timeAverageSort(reverseOrderedTestArray, sortAlgo, TEST_RUNS), arrLen, TEST_RUNS);
        System.out.printf("%8d nanoseconds on average to sort a randomly ordered array of %d elements over %d runs.\n", timeAverageSort(randomTestArray, sortAlgo, TEST_RUNS), arrLen, TEST_RUNS);
    }

    public static void testSort(Consumer<Integer[]> sortAlgo)
    {
        testSort(sortAlgo, 5000);
    }

    public static void main(String[] args)
    {
        System.out.println("-------------- Bubble Sort --------------");
        testSort(BubbleSort::bubbleSort);
        System.out.println("-------------- Quick Sort --------------");
        testSort(QuickSort::quickSort);
        System.out.println("-------------- Heap Sort --------------");
        testSort(HeapSort::heapSort);
        System.out.println("-------------- Built-in Sort --------------");
        testSort(Arrays::sort);
    }
}