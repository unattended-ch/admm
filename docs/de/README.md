[English][english]

# admm

       ADMin Menü TUI

       Den Server von den Konsole verwalten

![Main Page][main]

## BESCHREIBUNG

       admm ist ein Administrator Menü TUI für Konsole basierend auf Shell scripts

       admm [OPTIONEN] <Enter>

       admm wurde entwickelt mit Lazarus und freevision paket

[Anleitungs Videos][tutorial]

## ÜBERSICHT

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

## OPTIONEN

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

## DATEIEN

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

## FUNKTIONS TASTEN

       F1 - Hilfeseite anzeigen wenn vorhanden (drücke F6 für eine neue Seite)
       F2 - Starte mc
       F3 - Bearbeite index.conf (Globale Menü Konfiguration)n
       F4 - Bearbeite angezeigtes Menü mit mcedit
       F5 - Bearbeite gewähltes Menü oder Script mit mcedit, wenn die Datei nicht existiert wird sie mit Vorlage erzeugt
       F6 - Bearbeite existierende Hilfeseite oder erstelle eine neue
       F7 - Ausgabe des letzten Befehls
       F8 - Lade Hauptmenü
       F9 - admm.log Anzeigen
       F10- Beenden
       SF1- admm.man anzeigen
       SF2- mc in Ordner der Menu Datei ausführen
       SF3- admm.conf bearbeiten
       SF5- functions.inc bearbeiten
       SF7- ouput.log anzeigen
       SF8- admm-scripts.sh ausführen für Server export
       SF9- changes.log anzeigen

## NAVIGATIONS TASTEN

       UP-/DOWN-Arrow - Wähle Menü position
       RIGHT-Arrow    - Öffne Untermenü (nicht Shell scripts)
       LEFT-Arrow     - Beende Menü oder Untermenü
       SPACE          - Beende Menü or Untermenü
       ENTER          - Ausgewählte Menü position ausführen

## MAUS TASTEN

       Left           - Taste auswählen durch klick, doppel-klick ausführen des Befehls
       Right          - Taste auswählen durch klick, doppel-klick bearbeiten der Datei

## KONFIGURATION

- [admm.conf](admm.conf)

- [admm.man](docs/admm.man)

- [scripts/debian/index.mnu](scripts/debian/index.mnu)

- [scripts/debian/index.conf](scripts/debian/index.conf)


[main]: docs/admm.png

[german]: docs/de/README.md

[english]: README.md

[tutorial]: docs/presentation/
