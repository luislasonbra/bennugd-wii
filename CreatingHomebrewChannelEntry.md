# Introduction #

This page includes basic details and an example on how to get your BennuGD gameintegrated with the Homebrew Channel. You'll know how to give your app a name and an icon.


# Details #

Things you'll need:

  * A working BennuGD game.
  * The homebrew Channel installed in your Wii ([instructions](http://wiibrew.org/wiki/Homebrew_setup)).
  * A PNG icon for your app, sized 128x48 pixels.

You can use the following icon as an example:

![http://bennugd-wii.googlecode.com/svn/wiki/BennuGDWii.png](http://bennugd-wii.googlecode.com/svn/wiki/BennuGDWii.png)

In the same game as the boot.elf/boot.dol file, add an XML file named meta.xml with the following content:
```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<app version="1">
  <name>GAMENAME</name>
  <coder>AUTHOR</coder>
  <version>VERSION</version>
  <release_date>RELEASEDATE</release_date>
  <short_description>A SHORT DESCRIPTION FOR YOUR GAME.</short_description> 
  <long_description>A LONGER DESCRIPTION FOR YOUR GAME.</long_description> 
</app>
```
Obviously, replace the text in uppercase with the applicable info for your game.
Congratulations, you should now be fully integrated with the Homebrew Channel :)