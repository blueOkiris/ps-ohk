# Layout Derivation

## Letters

Let's begin with letters

We have essentially 5 locations based on our hand:

```
    Ring Middle
             First
Pinky

                  Thumb
```

Note that I will represent the keys as a grid, but it will be slightly not a grid as columns will not be in line with each other to match the curve of the hand.

Those 5 should probably be the top 5 most used keys, and similar keys can be placed above and below based on relationship to the letter

Let's look at letter frequencies.

1. E
2. A
3. R
4. I
5. O
6. T
7. N
8. S
9. L
10. C
11. U
12. D
13. P
14. M
15. H
16. G
17. B
18. F
19. Y
20. W
21. K
22. V
23. X
24. Z
25. J
26. Q

Notice how almost all the vowels are in the top 5? Even then U is upper 50% of the keyboard. I think it makes sense to make the vowels all near the thumb:

```
  r m
      f A
p       E I
        O U
```

The top 4 consonants are then: R, T, N, and S:

```
  T N
      S A
R       E I
        O U
```

We can pick another 4 to go over: L, C, D, and P. How do those relate to the others?

Well, L and R typically represent similar sounds, as do D and T and S and C. The odd ones out are P and N, so we'll pair it with N for now:

```
  D P
  T N C
L     S A
R       E I
        O U
```

Now for to go under: M, H, G, and B. M goes with N, B goes with P, H doesn't go with any and neither does G.

Here's one way to start to fix it. Let's pull out P, even though it's a bit more frequent than M, and let's put M in its place, and put P under M. Then we can put B under P. We can make H lateral to L, since I don't think many other sounds will be similar to H, and then we can throw G in there for now

```
    D M
  G T N C
H L   P S A
  R   B   E I
          O U
```

What's next? F, Y, W, K

K goes with G, we'll throw it above. F kinda goes with P, we'll put it to the left. Y is sometimes a Vowel. Let's put it with E. W can go over there with H. It's kinda its own thing.

```
  K D M 
W G T N C 
H L F P S _
  R   B _|A|_
       |Y E I|
         |O U|
          ---
```

I also show a bit of grouping to show that Y should be in line with E once I've moved the columns up and down to fit curvature

What's left? V, X, Z, J, Q

V is like F, J is like D, Z is like S, X is like K, and Q always goes with U, so:

```
  X J
  K D M
W G T N C
H L F P S
  R V B Z|A
       |Y E I
          O U
            Q
```

## Special Keys

Namely: Function Keys, Escape, Numbers, Shift, Ctrl/Win/Alt, Ins/Home/PgUp/Del/End/PgDn, Tab, Caps Lock, Backslash, Return, and Space

I'll throw - and = below E as well

```
Es f1 f2 f3 f4 f5 f6
   f7 f8 f9 f0 fL fT
      ____
      3  4       |In Hm PU
      X  J  5    |Dl Ed PD
1  2  K  D  M
`  W  G  T  N  6  \
CL H  L  F  P  S  7______
Tb __ R  V  B__Z_|A  8  9
Sf|Up|___  |Al Y  E  I  0
←  Dw → |  |Wn Cl Sp O  U
               Rn -  =  Q
```

And of course the \` + 0-9 + -/= + \\ are also ~, !, @, #, $, %, ^, &, \*, \(, \), \_, +, and | when shifted

Ctrl/Win/Alt are all near the thumb (tho you'll have to shift your hand), so you can press them and another key and use Shift with your pinky.

Function Keys and Insert Rows are not really used with other keys nor that often, so they can be their own little islands.

You'll have to shift for arrow keys, but not very far

## Punctuation

With what room is left, I had trouble placing punctuation. After pretending to type for a bit with the new layout, I found the best spot was top left:

```
Es f1 f2 f3 f4 f5 f6
   f7 f8 f9 f0 fL fT
[  ]
;  '  3  4  /    |In Hm PU
,  .  X  J  5    |Dl Ed PD
1  2  K  D  M
`  W  G  T  N  6  \
CL H  L  F  P  S  7______
Tb __ R  V  B__Z_|A  8  9
Sf|Up|___  |Al Y  E  I  0
←  Dw → |  |Wn Cl Sp O  U
               Rn -  =  Q
```

And of course, ., ',', ', ;, /, \[, and \] become <, >, ", :, ?, \{, and \} when shifted.

And that's it. 77 keys. But this isn't quite like the 60-75% keyboards you're used to:

- Why don't we have a numpad? It's not because we want to shrink the keyboard and we just have to deal with the number row. Our number row is designed to be used 1-handed, so we have the functionality of a number pad. Count those 17 keys!
- We still have the function row, because every keyboard should have one!
- We still have our navigational cluster. It's only 6 keys, why not?!
- We don't have duplicates of Win, Ctrl, Shift, and Alt, and we don't have Fn keys as we expect normal people to use their function keys as intended.

All of the missing keys aren't missing to make the keyboard smaller but because their functionality is placed elswhere, so this is functionally a 100% keyboard.

