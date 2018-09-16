/*
*
*   Meng Qui, Kaitlynn Prescott, Christopher Rudel
*   RunningMedian.java
*   We pledge our honor that we have abided by the Stevens Honor System
*
*/

import java.util.*;
/*
*   IMPORTANT: Run as Java 8 on Hackerrank, Java 7 gives a compilation error
*/
public class RunningMedian {
    

    private static PriorityQueue<Double> lower;
    private static PriorityQueue<Double> higher;
    
public static void main(String[] args) 
{
    lower = new PriorityQueue<Double>(Collections.reverseOrder());
    /* Collections.reverseOrder ensures that the highest number in the heap is at the front, thanks built ins */
    higher = new PriorityQueue<Double>();
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int [] nums = new int[n];
    for (int i = 0; i < n; i++) 
        nums[i] = sc.nextInt();
    
    medianTracker(nums);
}
    
static void medianTracker(int [] arr) 
{
    for (int i = 0; i < arr.length; i++) 
    {
        if (lower.isEmpty())    //Lower should always should be >= higher 
            lower.add((double) arr[i]);
        else if (lower.size() > higher.size())
        {
            if ((double) arr[i] > lower.peek()) 
                higher.add((double) arr[i]);
            else 
            {
                lower.add((double) arr[i]);
                higher.add(lower.remove());
            }
        }   
        else if (lower.size() == higher.size()) 
        {
            if ((double) arr[i] < higher.peek()) 
                lower.add((double) arr[i]);
            else 
            {
                higher.add((double) arr[i]);
                lower.add(higher.remove());
            }
        }
       System.out.println(getMedian());
    }
    return;
}
    /*  Simple way to get the median, since the Priority Queues
        can be seen by everything in the class */
    private static double getMedian() {
        if (lower.isEmpty()) 
            return 0;
        else if (lower.size() == higher.size()) 
            return (lower.peek() + higher.peek()) / 2;
        else  
            return lower.peek();
    }
}
