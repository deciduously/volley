# SDEV240 Final Project Proposal

## CLI Battleship

I’d like to implement a game of Battleship played on the command line against a mostly-randomly playing computer opponent.  If the computer hits, it will search until it sinks the ship it hits.  The UI will be rendered as text, and keyboard commands used to control your player.  There will be two stages to a round.  In the first stage, it will how you one board and prompt you to enter your ship placement, one at a time:

```
      A  B  C   D  E   F  G   H   I   J
1    _   _   _   _   _   _   _   _   _   _                      Ships remain: {5:A 4:B 3:C 3:U 2:D}
2    _   _   _   _   _   _   _   _   _   _
3    _   _   _   _   _   _   _   _   _   _
4    _   _   _   _   _   _   _   _   _   _
5    _   _   _   _   _   _   _   _   _   _
6    _   _   _   _   _   _   _   _   _   _
7    _   _   _   _   _   _   _   _   _   _
8    _   _   _   _   _   _   _   _   _   _
9    _   _   _   _   _   _   _   _   _   _
10   _   _   _   _   _   _   _   _   _   _

Which length ship do you want to add? 6
Not an available ship!
Which length ship do you want to add? 5
Origin: 9B // accepts either RowCol or ColRow: A1 or 1A
(L)eft or (d)own: D // case insensitive
Unable to place carrier ship there.  // each ship has a display name as well as a board name
Change (d)irection or (o)rigin? D

Placing Left instead:
      A  B  C   D  E   F  G   H   I   J
1    _   _   _   _   _   _   _   _   _   _                      Ships remain: {5:A 4:B 3:C 3:U 2:D}
2    _   _   _   _   _   _   _   _   _   _
3    _   _   _   _   _   _   _   _   _   _
4    _   _   _   _   _   _   _   _   _   _
5    _   _   _   _   _   _   _   _   _   _
6    _   _   _   _   _   _   _   _   _   _
7    _   _   _   _   _   _   _   _   _   _
8    _   _   _   _   _   _   _   _   _   _
9    _   A   A   A   A   A   _   _   _   _
10   _   _   _   _   _   _   _   _   _   _

Confirm placement (y/n): y // will always display and confirm before placing
```

First ship should just prompt to place, future ships should prompt to place or change an already placed ship, if all five are placed, prompt to change or finish.

Also, don't pick by length, obviously.  They have unique letters, use those.

After all ships have been place the game begins:

```
                       YOU                                                         THEM
                   Ships left: 5                                              Ships left: 5

      A  B   C   D   E   F   G   H   I   J                        A   B   C   D   E   F   G   H   I   J
1    _   _   _   _   _   _   _   _   _   D                   1    _   _   _   _   _   _   _   _   _   _
2    _   _   _   _   _   B   _   _   _   D                   2    _   _   _   _   _   _   _   _   _   _
3    _   _   _   _   _   B   _   _   _   _                   3    _   _   _   _   _   _   _   _   _   _
4    _   U   U   U   _   B   _   _   _   _                   4    _   _   _   _   _   _   _   _   _   _
5    _   _   _   _   _   B   _   _   _   _                   5    _   _   _   _   _   _   _   _   _   _
6    _   _   _   _   _   _   _   _   _   _                   6    _   _   _   _   _   _   _   _   _   _
7    _   _   _   _   _   _   _   _   _   _                   7    _   _   _   _   _   _   _   _   _   _
8    _   _   _   _   _   _   _   _   _   _                   8    _   _   _   _   _   _   _   _   _   _
9    _   A   A   A   A   A   _   _   _   _                   9    _   _   _   _   _   _   _   _   _   _
10   _   _   _   _   C   C   C   _   _   _                  10    _   _   _   _   _   _   _   _   _   _

Your move: D2 // same syntax as placing the origin, either way works

Miss!

They fire at D4...it’s a hit!


                       YOU                                                         THEM
                   Ships left: 5                                              Ships left: 5

      A  B   C   D   E   F   G   H   I   J                        A   B   C   D   E   F   G   H   I   J
1    _   _   _   _   _   _   _   _   _   D                   1    _   _   _   _   _   _   _   _   _   _
2    _   _   _   _   _   B   _   _   _   D                   2    _   _   _   O   _   _   _   _   _   _
3    _   _   _   _   _   B   _   _   _   _                   3    _   _   _   _   _   _   _   _   _   _
4    _   U   U   X   _   B   _   _   _   _                   4    _   _   _   _   _   _   _   _   _   _
5    _   _   _   _   _   B   _   _   _   _                   5    _   _   _   _   _   _   _   _   _   _
6    _   _   _   _   _   _   _   _   _   _                   6    _   _   _   _   _   _   _   _   _   _
7    _   _   _   _   _   _   _   _   _   _                   7    _   _   _   _   _   _   _   _   _   _
8    _   _   _   _   _   _   _   _   _   _                   8    _   _   _   _   _   _   _   _   _   _
9    _   A   A   A   A   A   _   _   _   _                   9    _   _   _   _   _   _   _   _   _   _
10   _   _   _   _   C   C   C   _   _   _                  10    _   _   _   _   _   _   _   _   _   _

Your move:
```

And so forth until one player runs out of ships.  When a ship is sunk, that player will be notified, the player via console output and the computer via toggling its active search flag.  Then the player will be prompted to play again or quit.

The computer will guess at random from the set of spaces it has not attempted yet unless it knows it’s searching for one.  If it does, it will build and store the neighborhood around the hit and try at random from those cells a turn at a time until a new hit, when it will add the new cells found.  I haven’t decided whether it will clean the neighborhood of cells in the wrong direction just in case ships were stored adjacently, or if it will stop searching the neighborhood if it sinks a ship.  I might implement both and test. When it sinks something, it will clear everything until it finds something again.  This is a rudimentary algorithm that can be fooled by adjacent ships, but works for providing tension during gameplay against a computer.

If time permits, I may extend the program to allow hotseat or even eventually network play.

This project involves several classes:

* Player
  * `board : Board`
  * `unassignedShips : std::vector<Ship>`
  * Default : default board and one of each ship in unassignedShips
* Computer inherits from Player
  * `searching: bool`
  * `neighborhood: std::vector(int, int)`
  * `std::tuple(int, int) getRandomShot(void)`
  * Default constructor will include randomly placing ships
* Board
  * `ships: std::vector<Ship>`
  * `bool occupied(std::tuple(int, int))`
  * `void addShip(Ship, origin: int, enum {Left, Down})`
  * Default constructor will start empty
* Ship
  * `origin: std::tuple(int, int)` // D2 = (4,2)`
  * `direction: enum {Left, Down}`
  * `hits: int`
  * `type: enum { AircraftCarrier, Battleship, Destroyer, U-Boat, Cruiser }`
  * `int getLength(void) // lengths are hardcoded for each type`
  * `char getShortName(void)`
  * `string getLongName(void)`
  * `bool isSunk(void)`
  * Child classes (?) will be provided for each type with a default constructor - are these just  plain functions, not classes?
* Game
  * `player : Player`
  * `computer : Computer`
  * `state : enum { Placement, Firing, GameOver }`
  * `void startGame(void)`
  * `string displayGame(void)`
  * Default constructor starts in Placement, with default players for Player and Computer

I’ve never been formally introduced to inheritance, so I may have that idea not quite right, but I think that’s the general idea.
