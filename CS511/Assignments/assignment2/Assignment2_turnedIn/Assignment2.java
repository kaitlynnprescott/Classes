/*
 * Authors: Jennifer Cafiero & Kaitlynn Prescott
 * CS511 Homework Assignment 2
 * Date: October 9, 2017
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System
 * File Name: Assignment2.java
 */

package Assignment2;

public class Assignment2 {
	public static void main(String[] args) {
	    Thread thread = new Thread(new Gym());
	    thread.start();
	    try {
	      thread.join();
	    } catch (InterruptedException e) {
	      e.printStackTrace();
	    }
	  }
}
