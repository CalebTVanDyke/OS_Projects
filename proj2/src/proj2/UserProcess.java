package proj2;

public class UserProcess extends Thread{

	private int logicalAddress;
	private MemoryManager memManThread;
	
	public UserProcess(int logicalAddress, MemoryManager memoryManager){
		this.logicalAddress = logicalAddress;
		memManThread = memoryManager;
	}
	
	@Override
	public void run() {
		memManThread.addProcess(this);
	}

	public int getLogicalAddress() {
		return logicalAddress;
	}

	public void setLogicalAddress(int logicalAddress) {
		this.logicalAddress = logicalAddress;
	}
	
	

}
