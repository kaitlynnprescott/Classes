/*
 * Authors: Jennifer Cafiero & Katie Prescott
   Date: September 8, 2017
   CS511 HW Assignment 1
   I pledge my honor that I have abided by the Stevens Honor System.
*/

import java.util.List;
import java.util.ArrayList;
class PrimeFinder implements Runnable {
  private Integer start;
  private Integer end;
  private List<Integer> primes;

  PrimeFinder(Integer startNum, Integer endNum) {
    //Constructs a PrimeFinder
    this.start = startNum;
    this.end = endNum;
    this.primes = new ArrayList<Integer>();
  }

  public List<Integer> getPrimesList() {
    //Returns the value of the attribute primes
    return this.primes;
  }
  public Boolean isPrime(int n) {
    //Determines whether its argument is prime or not
    if (n == 2)
      return true;
    if (n % 2 == 0)
      return false;
    for (int i = 3; i * i <= n; i += 2){
      if (n % i == 0){
        return false;
      }
    }
    return true;
  }
  public void run() {
    //Adds all primes in [this.start, this.end) to the attribute primes
    for (int i = start; i < end; i++) {
      if (isPrime(i)) {
        primes.add(new Integer(i));
      }
    }
  }
}
