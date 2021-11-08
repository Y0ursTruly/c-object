# Object made in C

In this program, I have designed an object system(which is similar to a **JavaScript Object** and is very hard given that all I really have in C is fixed length data types).

![Working Example](https://i.stack.imgur.com/x0sPl.png)

The only thing I knew before beginning was about the concept of a [linked list](https://www.geeksforgeeks.org/linked-list-set-1-introduction/) being a way to have an *"array"* which when taught in school didn't seem to make sense because you could not directly access anything in the array besides the `next` pointer.

Making an *"array"* like that means to access *"position x"* you would have to loop *x* times in just to access it, which is more similar to a nested object than an array. However this *"nested object"* can only have the struct's pre-set *"keys"*(those being the variables inside the struct on declaration)

Then it hit me.. what if the ***key*** to an object was a linked list itself, with each node pointing to an array of nodes of length `n+1`and each letter itself would be converted to numbers and if those numbers are not *less than* `n`, they would be broken down as a linked list to base `n` and then using the position `n` in the array to distinguish between letters

Now what do I mean by: `n`, `n+1`, `less than n`, `base n`?<br>
Think of the letter `l`. It turns into `108`(base 10) and if `n` is `10`, it would be `someNode->key[1]->key[0]->key[8]`.<br>
If `n` was `50`, the same number value of `l` would then translate to `someNode->key[2]->key[8]`

Finally, in multiple character keys, let's use `lol` as our example key for the object and have `n` at `10`.<br>
Accessing the `*data value` from that key would be something like:
```c
data *result=someNode
->key[1]->key[0]->key[8] //l
->key[n] //new character
->key[1]->key[1]->key[1] //o
->key[n] //new character
->key[1]->key[0]->key[1] //l
->value
```

~~Admittently, the idea about the `n+1` came in the middle of me making this~~
