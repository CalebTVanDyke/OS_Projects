package proj2;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class MemoryManager extends Thread {

	private List<UserProcess> userProcesses;
	boolean isDone = false;

	public MemoryManager() {
		userProcesses = Collections.synchronizedList(new LinkedList<UserProcess>());
	}

	@Override
	public void run() {
		while(!isDone){
			while (userProcesses.size() != 0) {
				System.out.println(userProcesses.remove(0).getLogicalAddress());
			}			
		}
	}
	/**
	 * Adds a new user process to be processed by the MemoryManager
	 * @param process
	 */
	public synchronized void addProcess(UserProcess process) {
		userProcesses.add(process);
	}
	/**
	 * Tells the MemoryManager that all UserProcess have been added
	 * and it is free to exit once all process have been completed
	 */
	public synchronized void finish(){
		isDone = true;
	}
}
