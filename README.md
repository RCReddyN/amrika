# amrika
production aipole.

ippatiki support aithe kinda kanipinche operations ki mathrame undi:

- [x] numerical variables
- [x] basic arithmetic
- [x] okavela - aithe statement
- [x] okavela - ainappudu loops
- [ ] text and numbers print cheyadam
- [ ] numbers input read cheyadam
- [x] comments
- [ ] expressions ki parantheses
- [ ] logical operators
- [ ] atlakakunda and lekapothe statements
- [ ] bin, hex and octal numerics
- [ ] compilation thappulu
- [ ] panulu

26-06-2021 - Lexical Analysis okkate ayindi. malla time unnappudu migithadi.
28-06-2021 - Parser is done.

```
g++ lessa.cpp lex.cpp parse.cpp && a
```

<h3>Mundhu idi chadavali:</h3>
<ul> 
<li>strings la escape characters unna, or "%" unna, unsupported character in string ani error osthadhi.
<li>identifier la only english letters undali. numbers, symbols undodhu.
<li>numbers antae only floating point numbers. integers ki ikkada place ledhu.
<li>okavela ends with a dot in a new line. same line lo end kavali. grammar reframe cheyali. will work on that the next time.
<li>assignment statements annitiki anuko prefix undalsindhe. idi kuda marchali. may be final statement ki specific ga marchali. will sit on this.
</ul>