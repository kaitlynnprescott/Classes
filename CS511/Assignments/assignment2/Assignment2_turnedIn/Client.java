/*
 * Authors: Jennifer Cafiero & Kaitlynn Prescott
 * CS511 Homework Assignment 2
 * Date: October 9, 2017
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System
 * File Name: Client.java
 */

package Assignment2;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;
import java.util.HashMap;
import java.util.Map;

public class Client {
  private int id;
  private List<Exercise> routine;

  public Client(int id) {
    this.id = id;
    this.routine = new ArrayList<Exercise>();
  }
  public void addExercise(Exercise e) {
    this.routine.add(e);
  }
  public static Client generateRandom(int id, Map<WeightPlateSize, Integer> noOfWeightPlates){
	
	
    Client client = new Client(id);
    int count = 16;
    for (int i = 0; i < count; i++) {

    	Random rand = new Random();
    	HashMap<WeightPlateSize, Integer> routine = new HashMap<WeightPlateSize, Integer>();
    	int s = rand.nextInt(noOfWeightPlates.get(WeightPlateSize.SMALL_3KG));
    	int m = rand.nextInt(noOfWeightPlates.get(WeightPlateSize.MEDIUM_5KG));
    	int l = rand.nextInt(noOfWeightPlates.get(WeightPlateSize.LARGE_10KG));
    	
    	routine.put(WeightPlateSize.SMALL_3KG, s);
    	routine.put(WeightPlateSize.MEDIUM_5KG, m);
    	routine.put(WeightPlateSize.LARGE_10KG, l);
    	Exercise exer = Exercise.generateRandom(routine);
    	client.addExercise(exer);
    }
    return client;
  }

  public List<Exercise> getRoutine() {
    return this.routine;
  }

}
