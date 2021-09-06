# amrika

This is named Amrika for no particular reason. You may find it crazy. Do not stop at the sight of this name. When you are done with the last sentence on this page, you might like this if you are familiar with the language Telugu. If you are foreign to it, you might want to remake this in your native tongue. Please, remember me using the words may and might. I am not promising you anything.

This is a compiler implemented in C++ for a language I cooked up. You might find the syntax and grammar familiar, may be because there are many programming languages lying around, and I might have picked up the flavours I like. Also, I put in some. Call this an abomination if you will. But, I call it Amrika.

The idea crept into my otherwise beautiful mind, when I came across a paper that describes a Perl module - Lingua::Romana::Perligata, that allows one to write scripts in Latin. I know people call Latin a dead language, still, I learnt a couple of sentences like 'Sum domi dormit'. Beware, you might not realise what you are getting into. The words I used for as keywords come from my personal vocabulary. You may find this project wherever, whenever, however, but do not find it funny. This is as personal as my toothbrush.

   




- [x] numerical variables
- [x] basic arithmetic
- [x] chudu - aithe statement
- [x] anuko, theesko statements
- [x] okavela - ainappudu loop
- [x] text and numbers print cheyadam
- [x] comments
- [ ] expressions ki parantheses
- [ ] logical operators
- [ ] atlakakunda and lekapothe statements
- [ ] bin, hex and octal numerics
- [ ] compilation thappulu
- [ ] panulu

ee kinda unna command mana code ni c code ki compile chesthadi: 
s
```
./amrika ../examples/hello.rc
```
out.c aney file lo mana code ki equivalent c code untadi. inka normal ga c code compile chesthey saripothadi.

```
g++ out.c && ./a.out
```


<h3>Mundhu idi chadavali:</h3>
<ul> 
<li>strings la escape characters unna, or "%" unna, unsupported character in string ani error osthadhi.
<li>identifier la only english letters undali. numbers, symbols undodhu.
<li>numbers integers use chesina, floating point use chesina, ikkada mathram floating point e theeskuntadi.
<li>okavela ends with a dot in a new line. same line lo end kavali. grammar reframe cheyali. will work on that the next time.
<li>assignment statements annitiki anuko prefix undalsindhe. idi kuda marchali. may be final statement ki specific ga marchali. will sit on this.
<<<<<<< HEAD
</ul>
=======
<li>syntax and grammar final kadhu. will make changes as I see fit.
</ul>
>>>>>>> e1cb1409010ee0401e872da57b34b24679f91ba2
