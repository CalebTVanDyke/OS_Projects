

import java.util.ArrayList;

public interface UserProcess {

	public ArrayList<Integer> getLogicalAddresses();

	public void setLogicalAddresses(ArrayList<Integer> logicalAddresses);

	public ProcessState getProcessState();

	public void setProcessState(ProcessState processState);

	public PageTableEntry[] getPageTable();

	public void setPageTable(PageTableEntry[] pageTable);

	public int getMaxPages();

	public void setMaxPages(int maxPages);

	public int getProcessID();

	public void setProcessID(int processID);

}