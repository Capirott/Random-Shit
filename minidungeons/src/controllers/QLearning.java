package controllers;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;

import dungeon.Dungeon;
import dungeon.DungeonLoader;
import dungeon.play.GameCharacter;
import dungeon.play.Hero;
import dungeon.play.PlayMap;
import sun.security.action.GetBooleanSecurityPropertyAction;
import util.math2d.Matrix2D;
import util.math2d.Point2D;
import util.statics.StatisticUtils;

/**
 * Q Learning sample class <br/>
 * <b>The goal of this code sample is for the character @ to reach the goal area
 * G</b> <br/>
 * compile using "javac QLearning.java" <br/>
 * test using "java QLearning" <br/>
 *
 * @author A.Liapis
 */
public class QLearning extends Controller{
	
	private static final float TIME_TO_REDUCE_EXPLORARION_CHANCE = 2000;

	public QLearning(PlayMap map, GameCharacter controllingChar) {
		super(map, controllingChar, "QLearningController");
		q = new Qtable(getActionRange());
	}

	public void setConfig(PlayMap map, GameCharacter controllingChar) {
		super.map = map;
		super.controllingChar = controllingChar;
	}
	
	/**
	 * The heart of the Q-learning algorithm, the Qtable contains the table
	 * which maps states, actions and their Q values. This class has elaborate
	 * documentation, and should be the focus of the students' body of work for
	 * the purposes of this tutorial.
	 *
	 * @author A.Liapis
	 */
	public class Qtable {
		/**
		 * for creating random numbers
		 */
		Random randomGenerator;
		/**
		 * the table variable stores the Q-table, where the state is saved
		 * directly as the actual map. Each map state has an array of Q values
		 * for all the actions available for that state.
		 */
		HashMap<String, float[]> table;
		/**
		 * the actionRange variable determines the number of actions available
		 * at any map state, and therefore the number of Q values in each entry
		 * of the Q-table.
		 */
		int actionRange;

		// E-GREEDY Q-LEARNING SPECIFIC VARIABLES
		/**
		 * for e-greedy Q-learning, when taking an action a random number is
		 * checked against the explorationChance variable: if the number is
		 * below the explorationChance, then exploration takes place picking an
		 * action at random. Note that the explorationChance is not a final
		 * because it is customary that the exploration chance changes as the
		 * training goes on.
		 */
		float explorationChance = 1.0f;
		/**
		 * the discount factor is saved as the gammaValue variable. The discount
		 * factor determines the importance of future rewards. If the gammaValue
		 * is 0 then the AI will only consider immediate rewards, while with a
		 * gammaValue near 1 (but below 1) the AI will try to maximize the
		 * long-term reward even if it is many moves away.
		 */
		float gammaValue = 0.9f;
		/**
		 * the learningRate determines how new information affects accumulated
		 * information from previous instances. If the learningRate is 1, then
		 * the new information completely overrides any previous information.
		 * Note that the learningRate is not a final because it is customary
		 * that the exploration chance changes as the training goes on.
		 */
		float learningRate = 0.5f;

		// PREVIOUS STATE AND ACTION VARIABLES
		/**
		 * Since in Q-learning the updates to the Q values are made ONE STEP
		 * LATE, the state of the world when the action resulting in the reward
		 * was made must be stored.
		 */
		String prevState;
		/**
		 * Since in Q-learning the updates to the Q values are made ONE STEP
		 * LATE, the index of the action which resulted in the reward must be
		 * stored.
		 */
		int prevAction;

		/**
		 * Q table constructor, initiates variables.
		 * 
		 * @param the
		 *            number of actions available at any map state
		 */
		Qtable(int actionRange) {
			randomGenerator = new Random();
			this.actionRange = actionRange;
			table = new HashMap<String, float[]>();
		}

		/**
		 * For this example, the getNextAction function uses an e-greedy
		 * approach, having exploration happen if the exploration chance is
		 * rolled.
		 *
		 * @param the
		 *            current map (state)
		 * @return the action to be taken by the calling progam
		 */
		int getNextAction(String map) {
			prevState = map;
			if (randomGenerator.nextFloat() < explorationChance) {
				prevAction = explore();
			} else {
				prevAction = getBestAction(map);
			}
			return prevAction;
		}

		/**
		 * The getBestAction function uses a greedy approach for finding the
		 * best action to take. Note that if all Q values for the current state
		 * are equal (such as all 0 if the state has never been visited before),
		 * then getBestAction will always choose the same action. If such an
		 * action is invalid, this may lead to a deadlock as the map state never
		 * changes: for situations like these, exploration can get the algorithm
		 * out of this deadlock.
		 *
		 * @param the
		 *            current map (state)
		 * @return the action with the highest Q value
		 */
		int getBestAction(String map) {
			int action = 0;
			if (table.containsKey(map)) {
				float qValue = Float.NEGATIVE_INFINITY;
				float[] qValues = table.get(map);
				for (int i = 0; i < getActionRange(); ++i) {
					if (qValues[i] > qValue) {
						qValue = qValues[i];
						action = i;
					}
				}
			}
			return action;
		}

		/**
		 * The explore function is called for e-greedy algorithms. It can choose
		 * an action at random from all available, or can put more weight
		 * towards actions that have not been taken as often as the others (most
		 * unknown).
		 *
		 * @return index of action to take
		 */
		int explore() {
			return randomGenerator.nextInt(getActionRange());
		}

		/**
		 * The updateQvalue is the heart of the Q-learning algorithm. Based on
		 * the reward gained by taking the action prevAction while being in the
		 * state prevState, the updateQvalue must update the Q value of that
		 * {prevState, prevAction} entry in the Q table. In order to do that,
		 * the Q value of the best action of the current map state must also be
		 * calculated.
		 *
		 * @param reward
		 *            at the current map state
		 * @param the
		 *            current map state (for finding the best action of the
		 *            current map state)
		 */
		void updateQvalue(float reward, String map, String currentMap) {
			float currentQValue = getActionsQValues(map)[prevAction];
			getActionsQValues(map)[prevAction] += (reward + gammaValue * getActionsQValues(currentMap)[getBestAction(currentMap)] - currentQValue);
		}

		/**
		 * The getActionsQValues function returns an array of Q values for all
		 * the actions available at any state. Note that if the current map
		 * state does not already exist in the Q table (never visited before),
		 * then it is initiated with Q values of 0 for all of the available
		 * actions.
		 *
		 * @param the
		 *            current map (state)
		 * @return an array of Q values for all the actions available at any
		 *         state
		 */
		float[] getActionsQValues(String map) {
			if (!table.containsKey(map)) {
				float[] initialActions = new float[actionRange];
				for (int i = 0; i < actionRange; i++)
					initialActions[i] = 0.f;
				table.put(map, initialActions);
				return initialActions;
			}
			float[] actions = table.get(map);
			return actions;
		}

		/**
		 * Helper function to find the Q-values of a given map state.
		 *
		 * @param the
		 *            current map (state)
		 * @return the Q-values stored of the Qtable entry of the map state,
		 *         otherwise null if it is not found
		 */
		float[] getValues(String map) {
			if (table.containsKey(map)) {
				return table.get(map);
			}
			return null;
		}
	};

	// --- movement constants
	public static final int UP = 0;
	public static final int RIGHT = 1;
	public static final int DOWN = 2;
	public static final int LEFT = 3;

	public int getActionRange() {
		return 4;
	}

	void runLearningLoop(String filename) throws Exception {
		
		q.explorationChance = 1.0f;
		initMetrics();
		
		String asciiMap = "";
		Scanner scanner = null;
		try {
			scanner = new Scanner(new File(filename));
			asciiMap = scanner.useDelimiter("\\A").next();
		} catch (Exception e) {
			System.out.println(e.toString());
		} finally {
			if (scanner != null) {
				scanner.close();
			}
		}
		Dungeon testDungeon = DungeonLoader.loadAsciiDungeon(asciiMap);
		PlayMap testPlay = new PlayMap(testDungeon);
		for (int i = 0; i < totalRuns; i++) {
			testPlay.startGame();

			int actions = 0;
			
			if (i > TIME_TO_REDUCE_EXPLORARION_CHANCE) {
				q.explorationChance /= 1.000009; 
			}

			while (!testPlay.isGameHalted() && actions < maxActions) {
				
				Hero hero = testPlay.getHero();
				
				int action = q.getNextAction(testPlay.toASCIIENCODED());
				Point2D nextTile = hero.getNextPosition(action);
				testPlay.updateGame(action);
				actions++;
				

				float reward = 0;
				
				if (!hero.isAlive()) {
					reward = -1.0f;
				}
				else {
					if (testPlay.isGameHalted()) {
						reward = 0.5f;
					}
					else if (!testDungeon.isPassable((int) nextTile.x, (int) nextTile.y)) {
						reward = -1.0f;
					}
				}
				
				q.updateQvalue(reward, q.prevState, testPlay.toASCIIENCODED());
				
			}
//			System.out.println(printMetrics(maxActions));
//			System.out.println("explorarionChance: " + q.explorationChance);
			updateMetrics(i, testPlay, actions);

		}
//		System.out.println("---------------------------------------");
		// System.out.println(printFullMetrics());

	}

	/**
	 * Q-learning maze-solving learning method
	 * 
	 * @param args
	 */
	public void train() {
		try {
			System.out.println("Learning process started...");
			for (int i = 0; i <= 10; i++) {
				System.out.println("\n--------------\nMAP"+i+" TRAINING \n--------------\n");
				runLearningLoop("./dungeons/map" + i + ".txt");
				System.out.println("\n--------------\nMAP"+i+" TRAINED \n--------------\n");
				
			}
			System.out.println("Learning process finished...");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	final int totalRuns = 250000;
	final int maxActions = 300;

	double[] hpRemaining;
	double[] monstersKilled;
	double[] treasuresCollected;
	double[] potionsDrunk;
	double[] actionsTaken;
	double[] tilesExplored;
	private Qtable q;

	protected void initMetrics() {
		initMetrics(totalRuns);
	}

	protected void initMetrics(int runs) {
		hpRemaining = new double[runs];
		monstersKilled = new double[runs];
		treasuresCollected = new double[runs];
		potionsDrunk = new double[runs];
		actionsTaken = new double[runs];
		tilesExplored = new double[runs];
	}

	protected void updateMetrics(int index, PlayMap finishedMap, int actions) {
		hpRemaining[index] = finishedMap.getHero().getHitpoints();
		monstersKilled[index] = Matrix2D.count(finishedMap.getDeadMonsterArray());
		treasuresCollected[index] = Matrix2D.count(finishedMap.getDeadRewardArray());
		potionsDrunk[index] = Matrix2D.count(finishedMap.getDeadPotionArray());
		actionsTaken[index] = actions;
		// if(hpRemaining[index]==0){ actionsTaken[index]=Double.NaN; }
		// tilesExplored[index] = Matrix2D.count(finishedMap.getExplored());
		// assuming you now have a int[][] visited array, the above can be
		// converted to:
		tilesExplored[index] = Matrix2D.count(finishedMap.getAnyVisited());
	}

	protected String printMetrics(int maxActions) {
		String result = "";
		result += "hpRemaining: " + hpAverage() + " (" + StatisticUtils.standardDeviation(hpRemaining) + ")\n";
		result += "monstersKilled: " + monsterAverage() + " (" + StatisticUtils.standardDeviation(monstersKilled)
				+ ")\n";
		result += "treasuresCollected: " + treasureAverage() + " ("
				+ StatisticUtils.standardDeviation(treasuresCollected) + ")\n";
		result += "potionsDrunk: " + potionAverage() + " (" + StatisticUtils.standardDeviation(potionsDrunk) + ")\n";
		result += "actionsTaken: " + actionAverage() + " (" + StatisticUtils.standardDeviation(actionsTaken) + ")\n";
		result += "tilesExplored: " + tilesAverage() + " (" + StatisticUtils.standardDeviation(tilesExplored) + ")\n";
		int timesCompleted = 0;
		timesCompleted = calcTimesCompleted(maxActions);
		result += "timesCompleted: " + timesCompleted + "\n";
		int timesDied = 0;
		for (int i = 0; i < hpRemaining.length; i++) {
			if (hpRemaining[i] <= 0) {
				timesDied++;
			}
		}
		result += "timesDied: " + timesDied + "\n";
		int timesUncompleted = 0;
		for (int i = 0; i < actionsTaken.length; i++) {
			if (actionsTaken[i] == maxActions) {
				timesUncompleted++;
			}
		}
		result += "timesUncompleted: " + timesUncompleted + "\n";
		return result;
	}

	public int calcTimesCompleted(int maxActions) {
		int timesCompleted = 0;
		for (int i = 0; i < hpRemaining.length; i++) {
			if (hpRemaining[i] > 0 && actionsTaken[i] < maxActions) {
				timesCompleted++;
			}
		}
		return timesCompleted;
	}

	public double tilesAverage() {
		return StatisticUtils.average(tilesExplored);
	}

	public double actionAverage() {
		return StatisticUtils.average(actionsTaken);
	}

	public double potionAverage() {
		return StatisticUtils.average(potionsDrunk);
	}

	public double treasureAverage() {
		return StatisticUtils.average(treasuresCollected);
	}

	public double monsterAverage() {
		return StatisticUtils.average(monstersKilled);
	}

	public double hpAverage() {
		return StatisticUtils.average(hpRemaining);
	}

	protected String printFullMetrics() {
		String result = "";
		result += "hpRemaining;";
		for (int i = 0; i < hpRemaining.length; i++) {
			result += hpRemaining[i] + ";";
		}
		result += "\n";
		result += "monstersKilled;";
		for (int i = 0; i < monstersKilled.length; i++) {
			result += monstersKilled[i] + ";";
		}
		result += "\n";
		result += "treasuresCollected;";
		for (int i = 0; i < treasuresCollected.length; i++) {
			result += treasuresCollected[i] + ";";
		}
		result += "\n";
		result += "potionsDrunk;";
		for (int i = 0; i < potionsDrunk.length; i++) {
			result += potionsDrunk[i] + ";";
		}
		result += "\n";
		result += "actionsTaken;";
		for (int i = 0; i < actionsTaken.length; i++) {
			result += actionsTaken[i] + ";";
		}
		result += "\n";
		result += "tilesExplored;";
		for (int i = 0; i < tilesExplored.length; i++) {
			result += tilesExplored[i] + ";";
		}
		result += "\n";
		return result;
	}

	public static void writeFile(String filename, String[] lines) throws IOException {
		BufferedWriter outputWriter = null;
		outputWriter = new BufferedWriter(new FileWriter(filename));
		for (int i = 0; i < lines.length; i++) {
			outputWriter.write(lines[i]);
			outputWriter.newLine();
		}
		outputWriter.flush();
		outputWriter.close();
	}

	@Override
	public int getNextAction() {
		return q.getNextAction(map.toASCIIENCODED());	
	}

};
