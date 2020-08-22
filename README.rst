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
    |    |                              | Preorder Tree Walk                    |  289 |
    |    |                              | Postorder Tree Walk                   |  289 |
    |    | BinarySearchTree.cpp         | Tree Search                           |  290 |
    |    |                              | Iterative Tree Search                 |  291 |
    |    |                              | Tree Minimum                          |  291 |
    |    |                              | Tree Maximum                          |  291 |
    |    |                              | Tree Successor                        |  292 |
    |    |                              | Tree Predecessor                      |  293 |
    |    |                              | Tree Insert                           |  294 |
    |    |                              | Transplant                            |  296 |
    |    |                              | Tree Delete                           |  298 |
    | 13 | RedBlackTree.cpp             | Left Rotate                           |  313 |
    |    |                              | Right Rotate                          |  313 |
    |    |                              | RB Insert                             |  315 |
    |    |                              | RB Insert Fixup                       |  316 |
    |    |                              | RB Transplant                         |  323 |
    |    |                              | RB Delete                             |  324 |
    |    |                              | RB Delete Fixup                       |  326 |
    | 14 | OrderStatisticTree.cpp       | OS Select                             |  341 |
    |    |                              | OS Rank                               |  342 |
    |    | IntervalTree.cpp             | Interval Search                       |  351 |
    | 15 | CutRod.cpp                   | Cut Rod                               |  363 |
    |    |                              | Momorized Cut Rod                     |  365 |
    |    |                              | Momorized Cut Rod Aux                 |  366 |
    |    |                              | Bottom Up Cut Rod                     |  366 |
    |    |                              | Extended Bottom Up Cut Rod            |  369 |
    |    |                              | Print Cut Rod Solution                |  369 |
    |    | MatrixChainOrder.cpp         | Matrix Multiply                       |  371 |
    |    |                              | Matrix Chain Order                    |  375 |
    |    |                              | Print Optimal Parens                  |  377 |
    |    |                              | Recursive Matrix Chain                |  385 |
    |    |                              | Memorized Matrix Chain                |  388 |
    |    |                              | Lookup Chain                          |  388 |
    |    | LCSLength.cpp                | LCS Length                            |  394 |
    |    |                              | Print LCS                             |  395 |
    |    | OptimalBST.cpp               | Optimal BST                           |  402 |
    | 16 | ActivitySelector.cpp         | Recursive Activity Selector           |  419 |
    |    |                              | Greedy Activity Selector              |  421 |
    |    | Huffman.cpp                  | Huffman                               |  431 |
    |    | Greedy.cpp                   | Greedy                                |  440 |
    |    | TaskSchedule.cpp             | Task Schedule                         |  446 |
    | 17 | Stack                    | Multi Pop                             |  453 |
    |    | BinaryCounter.cpp            | Increment                             |  454 |
    |    | DynamicTable.cpp             | Table Insert                          |  464 |
    | 18 | BTree.cpp                    | B Tree Search                         |  491 |
    |    |                              | B Tree Create                         |  492 |
    |    |                              | B Tree Split Child                    |  494 |
    |    |                              | B Tree Insert                         |  495 |
    |    |                              | B Tree Insert Nonfull                 |  495 |
    |    |                              | B Tree Insert Delete                  |  502 |
    | 19 | FibHeap.cpp                  | Make Fib Heap                         |  510 |
    |    |                              | Fib Heap Insert                       |  510 |
    |    |                              | Fib Heap Minimum                      |  511 |
    |    |                              | Fib Heap Union                        |  512 |
    |    |                              | Fib Heap Extract Min                  |  513 |
    |    |                              | Consolidate                           |  516 |
    |    |                              | Fib Heap Link                         |  516 |
    |    |                              | Fib Heap Decrease Key                 |  519 |
    |    |                              | Cut                                   |  519 |
    |    |                              | Cascading Cut                         |  519 |
    |    |                              | Fib Heap Delete                       |  522 |
    | 20 | ProtovEB.cpp                 | Proto vEB Member                      |  541 |
    |    |                              | Proto vEB Minimum                     |  542 |
    |    |                              | Proto vEB Successor                   |  543 |
    |    |                              | Proto vEB Insert                      |  544 |
    |    |                              | Proto vEB Delete                      |  544 |
    |    | vEB.cpp                      | vEB Tree Minimum                      |  550 |
    |    |                              | vEB Tree Maximum                      |  550 |
    |    |                              | vEB Tree Member                       |  550 |
    |    |                              | vEB Tree Successor                    |  551 |
    |    |                              | vEB Tree Predecessor                  |  552 |
    |    |                              | vEB Empty Tree Insert                 |  553 |
    |    |                              | vEB Tree Insert                       |  553 |
    |    |                              | vEB Tree Delete                       |  554 |
    | 21 | DisjointSet.cpp              | Connected Components                  |  563 |
    |    |                              | Same Component                        |  563 |
    |    |                              | Make Set                              |  571 |
    |    |                              | Union                                 |  571 |
    |    |                              | Link                                  |  571 |
    |    |                              | Find Set                              |  571 |
    | 22 | BFS.cpp                      | BFS                                   |  595 |
    |    |                              | Print Path                            |  601 |
    |    | DFS.cpp                      | DFS                                   |  604 |
    |    |                              | DFS Visit                             |  604 |
    |    | TopologicalSort.cpp          | Topological Sort                      |  613 |
    |    | SCC.cpp                      | Strongly Connected Components         |  617 |
    | 23 | MST.cpp                      | MST Kruskal                           |  631 |
    |    |                              | MST Prim                              |  634 |
    | 24 | BellmanFord.cpp              | Initialize Single Source              |  648 |
    |    |                              | Relax                                 |  649 |
    |    |                              | Bellman Ford                          |  651 |
    |    | DagShortestPaths.cpp         | Dag Shortest Paths                    |  655 |
    |    | Dijkstra.cpp                 | Dijkstra                              |  658 |
    | 25 | FloydWarshall.cpp            | Print All Pairs Shortest Path         |  685 |
    |    | AllPairsShortestPaths.cpp    | Extend Shortest Paths                 |  688 |
    |    |                              | Slow All Pairs Shortest Paths         |  689 |
    |    |                              | Faster All Pairs Shortest Paths       |  691 |
    |    | FloydWarshall.cpp            | Floyd Warshall                        |  695 |
    |    | TransitiveClosure.cpp        | Transitive Closure                    |  698 |
    |    | Johnson.cpp                  | Johnson                               |  704 |
    | 26 | FordFulkerson.cpp            | Ford Fulkerson                        |  724 |
    |    | MaximumBipartiteMatching.cpp | Maximum Bipartite Matching            |  733 |
    |    | RelabelToFront.cpp           | Push                                  |  739 |
    |    |                              | Relabel                               |  740 |
    |    |                              | Initialize Preflow                    |  740 |
    |    |                              | Discharge                             |  751 |
    |    |                              | Relabel To Front                      |  755 |
    | 27 | Fib.cpp                      | Fib                                   |  775 |
    |    |                              | P Fib                                 |  776 |
    |    | MatVec.cpp                   | Mat Vec                               |  785 |
    |    |                              | Mat Vec Main Loop                     |  785 |
    |    | RaceExample.cpp              | Race Example                          |  788 |
    |    | MatVec.cpp                   | Mat Vec Wrong                         |  790 |
    |    | PSquareMatrixMultiply.cpp    | P Square Matrix Multiply              |  793 |
    |    |                              | P Matrix Multiply Recursive           |  794 |
    |    |                              | P Matrix Multiply Strassen            |  794 |
    |    | PMergeSort.cpp               | Merge Sort prime                      |  797 |
    |    |                              | Binary Search                         |  799 |
    |    |                              | P Merge                               |  800 |
    |    |                              | P Merge Sort                          |  803 |
    | 28 | LUPSolve.cpp                 | LUP Solve                             |  817 |
    |    |                              | LU Decomposition                      |  821 |
    |    |                              | LUP Decomposition                     |  824 |
    |    | MatrixInverse.cpp            | Matrix Inverse                        |  828 |
    |    | LeastSquareApprox.cpp        | Least Square Approx                   |  837 |
    | 29 | Simplex.cpp                  | Pivot                                 |  869 |
    |    |                              | Simplex                               |  871 |
    |    |                              | Initialize Simplex                    |  887 |
    | 30 | RecursiveFFT.cpp             | Recursive FFT                         |  911 |
    |    |                              | Inverse FFT                           |  913 |
    |    |                              | Polynomial Multiply                   |  914 |
    |    | IterativeFFT.cpp             | Iterative FFT                         |  917 |
    |    |                              | Bit Reversal Copy                     |  918 |
    | 31 | Euclid.cpp                   | Euclid                                |  935 |
    |    |                              | Extended Euclid                       |  937 |
    |    | ModLinEquationSolver.cpp     | Modular Linear Equation Solver        |  949 |
    |    | ModularExponentiation.cpp    | Modular Exponentiation                |  957 |
    |    | Pseudoprime.cpp              | Pseudoprime                           |  967 |
    |    | MillerRabin.cpp              | Witness                               |  969 |
    |    |                              | Miller Rabin                          |  970 |
    |    | PollardRho.cpp               | Pollard Rho                           |  977 |
    | 32 | NaiveStringMatcher.cpp       | Naive String Matcher                  |  988 |
    |    | RabinKarpMatcher.cpp         | Rabin Karp Matcher                    |  993 |
    |    | FiniteAutomatonMatcher.cpp   | Finite Automaton Matcher              |  999 |
    |    |                              | Compute Transition Function           | 1001 |
    |    | KMPMatcher.cpp               | KMP Matcher                           | 1005 |
    |    |                              | Compute Prefix Function               | 1006 |
    | 33 | SegmentsIntersect.cpp        | Segments Intersect                    | 1018 |
    |    |                              | Direction                             | 1018 |
    |    |                              | On Segment                            | 1018 |
    |    | AnySegmentsIntersect.cpp     | Insert                                | 1024 |
    |    |                              | Delete                                | 1024 |
    |    |                              | Above                                 | 1024 |
    |    |                              | Below                                 | 1024 |
    |    |                              | Any Segments Intersect                | 1025 |
    |    | GrahamScan.cpp               | Graham Scan                           | 1031 |
    |    | JarvisMarch.cpp              | Jarvis March                          | 1038 |
    |    | ClosestPairPoints.cpp        | Closest Pair Points                   | 1043 |
    | 35 | ApproxVertexCover.cpp        | Approx Vertex Cover                   | 1109 |
    |    | ApproxTSPTour.cpp            | Approx TSP Tour                       | 1112 |
    |    | GreedySetCover.cpp           | Greedy Set Cover                      | 1119 |
    |    | ApproxMinWeightVC.cpp        | Approx Min Weight VC                  | 1126 |
    |    | SubsetSum.cpp                | Exact Subset Sum                      | 1129 |
    |    |                              | Trim                                  | 1130 |
    |    |                              | Approx Subset Sum                     | 1131 |

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
