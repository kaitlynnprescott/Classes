/************************************************************************************
 * Name        : ApparatusType.java
 * Author      : Kaitlynn Prescott && Jennifer Cafiero
 * Date        : Oct 9, 2017
 * Description : CS-511 Assignment2: Gym
 * Pledge      : We pledge our honor that we have abided by the Stevens honor system.
 ************************************************************************************/

import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;


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
	private static int SIZE = MACHINES.size();

	public static ApparatusType randomType() {
		at = MACHINES.get(rand.nextInt(SIZE));
		return at;
	}
}