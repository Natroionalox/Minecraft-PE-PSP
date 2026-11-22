## Downloading needed files and programs
1. download pspdev using instructions from [psp dev github](https://pspdev.github.io/)
2. copy [Minecraft-PE-PSP distro](https://github.com/Pencea-Flavius/Minecraft-PE-PSP)
## Seting up workplace
1. on our repository, create a separate test branch
## First compilation
1. follow steps in README.md
2. try to run EBOOT.PBP on PPSSPP
## First edits to game physics/content
try changing gamemode.cpp block hit range - doesnt work
try changing player flying up speed - it does indeed work.
-discovered that cpp are source code files
-.h files are headers that indicate structure of objects
-.d are automatically made during compilation
-too much speed freezes game

changing player hp in entity/player.h works as expected

discovered local_player.cpp
attempt at increasing movement speed by a variable
-turns out thats turning speed

player inherits from mob who inherits from entity

## Adding in tool item
-in item.cpp add the item to the list.
- name - must be logget in item.h with a valid id.
- tier - (dont know what that is yet, i assume its breaking power, damage and speed)
- ic - icon coordinate in items.png
 - this doesnt appear to work as ive expected, as the new item doesnt have texture and im unable to change the texture of already existing items this way
-add the item to the presumeably item list in item.cpp
- name - same as before
- category - as declared in item.h
-adding crafting recime
- in recipes.cpp Recipes() you can add a recipe
- for tools there will be a list of materials and each recipe will be created automatically
 - its necesarry for those to increase matTypes if you plan on using new material
 - presumeably you should also increase toolTypes if you wish to create new tool type (more complex)
-adding to crafting menu
 - in creative_items.cpp there is a list of creative items
 - adding the item in item.cpp to the second list makes me able to move it to different menu (thats indicated by the number besides item id), however its placement in the tab is mysterious 
  - order of the items within the creative menu tab is set by the order of creation in creative_items.cpp
-in hud.cpp you add the name of hte object

-in creative_items.h ive changed the number of creative tab menus to 5 to accomidate for mod item menu.
 - for this ive had to comment out few lines in inventory_ui.cpp as it restricted me from adding more menus due to ui overflow
 - needed to create a creative tab icon, however since the "Bowl Pickaxe" (jesus crhist be fr) item has no working sprite, its blank


## Things needed to be done:
-figure out how to create a working sprite for the modded item
-make the ui scaleable, or otherwise functioning as to not comment out original coders allerts or whatever