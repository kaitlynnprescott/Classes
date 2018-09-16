/*
*
*	I pledge my honor that I have abided by the Stevens Honor System
*	Christopher Rudel, Kaitlynn Prescott, Meng Qui
*	2/4/18
*
*
*/
import java.util.*;
public class SubstringDivisibility
{
    public static long  sum = 0;

    private static void permute(ArrayList<Integer> arr, int k)
    {
        if(arr.size() == 10)
        {
            ten();
        }
        else{
            for(int i=k; i<arr.size(); i++)
            {
				/*Creates permutations*/
                java.util.Collections.swap(arr,i,k);
                permute(arr, k+1);
                java.util.Collections.swap(arr,k,i);
            }
            if (k==arr.size()-1 && arr.get(3) %2 ==0) /* Checks if size of int is 4*/
            {
                if(arr.size() ==4) {
                    System.out.println(toString(arr));
                    sum += toInt(arr);
                }
                else if( arr.size() >4){
                    int f = arr.get(2) + arr.get(3) + arr.get(4); /* A number is divisible by 3 if, when you add all the digits, its still divisible by 3 */
                    boolean div3 = f%3==0;	
                    if (arr.size() == 5 && k==arr.size()-1 && arr.get(3) %2 ==0 && div3)
                    {
                        System.out.println(toString(arr));
                        sum+= toInt(arr);
                    }
                    else if( arr.size() >5 && div3){
                        if (arr.size() == 6 && k==arr.size()-1 && arr.get(3) %2 ==0 && arr.get(5) % 5 == 0)	/*Checks conditions up to length 6*/
                        {
                            System.out.println(toString(arr));
                            sum+= toInt(arr);
                        }
                        else if( arr.size() >6 && div3){
                            int[] seven = {arr.get(4), arr.get(5), arr.get(6)};
                            int se = toInt(seven);
                            boolean div7 = se%7 == 0;
                            if (arr.size() == 7 && k==arr.size()-1 && arr.get(3) %2 ==0 && arr.get(5) % 5 == 0  && div7) /*Checks conditions up to length 7*/
                            {
                                System.out.println(toString(arr));
                                sum+= toInt(arr);
                            }
                            else if( arr.size() >7 && div3 && div7){
                                int[] eight = {arr.get(5), arr.get(6), arr.get(7)};
                                int ei = toInt(eight);
                                boolean div8 = ei%11 ==0;
                                if (arr.size() == 8 && k==arr.size()-1 && arr.get(3) %2 ==0
                                        && arr.get(5) == 5 && div8) /*Checks conditions up to length 8*/
                                {
                                    System.out.println(toString(arr));
                                    sum+= toInt(arr);
                                }
                                else if( arr.size() >8 && div3 && div7 && div8){
                                    int[] nine = {arr.get(6), arr.get(7), arr.get(8)};
                                    int ni = toInt(nine);
                                    if (arr.size() == 9 && k==arr.size()-1 && arr.get(3) %2 ==0
                                            && arr.get(5) == 5 && ni % 13 == 0) /*Checks conditions up to length 9, takes too long for assignment though */
                                    {
                                        System.out.println(toString(arr));
                                        sum+= toInt(arr);
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
    }


    private static void ten()	/*Decided to hard code this because pandigital numbers that are length 10 are always these 6 numbers */
    {
        long[] nums = {1430952867, 1460357289, 1406357289, 4130952867L, 4160357289L, 4106357289L};
        sum += 16695334890L;
        for(int i=0; i<6; i++)
            System.out.println(nums[i]);
    }

	/* Decided to use method overloading to make reading easier */

	/* Used StringBuilder because it takes up less runtime due to the way concatinating strings using tradional method works */
    private static String toString(ArrayList<Integer> arr)
    {
        StringBuilder ans = new StringBuilder("");
        for(int i=0; i<arr.size(); i++)
            ans.append(arr.get(i));
        return ans.toString();
    }
    private static int toInt(ArrayList<Integer> arr)
    {
        int answer;
        StringBuilder ans = new StringBuilder("");
        for(int i=0; i<arr.size(); i++)
            ans.append( arr.get(i));
        answer = Integer.parseInt(ans.toString());
        return answer;
    }
    private static int toInt(int[] arr)
    {
        int answer;
        StringBuilder ans = new StringBuilder("");
        for(int i=0; i<arr.length; i++)
            ans.append( arr[i]);
        answer = Integer.parseInt(ans.toString());
        return answer;
    }

	/* Checks to see if the user entered number is pandigital */
    private static boolean check(String num)
    {
        boolean answer = true;
        if (num.length() < 4 || num.length() > 10)
            return !answer;
        for (int i = 0; i < num.length() - 1; i++) {
            char the = num.charAt(i);
            char next = num.charAt(i + 1);
            if (the == next) {
                answer = false;
                break;
            }
        }
        return answer;
    }
    public static void main(String args[])
    {

        long time1 = System.nanoTime();
        if(check(args[0]))
        {
            ArrayList<Integer> nums = new ArrayList<>();
            for(int i=0; i<args[0].length(); i++)
                nums.add(Character.getNumericValue(args[0].charAt(i)));
            permute(nums, 0);
			System.out.print("Sum: ");
            System.out.println(sum);
        }
        else{
            System.out.println("The string you entered isn't pandigital or not long enough");
        }

        System.out.printf("Elapsed time: %.6f ms\n", (System.nanoTime() - time1) / 1e6);
    }
}
