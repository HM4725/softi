Project2 Milestone1: Analyze the given b+tree code
=================================
A. Possible call path of the insert/delete operation
--------------------------------------------------------

### [**insert**]

```c
[insert 함수]

node * insert( node * root, int key, int value ) {

    record * pointer;
    node * leaf;

// case 1
    if (find(root, key, false) != NULL)
        return root;

    pointer = make_record(value);

// case 2
    if (root == NULL) 
        return start_new_tree(key, pointer);

    leaf = find_leaf(root, key, false);

// case 3
    if (leaf->num_keys < order - 1) {
        leaf = insert_into_leaf(leaf, key, pointer);
        return root;
    }

// case 4
    return insert_into_leaf_after_splitting(root, leaf, key, pointer);
}
```
insert 함수는 실행 흐름이 4가지 경우로 나누어진다.


  * **case 1: 이미 key가 존재하는 경우**

````
[function trace]

insert(root, key, value);
    find(root, key, false);
        find_leaf( root, key, false); 
    find(root, key, false);
insert(root, key, value);
```

해당 key가 이미 존재하는 지를 확인하기 위해 `find(root, key, false)` 함수를 사용한다. `find`함수는 `find_leaf`함수를 통해 root 노드에서 시작해 key가 들어갈 수 있는 leaf 노드를 찾는다.  tree가 존재하지 않아 leaf 노드를 찾지 못하면 NULL을 반환하고 만약 찾았다면 그 leaf노드에서 key를 검색한 후 만약 key가 존재하면 이에 맞는 record의 주소를 반환한다. 만약 찾지 못했다면 NULL을 반환한다.

`find(root, key, false)`이 NULL을 반환하지 않는다면, 이미 key에 맞는 레코드가 존재하기 때문에 insert를 하지 않고 root 노드의 주소를 반환한다. 

만약 NULL을 반환한다면, tree가 존재하지 않거나 해당 key가 tree에 존재하지 않기 때문이다. NULL을 반환한다면 다음 경우에 해당한다. 

  * **case 2: tree가 존재하지 않는 경우**

```
[function trace]

insert(root, key, value)
    find(root, key, false)
        find_leaf( root, key, false) 
    find(root, key, false)
insert(root, key, value)
    make_record(value)
insert(root, key, value)
    start_new_tree(key,pointer)
        make_leaf( )
            make_node( )
        make_leaf( )
    start_new_tree(key,pointer)
insert(root, key, value)
```

tree가 존재하지 않는다면, `find_leaf( root, key, false)` 이 `NULL` 을 반환하기 때문에 `find(root, key, false)` 또한 NULL을 반환한다. `find(root, key, false) == NULL` 이므로  insert함수에서 첫번째 if문을 건너뛰게 된다. 이후 `pointer = make_record(value)`를 통해 value를 저장하는 record를 만들고 pointer가 이를 가리키도록 한다.

tree가 존재하지 않기 때문에 `root==NULL` 이다. 그러므로 insert의 2번째 if문 내부로 들어가 `start_new_tree(key,pointer)`를 호출하고 이 함수의 반환값을 반환한다. `start_new_tree`함수는 `make_leaf()`를 통해 새로운 leaf 노드를 만들고 key와 pointer를 저장하고 이 노드의 주소를 반환한다.

  * **case 3: leaf 노드에 free space가 존재하는 경우**

```
[function trace]

insert(root, key, value)
    find(root, key, false)
        find_leaf( root, key, false) 
    find(root, key, false)
insert(root, key, value)
    make_record(value)
insert(root, key, value)
    find_leaf( root, key, false)
insert(root, key, value)
    insert_into_leaf(leaf, key, pointer)
insert(root, key, value)
```

insert 하고자 하는 key가 존재하지 않고 tree가 이미 존재하며 leaf 노드에 free space가 존재하는 경우이다. 이미 tree가 존재하고 key가 tree에 존재하지 않기 때문에 `find(root, key, false)==NULL`이며 `root!=NULL`이다. 그러므로 `insert` 함수 내의 1, 2번째 if문을 건너뛴다. `pointer = make_record(value)`를 통해 pointer는 새로운 레코드를 가리킨다. 또한 `leaf = find_leaf(root, key, false)`를 통해 leaf는 해당 key가 들어갈 leaf node를 가리킨다.

leaf node에 free space가 존재하므로 `leaf->num_keys < order -1`은 `true`이다. 그렇기 때문에 insert 함수의 3번째 if문 내로 들어가 `insert_into_leaf(leaf, key, pointer)`를 호출한다. 이 함수는 leaf node 내에서 key가 들어갈 위치를 찾은 후 그 위치에 key와 pointer를 저장한다.

  * **case 4: leaf 노드에 free space가 없는 경우**

insert 하고자 하는 key가 존재하지 않고 tree가 이미 존재하며 leaf 노드에 free space가 없는 경우이다. 이 때 insert 함수 내의 3가지 if문을 모두 건너뛴다. leaf 노드에 free space가 없기 때문에 leaf 노드를 둘로 쪼개야 하는데, 이를 위해 마지막에 `insert_into_leaf_after_splitting(root, leaf, key, pointer)`를 호출한다.

```c
[insert_into_leaf_splitting 함수]

node * insert_into_leaf_after_splitting(node * root, node * leaf, int key, record * pointer) {

    node * new_leaf;
    int * temp_keys;
    void ** temp_pointers;
    int insertion_index, split, new_key, i, j;

    new_leaf = make_leaf();

    temp_keys = malloc( order * sizeof(int) );
    if (temp_keys == NULL) {
        perror("Temporary keys array.");
        exit(EXIT_FAILURE);
    }

    temp_pointers = malloc( order * sizeof(void *) );
    if (temp_pointers == NULL) {
        perror("Temporary pointers array.");
        exit(EXIT_FAILURE);
    }

    insertion_index = 0;
    while (insertion_index < order - 1 && leaf->keys[insertion_index] < key)
        insertion_index++;

    for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {
        if (j == insertion_index) j++;
        temp_keys[j] = leaf->keys[i];
        temp_pointers[j] = leaf->pointers[i];
    }

    temp_keys[insertion_index] = key;
    temp_pointers[insertion_index] = pointer;

    leaf->num_keys = 0;

    split = cut(order - 1);

    for (i = 0; i < split; i++) {
        leaf->pointers[i] = temp_pointers[i];
        leaf->keys[i] = temp_keys[i];
        leaf->num_keys++;
    }

    for (i = split, j = 0; i < order; i++, j++) {
        new_leaf->pointers[j] = temp_pointers[i];
        new_leaf->keys[j] = temp_keys[i];
        new_leaf->num_keys++;
    }

    free(temp_pointers);
    free(temp_keys);

    new_leaf->pointers[order - 1] = leaf->pointers[order - 1];
    leaf->pointers[order - 1] = new_leaf;

    for (i = leaf->num_keys; i < order - 1; i++)
        leaf->pointers[i] = NULL;
    for (i = new_leaf->num_keys; i < order - 1; i++)
        new_leaf->pointers[i] = NULL;

    new_leaf->parent = leaf->parent;
    new_key = new_leaf->keys[0];

    return insert_into_parent(root, leaf, new_key, new_leaf);
}
```

`insert_into_leaf_after_splitting` 함수는 크기가 order인 2가지 temp array를 만들어 새로운 키가 포인터를 모두 집어넣어 정렬한다. 이후 새로운 new_leaf 노드를 만들어 temp array의 뒤쪽 반절을 insert한다. temp array의 앞쪽 반절은 기존의 leaf_node에 insert한다. 이후 두 node의 field를 적절히 설정한다. 하나의 leaf 노드가 두 개의 leaf node로 나누어지고 적절히 정렬된 상태이다. 두 leaf node에 맞게 부모 internal 노드도 설정해주어야 하기 때문에 마지막엔 `insert_into_parent(root, leaf, new_key, new_leaf)`를 호출한다.

```c
[insert_into_parent 함수]

node * insert_into_parent(node * root, node * left, int key, node * right) {

    int left_index;
    node * parent;

    parent = left->parent;

// case 4_1
    if (parent == NULL)
        return insert_into_new_root(left, key, right);

    left_index = get_left_index(parent, left);

// case 4_2
    if (parent->num_keys < order - 1)
        return insert_into_node(root, parent, left_index, key, right);

// case 4_3
    return insert_into_node_after_splitting(root, parent, left_index, key, right);
}
```

`insert_into_parent` 함수에선 insert 함수와 비슷하게 3가지 경우로 또 나뉘게 된다. 부모 노드가 없는 경우와 있지만 부모 노드에 free space가 있는 경우와 없는 경우이다.

*  case 4_1: 부모 노드가 없는 경우

```
[function trace]

insert(root, key, value)
    find(root, key, false)
        find_leaf( root, key, false) 
    find(root, key, false)
insert(root, key, value)
    make_record(value)
insert(root, key, value)
    find_leaf( root, key, false)
insert(root, key, value)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        make_leaf( )
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        cut(order - 1)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        insert_into_parent(root, leaf, new_key, new_leaf)
            insert_into_new_root(left, key, right)
                make_node()
            insert_into_new_root(left, key, right)
        insert_into_parent(root, leaf, new_key, new_leaf)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
insert(root, key, value)
```

부모 노드가 경우 `parent==NULL`이므로 insert_into_parent 함수 내의 첫번째 if문의 조건을 만족시킨다. if문 내로 들어가 `insert_into_new_root(left, key, right)`를 호출한다. `insert_into_new_root`는 새로운 root 노드를 만들고 각 field를 설정해주고 root 노드의 주소를 반환한다.

* case 4_2: 부모 노드에 free space가 있는 경우

```
[function trace]

insert(root, key, value)
    find(root, key, false)
        find_leaf( root, key, false) 
    find(root, key, false)
insert(root, key, value)
    make_record(value)
insert(root, key, value)
    find_leaf( root, key, false)
insert(root, key, value)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        make_leaf( )
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        cut(order - 1)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        insert_into_parent(root, leaf, new_key, new_leaf)
            get_left_index(parent, left)
        insert_into_parent(root, leaf, new_key, new_leaf)
            insert_into_node(root, parent, left_index, key, right)
        insert_into_parent(root, leaf, new_key, new_leaf)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
insert(root, key, value)
```

부모 노드가 있으므로 `parent!=NULL`이다. 그러므로 insert_into_parent 함수의 첫번쨰 if문은 건너뛴다. 그 다음 `get_left_index(parent, left)`를 호출하여 부모 노드에서 left 자식 노드의 주소를 저장하고 있는 위치의 index를 얻는다. 그 다음은 2번째 if문이다. 부모 노드에 free space가 있기 때문에 `parent->num_keys < order -1`은 `true`이다. 2번째 if문 내로 들어가 `insert_into_node(root, parent, left_index, key, right)`를 호출한다. `insert_into_node` 함수는 internal node에 새로운 key와 pointer를 insert하는 함수이다. `get_left_index`를 통해 얻었던 index를 바탕으로 right 자식 노드의 첫번째 key와 pointer를 부모노드에 집어넣는다. 이후 root 노드의 주소를 반환한다.

* case 4_3: 부모 노드에 free space가 없는 경우

```
[function trace]

insert(root, key, value)
    find(root, key, false)
        find_leaf( root, key, false) 
    find(root, key, false)
insert(root, key, value)
    make_record(value)
insert(root, key, value)
    find_leaf( root, key, false)
insert(root, key, value)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        make_leaf( )
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        cut(order - 1)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
        insert_into_parent(root, leaf, new_key, new_leaf)
            get_left_index(parent, left)
        insert_into_parent(root, leaf, new_key, new_leaf)
            insert_into_node_after_splitting(root, parent, left_index, key, right)
                cut(order)
            insert_into_node_after_splitting(root, parent, left_index, key, right)
                make_node()
            insert_into_node_after_splitting(root, parent, left_index, key, right)
                insert_into_parent(root, old_node, k_prime, new_node) 
                [반복: case 4_1, case4_2, case4_3]
            insert_into_node_after_splitting(root, parent, left_index, key, right)
        insert_into_parent(root, leaf, new_key, new_leaf)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
insert(root, key, value)
```

case 4_2처럼 부모 노드가 있으므로 `parent!=NULL`이다. 그러므로 insert_into_parent 함수의 첫번쨰 if문은 건너뛴다. 그 다음 `get_left_index(parent, left)`를 호출하여 부모 노드에서 left 자식 노드의 주소를 저장하고 있는 위치의 index를 얻는다. 그 다음은 2번째 if문이다. 부모 노드에 free space가 없기 때문에 `parent->num_keys < order -1`은 `false`이다.  2개의 if문을 모드 건너 뛰고  `insert_into_node_after_splitting(root, parent, left_index, key, right)`를 호출한다.

이 함수는 `insert_into_leaf_after_splitting`과 비슷하다. temp array를 생성하여 기존의 key, pointer와 새로운 key, pointer를 모두 저장한다. 새로운 new_node를 만들어 temp array의 뒤쪽 반절을 insert한다. temp array의 앞쪽 반절은 비워진 old_node에 insert한다. key 중 저장되지 않은 하나의 key는 `k_prime`에 임시로 저장한다. 그 다음 두 node의 field를 설정하고 두 노드의 자식 노드의 field도 설정한다. 마지막으로 `insert_into_parent(root, old_node, k_prime, new_node)`를 호출한다. 그리고 다시 case 4_1, case 4_2, case 4_3 중 하나를 반복한다.

### [**delete**]

`delete` 함수는 `find`와 `find_leaf`를 통해 삭제하고자 하는 record와 그 key가 속한 leaf 노드를 찾는다. 만약 record와 leaf_node가 존재한다면, 그때 `delete_entry(root, key_leaf, key, key_record)`를 호출한다. 만약 존재하지 않는다면 바로 root노드의 주소를 반환한다.
```c
[delete_entry 함수]

node * delete_entry( node * root, node * n, int key, void * pointer ) {

    int min_keys;
    node * neighbor;
    int neighbor_index;
    int k_prime_index, k_prime;
    int capacity;

    n = remove_entry_from_node(n, key, pointer);

// case 1
    if (n == root) 
        return adjust_root(root);

    min_keys = n->is_leaf ? cut(order - 1) : cut(order) - 1;
// case 2
    if (n->num_keys >= min_keys)
        return root;

    neighbor_index = get_neighbor_index( n );
    k_prime_index = neighbor_index == -1 ? 0 : neighbor_index;
    k_prime = n->parent->keys[k_prime_index];
    neighbor = neighbor_index == -1 ? n->parent->pointers[1] : 
        n->parent->pointers[neighbor_index];

    capacity = n->is_leaf ? order : order - 1;

// case 3:  Coalescence
    if (neighbor->num_keys + n->num_keys < capacity)
        return coalesce_nodes(root, n, neighbor, neighbor_index, k_prime);

// case 4: Redistribution
    else
        return redistribute_nodes(root, n, neighbor, neighbor_index, k_prime_index, k_prime);
}
```

`delete_entry` 함수 내에선 가장 먼저 `remove_entry_from_node(n, key, pointer)`를 호출한다. 이 함수는 n노드에서 삭제할 key와 포인터를 지우는 함수이다. 그런데 삭제 후 tree의 형태가 b+tree의 조건을 만족하지 못할 수도 있다. 그렇기 때문에 다시 함수의 흐름이 4가지 경우로 나누어 진행된다.

*  case 1: root 노드에서 delete가 이루어진 경우

```
[function trace]

delete(root, input)
    find(root, key, false)
        find_leaf(root, key, false)
    find(root, key, false)
delete(root, input)
    find_leaf(root, key, false)
delete(root, input)
    delete_entry(root, key_leaf, key, key_record)
        remove_entry_from_node(n, key, pointer)
    delete_entry(root, key_leaf, key, key_record)
        adjust_root(root)
    delete_entry(root, key_leaf, key, key_record)
delete(root, input)
```

`n==root`이므로 `adjust_root(root)`을 호출한다. 여기서 또 2가지 경우로 나뉜다. key 삭제 후 root 노드의 크기가 0일 때와 0이 아닐 때이다. 만약 0보다 크다면 b+tree에서 root 노드는 크기에 제약이 없으므로 바로 root의 주소를 반환하고 마무리된다. 만약 0이라면 다르다. key가 1개인 leaf root 노드에서 1개의 key를 지우면 크기가 0이 되고 이는 비어있는 트리를 의미한다. 그렇기 때문에 free를 통해 root 노드를 없애주어야 한다.

*  case 2: delete 후에도 그 노드가 b+tree의 조건을 만족하는 경우

```
[function trace]

delete(root, input)
    find(root, key, false)
        find_leaf(root, key, false)
    find(root, key, false)
delete(root, input)
    find_leaf(root, key, false)
delete(root, input)
    delete_entry(root, key_leaf, key, key_record)
        remove_entry_from_node(n, key, pointer)
    delete_entry(root, key_leaf, key, key_record)
delete(root, input)
```

root 노드가 아닌 노드에서 delete가 이루어지고 이 후에도 그 노드가 b+tree의 조건을 만족하는 경우이다. b+tree의 조건은 대략적으로 각 노드는 전체 크기의 반절 이상의 key를 가져야 하는 것을 의미한다. delete 후에도 b+tree의 조건을 만족하므로 다른 처리를 해줄 필요가 없다. 그렇기 때문에 그대로 root의 주소를 반환한다.

*  case 3: b+tree의 조건을 만족하지 못하지만 두 노드를 합칠 수 있을 때 (Coalescence, Merge)

```
[function trace]

delete(root, input)
    find(root, key, false)
        find_leaf(root, key, false)
    find(root, key, false)
delete(root, input)
    find_leaf(root, key, false)
delete(root, input)
    delete_entry(root, key_leaf, key, key_record)
        remove_entry_from_node(n, key, pointer)
    delete_entry(root, key_leaf, key, key_record)
        coalesce_nodes(root, n, neighbor, neighbor_index, k_prime)
            delete_entry(root, n->parent, k_prime, n)
            [반복: case 1, case 2, case 3, case 4]
        coalesce_nodes(root, n, neighbor, neighbor_index, k_prime)
    delete_entry(root, key_leaf, key, key_record)
delete(root, input)
```

non root 노드에서 delete가 이루어지고 이후에 그 노드가 b+tree의 조건을 만족하지 못하는 경우이다. b+tree의 조건을 충족시키기 위해 두 노드를 합친다. 두 노드를 하나로 합치면 두 노드를 가르는 부모 노드의 키를 하나를 없애주어야 한다. 즉, 부모 노드의 key를 하나 delete해야 하는 것이다. 그렇기 때문에 이 key를 가지고 다시 `delete_entry(root, n->parent, k_prime, n)`를 호출하여 재귀적으로 다시 case1, case2, case3, case4로 나누어 진행한다.

*  case 4: b+tree의 조건을 만족하지 못하고 두 노드를 합칠 수도 없을 때 (Redistribution)

```
[function trace]

delete(root, input)
    find(root, key, false)
        find_leaf(root, key, false)
    find(root, key, false)
delete(root, input)
    find_leaf(root, key, false)
delete(root, input)
    delete_entry(root, key_leaf, key, key_record)
        remove_entry_from_node(n, key, pointer)
    delete_entry(root, key_leaf, key, key_record)
        redistribute_nodes(root, n, neighbor, neighbor_index, k_prime_index, k_prime)
    delete_entry(root, key_leaf, key, key_record)
delete(root, input)
```

non root 노드에서 delete가 이루어지고 이후에 그 노드가 b+tree의 조건을 만족하지 못하는 경우이다. b+tree의 조건을 충족시키기 위해 두 노드를 합쳐야 하는데 합치는 순간 합친 노드의 크기가 노드의 최대 크기를 넘어가기 때문에 합칠 수 없다. 그렇기 때문에 두 노드를 적절히 재분배 해주어야 한다. 이때 b+tree의 조건을 충족시키기에 그 수가 부족한 노드는 이웃 노드에서 key를 가져온다. 이 방식으로 두 노두 모두 b+tree의 조건을 만족하게 된다.


B. Detail flow of the structure modification (split, merge) 
--------------------------------------------------------------

### [**split**]

bpt.c 코드와 https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html 의 split되는 두 노드의 크기 기준이 다르다. order-5 b+tree에서  5개 key를 2개의 노드로 split할 때, bpt.c는 2개, 3개로 나누지만, 해당 홈페이지의 b+tree는 3개, 2개로 나눈다. 삽입할 key까지 포함해서 키의 수가 짝수가 될 땐 둘 다 동일하다. 홀수일 때가 문제가 된다. 다음 설명은 해당 홈페이지 기준으로 진행한다.  

* **case 4_1**

![split_1_01](/uploads/0ac816b28aa783d2208a0e7d66772253/split_1_01.PNG)
**<그림 1>**

<그림 1>은 order-4인 b+tree에서 하나의 노드가 모두 차있는 상태이다. 여기서 4를 insert할 것이다. order-4인 b+tree는 하나의 노드에서 key가 3개까지 저장될 수 있기 때문에 하나의 key를 더 저장하려면 노드를 하나 더 만들어야 한다. 5개의 key를 저장하는 temp array와 5개의 pointer를 저장하는 temp array를 만들어 이전 노드의 key, pointer와 삽입할 key, pointer를 저장한다. 여기서 새로 삽입되는 pointer는 새로운 record를 가리킨다. 기존의 노드를 초기화하고 새로운 노드를 만들고 기존의 노드엔 temp array의 반절 앞부분을 저장하고 새로운 노드엔 temp array의 반절 뒷부분을 저장한다. 이후 각 leaf 노드의 마지막 pointer를 그 다음 leaf노드를 가리키도록 설정한다.

그 다음 새로운 internal 노드를 만든다. 이 internal 노드의 첫번째 key에 새로운 leaf노드의 첫번째 key를 저장한다. 이후 pointer[0]에 기존 노드의 주소를 저장하고 pointer[1]에 새로운 leaf노드의 주소를 저장한다. 그리고 각 leaf 노드의 parent 멤버 변수가 새로운 internal 노드를 가리키도록 설정한다.

![split_1_02](/uploads/25dc7cf746400a8c6a947ee286588cdf/split_1_02.PNG)
**<그림 2>**

<그림 2>는 <그림 1>에서 case4_1의 과정(insert 4)을 거치면 확인할 수 있는 결과이다.

* **case 4_2**

![split_2_01](/uploads/64227ba307dd22db9ba335415bb64872/split_2_01.PNG)
**<그림 3>**

<그림 3>은 order-4인 b+tree에서 internal 노드가 존재하고 하나의 노드가 모두 차있는 상태이다. 여기서 5를 insert할 것이다. 5개의 key를 저장하는 temp array와 5개의 pointer를 저장하는 temp array를 만들어 이전 노드의 key, pointer와 삽입할 key, pointer를 저장한다. 여기서 새로 삽입되는 pointer는 새로운 record를 가리킨다. 기존의 노드를 초기화하고 새로운 노드를 만들고 기존의 노드엔 temp array의 반절 앞부분을 저장하고 새로운 노드엔 temp array의 반절 뒷부분을 저장한다. 이후 각 leaf 노드의 마지막 pointer를 그 다음 leaf노드를 가리키도록 설정한다.

그 다음 이미 존재하는 internal 노드에 새로운 leaf 노드의 key를 저장한다. internal 노드의 pointer에 새로운 leaf 노드의 주소를 저장하고, 새로운 leaf 노드의 parent 멤버 변수에 internal 노드의 주소를 저장한다.

![split_2_02](/uploads/bb80b35fa859e2d18ea7dc57a2d12723/split_2_02.PNG)
**<그림 4>**

<그림 4>는 <그림 3>에서 case4_2의 과정(insert 5)을 거치면 확인할 수 있는 결과이다.

* **case 4_3 -> case 4_1**

![split_3_01](/uploads/e3cd18ce6e8a12dd0ba532299eeb1571/split_3_01.PNG)
**<그림 5>**

<그림 5>는 order-4인 b+tree에서 internal 노드와 하나의 노드가 모두 차있는 상태이다. 여기서 8을 insert할 것이다. . 5개의 key를 저장하는 temp array와 5개의 pointer를 저장하는 temp array를 만들어 이전 노드의 key, pointer와 삽입할 key, pointer를 저장한다. 여기서 새로 삽입되는 pointer는 새로운 record를 가리킨다. 기존의 노드를 초기화하고 새로운 노드를 만들고 기존의 노드엔 temp array의 반절 앞부분을 저장하고 새로운 노드엔 temp array의 반절 뒷부분을 저장한다. 이후 각 leaf 노드의 마지막 pointer를 그 다음 leaf노드를 가리키도록 설정한다.

그 다음 이미 존재하는 internal 노드에 새로운 leaf 노드의 key를 저장해야 한다. 하지만 internal 노드가 모두 차있기 때문에 insert를 할 수 없다. leaf 노드를 split한 것처럼 internal 노드도 split해야한다. leaf 노드를 split할 때와 같은 방식으로 temp array를 이용해 internal 노드를 둘로 나눈다. 이 때 split된 두 internal 노드의 기준이 되는 key가 남는다. 이 key를 해당 노드의 부모 노드에 집어넣어야 한다. 만약 부모 노드가 없다면, case 4_1을 다시 진행해야한다. free space가 존재하는 부모 노드가 존재한다면, case 4_2를 다시 진행한다. 만약 부모 노드에 free space가 없다면 다시 case 4_3을 반복해야 한다.  <그림 5>에서 insert 8을 하는 경우는 case 4_1에 속한다.

![split_3_02](/uploads/daf8c5671977a90cdbcd4275154a67e9/split_3_02.PNG)
**<그림 6>**

<그림 6>은 <그림 5>에서 case4_3 -> case4_1의 과정(insert 8)을 거치면 확인할 수 있는 결과이다.

### [**merge**]

```c
[coalesce_nodes 함수]

node * coalesce_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime) {

    int i, j, neighbor_insertion_index, n_end;
    node * tmp;

    if (neighbor_index == -1) {
        tmp = n;
        n = neighbor;
        neighbor = tmp;
    }

    neighbor_insertion_index = neighbor->num_keys;

    if (!n->is_leaf) {

        neighbor->keys[neighbor_insertion_index] = k_prime;
        neighbor->num_keys++;


        n_end = n->num_keys;

        for (i = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_keys++;
            n->num_keys--;
        }

        neighbor->pointers[i] = n->pointers[j];

        for (i = 0; i < neighbor->num_keys + 1; i++) {
            tmp = (node *)neighbor->pointers[i];
            tmp->parent = neighbor;
        }
    }

    else {
        for (i = neighbor_insertion_index, j = 0; j < n->num_keys; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_keys++;
        }
        neighbor->pointers[order - 1] = n->pointers[order - 1];
    }

    root = delete_entry(root, n->parent, k_prime, n);
    free(n->keys);
    free(n->pointers);
    free(n); 
    return root;
}
```

merge는 delete의 case 3에서 발생한다. non root 노드에서 delete가 이루어지고 이후에 그 노드가 b+tree의 조건을 만족하지 못하는 경우이다. b+tree의 조건을 충족시키기 위해 두 노드를 합치는 것이다. 

![delete_01](/uploads/eb12ed56ab03ae5aeae6a6ee4f2e51d5/delete_01.PNG)

**<그림 7>**

<그림 7>은 1부터 7까지의 key가 insert된 order-5 b+tree이다. 각 노드는 반드시 2개 이상 4개 이하의 key를 가지고 있어야 한다. 이 상황에서 key 6을 delete해보자. 가장 먼저 `delete` 함수를 호출할 것이다. <그림 7>에는 key 6이 존재하기 때문에 `delete_entry(root, key_leaf, key, key_record)`를 호출한다. 여기서 key_leaf는 key가 들어있는 leaf노드를 의미하고 key_record는 key 6이 가리키는 record를 나타낸다. 그리고 key는 6이다. `delete_entry`로 넘어오면 `remove_entry_from_node(n, key, pointer)`를 통해 key 6과 key 6의 pointer를 지우게 된다.

![delete_02](/uploads/8072254604e2db7d235b9de63c23e325/delete_02.PNG)

**<그림 8>**

<그림 8>은 <그림7>에서 `remove_entry_from_node(n, key, pointer)`를 통해 key 6과 포인터를 지운 상태이다. `remove_entry_from_node`가 끝난 후, `n!=root`이므로 `delete_entry`의 첫번째 if문을 건너뛰고 `min_keys`를 설정한다. `min_keys`는 b+tree의 조건을 충족시키기 위한 최소한의 key의 개수를 뜻한다. leaf노드에선 `min_keys`는 2이다. 즉, order 5의 leaf 노드에선 적어도 2개의 key를 가지고 있어야 한다는 것이다. 하지만 <그림 8>의 3번째 leaf노드를 보면 그렇지 않다. `n->num_keys < min_keys`이므로 `delete_entry`에서 2번째 if문도 건너뛰게 된다. 그 다음 `neighbor_index, k_prime_index, k_prime, neighbor, capacity`를 설정한다. `neighbor`는 하나의 부모 노드에 연결된 노드들 중 key를 지운 노드 n의 왼쪽 노드이다. 만약 n 노드가 가장 왼쪽 노드이면 그 노드의 오른쪽 노드가 `neighbor`이다. `neighbor_index`는 n 노드의 왼쪽 노드의 index이다. 만약 n 노드가 가장 왼쪽 노드이면 `neighbor_index`는 -1이 된다. k_prime은 n 노드와 neighbor를 가르는 key를 의미하고 k_prime_index는 부모 노드의 key 중 k_prime의 index를 뜻한다. `capicity`는 각 노드의 최대 크기를 의미한다. <그림 8>에선 `neighbor_index`는 1, `k_prime_index`는 1, `k_prime`은 5, `neighbor`는 [3][4][ ][ ], 마지막으로 capacity는 5이다. `neighbor->num_keys`는 2이고 `n->num_keys`는 1이므로 이 둘의 합은 3이다. `capacity`는 4이므로 두 노드를 합칠 수 있다. 즉, neighbor->num_keys + n->num_keys < capacity`는 `true`이기 때문에 3번째 if문 안으로 들어가 `coalesce_nodes(root, n, neighbor, neighbor_index, k_prime)`를 호출한다.

![delete_03](/uploads/7f9a80a952126f6d41429f24aafea2bd/delete_03.PNG)

**<그림 9>**

`coalesce_nodes`는 두 노드를 합치는 함수이다. <그림 9>는 `delete_entry(root, n->parent, k_prime, n)` 이전까지 진행된 tree의 모습을 나타낸다. 3번째 leaf 노드와 k_prime는 이제 제거해주어야 한다. 즉, 다시 부모 노드에서 key 5를 지워야 하는 것이다. leaf노드에서 key 6과 pointer를 지웠던 것 처럼 부모 노드에서  key 5와 3번째 leaf 노드를 가리키는 pointer를 지워야 한다. 그렇기 때문에 재귀적으로 `delete_entry(root, n->parent, k_prime, n)`를 호출한다.  `delete_entry`에서 다시 위에서 한 일을 반복한다. leaf노드와 internal노드의 차이 빼고는 거의 흐름이 비슷하다. `delete_entry`에서 먼저 `remove_entry_from_node`를 호출해 key 5를 지운다. `remove_entry_from_node`의 결과는 다음과 같다.

![delete_04](/uploads/16db6696dd58f7d432a445164e257ae3/delete_04.PNG)

**<그림 10>**

<그림 10>은 부모 노드에서 key 5를 지운 상태이다. <그림 10>에서 부모 노드는 root노드이므로 첫번째 if문으로 들어가 `adjust_root(root)`를 호출한다. `adjust_root`에서 `root->num_keys`는 2이므로 `root->num_keys > 0`는 `true`이다. 그렇기 때문에 root의 주소를 반환하고 마무리된다. 

이 예시는 delete의 case 3에서 case 1로 진행된 예이다. 하지만 case 3에서 case 2, 3, 4로도 진행될 수도 있다. 만약 case 3에서 case 3으로 진행된다면 이어서 case 1, 2, 3, 4 중 하나로 진행될 것이다. case 3은 재귀적으로 계속 root노드를 향해서 propagate될 수 있는 경우이다. 그 이유는 merge를 하는 순간 하나의 노드가 사라지기 때문에 부모 노드에서 key를 하나 delete해야 하기 때문이다.

C. (Naive) designs or required changes for building on-disk b+ tree
----------------------------------------------------------------------

* **bpt 코드의 delete 함수 (`remove_entry_from_node`) 보완**

i) 3rd parameter: node* -> void*
        pointer 변수가 record도 가리킬 수 있기 때문이다.

ii) internal 노드 내의 키와 같은 값을 지우면, leaf 노드에선 지워지지만 internal 노드에선 그대로이다.

-> internal 노드에서 새로운 키값으로 변경해주어야 한다. (루트 노드에선 예외) 

iii) record도 지울 수 있는 부분을 추가하여야 한다.

* **on-disk를 위해 필요한 부분**

i) record 크기와 block 크기를 생각하여 노드의 멤버 변수들의 크기를 잘 설정해주어야 한다.

ii) fileio를 통해 입력된 값을 저장해야 한다.
