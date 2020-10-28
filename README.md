[README.md - German](docs/de/README.md)



### NAME

       admm - ADMin Menu TUI

![Main Page](/docs/admm.png)

### DESCRIPTION

       admm is a administrator menu TUI for console based on shell scripts

       admm [OPTIONS] <Enter>

![	Overview](/docs/presentation/admm-overview-de.mp4)


### SYNOPSIS

       - The basic idea is to use existing shell scripts and display them in a menu

       - Start admm and press F4 to edit index.mnu or press F3 to edit index.conf for your needs

       - With admm you can edit the menus and scripts, append a new entry to menus and add new scripts

       - If a command is executed, the screen output will be appended to output.log
         To send output.log as email to $INFORM run admm -e

       - If a menu or script file is edited, the menu version will be incremented and
         all modifications are saved as diff output in file changes.log

       - On Master and Clients you always load the scripts from the Master Server= URL if specified
         [admm.conf -> Server=http://server.domain/share/admm-scripts.tar.gz]
         On a master server you can modify the menu files and save them for all nodes on this server
         with [admm Maintenance Menu -> Create admm-scripts.tar.gz]

       - To send emails you must install sSMTP or mSMTP on the master and define [index.conf -> INFORM=name@domain]
         You can find it under [System Installation Menu -> System Software Menu]

       - admm can autoplay hotkey commands with --run="X  "
         X is the hotkey character from Menu or Submenu, use " " to leave a submenu or "  " to exit menu
         If you append -e user $INFORM will be informed with output.log
         After sending the email output.log will be deleted

       - You can extend command line parameters with your own commands. You must insert your command in
         index.conf [Commands] -cmd="aa  "=Comment

       - GPG is used to create and read encrypted password files for scripts.

### OPTIONS

       -c --changes        Display changes.log
       -d --debug=N        Set debug level (see admm.conf)
       -e --email          Send email with output.log to $INFORM
       -h --help           Display options help
       -l --log            Display admm.log
       -o --out            Display output.log
       -r --run="aM   "    Autorun hotkey commands from Menu
       -s --server=""      Select server with admm-*.tar.gz

       -u                  Run system dist-upgrade (see index.conf [Commands])
       -a                  Run system autoremove (see index.conf [Commands])

### FILES

       /usr/local/bin/admm                               Executable
       /usr/local/etc/admm.conf                          Configuration for admm
       /usr/local/share/admm/plugins/template/*.tmpl     Templates for .man .mnu .sh
       /usr/local/share/admm/sripts/debian/index.mnu     Main menu for admm
       /usr/local/share/admm/sripts/debian/index.conf    Main menu configuration
       /usr/local/share/admm/sripts/debian/...           Location for menus and shell scripts or other files used by scripts
       /usr/local/share/admm/admm.log                    Log file of admm, to enable set Debug= > 0 (Default = 1)
       /usr/local/share/admm/changes.log                 Log file with changes of menu and script files (Debug= > 0)
       /usr/local/share/admm/output.log                  Log file with output of executed scripts (Debug= > 0)
       /usr/local/man/admm.man                           This page

### FUNCTION KEYS

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
       SF2- Run mc in /usr/local/share/admm
       SF3- Edit admm.conf
       SF7- Display ouput.log
       SF9- Display changes.log

### NAVIGATION KEYS

       UP-/DOWN-Arrow - Select Menu position
       RIGHT-Arrow    - Open Submenu (not Shell scripts)
       LEFT-Arrow     - Exit from Menu or Submenu
       SPACE          - Exit from Menu or Submenu
       ENTER          - Execute selected Menu position

### MOUSE KEYS

       Left           - Select a button by click, double-click to execute the command
       Right          - Select a button by click, double-click to edit the file

### CONFIGURATION

- [admm.conf](admm.conf)

- [admm.man](docs/admm.man)

- [scripts/debian/index.mnu](scripts/debian/index.mnu)

- [scripts/debian/index.conf](scripts/debian/index.conf)

