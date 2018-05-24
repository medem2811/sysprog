#
#	baut das komplette Scanner Projekt
#
OBJDIR = objs

AUTOMATDIR = Automat

BUFFERDIR = Buffer

SYMBOLTABLEDIR = Symboltable

SCANNERDIR = Scanner

TOKENDIR = Token

PARSERDIR = Parser


all:	automatOBJs bufferOBJs symboltableOBJs tokenOBJs scanner parser  
	@echo "target all"

	
# rm 	remove
# -f	force, ohne nachfragen
clean:
	rm -f $(AUTOMATDIR)/$(OBJDIR)/*.o
	rm -f $(BUFFERDIR)/$(OBJDIR)/*.o
	rm -f $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o
	rm -f $(SCANNERDIR)/$(OBJDIR)/*.o
	rm -f $(TOKENDIR)/$(OBJDIR)/*.o
	rm -f $(SCANNERDIR)/debug/*
	rm -f $(PARSERDIR)/debug/*


automatOBJs:
	$(MAKE) -C $(AUTOMATDIR) AutomatOBJTarget
	
	
bufferOBJs:
	$(MAKE) -C $(BUFFERDIR) BufferOBJTarget

	
symboltableOBJs:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableOBJTarget
	
tokenOBJs: 
	$(MAKE) -C $(TOKENDIR) TokenOBJTarget

scanner: 
	$(MAKE) -C $(SCANNERDIR) makeTestScanner
	
parser: 
	$(MAKE) -C $(PARSERDIR) makeTestParser
	


	