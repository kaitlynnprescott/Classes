/************************************************************************************
 * Name        : Exercise.java
 * Author      : Kaitlynn Prescott && Jennifer Cafiero
 * Date        : Oct 9, 2017
 * Description : CS-511 Assignment2: Gym
 * Pledge      : We pledge our honor that we have abided by the Stevens honor system.
 ************************************************************************************/

import java.util.Random;
import java.util.Map;

public class Exercise {

	private ApparatusType at;
	private Map<WeightPlateSize, Integer> weight;
	private int duration;
	private static Random rand = new Random();

	public Exercise(ApparatusType at, Map<WeightPlateSize, Integer> weight, int duration){
		this.at = at;
		this.weight = weight;
		this.duration = duration;

	}

	public static Exercise generateRandom(Map<WeightPlateSize, Integer> plates) {
		Exercise exercise = new Exercise(ApparatusType.randomType(), plates, rand.nextInt(10000) + 1);
		return exercise;
	}

	public ApparatusType getAt() {
		return this.at;
	}

	public Map<WeightPlateSize, Integer> getPlates() {
		return this.weight;
	}
	




}