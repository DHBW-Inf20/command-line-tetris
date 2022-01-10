# Tetris auf der Kommandozeile

### Allgemeine Informationen
- Projektteilnehmer: Jonathan Schwab, Luca Negron, Jonas Weis
- Programmiersprache: C++
- Build-Command: Wir haben im "out"-Verzeichnis eine Makefile, diese erzeugt eine ausführbare Datei
- Beim Ausführen muss darauf geachtet werden, dass das Fenster ausreichend groß ist, um das Spielfeld darzustellen

### Was wurde umgesetzt
Ein klassisches Tetris-Spiel ist möglich. Darunter verstehen wir folgendes:
- Beim Spielstart kann ein Name vergeben werden
- Einer von sieben Blocks wird relativ ausgewogen gespawnt
- Der Block bewegt sich je nach Level mit unterschiedlicher Geschwindigkeit nach unten
- Der Block kann mit "W" gedreht und mit "A" und "D" in beide Richtungen verschoben werden
- Der Block kann mit "Leertaste" soweit wie möglich ganz und mit "S" schneller nach unten befördert werden
- Ist eine Reihe voll, wird sie gelöscht
- Je nach Level (0-10) und Anzahl der gleichzeitig geklärten Reihen (1-4) werden dem Spieler Punkte zugeschrieben
- Das Löschen von Reihen erhöht auch das Level und somit die Schwierigkeit
- Der aktuelle Punktestand und das Level werden in Echtzeit neben dem Spielfeld angezeigt
- Nach dem Spiel werden die erreichten Punkte in die Bestenliste (lokal) eingetragen (immer nur Top 10)
- Erneutes Spielen oder das Anzeigen der Bestenliste ist möglich


### Wie wurde es umgesetzt
Zur Umsetzung der Anzeige auf der Konsole wurden ANSI-Escape-Codes genutzt ([Quelle](https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/)). Die Konsole wird in kleinen Intervallen, bzw. 
bei Tastendruck aktualisiert. 
Der genutzte Keylistener wurde auf Stackoverflow gefunden ([Quelle](https://stackoverflow.com/a/67038432)) und für unsere Bedürfnisse ergänzt.
Damit Eingaben registriert und angezeigt werden können nutzen wir Multithreading.
Ansonsten wurde auf in der Vorlesung erlernte Mittel zurückgegriffen (Klassen, Headerfiles, Vektoren, Pointer, etc). 
Die Nutzung der verschiedenen Tetrisblöcke wurde durch Polymorphie umgesetzt. 
Als Codierungsrichtlinien wurde der Microsoft C++ Standard verwendet. Die verwendeten Entwicklungsumgebungen sind Visual Studio Code und Visual Studio 2019. Angepasst wurde alles an den GNU-Compiler mit dem Treiber G++. Unterstützt werden Unix- und Windows-Betriebssysteme.
