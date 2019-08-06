# volley

A CLI game of Battleship implemented in C++

WIP

## Usage

```
$ make
$ build/volley
```

If an 'E' shows up on the board, something is wrong. That's used to signify an Error. Valid ships are `A`, `B`, `C`, `D`, and `U`. Empty spaces are `.`, Hits are `X`. Misses are `O`.

```
Enter Target.  Enter 'R' for random.  (ColRow, e.g. "A1" or "a1")> r
Rolling the dice...
Row: 10 Col: A
It's a miss.
Computer fires at: Row: 6 Col: G
It's a miss.
                Player                                   Computer
Ships alive:                                 Ships alive:
{ A:5 B:4 C:3 D:2 U:3 }                              { A:5 B:4 C:3 D:2 U:3 }

    A  B  C  D  E  F  G  H  I  J              A  B  C  D  E  F  G  H  I  J

 1  .  .  .  .  .  .  .  .  O  O           1  O  .  .  O  .  .  .  .  .  .

 2  .  .  .  .  .  .  B  B  B  B           2  .  .  .  .  .  .  .  O  O  .

 3  .  .  .  O  .  .  O  .  .  .           3  .  .  .  .  X  .  O  .  .  .

 4  .  .  O  O  .  .  .  O  O  .           4  .  .  .  .  .  .  .  O  O  .

 5  O  O  .  .  .  X  O  .  .  .           5  .  O  .  .  O  O  .  .  .  .

 6  .  .  .  .  .  X  O  O  O  .           6  .  .  .  .  .  .  .  .  .  .

 7  .  D  D  .  .  U  .  .  .  .           7  .  .  .  .  .  .  X  .  O  .

 8  .  .  O  .  .  A  A  A  A  A           8  .  .  .  .  .  .  O  .  O  O

 9  .  .  O  .  .  .  .  O  O  .           9  O  .  .  .  .  .  .  .  O  .

10  C  C  C  .  .  .  .  .  O  .          10  O  O  .  .  .  .  .  O  .  .
```
