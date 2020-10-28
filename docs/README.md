## README.md and admm.man language translation

#### Original files for translation
    ../README.md
    ./admm.man

#### Translated files
    ./[xx]/README.md
    ./[xx]/admm.man

    xx = Language short code en, de, fr ...

#### Translation scripts
#####    To use the scripts you have to install [po4a] package from ubuntu or debian

    1. Edit the po-*.sh scripts replace LNG="de fr" with your languages
    2. Only when LNG= has changed you have to run po-create.sh
    3. Run po-translate.sh for translation on all languages in LNG=
    4. Edit the .po files
    5. Run po-update.sh to generate files for all languages in LNG=

#### Tranlating .po files
    - I use poedit for tranlations.
#####    You have to install [poedit]  package from ubuntu or debian
    - When you edit the .po file always copy original text and replace english with your
      language to preserve formatting.

    - Please send me your .po files back for integration in the installer package

#### Thank you in advance for your contribution!
