Trie Harder: A rhyming dictionary in C
========

A Trie is a tree data structure used for information retrieval. An easy example to show its efficiency is shown below.

<img src = "https://upload.wikimedia.org/wikipedia/commons/thumb/b/be/Trie_example.svg/250px-Trie_example.svg.png">

A trie for keys "A","to", "tea", "ted", "ten", "i", "in", and "inn".
<br>Source: Wikipedia

Here we see that instead of storing the words tea, ted, and ten (9 characters) by themselves, we can simple store the letter t, e, a, d, and n (5 characters).

My program initially reads dictionary.txt and creates the trie data structure. There is an option to also add and remove words.

# Program Description

Words that rhyme together are usually because they have the same vowel and/or consonant - basically, the same or similar sound - at the end. This program assumes that these words will have the exact same letters at the end. For example, "house" has the "ouse" at the end. This means mouse and spouse rhymes with it. Below is a run through of this example.


# Example run-through

### Search

```
Program: Trie Harder
Using a trie to find rhyming words.

Author: Oliver Hui
Class: Data Structures
Options:
f str  Find str
p n    Print next n
a str  Add str
d str  Delete str
? Help
x Exit

What are your instructions commander?: f ouse
Great! Word has been found! Cursor points to the letter o

What are your instructions commander?: p 60
1) house
2) alehouse
3) gatehouse
4) statehouse
5) icehouse
6) rehouse
7) storehouse
8) whorehouse
9) warehouse
10) smokehouse
11) blockhouse
12) bunkhouse
13) drinkhouse
14) parkhouse
15) workhouse
16) boardinghouse
17) clearinghouse
18) countinghouse
19) meetinghouse
20) westinghouse
21) doghouse
22) boathouse
23) courthouse
24) guesthouse
25) hothouse
26) pothouse
27) lighthouse
28) nuthouse
29) outhouse
30) penthouse
31) chophouse
32) clubhouse
33) coalhouse
34) dollhouse
35) tollhouse
36) schoolhouse
37) customhouse
38) farmhouse
39) glasshouse
40) greenhouse
41) guardhouse
42) madhouse
43) roadhouse
44) roundhouse
45) playhouse
46) poorhouse
47) porterhouse
48) slaughterhouse
49) powerhouse
50) roughhouse
51) teahouse
52) rouse
53) arouse
54) carouse
55) grouse
56) louse
57) blouse
58) delouse
59) douse
60) spouse

What are your instructions commander?: p 30
1) espouse
2) mouse
3) fieldmouse
4) titmouse
End of list. could not find more
```

As you can see, the cursor does not reset back to the first word after a find. When asked to print again, the program will start after the last word it printed.

### Add a word
```
What are your instructions commander?: f ebook
Great! Word has been found! Cursor points to the letter e

What are your instructions commander?: p 20
1) casebook
2) phrasebook
3) guidebook
4) notebook
5) rulebook
6) scorebook
End of list. could not find more.

What are your instructions commander?: a facebook
I will assume perfect input and you didn't want to destroy my tree
I've added "facebook" to the tree.

What are your instructions commander?: f ebook
Great! Word has been found! Cursor points to the letter e

What are your instructions commander?: p 20
1) casebook
2) phrasebook
3) guidebook
4) notebook
5) rulebook
6) scorebook
7) facebook
End of list. could not find more.
```
