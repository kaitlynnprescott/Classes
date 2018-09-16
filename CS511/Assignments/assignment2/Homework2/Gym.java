/************************************************************************************
 * Name        : Gym.java
 * Author      : Kaitlynn Prescott && Jennifer Cafiero
 * Date        : Oct 9, 2017
 * Description : CS-511 Assignment2: Gym
 * Pledge      : We pledge our honor that we have abided by the Stevens honor system.
 ************************************************************************************/

import java.util.Map;
import java.util.Set;
import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Semaphore;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;


public class Gym implements Runnable {

	private static final int GYM_SIZE = 30;
	private static final int GYM_REGISTERED_CLIENTS = 10000;
	private static Map<WeightPlateSize, Integer> noOfWeightPlates = new LinkedHashMap<WeightPlateSize,Integer>();
	private static Set<Integer> clients;
	private static ExecutorService executor = Executors.newFixedThreadPool(30);

	private static int count = 0;
	private static int routineCount = 0;
	private Client[] clientList;
	private Random rand = new Random();

	private Semaphore[] apparatuses = new Semaphore[] {new Semaphore(1), new Semaphore(1), new Semaphore(1), new Semaphore(1), new Semaphore(1), new Semaphore(1), new Semaphore(1), new Semaphore(1)};

	private Semaphore[] openWeights = new Semaphore[] {new Semaphore(110), new Semaphore(90), new Semaphore(75)};

	public Gym() {

	}

	public void run() {
		int[] ids = new int[10000];
		Client[] clientList = new Client[10000];
		for (int i = 0; i < 10000; i++) {
			ids[i] = i;
			clientList[i] = new Client(i);
		}
		clients = new HashSet(Arrays.asList(ids));

		for (int i = 0; i < 10000; i++) {
			noOfWeightPlates.clear();
			noOfWeightPlates.put(WeightPlateSize.getWeights().get(0), rand.nextInt(20));
			noOfWeightPlates.put(WeightPlateSize.getWeights().get(1), rand.nextInt(20));
			noOfWeightPlates.put(WeightPlateSize.getWeights().get(2), rand.nextInt(20));
			for (int j = 0; j < rand.nextInt(10); j++) {
				clientList[i].addExercise(Exercise.generateRandom(noOfWeightPlates));
			}
		}
		executor.execute(new Runnable() {
			public void run() {
				routineCount = 0;
				while (count < 10000) {
					for (int k = 0; k < 8; k++) {
						if (clientList[count].getRoutine().size() > routineCount) {
							if (clientList[count].getRoutine().get(routineCount).getAt() == ApparatusType.MACHINES.get(k)) {
								try {
									apparatuses[k].acquire();
									for (int j = 0; j < 3; j++) {
										openWeights[j].acquire(clientList[count].getRoutine().get(routineCount).getPlates().get(WeightPlateSize.getWeights().get(0)));
									}
									for (int j = 0; j < 3; j++) {
										openWeights[j].release(clientList[count].getRoutine().get(routineCount).getPlates().get(WeightPlateSize.getWeights().get(0)));
									}
									routineCount++;
									apparatuses[k].release();
								} catch (InterruptedException e) {
									e.printStackTrace();
								}
							}
						}
					}
					count++;
				}
				executor.shutdown();
			}
		});
		executor.shutdown();
	}
}