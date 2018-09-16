/*
 * Authors: Jennifer Cafiero & Kaitlynn Prescott
 * CS511 Homework Assignment 2
 * Date: October 9, 2017
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System
 * File Name: Gym.java
 */

package Assignment2;

import java.util.Map;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Semaphore;
import java.util.concurrent.Executors;
import java.util.Random;
import java.util.Arrays;
import java.util.HashSet;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.ArrayList;

public class Gym implements Runnable {
  private static final int GYM_SIZE = 30;
  private static final int GYM_REGISTERED_CLIENTS = 10000;
  private Map<WeightPlateSize,Integer> noOfWeightPlates = new LinkedHashMap<WeightPlateSize, Integer>();
  private Set<Integer> clients; //for generating fresh client ids
  private ExecutorService executor = Executors.newFixedThreadPool(GYM_SIZE);


  private static int count = 0;
  private static int routineCount = 0;
  private Client[] clientList;
  private Random rand = new Random();

  private Semaphore[] apparatuses = new Semaphore [] {new Semaphore(5), new Semaphore(5), new Semaphore(5), new Semaphore(5), new Semaphore(5), new Semaphore(5), new Semaphore(5), new Semaphore(5)};
  private Semaphore[] openWeights = new Semaphore [] {new Semaphore(110), new Semaphore(90), new Semaphore(75)};
  private Semaphore[] mutexWeights = new Semaphore [] {new Semaphore(1), new Semaphore(1), new Semaphore(1)};

  public Gym() {

  }

  public void run() {
    int[] ids = new int[10000];
    Client[] clientList = new Client[10000];
    noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, 10);
    noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, 10);
    noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, 10);
    clients = new HashSet<Integer>();
    for (int i = 0; i < GYM_REGISTERED_CLIENTS; i++) {
      ids[i] = i;
      clientList[i] = Client.generateRandom(i, noOfWeightPlates);
      clients.add(i);
    }
    
    

    for (final Integer id : clients) {
	    executor.execute(new Runnable(){
	      public void run() {
	    	  try {
	    		  Client currCli = clientList[id];
	 	    	 ArrayList<Exercise> currRout = (ArrayList<Exercise>)currCli.getRoutine();
	 	    	 System.out.println("Welcome client " + id + " to the gym!");
	 	    	 for (Exercise x: currRout) {
	 	    		 int time = x.getDuration();
	 	    		 ApparatusType at = x.getAT();
	 	    		 Map<WeightPlateSize, Integer> wt = x.getWeights();
	 	    		 
	 	    		 int s = wt.get(WeightPlateSize.SMALL_3KG);
	 	    		 int m = wt.get(WeightPlateSize.MEDIUM_5KG);
	 	    		 int l = wt.get(WeightPlateSize.LARGE_10KG);
	 	    		 if (s != 0) {
	 	    			 mutexWeights[WeightPlateSize.SMALL_3KG.ordinal()].acquire();
	 	    			 for (int i = 0; i < s; i++) {
	 	    				openWeights[WeightPlateSize.SMALL_3KG.ordinal()].acquire();
	 	    			 }
	 	    			mutexWeights[WeightPlateSize.SMALL_3KG.ordinal()].release();
	 	    		 }
	 	    		 if (m != 0) {
	 	    			 mutexWeights[WeightPlateSize.MEDIUM_5KG.ordinal()].acquire();
	 	    			 for (int i = 0; i < m; i++) {
	 	    				openWeights[WeightPlateSize.MEDIUM_5KG.ordinal()].acquire();
	 	    			 }
	 	    			mutexWeights[WeightPlateSize.MEDIUM_5KG.ordinal()].release();
	 	    		 }
	 	    		 if (l != 0) {
	 	    			 mutexWeights[WeightPlateSize.LARGE_10KG.ordinal()].acquire();
	 	    			 for (int i = 0; i < l; i++) {
	 	    				openWeights[WeightPlateSize.LARGE_10KG.ordinal()].acquire();
	 	    			 }
	 	    			mutexWeights[WeightPlateSize.LARGE_10KG.ordinal()].release();
	 	    		 }
	 	    		 
	 	    		 apparatuses[at.ordinal()].acquire();
	 		    	 System.out.println("Client " + id + " picks up the " + at + " apparatus with weights " + wt);
	 		    	 Thread.sleep(time);
	 		    	 System.out.println("Client " + id + " puts back the " + at + "apparatus with weights " + wt);
	 		    	 apparatuses[at.ordinal()].release();
	 		    	 
	 		    	 for (int i = 0; i < s; i++) {
	 		    		openWeights[WeightPlateSize.SMALL_3KG.ordinal()].release();
	 		    	 }
	 		    	for (int i = 0; i < m; i++) {
	 		    		openWeights[WeightPlateSize.MEDIUM_5KG.ordinal()].release();
	 		    	 }
	 		    	for (int i = 0; i < l; i++) {
	 		    		openWeights[WeightPlateSize.LARGE_10KG.ordinal()].release();
	 		    	 }
	 		    
	 	    	 }
	 	    	 System.out.println("Client " + id + " has left the gym.");
	    	  } catch (InterruptedException e){
	    		  e.printStackTrace();
	    	  }
	    	 
	    	 
	    	 
	      }
	    });
	   
	  }
    executor.shutdown();
  }
}
