# Soccer Emulator

![Soccer Emulator Screen Shot](https://raw.github.com/DeadHeadRussell/website/master/Servers/data/images/personalProjects/Soccer%20Emulator.png)

Text based emulation of soccer games.  Teams are created in text files with a set of stats which are updated over time based on the games played.

## Building

Dependencies:
* Windows (W32 API)
* MinGW

Building (MinGW must be added to the PATH):
```bash
cd <project_dir>
make
```

The executable is placed in the root of the project folder.

## Running

To create a team file, use the following format:

TeamName Offence Midfield Defence Goalie Coach Aggressivness Gamesplayed Gameswon Redflags Yellowflags

Example

Winners 10 11 9 10 8 6 0 0 0 0

Always set the gamesplayed, gameswon, redflags, and yellowflags to zero if it is the beginning of the season or if it is a new team entering.  After the team plays a game, the offence and other stats will turn into big long decimal numbers.  This is fine.  Also, all the stats from offence to aggressivness can be a decimal number instead of an integer.  Average stats for the offence to the aggressiveness is 8.

All stats but the coach and aggressivness are automatically updated after each game based on their coach's skill level.  Aggressivness and coach stats should only be updated at the end of the season, coach based on how well the team did overall, and aggressivness would depend on how well the team did compared to how many fouls they committed.

The game folder contains stats outputted from the game.  These include score, overtime score, fouls, and possession.  The rounds folder contains stats outputted from the game, round at a time.  This was mainly for my debugging purposes, but it basically contains what happens during each round of play.  Each round is considered 1 minute long.

