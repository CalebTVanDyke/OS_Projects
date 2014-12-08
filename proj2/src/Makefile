JFLAGS = -g
JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java
	
CLASSES = \
	PageTableEntry.java \
	ProcessState.java \
	PhysicalMemory.java \
	UserProcess.java \
	MemoryManager.java \
	PageFaultHandler.java \
	simVM.java
	
default: classes

classes: $(CLASSES:.java=.class)

MemoryManager.class: UserProcess.class PageFaultHandler.class PhysicalMemory.class PageTableEntry.class

PageFaultHandler.class: PhysicalMemory.class PageTableEntry.class UserProcess.class

PageTableEntry.class: 

PhysicalMemory.class: UserProcess.class

ProcessState.class: 

UserProcess.class: PageTableEntry.class ProcessState.class

simVM.class: UserProcessImpl.class PhysicalMemory.class PageFaultHandler.class MemoryManager.class

UserProcessImpl.class: MemoryManager.class PageTableEntry.class ProcessState.class UserProcess.class


clean: 
	rm -f *.class