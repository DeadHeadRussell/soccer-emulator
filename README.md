Soccer Emulator
===============

Text based emulation of soccer games.  Teams are created in text files with a set of stats which are updated over time based on the games played.

Building
===============

This project requires MinGW to build and run. Once MinGW is setup, simply run `make` in the root folder of the project. This will produce the executable file in the same folder.

Running
===============

To create a team file, use the following format:

TeamName Offence Midfield Defence Goalie Coach Aggressivness Gamesplayed Gameswon Redflags Yellowflags

Example

Winners 10 11 9 10 8 6 0 0 0 0

Always set the gamesplayed, gameswon, redflags, and yellowflags to zero if it is the beginning of the season or if it is a new team entering.  After the team plays a game, the offence and other stats will turn into big long decimal numbers.  This is fine.  Also, all the stats from offence to aggresevness can be a decimal number instead of an integer.  Average stats for the offence to the aggresiveness is 8.

All stats but the coach and aggresevness are automaticaly updated after each game based on their coach's skill level.  Agressivness and coach stats shouldonly be updated at the end of the season, coach based on how well the team did overall, and aggressivness would depend on how well the team did compared to how many fouls they committed.

The game folder contains stats outputed from the game.  These include score, overtime score, fouls, and possession.  The rounds folder contains stats ouputed from the game, round at a time.  This was mainly for my debugging purposes, but it basicly contains what happens during each round of play.  Each round is considered 1 minute long.

