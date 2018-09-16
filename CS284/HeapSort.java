import java.util.Arrays;

public class HeapSort
{
    public static <T extends Comparable<T>> void heapSort(T[] arr)
    {
        buildHeap(arr);
        shrinkHeap(arr);
    }

    private static <T extends Comparable<T>> void buildHeap(T[] arr)
    {
        int n = 1;
        while (n < arr.length)
        {
            n++;
            int child = n - 1;
            int parent = (child - 1) / 2;
            while (parent >= 0 && arr[parent].compareTo(arr[child]) < 0)
            {
                T tmp = arr[parent];
                arr[parent] = arr[child];
                arr[child] = tmp;

                child = parent;
                parent = (child - 1) / 2;
            }
        }
    }

    private static <T extends Comparable<T>> void shrinkHeap(T[] arr)
    {
        int n = arr.length;
        while (n > 0)
        {
            n--;

            T tmp = arr[0];
            arr[0] = arr[n];
            arr[n] = tmp;

            int parent = 0;
            while (true)
            {
                int leftChild = 2 * parent + 1;
                if (leftChild >= n)
                {
                    break;
                }

                int rightChild = leftChild + 1;
                int maxChild = leftChild;

                if (rightChild < n && arr[leftChild].compareTo(arr[rightChild]) < 0)
                {
                    maxChild = rightChild;
                }
                if (arr[parent].compareTo(arr[maxChild]) < 0)
                {
                    tmp = arr[parent];
                    arr[parent] = arr[maxChild];
                    arr[maxChild] = tmp;

                    parent = maxChild;
                }
                else
                {
                    break;
                }
            }
        }
    }

    public static void main(String[] args)
    {
        System.out.println("---------- Heap Sort ----------");

        Integer[] arr1 = {10,9,8,7,6,5,4,3,2,1};
        System.out.println(Arrays.toString(arr1));
        heapSort(arr1);
        System.out.println(Arrays.toString(arr1));

        System.out.println();

        Integer[] arr2 = {12,3,3,12,454,1,1,55};
        System.out.println(Arrays.toString(arr2));
        heapSort(arr2);
        System.out.println(Arrays.toString(arr2));

        System.out.println();
    }
}