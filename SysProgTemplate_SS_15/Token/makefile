# Definition der Variablen

# enthaelt die Header Files
HEADERDIR = includes

# enthaelt die Source Files
SRCDIR = src

# enthaelt die Obj Files fuer das Gesamtprojekt
OBJDIR = objs

# enthaelt die Objectfiles und das ausfuehrbare File zum Testen des Teilprojekts
BINDIRTEST = debug

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von TokenTarget und TestTokenTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestToken: TokenTarget 	TestTokenTarget
	g++ -g $(OBJDIR)/Token.o 	$(BINDIRTEST)/TestToken.o  -o $(BINDIRTEST)/TokenTest
	

# compilieren der Source-files
# Token.o ist abhaengig von Token.cpp und Token.h
# flag:
# -c --> nur compilieren
# -g --> debug Informationen erzeugen
# -Wall --> alle meldungen erzeugen (Warning all)

TokenTarget :  $(SRCDIR)/Token.cpp $(HEADERDIR)/Token.h 
	g++ -g  -c -Wall  $(SRCDIR)/Token.cpp -o $(OBJDIR)/Token.o

#TestToken.o ist abhaengig von TestToken.cpp und Token.h
TestTokenTarget :  $(SRCDIR)/TestToken.cpp $(HEADERDIR)/Token.h
	g++ -g  -c -Wall $(SRCDIR)/TestToken.cpp -o $(BINDIRTEST)/TestToken.o




# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren

cleanToken:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIRTEST)/*
	$(MAKE) makeTestToken
	

# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer GesamtProjekt loeschen und dann neu erzeugen
TokenOBJTarget:
	$(MAKE) TokenTarget

	