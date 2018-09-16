import java.util.Random;
import java.util.Arrays;

public class Bogo
{
    public static boolean isSorted(int[] array)
    {
        if (array.length == 1)
        {
            return true;
        }
        for (int i = 0; i < array.length - 1; ++i)
        {
            if (array[i] > array[i + 1])
            {
                return false;
            }
        }
        return true;
    }

    public static void bogoSort(int[] array)
    {
        Random randomInts = new Random();
        while (!isSorted(array))
        {
            for (int i = 0; i < array.length; ++i)
            {
                int swapIndex = randomInts.nextInt(array.length);

                int tmp          = array[swapIndex];
                array[swapIndex] = array[i];
                array[i]         = tmp;
            }
            System.out.println(Arrays.toString(array));
        }
    }

    public static void main(String[] args)
    {
        int[] array = {3, 4, 2, 1, 10, 15, 5, 60, 45, 30, 42, 7, 1, 12, 33, 99, 100, 41, 50, 77, 88, 33, 22, 11};

        bogoSort(array);
    }
}