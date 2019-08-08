# volley

A CLI game of Battleship implemented in C++ for one player against a ship-seeking computer opponent.

## Usage

```
$ make
$ build/volley
```

If an 'E' shows up on the board, something is wrong. That's used to signify an Error. Valid ships are `A`, `B`, `C`, `D`, and `U`. Empty spaces are `.`, Hits are `X`. Misses are `O`.

```
Enter Target.  Enter 'R' for random.  (ColRow, e.g. "A1" or "a1")> r
Rolling the dice...
Row: 10 Col: H
It's a miss.
Computer fires at: Row: 10 Col: A
It's a hit!
The Computer sank The Player's Battleship!
                Player                                   Computer
Ships alive:                                 Ships alive:
{ U:3 }                              { A:5 B:4 C:3 D:2 U:3 }

    A  B  C  D  E  F  G  H  I  J              A  B  C  D  E  F  G  H  I  J

 1  .  O  .  .  .  .  O  O  .  O           1  .  X  .  .  .  O  .  .  .  O

 2  .  O  X  O  .  .  .  .  O  .           2  .  O  O  O  .  X  O  O  O  O

 3  .  O  X  O  .  O  .  .  X  .           3  O  .  .  O  .  X  O  .  O  O

 4  .  .  X  .  .  X  O  .  X  .           4  .  .  X  .  .  .  .  O  .  X

 5  .  .  O  .  .  X  O  .  O  .           5  .  .  .  .  .  .  O  .  O  .

 6  O  O  .  .  O  X  .  O  .  .           6  .  .  .  .  .  .  .  O  O  .

 7  X  U  U  U  .  X  .  O  O  .           7  .  O  O  .  .  O  .  .  .  O

 8  X  .  .  .  .  X  .  O  .  .           8  .  O  O  .  O  .  .  .  .  O

 9  X  .  .  .  .  .  .  O  .  .           9  O  .  O  O  .  O  .  .  .  .

10  X  .  O  .  .  O  O  O  O  .          10  .  O  O  .  .  O  .  O  .  O
```
