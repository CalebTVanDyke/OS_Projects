

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class simVM {

	public static void main(String[] args) throws InterruptedException {
		if(args.length < 4){
			System.out.println("No arguments provided.");
			System.exit(1);
		}
		int pageFrameSize = Integer.valueOf(args[0]);
		int maxPages = Integer.valueOf(args[1]);
		int maxFrames = Integer.valueOf(args[2]);
		int numProcs = Integer.valueOf(args[3]);
		PhysicalMemory mem = new PhysicalMemory(pageFrameSize, maxFrames);
		PageFaultHandler pageFault = new PageFaultHandler(pageFrameSize, mem, numProcs);
		MemoryManager manager = new MemoryManager(pageFrameSize, maxFrames, numProcs, pageFault, mem);
		manager.start();
		pageFault.start();
		for(int i = 4; i < numProcs + 4; i++){
			UserProcessImpl process = new UserProcessImpl(i - 4, maxPages, manager);
			File addresses = new File(args[i]);
			try {
				Scanner scan = new Scanner(addresses);
				while(scan.hasNextInt()){
					Integer address = scan.nextInt();
					process.getLogicalAddresses().add(address);
				}
				process.start();
				scan.close();
			} catch (FileNotFoundException e) {
				System.out.println(args[i] + " could not be found. Proceeding with next process");
				manager.incrementProcessCount();
				pageFault.incrementProcessCount();
			}
		}
	}

}
