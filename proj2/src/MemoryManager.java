import java.util.concurrent.BlockingDeque;
import java.util.concurrent.LinkedBlockingDeque;

public class MemoryManager extends Thread {
	private BlockingDeque<UserProcess> userProcesses;
	private int bytesPerFrame;
	private int totalFrames;
	private int totalProcesses;
	private int processCount;
	private PageFaultHandler pageFault;
	private PhysicalMemory mem;

	public MemoryManager(int bytesPerFrame, int totalFrames,
			int totalProcesses, PageFaultHandler pageFault, PhysicalMemory mem) {
		userProcesses = new LinkedBlockingDeque<UserProcess>();
		this.bytesPerFrame = bytesPerFrame;
		this.totalFrames = totalFrames;
		processCount = 0;
		this.totalProcesses = totalProcesses;
		this.pageFault = pageFault;
		this.mem = mem;
	}

	@Override
	public void run() {
		while (processCount < totalProcesses) {
			UserProcess process = userProcesses.poll();
			if (process != null) {
				if (process.getProcessState() == ProcessState.PAGE_FAULT) {
					userProcesses.addLast(process);
					continue;
				}
				while (process.getLogicalAddresses().size() > 0) {
					int address = process.getLogicalAddresses().get(0);
					PageTableEntry[] pageTable = process.getPageTable();
					int pageNumber = address / bytesPerFrame;
					if (pageNumber > pageTable.length) {
						System.out.println("Process " + process.getProcessID()
								+ "] logical address " + address
								+ " was not a valid address.");
					}
					int pageOffset = address % bytesPerFrame;
					PageTableEntry entry = pageTable[pageNumber];
					if (entry.getFrameNumber() == -1) {
						process.setProcessState(ProcessState.PAGE_FAULT);
						System.out.println("[Process " + process.getProcessID()
								+ "] accesses address " + address
								+ " (page number=" + pageNumber
								+ ", page offset=" + pageOffset
								+ ") not in main memory.");
						pageFault.addAddress(process, 0);
						userProcesses.addLast(process);
						break;
					} else {
						mem.accessMemory(entry.getFrameNumber());
						System.out.println("[Process " + process.getProcessID()
								+ "] accesses address " + address
								+ " (page number=" + pageNumber
								+ ", page offset=" + pageOffset
								+ ") in main memory (frame number = "
								+ entry.getFrameNumber() + ").");
						process.getLogicalAddresses().remove(0);
					}
				}
				if (process.getProcessState() != ProcessState.PAGE_FAULT) {
					incrementProcessCount();
					pageFault.incrementProcessCount();
					System.out.println("[Process " + process.getProcessID() + "] ends");
				}
			}
		}
	}

	/**
	 * Adds a new user process to be processed by the MemoryManager
	 * 
	 * @param process
	 */
	public synchronized void addProcess(UserProcessImpl process) {
		userProcesses.add(process);
	}

	/**
	 * This is used if a file is not found from the main method and when the
	 * process completes in MemoryManager
	 */
	public synchronized void incrementProcessCount() {
		processCount++;
	}
}
