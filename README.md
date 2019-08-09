# volley

A CLI game of Battleship implemented in C++ for one player against a ship-seeking computer opponent.

## Usage

```
$ make
$ build/volley
```

Sample gameplay:

```
Enter Target.  'R' for random.  (e.g. "A1" | "a1" | "1A" | "1a")> r
Rolling the dice...
Row: 8 Col: G
It's a miss.
Computer fires at: Row: 5 Col: F
It's a hit!
The Computer sank The Player's Cruiser (3)!
                Player                                   Computer
Ships alive:                                 Ships alive:
{ A:5 B:4 }                                                 { C:3 D:2 U:3 }

    A  B  C  D  E  F  G  H  I  J              A  B  C  D  E  F  G  H  I  J

 1  .  .  O  .  .  .  B  O  O  .           1  .  O  .  .  .  .  O  .  .  .

 2  .  .  .  O  .  .  B  .  .  O           2  .  .  .  .  O  .  .  .  .  .

 3  .  O  .  .  .  .  B  .  O  O           3  .  .  .  O  X  O  O  .  .  .

 4  A  .  .  O  .  .  B  X  X  X           4  .  .  .  .  X  O  .  .  .  O

 5  A  .  .  .  .  X  X  X  O  .           5  .  .  .  .  X  O  .  .  .  O

 6  A  .  .  .  O  .  .  .  .  .           6  .  O  .  .  X  .  .  .  .  X

 7  A  .  .  .  .  O  .  .  O  .           7  .  .  .  O  O  O  .  .  .  X

 8  A  .  .  .  .  O  .  .  .  .           8  .  .  .  .  O  .  O  .  .  X

 9  .  .  .  .  .  .  .  X  X  .           9  .  O  .  .  .  .  .  .  .  X

10  O  .  .  .  .  .  .  O  O  .          10  .  .  .  .  .  .  .  .  .  X
```
