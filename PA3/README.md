Performance:
`avl_map` uses AVL trees to keep operations like insert and find in O(log n) time by keeping the tree balanced.
 It does this using left/right rotations after insert or delete to avoid skewed trees
Benchmark look up 1000 zips:
avl_map : 0.67ms
srd::map: 0.71 ms

Conclusion:
avl_map is fast, balanced and performs close to or better than std::map 

