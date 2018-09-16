/*
 * Authors: Jennifer Cafiero & Kaitlynn Prescott
 * CS511 Homework Assignment 2
 * Date: October 9, 2017
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System
 * File Name: ApparatusType.java
 */

package Assignment2;

import java.util.Random;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;

public enum ApparatusType {
  LEGPRESSMACHINE,
  BARBELL,
  HACKSQUATMACHINE,
  LEGEXTENSIONMACHINE,
  LEGCURLMACHINE,
  LATPULLDOWNMACHINE,
  PECDECKMACHINE,
  CABLECROSSOVERMACHINE;

  private static Random rand = new Random();
  private static ApparatusType at;
  public static List<ApparatusType> MACHINES = Collections.unmodifiableList(Arrays.asList(values()));
  private static int MACHINES_SIZE = MACHINES.size();

  public static ApparatusType randApp() {
    at = MACHINES.get(rand.nextInt(MACHINES_SIZE));
    return at;
  }
}
