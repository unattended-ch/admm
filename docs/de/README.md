[README.md - Englisch](/README.md)

[Tutorial Videos](docs/presentation/)


### NAME

       admm - ADMin Menü TUI

![Main Page](/docs/admm.png)

### BESCHREIBUNG

       admm ist ein Administrator Menü TUI für Konsole basierend auf Shell scripts

       admm [OPTIONEN] <Enter>

       admm wurde entwickelt mit Lazarus und freevision paket

### ÜBERSICHT

       - Die Grund Idee ist der Einsatz von existierenden Shell scripts in
         einem Menü

       - Starte admm und drücke F4 um index.mnu oder F3 um index.conf zu
         bearbeiten

       - Mit admm kann man Menüs und Scripts bearbeiten, neue Einträge
         einfügen und neue Scripts erstellen

       - Beim ausführen eines Befehls, wird die Bildschirmausgabe der Datei
         output.log angehängt. Um output.log per Email an $INFORM zu
         versenden starte admm -e

       - Wenn eine Menü- oder Script- Datei editiert wird, erhöht sich die
         Version automatisch und alle Änderungen werden als diff Ausgabe der
         Datei changes.log angehängt

       - Auf dem Master und den Klienten werden die Scripts vom Master
         Server= URL wenn angegeben [admm.conf ->
         Server=http://server.domain/share/admm-scripts.tar.gz]. Auf einem
         Master Server kann man die Menü Dateien bearbeiten und für alle auf
         diesem Server speichern mit [admm Maintenance Menu -> Create
         admm-scripts.tar.gz]

       - Um Emails zu versenden muss sSMTP oder mSMTP auf dem Master
         installiert werden. Man findet Installationen unter [System
         Installation Menu -> System Software Menu]. Definiere [index.conf
         -> INFORM=name@domain] mit der Admin Email Adresse

       - admm kann automatisch Schnelltasten Befehle abspielen mit --run="X
         ". X ist die Schnelltaste aus dem Menü oder Untermenü, benutze ein
         " " um das Untermenü oder Menü zu verlassen. Wenn man -e anhängt
         wird Benutzer $INFORM die Datei output.log gesendet. Nach dem
         versenden wird output.log gelöscht

       - Man kann Kommandozeilen Parameter erweitern mit eigenen
         Befehlen. Man muss dazu den Befehl einfügen in index.conf
         [Commands] -cmd="aa  "=Comment

       - GPG wird verwendet um Verschlüsselte Dateien mit Passwörtern zu
         erstellen und zu lesen.

### OPTIONEN

       -c --changes        changes.log anzeigen
       -d --debug=N        Debug level setzen (see admm.conf)
       -e --email          Email versenden mit output.log an $INFORM
       -h --help           Optionen Hilfe anzeigen
       -l --log            admm.log anzeigen
       -o --out            output.log anzeigen
       -r --run="aM   "    Ausführen von Schnelltasten des Menüs
       -s --server=""      Wähle Server mit admm-*.tar.gz

       -u                  Starte System dist\-upgrade (siehe index.conf [Commands])
       -a                  Starte System autoremove (siehe index.conf [Commands])

### DATEIEN

       /usr/local/bin/admm                               Ausführbare Datei
       /usr/local/etc/admm.conf                          Konfiguration für admm
       /usr/local/share/admm/plugins/template/*.tmpl     Vorlagen für .man .mnu .sh
       /usr/local/share/admm/sripts/debian/index.mnu     Hauptmenü für admm
       /usr/local/share/admm/sripts/debian/index.conf    Hauptmenü konfiguration
       /usr/local/share/admm/sripts/debian/...           Ordner für Menüs und Scripts oder andere benötigte Dateien
       /usr/local/share/admm/admm.log                    Logdatei von admm, Aktivieren mit Debug= > 0 (Default = 1)
       /usr/local/share/admm/changes.log                 Logdatei mit Änderungen von Menüs und Script (Debug= > 0)
       /usr/local/share/admm/output.log                  Logdatei mit Ausgabe der ausgeführten Befehle (Debug= > 0)
       /usr/local/man/admm.man                           Man Seite für admm

### FUNKTIONS TASTEN

       F1 - Display Help if available (press F6 to create a new man page)
       F2 - Start mc
       F3 - Edit index.conf (global menu configuration)
       F4 - Edit displayed Menu with mcedit
       F5 - Edit selected Menu or Shell script with mcedit, if not exists create it with template
       F6 - Edit existing Help or create a new man page
       F7 - Output of last executed command
       F8 - Load Mainmenu
       F9 - Display admm.log
       F10- Exit
       SF1- Display admm.man
       SF2- Run mc in folder wher menu file is located
       SF3- Edit admm.conf
       SF7- Display ouput.log
       SF8- Run admm-scripts.sh for export to server
       SF9- Display changes.log

### NAVIGATIONS TASTEN

       UP-/DOWN-Arrow - Wähle Menü position
       RIGHT-Arrow    - Öffne Untermenü (nicht Shell scripts)
       LEFT-Arrow     - Beende Menü oder Untermenü
       SPACE          - Beende Menü or Untermenü
       ENTER          - Ausgewählte Menü position ausführen

### MAUS TASTEN

       Left           - Taste auswählen durch klick, doppel-klick ausführen des Befehls
       Right          - Taste auswählen durch klick, doppel-klick bearbeiten der Datei

### KONFIGURATION

- [admm.conf](admm.conf)

- [admm.man](docs/admm.man)

- [scripts/debian/index.mnu](scripts/debian/index.mnu)

- [scripts/debian/index.conf](scripts/debian/index.conf)

