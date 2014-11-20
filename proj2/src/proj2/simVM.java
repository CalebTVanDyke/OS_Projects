package proj2;

public class simVM {

	public static void main(String[] args) throws InterruptedException {
		MemoryManager manager = new MemoryManager();
		UserProcess process1 = new UserProcess(1, manager);
		UserProcess process2 = new UserProcess(2, manager);
		UserProcess process3 = new UserProcess(3, manager);
		UserProcess process4 = new UserProcess(4, manager);
		process1.start();
		manager.start();
		process2.start();
		process3.start();
		process4.start();
		manager.finish();
	}

}
