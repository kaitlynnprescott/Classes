import java.util.Arrays;

public class BubbleSort
{
	public static <T extends Comparable<T>> void bubbleSort(T[] arr)
	{
		boolean swapped = true;
		while (swapped)
		{
			swapped = false;
			for (int i = 0; i < arr.length - 1; ++i) 
			{
				if (arr[i].compareTo(arr[i + 1]) > 0) 
				{
					T tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;

					swapped = true;
				}
			}
		}
	}

	public static void main(String[] args) 
	{
		System.out.println("- - - - - - - - Bubble Sort - - - - - - - -");
		
		Integer[] arr1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
		System.out.println(Arrays.toString(arr1));
		bubbleSort(arr1);
		System.out.println(Arrays.toString(arr1));
		
		System.out.println();

		Integer[] arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		System.out.println(Arrays.toString(arr2));
		bubbleSort(arr2);
		System.out.println(Arrays.toString(arr2));

		System.out.println();

		Integer[] arr3 = {12, 13, 12, 5, 8, 3, 9, 12, 123};
		System.out.println(Arrays.toString(arr3));
		bubbleSort(arr3);
		System.out.println(Arrays.toString(arr3));

		System.out.println();

		String[] arr5 = {"hi", "hello", "abcd", "bat"};
		System.out.println(Arrays.toString(arr5));
		bubbleSort(arr5);
		System.out.println(Arrays.toString(arr5));
	}
}