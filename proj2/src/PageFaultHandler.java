

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class PageFaultHandler extends Thread {

	private BlockingQueue<PageFaultInfo> addresses;
	private int bytesPerFrame;
	private PhysicalMemory mem;
	private int maxProcess;
	private int processCount;

	public PageFaultHandler(int bytesPerFrame, PhysicalMemory mem, int maxProcess) {
		addresses = new LinkedBlockingQueue<PageFaultInfo>();
		this.bytesPerFrame = bytesPerFrame;
		this.mem = mem;
		this.maxProcess = maxProcess;
		processCount = 0;
	}

	@Override
	public void run() {
		while (processCount < maxProcess) {
			PageFaultInfo info = null;
			while ((info = addresses.poll()) != null) {
				int pageNumber = info.process.getLogicalAddresses().get(info.addressIndex) / bytesPerFrame;
				// If frame number does not equal -1 then it will equal
				// to an empty position in the physical memory
				int frameNumber = mem.getEmptyFrame();
				if (frameNumber != -1) {
					System.out
							.println("[Process "
									+ info.process.getProcessID()
									+ "] finds a free frame in main memory (frame number = "
									+ frameNumber + ").");
				} else {
					frameNumber = mem.getLRU();
					System.out.println("[Process "
							+ info.process.getProcessID()
							+ "] replaces a frame (frame number = "
							+ frameNumber + ") from the main memory.");
				}
				System.out
						.println("[Process "
								+ info.process.getProcessID()
								+ "] issues an I/O operation to swap in demanded page (page number = "
								+ pageNumber + ").");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				System.out.println("[Process " + info.process.getProcessID()
						+ "] demanded page (page number = " + pageNumber
						+ ") has been swapped in main memory (frame number = "
						+ frameNumber + ").");
				// Make sure the other processes page table is updated so
				// it knows that that page table entry no longer
				// points to the correct frame
				UserProcess invalid = mem.getResource(frameNumber);
				if (invalid != null) {
					for (PageTableEntry entry : invalid.getPageTable()) {
						if (entry.getFrameNumber() == frameNumber) {
							entry.setFrameNumber(-1);
							break;
						}
					}
				}
				mem.replaceFrame(frameNumber, info.process);
				info.process.getPageTable()[pageNumber]
						.setFrameNumber(frameNumber);
				info.process.setProcessState(ProcessState.RUN);
			}
		}
	}

	public synchronized void addAddress(UserProcess process, int addressIndex) {
		addresses.add(new PageFaultInfo(process, addressIndex));
	}
	
	/**
	 * This is used to let the page fault handler know one of the processes is complete
	 * This helps the page fault handler know when to terminate
	 */
	public synchronized void incrementProcessCount() {
		processCount++;
	}

	private class PageFaultInfo {
		public UserProcess process;
		public int addressIndex;

		public PageFaultInfo(UserProcess process, int addressIndex) {
			super();
			this.process = process;
			this.addressIndex = addressIndex;
		}
	}

}
