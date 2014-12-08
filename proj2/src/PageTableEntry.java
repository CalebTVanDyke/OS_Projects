

public class PageTableEntry {
	
	private int frameNumber;
	
	public PageTableEntry(){
		this.frameNumber = -1;
	}
	public PageTableEntry(int frameNumber){
		this.frameNumber = frameNumber;
	}
	public int getFrameNumber() {
		return frameNumber;
	}
	public void setFrameNumber(int frameNumber) {
		this.frameNumber = frameNumber;
	}
	
	
}
