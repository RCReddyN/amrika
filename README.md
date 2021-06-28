# amrika
production aipole.

ippatiki support aithe kinda kanipinche operations ki mathrame undi:

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
<li>syntax and grammar final kadhu. will make changes as I see fit.
</ul>