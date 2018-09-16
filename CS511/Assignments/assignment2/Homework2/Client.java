/************************************************************************************
 * Name        : Client.java
 * Author      : Kaitlynn Prescott && Jennifer Cafiero
 * Date        : Oct 9, 2017
 * Description : CS-511 Assignment2: Gym
 * Pledge      : We pledge our honor that we have abided by the Stevens honor system.
 ************************************************************************************/

import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;


public class Client {
	private int id;
	private static List<Exercise> routine;

	public Client(int id) {
		this.id = id;
		this.routine = new ArrayList<Exercise>();
	}

	public void addExercise(Exercise e) {
		this.routine.add(e);
	}

	public static Client generateRandom(int id) {
		Client client = new Client(id);
		return client;
	}

	public List<Exercise> getRoutine() {
		return this.routine;
	}

}