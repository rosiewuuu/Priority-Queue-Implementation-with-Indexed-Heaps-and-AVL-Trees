# Priority Queue (PQ) Implementation with Indexed Heaps and AVL Trees

## Project Idea

This project presents an implementation of a Priority Queue (PQ) using a combination of a Binary Heap and an AVL Tree to efficiently handle tasks with unique IDs and associated priorities. The design allows for efficient priority updates and task retrieval operations, extending traditional data structures to cater to real-world scenarios.

## Structure

The project comprises three main classes: `BinaryHeap`, `AvlTree`, and `PQ`. 

- **BinaryHeap**: Implements a min-heap using an array where each element is a heap node containing the task priority and a pointer to the corresponding node in the AVL Tree.
  
- **AvlTree**: Stores project numbers in a way that allows for quick traversal and retrieval of project numbers in O(log n) time.
  
- **PQ**: Contains instances of `BinaryHeap` and `AvlTree`, named `priorityList` and `taskTree` respectively, facilitating the management of tasks and their priorities.

## Class Details

### PQ.h

- Private Variables: Objects of `AvlTree` and `BinaryHeap` classes that communicate using pointers and array indices.

### AvlTree.h

- **set_index**: Updates the heapIndex of the AvlNode containing a specified project number.
- **get_avlNodePtr_from_prj**: Returns a pointer to the node containing a specified project number.
- **get_avlNodePtr_from_ind**: Returns a pointer to the node containing a specified index.
- **insert**: Modified to accept two arguments and update the project number and heapIndex in the AvlNode.
- **displayLinks**: Outputs the internal structure of the AVL project tree, showcasing project numbers, indices, and node addresses.

### BinaryHeap.h

- **get_currentSize**: Returns the current size of the priority list.
- **get_index**: Returns the index of the node containing a specified priority.
- **get_ptr2AVL**: Returns a pointer to the AVL node at a specified array index.
- **set_ptr_by_priority**: Updates the pointer of an array element with a specified priority.
- **set_ptr_by_ind**: Updates the pointer of an array element at a specified index.
- **priorityRepeated**: Checks if a specified priority exists in the array.
- **update_priority**: Updates the priority of an element at a specified array index.
- **insert**: Modified to accept two arguments, forming a heapNode, and inserting it into the array.
- **displayArray**: Outputs the priority list, displaying priority numbers and AVLNode addresses at each index.

### AvlNode.h

- **AvlNode**: Implemented as a struct in a separate header file, extracted from the AvlTree class to allow the PQ class to utilize AvlNode pointers for its template type, initializing an array with AvlNode pointers.

## Documentation

Further documentation regarding design choices and function modifications is provided in the `Doc.pdf` file.

## Demo Program

A demonstration program `PQdemo.cpp` is included to validate the correctness of the PQ class implementation.

## Building and Running the Program

This project includes a Makefile to simplify the compilation and execution process. Here's how you can build and run the program:

1. **Compilation**:
    - Open a terminal and navigate to the project directory where the Makefile is located.
    - Run the following command to compile the source files and generate the executable:
    ```bash
    make all
    ```

2. **Running the Program**:
    - After successful compilation, you can run the program using the following command:
    ```bash
    ./PQdemo
    ```

3. **Cleaning the Build**:
    - If you wish to clean the build, i.e., remove all the compiled and intermediary files, run the following command:
    ```bash
    make clean
    ```

4. **Displaying the Priority Queue**:
    - The program provides a display function to output the internal structure of the priority queue and associated data structures. This is triggered within the demo program `PQdemo.cpp`. Upon running the program, you should see the output on the terminal, showcasing the structure and functionalities of the implemented Priority Queue.

Ensure you have all the necessary files and dependencies in the project directory before initiating the build process. Follow the prompts in the terminal for any additional instructions or error messages.

