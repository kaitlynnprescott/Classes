/*
 * Authors: Jennifer Cafiero & Kaitlynn Prescott
 * CS511 Homework Assignment 2
 * Date: October 9, 2017
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System
 * File Name: WeightPlateSize.java
 */

package Assignment2;

import java.util.Random;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;

public enum WeightPlateSize {
  SMALL_3KG, MEDIUM_5KG, LARGE_10KG;

  private static WeightPlateSize weight;
  private static Random rand = new Random();
  public static List<WeightPlateSize> WEIGHTS = Collections.unmodifiableList(Arrays.asList(values()));
  private static int WEIGHTS_SIZE = WEIGHTS.size();

  public static WeightPlateSize randWeight() {
    weight = WEIGHTS.get(rand.nextInt(WEIGHTS_SIZE));
    return weight;
  }

  public static List<WeightPlateSize> getWeights() {
    return WEIGHTS;
  }
}