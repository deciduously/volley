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
Row: 6 Col: H
It's a hit!
               Player                                   Computer

    A  B  C  D  E  F  G  H  I  J              A  B  C  D  E  F  G  H  I  J

 1  .  U  .  .  .  .  .  .  .  .           1  .  .  .  .  .  .  .  .  .  .

 2  .  U  .  .  .  .  O  .  .  .           2  .  .  .  .  O  .  .  .  .  .

 3  .  U  .  .  .  .  .  .  .  .           3  .  O  .  .  .  .  .  .  .  .

 4  O  .  .  .  .  .  .  .  C  .           4  .  .  .  .  .  .  .  .  .  .

 5  .  .  .  .  .  .  A  .  C  .           5  .  .  .  .  .  .  .  .  .  .

 6  .  .  B  .  .  .  A  .  C  .           6  .  .  .  .  .  O  .  X  .  .

 7  .  .  B  .  .  .  A  .  D  .           7  .  .  .  .  .  .  .  .  .  .

 8  .  .  B  .  .  .  X  .  D  .           8  .  .  .  .  .  .  .  .  .  .

 9  .  .  B  .  .  .  A  .  .  .           9  .  .  .  .  .  .  .  .  .  .

10  .  .  .  .  .  .  .  .  .  .          10  .  .  .  .  .  .  .  .  .  .
```
