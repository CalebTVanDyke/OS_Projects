

public class PhysicalMemory {

	private Frame[] frames;

	public PhysicalMemory(int bytesPerFrame, int numFrames) {
		frames = new Frame[numFrames];
		for (int i = 0; i < frames.length; i++) {
			frames[i] = new Frame();
		}
	}

	public synchronized int getEmptyFrame() {
		for (int i = 0; i < frames.length; i++) {
			if (frames[i].resource == null) {
				return i;
			}
		}
		return -1;
	}

	public synchronized int getLRU() {
		int lru = 0;
		for (int i = 0; i < frames.length; i++) {
			if (frames[i].resource == null) {
				continue;
			}
			if (frames[lru].count < frames[i].count) {
				lru = i;
			}
		}
		return lru;
	}
	
	public synchronized boolean accessMemory(int frameNumber){
		if(frames[frameNumber].resource == null){
			return false;
		}
		for(int i = 0; i < frames.length; i++){
			if(i == frameNumber){
				frames[i].count = 0;
			}else{
				frames[i].count++;
			}
		}
		return true;
	}
	public synchronized boolean replaceFrame(int frameNumber, UserProcess resource){
		frames[frameNumber].resource = resource;
		frames[frameNumber].count = 0;
		return true;
	}
	
	public synchronized UserProcess getResource(int frameNumber){
		return frames[frameNumber].resource;
	}

	private class Frame {
		public int count;
		public UserProcess resource;
		
		public Frame() {
			count = 0;
			resource = null;
		}

		public Frame(int count, UserProcess resource) {
			super();
			this.count = count;
			this.resource = resource;
		}
		
	}
}
