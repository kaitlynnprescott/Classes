/*
 * Authors: Jennifer Cafiero & Katie Prescott
   Date: September 8, 2017
   CS511 HW Assignment 1
   I pledge my honor that I have abided by the Stevens Honor System.
*/


import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;

public class AssignmentOne {
  public static List<Integer> returnList = new ArrayList<Integer>();

  public static List<Integer> lprimes(List<Integer[]> intervals) {
    //Given a list of arrays of integers of size 2, creates threads for each pair and computes the primes between the two numbers of the pair.

    Thread[] threads = new Thread[intervals.size()];
    for (int i = 0; i < intervals.size(); i++) {

      PrimeFinder primeF = new PrimeFinder(intervals.get(i)[0], intervals.get(i)[1]);
      Thread t = new Thread(primeF);
      t.start();
      try {
        t.join();
      }
      catch (InterruptedException e) {
        e.printStackTrace();
      }
      threads[i] = t;
      returnList.addAll(primeF.getPrimesList());
    }
    return returnList;
  }

  public static void main(String[] args) {
    List<Integer[]> intervals = new ArrayList<>();
    Integer[] output = new Integer[(args.length)];
    
    Integer i = 0;

    for (int j = 0; j < args.length; j++) {
      try {
        i = Integer.parseInt(args[j]);
      } catch (NumberFormatException e) {
        System.err.println("Argument '" + args[j] + "' needs to be an integer");
        System.exit(1);
      }
      output[j] = i;

        }
    Arrays.sort(output);

    for (int j = 1; j < output.length; j++) {
      intervals.add(new Integer[]{output[j - 1], output[j]});
    }
    System.out.println(lprimes(intervals));

  }
}
