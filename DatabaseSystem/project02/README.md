Project2 Milestone1: Analyze the given b+tree code
=================================
A. Possible call path of the insert/delete operation
--------------------------------------------------------

### [**insert**]

```c
[insert �Լ�]

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
insert �Լ��� ���� �帧�� 4���� ���� ����������.


  * **case 1: �̹� key�� �����ϴ� ���**

````
[function trace]

insert(root, key, value);
    find(root, key, false);
        find_leaf( root, key, false); 
    find(root, key, false);
insert(root, key, value);
```

�ش� key�� �̹� �����ϴ� ���� Ȯ���ϱ� ���� `find(root, key, false)` �Լ��� ����Ѵ�. `find`�Լ��� `find_leaf`�Լ��� ���� root ��忡�� ������ key�� �� �� �ִ� leaf ��带 ã�´�.  tree�� �������� �ʾ� leaf ��带 ã�� ���ϸ� NULL�� ��ȯ�ϰ� ���� ã�Ҵٸ� �� leaf��忡�� key�� �˻��� �� ���� key�� �����ϸ� �̿� �´� record�� �ּҸ� ��ȯ�Ѵ�. ���� ã�� ���ߴٸ� NULL�� ��ȯ�Ѵ�.

`find(root, key, false)`�� NULL�� ��ȯ���� �ʴ´ٸ�, �̹� key�� �´� ���ڵ尡 �����ϱ� ������ insert�� ���� �ʰ� root ����� �ּҸ� ��ȯ�Ѵ�. 

���� NULL�� ��ȯ�Ѵٸ�, tree�� �������� �ʰų� �ش� key�� tree�� �������� �ʱ� �����̴�. NULL�� ��ȯ�Ѵٸ� ���� ��쿡 �ش��Ѵ�. 

  * **case 2: tree�� �������� �ʴ� ���**

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

tree�� �������� �ʴ´ٸ�, `find_leaf( root, key, false)` �� `NULL` �� ��ȯ�ϱ� ������ `find(root, key, false)` ���� NULL�� ��ȯ�Ѵ�. `find(root, key, false) == NULL` �̹Ƿ�  insert�Լ����� ù��° if���� �ǳʶٰ� �ȴ�. ���� `pointer = make_record(value)`�� ���� value�� �����ϴ� record�� ����� pointer�� �̸� ����Ű���� �Ѵ�.

tree�� �������� �ʱ� ������ `root==NULL` �̴�. �׷��Ƿ� insert�� 2��° if�� ���η� �� `start_new_tree(key,pointer)`�� ȣ���ϰ� �� �Լ��� ��ȯ���� ��ȯ�Ѵ�. `start_new_tree`�Լ��� `make_leaf()`�� ���� ���ο� leaf ��带 ����� key�� pointer�� �����ϰ� �� ����� �ּҸ� ��ȯ�Ѵ�.

  * **case 3: leaf ��忡 free space�� �����ϴ� ���**

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

insert �ϰ��� �ϴ� key�� �������� �ʰ� tree�� �̹� �����ϸ� leaf ��忡 free space�� �����ϴ� ����̴�. �̹� tree�� �����ϰ� key�� tree�� �������� �ʱ� ������ `find(root, key, false)==NULL`�̸� `root!=NULL`�̴�. �׷��Ƿ� `insert` �Լ� ���� 1, 2��° if���� �ǳʶڴ�. `pointer = make_record(value)`�� ���� pointer�� ���ο� ���ڵ带 ����Ų��. ���� `leaf = find_leaf(root, key, false)`�� ���� leaf�� �ش� key�� �� leaf node�� ����Ų��.

leaf node�� free space�� �����ϹǷ� `leaf->num_keys < order -1`�� `true`�̴�. �׷��� ������ insert �Լ��� 3��° if�� ���� �� `insert_into_leaf(leaf, key, pointer)`�� ȣ���Ѵ�. �� �Լ��� leaf node ������ key�� �� ��ġ�� ã�� �� �� ��ġ�� key�� pointer�� �����Ѵ�.

  * **case 4: leaf ��忡 free space�� ���� ���**

insert �ϰ��� �ϴ� key�� �������� �ʰ� tree�� �̹� �����ϸ� leaf ��忡 free space�� ���� ����̴�. �� �� insert �Լ� ���� 3���� if���� ��� �ǳʶڴ�. leaf ��忡 free space�� ���� ������ leaf ��带 �ѷ� �ɰ��� �ϴµ�, �̸� ���� �������� `insert_into_leaf_after_splitting(root, leaf, key, pointer)`�� ȣ���Ѵ�.

```c
[insert_into_leaf_splitting �Լ�]

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

`insert_into_leaf_after_splitting` �Լ��� ũ�Ⱑ order�� 2���� temp array�� ����� ���ο� Ű�� �����͸� ��� ����־� �����Ѵ�. ���� ���ο� new_leaf ��带 ����� temp array�� ���� ������ insert�Ѵ�. temp array�� ���� ������ ������ leaf_node�� insert�Ѵ�. ���� �� node�� field�� ������ �����Ѵ�. �ϳ��� leaf ��尡 �� ���� leaf node�� ���������� ������ ���ĵ� �����̴�. �� leaf node�� �°� �θ� internal ��嵵 �������־�� �ϱ� ������ �������� `insert_into_parent(root, leaf, new_key, new_leaf)`�� ȣ���Ѵ�.

```c
[insert_into_parent �Լ�]

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

`insert_into_parent` �Լ����� insert �Լ��� ����ϰ� 3���� ���� �� ������ �ȴ�. �θ� ��尡 ���� ���� ������ �θ� ��忡 free space�� �ִ� ���� ���� ����̴�.

*  case 4_1: �θ� ��尡 ���� ���

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

�θ� ��尡 ��� `parent==NULL`�̹Ƿ� insert_into_parent �Լ� ���� ù��° if���� ������ ������Ų��. if�� ���� �� `insert_into_new_root(left, key, right)`�� ȣ���Ѵ�. `insert_into_new_root`�� ���ο� root ��带 ����� �� field�� �������ְ� root ����� �ּҸ� ��ȯ�Ѵ�.

* case 4_2: �θ� ��忡 free space�� �ִ� ���

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

�θ� ��尡 �����Ƿ� `parent!=NULL`�̴�. �׷��Ƿ� insert_into_parent �Լ��� ù���� if���� �ǳʶڴ�. �� ���� `get_left_index(parent, left)`�� ȣ���Ͽ� �θ� ��忡�� left �ڽ� ����� �ּҸ� �����ϰ� �ִ� ��ġ�� index�� ��´�. �� ������ 2��° if���̴�. �θ� ��忡 free space�� �ֱ� ������ `parent->num_keys < order -1`�� `true`�̴�. 2��° if�� ���� �� `insert_into_node(root, parent, left_index, key, right)`�� ȣ���Ѵ�. `insert_into_node` �Լ��� internal node�� ���ο� key�� pointer�� insert�ϴ� �Լ��̴�. `get_left_index`�� ���� ����� index�� �������� right �ڽ� ����� ù��° key�� pointer�� �θ��忡 ����ִ´�. ���� root ����� �ּҸ� ��ȯ�Ѵ�.

* case 4_3: �θ� ��忡 free space�� ���� ���

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
                [�ݺ�: case 4_1, case4_2, case4_3]
            insert_into_node_after_splitting(root, parent, left_index, key, right)
        insert_into_parent(root, leaf, new_key, new_leaf)
    insert_into_leaf_after_splitting(root, leaf, key, pointer)
insert(root, key, value)
```

case 4_2ó�� �θ� ��尡 �����Ƿ� `parent!=NULL`�̴�. �׷��Ƿ� insert_into_parent �Լ��� ù���� if���� �ǳʶڴ�. �� ���� `get_left_index(parent, left)`�� ȣ���Ͽ� �θ� ��忡�� left �ڽ� ����� �ּҸ� �����ϰ� �ִ� ��ġ�� index�� ��´�. �� ������ 2��° if���̴�. �θ� ��忡 free space�� ���� ������ `parent->num_keys < order -1`�� `false`�̴�.  2���� if���� ��� �ǳ� �ٰ�  `insert_into_node_after_splitting(root, parent, left_index, key, right)`�� ȣ���Ѵ�.

�� �Լ��� `insert_into_leaf_after_splitting`�� ����ϴ�. temp array�� �����Ͽ� ������ key, pointer�� ���ο� key, pointer�� ��� �����Ѵ�. ���ο� new_node�� ����� temp array�� ���� ������ insert�Ѵ�. temp array�� ���� ������ ����� old_node�� insert�Ѵ�. key �� ������� ���� �ϳ��� key�� `k_prime`�� �ӽ÷� �����Ѵ�. �� ���� �� node�� field�� �����ϰ� �� ����� �ڽ� ����� field�� �����Ѵ�. ���������� `insert_into_parent(root, old_node, k_prime, new_node)`�� ȣ���Ѵ�. �׸��� �ٽ� case 4_1, case 4_2, case 4_3 �� �ϳ��� �ݺ��Ѵ�.

### [**delete**]

`delete` �Լ��� `find`�� `find_leaf`�� ���� �����ϰ��� �ϴ� record�� �� key�� ���� leaf ��带 ã�´�. ���� record�� leaf_node�� �����Ѵٸ�, �׶� `delete_entry(root, key_leaf, key, key_record)`�� ȣ���Ѵ�. ���� �������� �ʴ´ٸ� �ٷ� root����� �ּҸ� ��ȯ�Ѵ�.
```c
[delete_entry �Լ�]

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

`delete_entry` �Լ� ������ ���� ���� `remove_entry_from_node(n, key, pointer)`�� ȣ���Ѵ�. �� �Լ��� n��忡�� ������ key�� �����͸� ����� �Լ��̴�. �׷��� ���� �� tree�� ���°� b+tree�� ������ �������� ���� ���� �ִ�. �׷��� ������ �ٽ� �Լ��� �帧�� 4���� ���� ������ ����ȴ�.

*  case 1: root ��忡�� delete�� �̷���� ���

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

`n==root`�̹Ƿ� `adjust_root(root)`�� ȣ���Ѵ�. ���⼭ �� 2���� ���� ������. key ���� �� root ����� ũ�Ⱑ 0�� ���� 0�� �ƴ� ���̴�. ���� 0���� ũ�ٸ� b+tree���� root ���� ũ�⿡ ������ �����Ƿ� �ٷ� root�� �ּҸ� ��ȯ�ϰ� �������ȴ�. ���� 0�̶�� �ٸ���. key�� 1���� leaf root ��忡�� 1���� key�� ����� ũ�Ⱑ 0�� �ǰ� �̴� ����ִ� Ʈ���� �ǹ��Ѵ�. �׷��� ������ free�� ���� root ��带 �����־�� �Ѵ�.

*  case 2: delete �Ŀ��� �� ��尡 b+tree�� ������ �����ϴ� ���

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

root ��尡 �ƴ� ��忡�� delete�� �̷������ �� �Ŀ��� �� ��尡 b+tree�� ������ �����ϴ� ����̴�. b+tree�� ������ �뷫������ �� ���� ��ü ũ���� ���� �̻��� key�� ������ �ϴ� ���� �ǹ��Ѵ�. delete �Ŀ��� b+tree�� ������ �����ϹǷ� �ٸ� ó���� ���� �ʿ䰡 ����. �׷��� ������ �״�� root�� �ּҸ� ��ȯ�Ѵ�.

*  case 3: b+tree�� ������ �������� �������� �� ��带 ��ĥ �� ���� �� (Coalescence, Merge)

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
            [�ݺ�: case 1, case 2, case 3, case 4]
        coalesce_nodes(root, n, neighbor, neighbor_index, k_prime)
    delete_entry(root, key_leaf, key, key_record)
delete(root, input)
```

non root ��忡�� delete�� �̷������ ���Ŀ� �� ��尡 b+tree�� ������ �������� ���ϴ� ����̴�. b+tree�� ������ ������Ű�� ���� �� ��带 ��ģ��. �� ��带 �ϳ��� ��ġ�� �� ��带 ������ �θ� ����� Ű�� �ϳ��� �����־�� �Ѵ�. ��, �θ� ����� key�� �ϳ� delete�ؾ� �ϴ� ���̴�. �׷��� ������ �� key�� ������ �ٽ� `delete_entry(root, n->parent, k_prime, n)`�� ȣ���Ͽ� ��������� �ٽ� case1, case2, case3, case4�� ������ �����Ѵ�.

*  case 4: b+tree�� ������ �������� ���ϰ� �� ��带 ��ĥ ���� ���� �� (Redistribution)

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

non root ��忡�� delete�� �̷������ ���Ŀ� �� ��尡 b+tree�� ������ �������� ���ϴ� ����̴�. b+tree�� ������ ������Ű�� ���� �� ��带 ���ľ� �ϴµ� ��ġ�� ���� ��ģ ����� ũ�Ⱑ ����� �ִ� ũ�⸦ �Ѿ�� ������ ��ĥ �� ����. �׷��� ������ �� ��带 ������ ��й� ���־�� �Ѵ�. �̶� b+tree�� ������ ������Ű�⿡ �� ���� ������ ���� �̿� ��忡�� key�� �����´�. �� ������� �� ��� ��� b+tree�� ������ �����ϰ� �ȴ�.


B. Detail flow of the structure modification (split, merge) 
--------------------------------------------------------------

### [**split**]

bpt.c �ڵ�� https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html �� split�Ǵ� �� ����� ũ�� ������ �ٸ���. order-5 b+tree����  5�� key�� 2���� ���� split�� ��, bpt.c�� 2��, 3���� ��������, �ش� Ȩ�������� b+tree�� 3��, 2���� ������. ������ key���� �����ؼ� Ű�� ���� ¦���� �� �� �� �� �����ϴ�. Ȧ���� ���� ������ �ȴ�. ���� ������ �ش� Ȩ������ �������� �����Ѵ�.  

* **case 4_1**

![split_1_01](/uploads/0ac816b28aa783d2208a0e7d66772253/split_1_01.PNG)
**<�׸� 1>**

<�׸� 1>�� order-4�� b+tree���� �ϳ��� ��尡 ��� ���ִ� �����̴�. ���⼭ 4�� insert�� ���̴�. order-4�� b+tree�� �ϳ��� ��忡�� key�� 3������ ����� �� �ֱ� ������ �ϳ��� key�� �� �����Ϸ��� ��带 �ϳ� �� ������ �Ѵ�. 5���� key�� �����ϴ� temp array�� 5���� pointer�� �����ϴ� temp array�� ����� ���� ����� key, pointer�� ������ key, pointer�� �����Ѵ�. ���⼭ ���� ���ԵǴ� pointer�� ���ο� record�� ����Ų��. ������ ��带 �ʱ�ȭ�ϰ� ���ο� ��带 ����� ������ ��忣 temp array�� ���� �պκ��� �����ϰ� ���ο� ��忣 temp array�� ���� �޺κ��� �����Ѵ�. ���� �� leaf ����� ������ pointer�� �� ���� leaf��带 ����Ű���� �����Ѵ�.

�� ���� ���ο� internal ��带 �����. �� internal ����� ù��° key�� ���ο� leaf����� ù��° key�� �����Ѵ�. ���� pointer[0]�� ���� ����� �ּҸ� �����ϰ� pointer[1]�� ���ο� leaf����� �ּҸ� �����Ѵ�. �׸��� �� leaf ����� parent ��� ������ ���ο� internal ��带 ����Ű���� �����Ѵ�.

![split_1_02](/uploads/25dc7cf746400a8c6a947ee286588cdf/split_1_02.PNG)
**<�׸� 2>**

<�׸� 2>�� <�׸� 1>���� case4_1�� ����(insert 4)�� ��ġ�� Ȯ���� �� �ִ� ����̴�.

* **case 4_2**

![split_2_01](/uploads/64227ba307dd22db9ba335415bb64872/split_2_01.PNG)
**<�׸� 3>**

<�׸� 3>�� order-4�� b+tree���� internal ��尡 �����ϰ� �ϳ��� ��尡 ��� ���ִ� �����̴�. ���⼭ 5�� insert�� ���̴�. 5���� key�� �����ϴ� temp array�� 5���� pointer�� �����ϴ� temp array�� ����� ���� ����� key, pointer�� ������ key, pointer�� �����Ѵ�. ���⼭ ���� ���ԵǴ� pointer�� ���ο� record�� ����Ų��. ������ ��带 �ʱ�ȭ�ϰ� ���ο� ��带 ����� ������ ��忣 temp array�� ���� �պκ��� �����ϰ� ���ο� ��忣 temp array�� ���� �޺κ��� �����Ѵ�. ���� �� leaf ����� ������ pointer�� �� ���� leaf��带 ����Ű���� �����Ѵ�.

�� ���� �̹� �����ϴ� internal ��忡 ���ο� leaf ����� key�� �����Ѵ�. internal ����� pointer�� ���ο� leaf ����� �ּҸ� �����ϰ�, ���ο� leaf ����� parent ��� ������ internal ����� �ּҸ� �����Ѵ�.

![split_2_02](/uploads/bb80b35fa859e2d18ea7dc57a2d12723/split_2_02.PNG)
**<�׸� 4>**

<�׸� 4>�� <�׸� 3>���� case4_2�� ����(insert 5)�� ��ġ�� Ȯ���� �� �ִ� ����̴�.

* **case 4_3 -> case 4_1**

![split_3_01](/uploads/e3cd18ce6e8a12dd0ba532299eeb1571/split_3_01.PNG)
**<�׸� 5>**

<�׸� 5>�� order-4�� b+tree���� internal ���� �ϳ��� ��尡 ��� ���ִ� �����̴�. ���⼭ 8�� insert�� ���̴�. . 5���� key�� �����ϴ� temp array�� 5���� pointer�� �����ϴ� temp array�� ����� ���� ����� key, pointer�� ������ key, pointer�� �����Ѵ�. ���⼭ ���� ���ԵǴ� pointer�� ���ο� record�� ����Ų��. ������ ��带 �ʱ�ȭ�ϰ� ���ο� ��带 ����� ������ ��忣 temp array�� ���� �պκ��� �����ϰ� ���ο� ��忣 temp array�� ���� �޺κ��� �����Ѵ�. ���� �� leaf ����� ������ pointer�� �� ���� leaf��带 ����Ű���� �����Ѵ�.

�� ���� �̹� �����ϴ� internal ��忡 ���ο� leaf ����� key�� �����ؾ� �Ѵ�. ������ internal ��尡 ��� ���ֱ� ������ insert�� �� �� ����. leaf ��带 split�� ��ó�� internal ��嵵 split�ؾ��Ѵ�. leaf ��带 split�� ���� ���� ������� temp array�� �̿��� internal ��带 �ѷ� ������. �� �� split�� �� internal ����� ������ �Ǵ� key�� ���´�. �� key�� �ش� ����� �θ� ��忡 ����־�� �Ѵ�. ���� �θ� ��尡 ���ٸ�, case 4_1�� �ٽ� �����ؾ��Ѵ�. free space�� �����ϴ� �θ� ��尡 �����Ѵٸ�, case 4_2�� �ٽ� �����Ѵ�. ���� �θ� ��忡 free space�� ���ٸ� �ٽ� case 4_3�� �ݺ��ؾ� �Ѵ�.  <�׸� 5>���� insert 8�� �ϴ� ���� case 4_1�� ���Ѵ�.

![split_3_02](/uploads/daf8c5671977a90cdbcd4275154a67e9/split_3_02.PNG)
**<�׸� 6>**

<�׸� 6>�� <�׸� 5>���� case4_3 -> case4_1�� ����(insert 8)�� ��ġ�� Ȯ���� �� �ִ� ����̴�.

### [**merge**]

```c
[coalesce_nodes �Լ�]

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

merge�� delete�� case 3���� �߻��Ѵ�. non root ��忡�� delete�� �̷������ ���Ŀ� �� ��尡 b+tree�� ������ �������� ���ϴ� ����̴�. b+tree�� ������ ������Ű�� ���� �� ��带 ��ġ�� ���̴�. 

![delete_01](/uploads/eb12ed56ab03ae5aeae6a6ee4f2e51d5/delete_01.PNG)

**<�׸� 7>**

<�׸� 7>�� 1���� 7������ key�� insert�� order-5 b+tree�̴�. �� ���� �ݵ�� 2�� �̻� 4�� ������ key�� ������ �־�� �Ѵ�. �� ��Ȳ���� key 6�� delete�غ���. ���� ���� `delete` �Լ��� ȣ���� ���̴�. <�׸� 7>���� key 6�� �����ϱ� ������ `delete_entry(root, key_leaf, key, key_record)`�� ȣ���Ѵ�. ���⼭ key_leaf�� key�� ����ִ� leaf��带 �ǹ��ϰ� key_record�� key 6�� ����Ű�� record�� ��Ÿ����. �׸��� key�� 6�̴�. `delete_entry`�� �Ѿ���� `remove_entry_from_node(n, key, pointer)`�� ���� key 6�� key 6�� pointer�� ����� �ȴ�.

![delete_02](/uploads/8072254604e2db7d235b9de63c23e325/delete_02.PNG)

**<�׸� 8>**

<�׸� 8>�� <�׸�7>���� `remove_entry_from_node(n, key, pointer)`�� ���� key 6�� �����͸� ���� �����̴�. `remove_entry_from_node`�� ���� ��, `n!=root`�̹Ƿ� `delete_entry`�� ù��° if���� �ǳʶٰ� `min_keys`�� �����Ѵ�. `min_keys`�� b+tree�� ������ ������Ű�� ���� �ּ����� key�� ������ ���Ѵ�. leaf��忡�� `min_keys`�� 2�̴�. ��, order 5�� leaf ��忡�� ��� 2���� key�� ������ �־�� �Ѵٴ� ���̴�. ������ <�׸� 8>�� 3��° leaf��带 ���� �׷��� �ʴ�. `n->num_keys < min_keys`�̹Ƿ� `delete_entry`���� 2��° if���� �ǳʶٰ� �ȴ�. �� ���� `neighbor_index, k_prime_index, k_prime, neighbor, capacity`�� �����Ѵ�. `neighbor`�� �ϳ��� �θ� ��忡 ����� ���� �� key�� ���� ��� n�� ���� ����̴�. ���� n ��尡 ���� ���� ����̸� �� ����� ������ ��尡 `neighbor`�̴�. `neighbor_index`�� n ����� ���� ����� index�̴�. ���� n ��尡 ���� ���� ����̸� `neighbor_index`�� -1�� �ȴ�. k_prime�� n ���� neighbor�� ������ key�� �ǹ��ϰ� k_prime_index�� �θ� ����� key �� k_prime�� index�� ���Ѵ�. `capicity`�� �� ����� �ִ� ũ�⸦ �ǹ��Ѵ�. <�׸� 8>���� `neighbor_index`�� 1, `k_prime_index`�� 1, `k_prime`�� 5, `neighbor`�� [3][4][ ][ ], ���������� capacity�� 5�̴�. `neighbor->num_keys`�� 2�̰� `n->num_keys`�� 1�̹Ƿ� �� ���� ���� 3�̴�. `capacity`�� 4�̹Ƿ� �� ��带 ��ĥ �� �ִ�. ��, neighbor->num_keys + n->num_keys < capacity`�� `true`�̱� ������ 3��° if�� ������ �� `coalesce_nodes(root, n, neighbor, neighbor_index, k_prime)`�� ȣ���Ѵ�.

![delete_03](/uploads/7f9a80a952126f6d41429f24aafea2bd/delete_03.PNG)

**<�׸� 9>**

`coalesce_nodes`�� �� ��带 ��ġ�� �Լ��̴�. <�׸� 9>�� `delete_entry(root, n->parent, k_prime, n)` �������� ����� tree�� ����� ��Ÿ����. 3��° leaf ���� k_prime�� ���� �������־�� �Ѵ�. ��, �ٽ� �θ� ��忡�� key 5�� ������ �ϴ� ���̴�. leaf��忡�� key 6�� pointer�� ������ �� ó�� �θ� ��忡��  key 5�� 3��° leaf ��带 ����Ű�� pointer�� ������ �Ѵ�. �׷��� ������ ��������� `delete_entry(root, n->parent, k_prime, n)`�� ȣ���Ѵ�.  `delete_entry`���� �ٽ� ������ �� ���� �ݺ��Ѵ�. leaf���� internal����� ���� ����� ���� �帧�� ����ϴ�. `delete_entry`���� ���� `remove_entry_from_node`�� ȣ���� key 5�� �����. `remove_entry_from_node`�� ����� ������ ����.

![delete_04](/uploads/16db6696dd58f7d432a445164e257ae3/delete_04.PNG)

**<�׸� 10>**

<�׸� 10>�� �θ� ��忡�� key 5�� ���� �����̴�. <�׸� 10>���� �θ� ���� root����̹Ƿ� ù��° if������ �� `adjust_root(root)`�� ȣ���Ѵ�. `adjust_root`���� `root->num_keys`�� 2�̹Ƿ� `root->num_keys > 0`�� `true`�̴�. �׷��� ������ root�� �ּҸ� ��ȯ�ϰ� �������ȴ�. 

�� ���ô� delete�� case 3���� case 1�� ����� ���̴�. ������ case 3���� case 2, 3, 4�ε� ����� ���� �ִ�. ���� case 3���� case 3���� ����ȴٸ� �̾ case 1, 2, 3, 4 �� �ϳ��� ����� ���̴�. case 3�� ��������� ��� root��带 ���ؼ� propagate�� �� �ִ� ����̴�. �� ������ merge�� �ϴ� ���� �ϳ��� ��尡 ������� ������ �θ� ��忡�� key�� �ϳ� delete�ؾ� �ϱ� �����̴�.

C. (Naive) designs or required changes for building on-disk b+ tree
----------------------------------------------------------------------

* **bpt �ڵ��� delete �Լ� (`remove_entry_from_node`) ����**

i) 3rd parameter: node* -> void*
        pointer ������ record�� ����ų �� �ֱ� �����̴�.

ii) internal ��� ���� Ű�� ���� ���� �����, leaf ��忡�� ���������� internal ��忡�� �״���̴�.

-> internal ��忡�� ���ο� Ű������ �������־�� �Ѵ�. (��Ʈ ��忡�� ����) 

iii) record�� ���� �� �ִ� �κ��� �߰��Ͽ��� �Ѵ�.

* **on-disk�� ���� �ʿ��� �κ�**

i) record ũ��� block ũ�⸦ �����Ͽ� ����� ��� �������� ũ�⸦ �� �������־�� �Ѵ�.

ii) fileio�� ���� �Էµ� ���� �����ؾ� �Ѵ�.
