# OS/161
- Contributors: Caleb L'Italien, Manav Bilakhia, John Collins 

- This repository contains our collective implementation of the OS/161 educational operating system, which serves as a pedagogical tool for understanding the intricacies of operating system design and kernel development. Our project work encompasses the development and enhancement of core OS functionalities, including process management, system calls, and synchronization mechanisms.

# Project Features
- Process Table: A comprehensive process table that manages and tracks processes within the OS kernel.
- Thread Mapping: A thread-to-process mapping system that facilitates efficient process scheduling and management.
- System Calls: Implementation of essential system calls like fork(), waitpid(), and exit() to manage process creation, execution, and termination.
- Synchronization Primitives: A suite of synchronization primitives designed to manage concurrent processes and threads, ensuring safe and predictable execution in a multi-threaded environment.
- FIFO Process Scheduling: The scheduler has been designed to employ a First-In-First-Out (FIFO) scheduling algorithm, ensuring a simple yet fair process execution order.
- File System Structure: A well-organized file system structure to handle file operations effectively, allowing for data persistence and management.

# Testing
 
- Comprehensive tests for each implemented feature can be found in the /testbin/ directory. These tests are designed to demonstrate the functionality and correctness of the system calls and synchronization primitives.    