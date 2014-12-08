

import java.util.ArrayList;

public class UserProcessImpl extends Thread implements UserProcess {

	private ArrayList<Integer> logicalAddresses;
	private PageTableEntry[] pageTable;
	private MemoryManager memManThread;
	private ProcessState processState;
	private int maxPages;
	private int processID;

	public UserProcessImpl(int processID, int maxPages, MemoryManager memoryManager) {
		this.processID = processID;
		logicalAddresses = new ArrayList<Integer>();
		memManThread = memoryManager;
		processState = ProcessState.RUN;
		this.maxPages = maxPages;
		pageTable = new PageTableEntry[maxPages];
		for(int i = 0; i < pageTable.length; i++){
			pageTable[i] = new PageTableEntry();
		}
	}

	@Override
	public void run() {
		memManThread.addProcess(this);
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#getLogicalAddresses()
	 */
	@Override
	public synchronized ArrayList<Integer> getLogicalAddresses() {
		return logicalAddresses;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#setLogicalAddresses(java.util.ArrayList)
	 */
	@Override
	public synchronized void setLogicalAddresses(ArrayList<Integer> logicalAddresses) {
		this.logicalAddresses = logicalAddresses;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#getProcessState()
	 */
	@Override
	public synchronized ProcessState getProcessState() {
		return processState;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#setProcessState(proj2.ProcessState)
	 */
	@Override
	public synchronized void setProcessState(ProcessState processState) {
		this.processState = processState;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#getPageTable()
	 */
	@Override
	public synchronized PageTableEntry[] getPageTable() {
		return pageTable;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#setPageTable(proj2.PageTableEntry[])
	 */
	@Override
	public synchronized void setPageTable(PageTableEntry[] pageTable) {
		this.pageTable = pageTable;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#getMaxPages()
	 */
	@Override
	public int getMaxPages() {
		return maxPages;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#setMaxPages(int)
	 */
	@Override
	public void setMaxPages(int maxPages) {
		this.maxPages = maxPages;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#getProcessID()
	 */
	@Override
	public int getProcessID() {
		return processID;
	}

	/* (non-Javadoc)
	 * @see proj2.UserProcess#setProcessID(int)
	 */
	@Override
	public void setProcessID(int processID) {
		this.processID = processID;
	}
	
}
