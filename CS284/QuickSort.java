import java.util.Arrays;

public class QuickSort
{
    public static <T extends Comparable<T>> void quickSort(T[] arr)
    {
        quickSort(arr, 0, arr.length - 1);
    }

    private static <T extends Comparable<T>> void quickSort(T[] arr, int first, int last)
    {
        if (first < last)
        {
            int pivotIndex = partition(arr, first, last);
            quickSort(arr, first, pivotIndex  - 1);
            quickSort(arr, pivotIndex + 1, last);
        }
    }

    private static <T extends Comparable<T>> int partition(T[] arr, int first, int last)
    {
        T pivot = arr[first];
        int up = first;
        int down = last;

        do
        {
            while ((up < last) && (pivot.compareTo(arr[up]) >= 0))
            {
                up++;
            }

            while (pivot.compareTo(arr[down]) < 0)
            {
                down--;
            }

            if (up < down)
            {
                T tmp = arr[up];
                arr[up] = arr[down];
                arr[down] = tmp;
            }
        } while(up < down);

        T tmp = arr[first];
        arr[first] = arr[down];
        arr[down] = tmp;

        return down;
    }

    public static void main(String[] args)
    {
        System.out.println("---------- Quick Sort ----------");

        Integer[] arr1 = {10,9,8,7,6,5,4,3,2,1};
        System.out.println(Arrays.toString(arr1));
        quickSort(arr1);
        System.out.println(Arrays.toString(arr1));

        System.out.println();

        Integer[] arr2 = {12,3,3,12,454,1,1,55};
        System.out.println(Arrays.toString(arr2));
        quickSort(arr2);
        System.out.println(Arrays.toString(arr2));

        System.out.println();
    }
}