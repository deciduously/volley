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
            Battleship!!!


Stage your battlefield!

               Player

    A  B  C  D  E  F  G  H  I  J

 1  .  .  .  .  .  .  .  .  .  .

 2  .  .  .  .  .  .  .  .  .  .

 3  .  .  .  .  .  .  .  .  .  .

 4  .  .  .  .  .  .  .  .  .  .

 5  .  .  .  .  .  .  .  .  .  .

 6  .  .  .  .  .  .  .  .  .  .

 7  .  .  .  .  .  .  .  .  .  .

 8  .  .  .  .  .  .  .  .  .  .

 9  .  .  .  .  .  .  .  .  .  .

10  .  .  .  .  .  .  .  .  .  .



Which ship do you want to add?
Select letter, or 'R' to place all the rest randomly: { A:5 B:4 C:3 D:2 U:3 }> r

Guns at the ready!

               Player                                    Computer

    A  B  C  D  E  F  G  H  I  J               A  B  C  D  E  F  G  H  I  J

 1  .  C  .  .  .  .  .  .  .  .            1  .  .  .  .  .  .  .  .  .  .

 2  .  C  .  .  .  .  .  .  .  .            2  .  .  .  .  .  .  D  .  .  .

 3  .  C  .  .  .  .  .  .  .  .            3  .  .  .  .  .  .  D  .  .  .

 4  .  .  .  .  .  .  .  .  .  .            4  .  .  .  .  .  .  .  B  .  .

 5  .  .  .  .  .  .  .  .  .  .            5  U  .  .  .  .  .  .  B  .  .

 6  .  .  .  .  .  .  .  .  .  .            6  U  .  .  .  .  .  .  B  .  .

 7  .  B  .  .  .  .  .  U  U  U            7  U  .  .  .  C  C  C  B  .  .

 8  .  B  .  D  .  A  A  A  A  A            8  .  .  .  .  .  .  .  .  .  .

 9  .  B  .  D  .  .  .  .  .  .            9  A  A  A  A  A  .  .  .  .  .

10  .  B  .  .  .  .  .  .  .  .           10  .  .  .  .  .  .  .  .  .  .


Enter Target.  Enter 'R' for random.  (ColRow, e.g. "A1" or "a1")> r
Rolling the dice...
Row: 7 Col: D
```
