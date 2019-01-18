# Design

To find the third most frequently accessed node of list in **O(1)**,

I added new fields (`fprev`, `fnext`, `naccess`, `leader`).

* `fprev`: frequency prev link pointer

* `fnext`: frequency next link pointer

* `naccess`: the number of access

* `leader`: the first node in a group where nodes has same `naccess`.

## insert

If you insert a node in the list, the node is attached next to the tail of the list.
And the node has 0 `naccess`.

## access

If you access a node, `naccess` increases 1.

Then the node moves between the group where member nodes has smaller and bigger `naccess`.

To move in **O(1)**, I added the `leader` field. 

By finding `leader` and `leader->fprev`, it can find the smaller `naccess` group and bigger `naccess` group in **O(1)**.

## Interview
```
Print the element which access the third most frequently in a list.
```

* Solution

Just print `fheader->fnext->fnext->element`

Time complexity: **O(1)**

# How to build and execute

1. Type `gcc -o bin list.c main.c`

2. Type `./bin`
