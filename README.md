# Memory Management Simulator (C++)
Project Overview

This project implements a **Memory Management Simulator** in C++ that models the core components of a modern operating system’s memory subsystem. The simulator demonstrates how memory is allocated, cached, and managed using virtual memory.



1. Physical Memory Management (Stage 1–4)
- Contiguous physical memory model
- Dynamic allocation and deallocation
- Allocation strategies:
  - First Fit
  - Best Fit
  - Worst Fit
- Block splitting and coalescing
- Memory statistics:
  - External Fragmentation
  - Memory Utilization
- Memory dump / visualization

2. Cache Hierarchy Simulation (Stage 5)
- Configurable cache:
  - Cache size
  - Block size
  - Associativity
- Set-associative cache model
- LRU (Least Recently Used) replacement policy
- Cache hit / miss tracking
- Hit ratio calculation
- Command-based cache access interface

3. Virtual Memory Management (Stage 6)
- Paging-based virtual memory
- Configurable:
  - Page size
  - Number of virtual pages
  - Number of physical frames
- Page table with valid bits
- Page fault handling
- LRU page replacement
- Virtual → Physical address translation
- Page fault rate calculation

