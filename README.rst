algorithms
==========
Personal implementation of some algorithms in "Introduction to Algorithms",
third edition

Contents
--------

+----+--------------------------+---------------------------------------+------+
| Ch.| Name                     | Algorithm                             | Page |
+====+==========================+=======================================+======+
|  2 | InsertSort               | Insersion Sort                        |   18 |
|    +--------------------------+---------------------------------------+------+
|    | MergeSort                | Merge                                 |   31 |
|    |                          +---------------------------------------+------+
|    |                          | Merge Sort                            |   34 |
+----+--------------------------+---------------------------------------+------+
|  4 | FindMaximumSubarray      | Find Max Crossing Subarray            |   71 |
|    |                          +---------------------------------------+------+
|    |                          | Find Maximum Subarray                 |   72 |
|    +--------------------------+---------------------------------------+------+
|    |                          | Square Matrix Multiply                |   75 |
|    |                          +---------------------------------------+------+
|    |                          | Square Matrix Multiply Recursive      |   77 |
|    |                          +---------------------------------------+------+
|    |                          | Square Matrix Multiply Strassen       |   82 |
+----+--------------------------+---------------------------------------+------+
|  5 | HireAssistant            | Hire Assistant                        |  115 |
|    |                          +---------------------------------------+------+
|    |                          | Randomized Hire Assistant             |  124 |
|    +--------------------------+---------------------------------------+------+
|    | RandomPermute            | Permute By Sorting                    |  125 |
|    |                          +---------------------------------------+------+
|    |                          | Randomize In Place                    |  126 |
|    +--------------------------+---------------------------------------+------+
|    | OnLineMaximum            | On Line Maximum                       |  140 |
+----+--------------------------+---------------------------------------+------+
|  6 | MaxHeap                  | Max Heapify                           |  154 |
|    |                          +---------------------------------------+------+
|    |                          | Build Max Heap                        |  157 |
|    |                          +---------------------------------------+------+
|    |                          | Heap Sort                             |  160 |
|    |                          +---------------------------------------+------+
|    |                          | Heap Maximum                          |  163 |
|    |                          +---------------------------------------+------+
|    |                          | Heap Extract Max                      |  163 |
|    |                          +---------------------------------------+------+
|    |                          | Heap Increase Key                     |  164 |
|    |                          +---------------------------------------+------+
|    |                          | Max Heap Insert                       |  164 |
|    |                          +---------------------------------------+------+
|    |                          | Build Max Heap prime                  |  167 |
+----+--------------------------+---------------------------------------+------+
|  7 | Quicksort                | Quicksort                             |  171 |
|    |                          +---------------------------------------+------+
|    |                          | Partition                             |  171 |
|    |                          +---------------------------------------+------+
|    |                          | Randomized Partition                  |  179 |
|    |                          +---------------------------------------+------+
|    |                          | Randomized Quicksort                  |  179 |
+----+--------------------------+---------------------------------------+------+
|  8 | CountingSort             | Counting Sort                         |  195 |
|    +--------------------------+---------------------------------------+------+
|    | RadixSort                | Radix Sort                            |  198 |
|    +--------------------------+---------------------------------------+------+
|    | BucketSort               | Bucket Sort                           |  201 |
+----+--------------------------+---------------------------------------+------+
|  9 | Minimum                  | Minimum                               |  214 |
|    |                          +---------------------------------------+------+
|    |                          | Maximum                               |  214 |
|    |                          +---------------------------------------+------+
|    |                          | Min Max                               |  214 |
|    +--------------------------+---------------------------------------+------+
|    | RandomizedSelect         | Randomized Select                     |  216 |
|    |                          +---------------------------------------+------+
|    |                          | Randomized Select Iter                |  219 |
|    +--------------------------+---------------------------------------+------+
|    | Select                   | Select                                |  220 |
+----+--------------------------+---------------------------------------+------+
| 10 | Stack                    | StackEmpty                            |  233 |
|    |                          +---------------------------------------+------+
|    |                          | Push                                  |  233 |
|    |                          +---------------------------------------+------+
|    |                          | Pop                                   |  233 |
|    +--------------------------+---------------------------------------+------+
|    | Queue                    | Enqueue                               |  235 |
|    |                          +---------------------------------------+------+
|    |                          | Dequeue                               |  235 |
|    +--------------------------+---------------------------------------+------+
|    | LinkedList               | List Search                           |  237 |
|    |                          +---------------------------------------+------+
|    |                          | List Insert                           |  238 |
|    |                          +---------------------------------------+------+
|    |                          | List Delete                           |  238 |
|    |                          +---------------------------------------+------+
|    |                          | List Delete prime                     |  238 |
|    |                          +---------------------------------------+------+
|    |                          | List Search prime                     |  239 |
|    |                          +---------------------------------------+------+
|    |                          | List Insert prime                     |  239 |
|    +--------------------------+---------------------------------------+------+
|    | StorageManage            | Allocate Object                       |  244 |
|    |                          +---------------------------------------+------+
|    |                          | Free Object                           |  244 |
+----+--------------------------+---------------------------------------+------+
| 11 | DirectAddress            | Direct Address Search                 |  254 |
|    |                          +---------------------------------------+------+
|    |                          | Direct Address Insert                 |  254 |
|    |                          +---------------------------------------+------+
|    |                          | Direct Address Delete                 |  254 |
|    +--------------------------+---------------------------------------+------+
|    | ChainedHash              | Chained Hash Insert                   |  258 |
|    |                          +---------------------------------------+------+
|    |                          | Chained Hash Search                   |  258 |
|    |                          +---------------------------------------+------+
|    |                          | Chained Hash Delete                   |  258 |
|    +--------------------------+---------------------------------------+------+
|    | Hash                     | Division Hash                         |  263 |
|    |                          +---------------------------------------+------+
|    |                          | Multiplication Hash                   |  263 |
|    |                          +---------------------------------------+------+
|    |                          | Universal Hash                        |  263 |
|    +--------------------------+---------------------------------------+------+
|    | OpenAddress              | Hash Insert                           |  270 |
|    |                          +---------------------------------------+------+
|    |                          | Hash Search                           |  271 |
+----+--------------------------+---------------------------------------+------+

.. code:: md

    | 12 | BinaryTree.cpp               | Inorder Tree Walk                     |  288 |
    | 12 | BinaryTree.cpp               | Preorder Tree Walk                    |  289 |
    | 12 | BinaryTree.cpp               | Postorder Tree Walk                   |  289 |
    | 12 | BinarySearchTree.cpp         | Tree Search                           |  290 |
    | 12 | BinarySearchTree.cpp         | Iterative Tree Search                 |  291 |
    | 12 | BinarySearchTree.cpp         | Tree Minimum                          |  291 |
    | 12 | BinarySearchTree.cpp         | Tree Maximum                          |  291 |
    | 12 | BinarySearchTree.cpp         | Tree Successor                        |  292 |
    | 12 | BinarySearchTree.cpp         | Tree Predecessor                      |  293 |
    | 12 | BinarySearchTree.cpp         | Tree Insert                           |  294 |
    | 12 | BinarySearchTree.cpp         | Transplant                            |  296 |
    | 12 | BinarySearchTree.cpp         | Tree Delete                           |  298 |
    | 13 | RedBlackTree.cpp             | Left Rotate                           |  313 |
    | 13 | RedBlackTree.cpp             | Right Rotate                          |  313 |
    | 13 | RedBlackTree.cpp             | RB Insert                             |  315 |
    | 13 | RedBlackTree.cpp             | RB Insert Fixup                       |  316 |
    | 13 | RedBlackTree.cpp             | RB Transplant                         |  323 |
    | 13 | RedBlackTree.cpp             | RB Delete                             |  324 |
    | 13 | RedBlackTree.cpp             | RB Delete Fixup                       |  326 |
    | 14 | OrderStatisticTree.cpp       | OS Select                             |  341 |
    | 14 | OrderStatisticTree.cpp       | OS Rank                               |  342 |
    | 14 | IntervalTree.cpp             | Interval Search                       |  351 |
    | 15 | CutRod.cpp                   | Cut Rod                               |  363 |
    | 15 | CutRod.cpp                   | Momorized Cut Rod                     |  365 |
    | 15 | CutRod.cpp                   | Momorized Cut Rod Aux                 |  366 |
    | 15 | CutRod.cpp                   | Bottom Up Cut Rod                     |  366 |
    | 15 | CutRod.cpp                   | Extended Bottom Up Cut Rod            |  369 |
    | 15 | CutRod.cpp                   | Print Cut Rod Solution                |  369 |
    | 15 | MatrixChainOrder.cpp         | Matrix Multiply                       |  371 |
    | 15 | MatrixChainOrder.cpp         | Matrix Chain Order                    |  375 |
    | 15 | MatrixChainOrder.cpp         | Print Optimal Parens                  |  377 |
    | 15 | MatrixChainOrder.cpp         | Recursive Matrix Chain                |  385 |
    | 15 | MatrixChainOrder.cpp         | Memorized Matrix Chain                |  388 |
    | 15 | MatrixChainOrder.cpp         | Lookup Chain                          |  388 |
    | 15 | LCSLength.cpp                | LCS Length                            |  394 |
    | 15 | LCSLength.cpp                | Print LCS                             |  395 |
    | 15 | OptimalBST.cpp               | Optimal BST                           |  402 |
    | 16 | ActivitySelector.cpp         | Recursive Activity Selector           |  419 |
    | 16 | ActivitySelector.cpp         | Greedy Activity Selector              |  421 |
    | 16 | Huffman.cpp                  | Huffman                               |  431 |
    | 16 | Greedy.cpp                   | Greedy                                |  440 |
    | 16 | TaskSchedule.cpp             | Task Schedule                         |  446 |
    | 17 | Stack                    | Multi Pop                             |  453 |
    | 17 | BinaryCounter.cpp            | Increment                             |  454 |
    | 17 | DynamicTable.cpp             | Table Insert                          |  464 |
    | 18 | BTree.cpp                    | B Tree Search                         |  491 |
    | 18 | BTree.cpp                    | B Tree Create                         |  492 |
    | 18 | BTree.cpp                    | B Tree Split Child                    |  494 |
    | 18 | BTree.cpp                    | B Tree Insert                         |  495 |
    | 18 | BTree.cpp                    | B Tree Insert Nonfull                 |  495 |
    | 18 | BTree.cpp                    | B Tree Insert Delete                  |  502 |
    | 19 | FibHeap.cpp                  | Make Fib Heap                         |  510 |
    | 19 | FibHeap.cpp                  | Fib Heap Insert                       |  510 |
    | 19 | FibHeap.cpp                  | Fib Heap Minimum                      |  511 |
    | 19 | FibHeap.cpp                  | Fib Heap Union                        |  512 |
    | 19 | FibHeap.cpp                  | Fib Heap Extract Min                  |  513 |
    | 19 | FibHeap.cpp                  | Consolidate                           |  516 |
    | 19 | FibHeap.cpp                  | Fib Heap Link                         |  516 |
    | 19 | FibHeap.cpp                  | Fib Heap Decrease Key                 |  519 |
    | 19 | FibHeap.cpp                  | Cut                                   |  519 |
    | 19 | FibHeap.cpp                  | Cascading Cut                         |  519 |
    | 19 | FibHeap.cpp                  | Fib Heap Delete                       |  522 |
    | 20 | ProtovEB.cpp                 | Proto vEB Member                      |  541 |
    | 20 | ProtovEB.cpp                 | Proto vEB Minimum                     |  542 |
    | 20 | ProtovEB.cpp                 | Proto vEB Successor                   |  543 |
    | 20 | ProtovEB.cpp                 | Proto vEB Insert                      |  544 |
    | 20 | ProtovEB.cpp                 | Proto vEB Delete                      |  544 |
    | 20 | vEB.cpp                      | vEB Tree Minimum                      |  550 |
    | 20 | vEB.cpp                      | vEB Tree Maximum                      |  550 |
    | 20 | vEB.cpp                      | vEB Tree Member                       |  550 |
    | 20 | vEB.cpp                      | vEB Tree Successor                    |  551 |
    | 20 | vEB.cpp                      | vEB Tree Predecessor                  |  552 |
    | 20 | vEB.cpp                      | vEB Empty Tree Insert                 |  553 |
    | 20 | vEB.cpp                      | vEB Tree Insert                       |  553 |
    | 20 | vEB.cpp                      | vEB Tree Delete                       |  554 |
    | 21 | DisjointSet.cpp              | Connected Components                  |  563 |
    | 21 | DisjointSet.cpp              | Same Component                        |  563 |
    | 21 | DisjointSet.cpp              | Make Set                              |  571 |
    | 21 | DisjointSet.cpp              | Union                                 |  571 |
    | 21 | DisjointSet.cpp              | Link                                  |  571 |
    | 21 | DisjointSet.cpp              | Find Set                              |  571 |
    | 22 | BFS.cpp                      | BFS                                   |  595 |
    | 22 | BFS.cpp                      | Print Path                            |  601 |
    | 22 | DFS.cpp                      | DFS                                   |  604 |
    | 22 | DFS.cpp                      | DFS Visit                             |  604 |
    | 22 | TopologicalSort.cpp          | Topological Sort                      |  613 |
    | 22 | SCC.cpp                      | Strongly Connected Components         |  617 |
    | 23 | MST.cpp                      | MST Kruskal                           |  631 |
    | 23 | MST.cpp                      | MST Prim                              |  634 |
    | 24 | BellmanFord.cpp              | Initialize Single Source              |  648 |
    | 24 | BellmanFord.cpp              | Relax                                 |  649 |
    | 24 | BellmanFord.cpp              | Bellman Ford                          |  651 |
    | 24 | DagShortestPaths.cpp         | Dag Shortest Paths                    |  655 |
    | 24 | Dijkstra.cpp                 | Dijkstra                              |  658 |
    | 25 | FloydWarshall.cpp            | Print All Pairs Shortest Path         |  685 |
    | 25 | AllPairsShortestPaths.cpp    | Extend Shortest Paths                 |  688 |
    | 25 | AllPairsShortestPaths.cpp    | Slow All Pairs Shortest Paths         |  689 |
    | 25 | AllPairsShortestPaths.cpp    | Faster All Pairs Shortest Paths       |  691 |
    | 25 | FloydWarshall.cpp            | Floyd Warshall                        |  695 |
    | 25 | TransitiveClosure.cpp        | Transitive Closure                    |  698 |
    | 25 | Johnson.cpp                  | Johnson                               |  704 |
    | 26 | FordFulkerson.cpp            | Ford Fulkerson                        |  724 |
    | 26 | MaximumBipartiteMatching.cpp | Maximum Bipartite Matching            |  733 |
    | 26 | RelabelToFront.cpp           | Push                                  |  739 |
    | 26 | RelabelToFront.cpp           | Relabel                               |  740 |
    | 26 | RelabelToFront.cpp           | Initialize Preflow                    |  740 |
    | 26 | RelabelToFront.cpp           | Discharge                             |  751 |
    | 26 | RelabelToFront.cpp           | Relabel To Front                      |  755 |
    | 27 | Fib.cpp                      | Fib                                   |  775 |
    | 27 | Fib.cpp                      | P Fib                                 |  776 |
    | 27 | MatVec.cpp                   | Mat Vec                               |  785 |
    | 27 | MatVec.cpp                   | Mat Vec Main Loop                     |  785 |
    | 27 | RaceExample.cpp              | Race Example                          |  788 |
    | 27 | MatVec.cpp                   | Mat Vec Wrong                         |  790 |
    | 27 | PSquareMatrixMultiply.cpp    | P Square Matrix Multiply              |  793 |
    | 27 | PSquareMatrixMultiply.cpp    | P Matrix Multiply Recursive           |  794 |
    | 27 | PSquareMatrixMultiply.cpp    | P Matrix Multiply Strassen            |  794 |
    | 27 | PMergeSort.cpp               | Merge Sort prime                      |  797 |
    | 27 | PMergeSort.cpp               | Binary Search                         |  799 |
    | 27 | PMergeSort.cpp               | P Merge                               |  800 |
    | 27 | PMergeSort.cpp               | P Merge Sort                          |  803 |
    | 28 | LUPSolve.cpp                 | LUP Solve                             |  817 |
    | 28 | LUPSolve.cpp                 | LU Decomposition                      |  821 |
    | 28 | LUPSolve.cpp                 | LUP Decomposition                     |  824 |
    | 28 | MatrixInverse.cpp            | Matrix Inverse                        |  828 |
    | 28 | LeastSquareApprox.cpp        | Least Square Approx                   |  837 |
    | 29 | Simplex.cpp                  | Pivot                                 |  869 |
    | 29 | Simplex.cpp                  | Simplex                               |  871 |
    | 29 | Simplex.cpp                  | Initialize Simplex                    |  887 |
    | 30 | RecursiveFFT.cpp             | Recursive FFT                         |  911 |
    | 30 | RecursiveFFT.cpp             | Inverse FFT                           |  913 |
    | 30 | RecursiveFFT.cpp             | Polynomial Multiply                   |  914 |
    | 30 | IterativeFFT.cpp             | Iterative FFT                         |  917 |
    | 30 | IterativeFFT.cpp             | Bit Reversal Copy                     |  918 |
    | 31 | Euclid.cpp                   | Euclid                                |  935 |
    | 31 | Euclid.cpp                   | Extended Euclid                       |  937 |
    | 31 | ModLinEquationSolver.cpp     | Modular Linear Equation Solver        |  949 |
    | 31 | ModularExponentiation.cpp    | Modular Exponentiation                |  957 |
    | 31 | Pseudoprime.cpp              | Pseudoprime                           |  967 |
    | 31 | MillerRabin.cpp              | Witness                               |  969 |
    | 31 | MillerRabin.cpp              | Miller Rabin                          |  970 |
    | 31 | PollardRho.cpp               | Pollard Rho                           |  977 |
    | 32 | NaiveStringMatcher.cpp       | Naive String Matcher                  |  988 |
    | 32 | RabinKarpMatcher.cpp         | Rabin Karp Matcher                    |  993 |
    | 32 | FiniteAutomatonMatcher.cpp   | Finite Automaton Matcher              |  999 |
    | 32 | FiniteAutomatonMatcher.cpp   | Compute Transition Function           | 1001 |
    | 32 | KMPMatcher.cpp               | KMP Matcher                           | 1005 |
    | 32 | KMPMatcher.cpp               | Compute Prefix Function               | 1006 |
    | 33 | SegmentsIntersect.cpp        | Segments Intersect                    | 1018 |
    | 33 | SegmentsIntersect.cpp        | Direction                             | 1018 |
    | 33 | SegmentsIntersect.cpp        | On Segment                            | 1018 |
    | 33 | AnySegmentsIntersect.cpp     | Insert                                | 1024 |
    | 33 | AnySegmentsIntersect.cpp     | Delete                                | 1024 |
    | 33 | AnySegmentsIntersect.cpp     | Above                                 | 1024 |
    | 33 | AnySegmentsIntersect.cpp     | Below                                 | 1024 |
    | 33 | AnySegmentsIntersect.cpp     | Any Segments Intersect                | 1025 |
    | 33 | GrahamScan.cpp               | Graham Scan                           | 1031 |
    | 33 | JarvisMarch.cpp              | Jarvis March                          | 1038 |
    | 33 | ClosestPairPoints.cpp        | Closest Pair Points                   | 1043 |
    | 35 | ApproxVertexCover.cpp        | Approx Vertex Cover                   | 1109 |
    | 35 | ApproxTSPTour.cpp            | Approx TSP Tour                       | 1112 |
    | 35 | GreedySetCover.cpp           | Greedy Set Cover                      | 1119 |
    | 35 | ApproxMinWeightVC.cpp        | Approx Min Weight VC                  | 1126 |
    | 35 | SubsetSum.cpp                | Exact Subset Sum                      | 1129 |
    | 35 | SubsetSum.cpp                | Trim                                  | 1130 |
    | 35 | SubsetSum.cpp                | Approx Subset Sum                     | 1131 |

Directory Structure
-------------------
(TODO)

Continuous Integration
----------------------
(TODO)

Supplementary Files
-------------------
(TODO)

Supplementary Programs
----------------------
(TODO)
