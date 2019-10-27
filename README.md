# Challange_eyeo

Answer for eyeo's challange <b>Liquid democracy</b>

Choose one of the tasks below and design five tests for it. Each test should be a pair of input
and output. Explain why you’ve chosen these tests. Write a C++ code that passes your tests.
The code should read its input from stdin and print the solution to stdout. Send us your solution
together with the tests.
Note: If some aspect of the problem is not clear from the description you can make
assumptions as necessary (submit all the assumptions you make together with the solution).


## 1. someone pick an item, someone delegate to other.

~~~
A pick Apple
Ari pick Apple
B pick Banana
C delegate A
D delegate C
E delegate B
~~~

> Normal situation, there's no invalid vote. Check if the code keep ther first rule,
Voters can choose one of the available options or delegate the choice to another voter.
Within above test case, Apple is picked from A and Ari, Also C delegate A, so C will pick Apple, D will pick Apple
Banana is picked from B and E also delegate B, so E will pick Banana.
So the result would be like

<b>4 Apple</b>

<b>2 Banana</b>


## 2. circular delegate situation

~~~
A pick Apple
B delegate C
C delegate D
D delegate B
E delegate E
~~~


> Check if the code keep seconnd rule, 
It is possible that a voter directly or indirectly delegates the vote to themselves. 
Such votes become invalid. All votes delegated to such voter also become invalid.
Apple is picked from A.
In case of B,C,D, they have circular dependency delegates, indirectly delegate themselves like
B -> C -> D ---> B
E delegate himself directly
So the result would be like

<b>1 Apple</b>
<b>4 invalid</b>

## 3. someone will delegate to a person who in the circular dependency

~~~
A delegate B
B delegate C
C delegate A
D delegate A
E pick Eclair
~~~

> With in circular dependency A->B->C->A, D will delegate A, so D should be counted as invalid
The result would be like

<b>1 Eclair</b>

<b>4 invalid</b>

> This isn't described at document, but in this situation, A delegate to Invalid voter would have to be handled as INVALID.

## 4. someone doesn't pick or delegate

~~~
A poke B
A pick
B delegate
~~~

> not registered method, poke will be handled as INVALID
pick, delegate without target, will be handled as INVALID
The result would be

<b>3 invalid</b>

> This isn't described at document, but in this situation, It treat as INVALID vote. 
should have to be counted followed by 4th condition
<i>If there are invalid votes they should be counted and reported.</i>

## 5. someone delegate to other, but that delegated person is not a voter.

~~~
A delegate B
C pick Cucumber
~~~

> A delegate B, but B never appears again as voter,
It should be handled as INVALID
The result would be

<b>1 Cucumber</b>

<b>1 invalid</b>

> This isn't described at document, but in this situation, It treat as INVALID vote.
