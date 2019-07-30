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
Row: 9 Col: D
It's a hit!
Opponent fires Row: 7 Col: D
It's a miss.
               Player                                   Computer

    A  B  C  D  E  F  G  H  I  J              A  B  C  D  E  F  G  H  I  J

 1  .  .  .  .  .  .  .  .  D  D           1  .  .  .  .  .  .  .  .  .  .

 2  .  .  .  .  .  .  .  .  .  .           2  .  .  .  .  .  .  .  O  .  .

 3  .  .  .  .  A  .  U  U  U  .           3  .  .  .  .  .  .  .  .  .  .

 4  .  .  .  .  A  .  .  .  O  .           4  .  .  .  .  .  .  O  .  .  .

 5  O  .  .  .  A  .  .  .  .  .           5  .  .  O  .  .  .  .  .  .  .

 6  .  .  .  .  A  .  .  .  .  .           6  .  .  .  .  .  .  .  .  .  .

 7  .  .  .  O  A  .  .  .  .  .           7  .  .  .  .  .  .  .  .  .  .

 8  .  B  B  B  B  .  C  .  .  .           8  .  .  .  .  .  .  .  .  .  .

 9  .  .  .  .  .  .  C  O  .  .           9  .  .  .  X  .  .  .  .  .  .

10  .  .  .  .  .  .  C  .  .  .          10  .  .  .  .  .  .  .  .  .  .

```
