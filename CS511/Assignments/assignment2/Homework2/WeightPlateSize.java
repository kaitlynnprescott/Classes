/************************************************************************************
 * Name        : WeightPlateSize.java
 * Author      : Kaitlynn Prescott && Jennifer Cafiero
 * Date        : Oct 9, 2017
 * Description : CS-511 Assignment2: Gym
 * Pledge      : We pledge our honor that we have abided by the Stevens honor system.
 ************************************************************************************/

import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;

public enum WeightPlateSize {
		SMALL_3KG,
		MEDIUM_5KG,
		LARGE_10KG;

	private static List<WeightPlateSize> WEIGHTS = Collections.unmodifiableList(Arrays.asList(values()));
	private static int SIZE = WEIGHTS.size();
	private static WeightPlateSize weight;
	private static Random rand = new Random();

	public static WeightPlateSize randomSize() {
		weight = WEIGHTS.get(rand.nextInt(SIZE));
		return weight;
	}

	public static List<WeightPlateSize> getWeights() {
		return WEIGHTS;
	}
}