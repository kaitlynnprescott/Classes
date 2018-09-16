/*
 * Authors: Jennifer Cafiero & Kaitlynn Prescott
 * CS511 Homework Assignment 2
 * Date: October 9, 2017
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System
 * File Name: Exercise.java
 */

package Assignment2;

import java.util.Random;
import java.util.Map;

public class Exercise{
  private ApparatusType at;
  private Map<WeightPlateSize,Integer> weight;
  private int duration;
  private static Random rand = new Random();

  public Exercise(ApparatusType at, Map<WeightPlateSize,Integer> weight, int duration) {
    this.at = at;
    this.weight = weight;
    this.duration = duration;
  }
  public static Exercise generateRandom(Map<WeightPlateSize, Integer> plates) {
    Exercise exercise = new Exercise(ApparatusType.randApp(), plates, rand.nextInt(150) + 1);
    return exercise;
  }
  public ApparatusType getAT() {
    return this.at;
  }
  public Map<WeightPlateSize, Integer> getWeights() {
    return this.weight;
  }
  public int getDuration() {
	  return this.duration;
  }
}

