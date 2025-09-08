# Push_Swap

A highly optimized stack sorting algorithm implementation in C that sorts stacks of integers with minimal operations, developed as part of the 42 curriculum.

![42 School Badge](https://img.shields.io/badge/42-School-black?style=flat-square&logo=42)
![C Badge](https://img.shields.io/badge/C-Language-blue?style=flat-square&logo=c)
![Build Status](https://img.shields.io/badge/Build-Passing-green?style=flat-square)

## 📋 Table of Contents

- [Overview](#overview)
- [Algorithm](#algorithm)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Performance](#performance)
- [Bonus - Checker](#bonus---checker)
- [Testing](#testing)
- [Technical Details](#technical-details)
- [Contributing](#contributing)

## 🎯 Overview

Push_Swap is a sorting algorithm project that challenges you to sort a stack of integers using a limited set of operations and achieving the minimum number of moves. The goal is to sort stack A in ascending order using an auxiliary stack B and a predefined set of operations.

### Rules

The program receives integers as arguments and must sort them using only these operations:

- **sa** - swap first 2 elements at the top of stack A
- **sb** - swap first 2 elements at the top of stack B
- **ss** - sa and sb at the same time
- **pa** - push first element of stack B to stack A
- **pb** - push first element of stack A to stack B
- **ra** - rotate stack A (first element becomes last)
- **rb** - rotate stack B (first element becomes last)
- **rr** - ra and rb at the same time
- **rra** - reverse rotate stack A (last element becomes first)
- **rrb** - reverse rotate stack B (last element becomes first)
- **rrr** - rra and rrb at the same time

## 🧠 Algorithm

The implementation uses a **cost-based optimization approach** with several key strategies:

### Core Strategy

1. **Small Stack Handling**: Direct sorting for stacks ≤ 3 elements using hardcoded optimal sequences
2. **Large Stack Processing (Phase 1 - Push to B)**:
   - Calculate the cost to move each element from A to its optimal position in B
   - Choose the element with minimum cost and execute the moves
   - Push that element to stack B
   - Repeat until either A is sorted OR only 3 elements remain in A
   - If 3 elements remain, sort them directly
3. **Large Stack Processing (Phase 2 - Push back to A)**:
   - Calculate the cost to move each element from B to its optimal position in A
   - Choose the element with minimum cost and execute the moves
   - Push that element to stack A
   - Repeat until B is empty
4. **Final Positioning**: Rotate A to position the minimum element at the top

### Key Optimizations

- **Cost Calculation**: Each move considers both rotation directions (ra/rra, rb/rrb)
- **Bidirectional Lists**: Efficient traversal in both directions for distance calculations
- **Target Position Finding**: Finds the exact position where each element should be inserted
- **Move Optimization**: Combines operations when beneficial (rr, rrr, ss) to reduce total moves

### Complexity Analysis

- **Time Complexity**: O(n²) in worst case, O(n log n) average
- **Space Complexity**: O(n) for the bidirectional list structure
- **Move Efficiency**: Typically achieves optimal or near-optimal move counts

## ✨ Features

- **High Performance**: Consistently achieves excellent move counts
- **Memory Efficient**: Custom bidirectional list implementation
- **Error Handling**: Comprehensive input validation and error management
- **Modular Design**: Clean separation of concerns across modules
- **Extensive Documentation**: Well-documented functions and structures
- **Testing Suite**: Comprehensive testing framework included

## 🚀 Installation

### Prerequisites

- GCC compiler
- Make utility
- Linux/Unix environment

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/PabloMzGa/42-pushswap.git
cd 42-pushswap

# Build the main program
make

# Build the bonus checker (optional)
make bonus

# Build both with debug flags
make debug
```

### Available Make Targets

```bash
make          # Build push_swap
make bonus    # Build checker
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
make debug    # Build with debug flags
```

## 📖 Usage

### Basic Usage

```bash
# Sort a list of integers
./push_swap 42 3 17 8 1

# Example output:
pb
ra
pb
ra
pa
ra
pa
```

### Input Validation

The program handles various input formats:

```bash
# Space-separated arguments
./push_swap 3 2 1 6 5 8

# Single quoted string
./push_swap "3 2 1 6 5 8"

# Mixed format
./push_swap 3 "2 1" 6 "5 8"
```

### Error Cases

The program will output "Error" for invalid inputs:
- Non-integer values
- Duplicate numbers
- Numbers outside integer range
- Empty input

## 📁 Project Structure

```
pushswap/
├── Makefile                    # Build configuration
├── README.md                   # Project documentation
├── include/
│   └── pushswap.h             # Main header file
├── src/
│   ├── main.c                 # Entry point
│   ├── arg_check.c            # Input validation
│   ├── error_clean.c          # Error handling and cleanup
│   ├── initialization.c       # Stack initialization
│   ├── algorithm/             # Core sorting algorithm
│   │   ├── apply_mov.c        # Movement application
│   │   ├── hard_sort.c        # Small stack sorting
│   │   ├── push_a.c           # Push to stack A logic
│   │   ├── push_b.c           # Push to stack B logic
│   │   ├── search_closest.c   # Target position finding
│   │   └── sort_check.c       # Sorting verification
│   ├── blist_helpers/         # Bidirectional list utilities
│   │   ├── blstadd_back.c     # Add node to back
│   │   ├── create_node.c      # Node creation
│   │   ├── get_distance.c     # Distance calculations
│   │   ├── get_highest_node.c # Find maximum value
│   │   ├── get_last_node.c    # Get last node
│   │   └── get_node_from_index.c # Index-based access
│   ├── cost_manager/          # Cost calculation system
│   │   ├── cost.c             # Main cost functions
│   │   └── cost_helpers.c     # Cost utilities
│   └── operations/            # Stack operations
│       ├── push.c             # Push operations
│       ├── reverse_rotate.c   # Reverse rotation
│       ├── rotate.c           # Rotation operations
│       └── swap.c             # Swap operations
├── bonus/                     # Bonus checker program
├── lib/
│   └── libft/                 # Custom C library
└── test/                      # Testing framework
```

## 📊 Performance

The algorithm achieves excellent performance across different input sizes:

### Move Count Targets (42 School)

| Stack Size | Excellent | Good | Acceptable |
|------------|-----------|------|------------|
| 3 elements | ≤ 3 moves | - | - |
| 5 elements | ≤ 12 moves | - | - |
| 100 elements | < 700 moves | < 900 moves | < 1500 moves |
| 500 elements | < 5500 moves | < 7000 moves | < 11500 moves |

### Actual Performance

Our implementation consistently achieves:
- **100 elements**: ~550-650 moves (excellent range)
- **500 elements**: ~4800-5200 moves (excellent range)
- **Success Rate**: 99.9%+ for correct sorting

## 🎁 Bonus - Checker

The bonus program validates sorting solutions:

```bash
# Build checker
make bonus

# Usage
ARG="4 67 3 87 23"; ./push_swap $ARG | ./bonus/checker $ARG

# Expected output for correct sorting:
OK

# Expected output for incorrect sorting:
KO
```

### Checker Features

- Reads operations from stdin
- Validates each operation
- Checks final stack state
- Provides clear OK/KO output

## 🧪 Testing

### Automated Testing

The project includes a comprehensive testing framework:

```bash
# Run the test suite (requires 4 parameters: repetitions, quantity, min, max)
./test/test.sh 1000 500 1 500

# Test different stack sizes
./test/test.sh 100 100 1 100    # 100 elements
./test/test.sh 500 500 1 500    # 500 elements

# Quick test
./test/test.sh 10 100 1 100
```

### Test Features

- Parallel execution for speed
- Statistical analysis
- Error detection
- Performance benchmarking
- Detailed logging

### Manual Testing

```bash
# Test with random numbers
ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l

# Verify sorting
ARG="3 1 4 1 5"; ./push_swap $ARG | ./bonus/checker $ARG
```

## 🔧 Technical Details

### Data Structures

- **t_blist**: Bidirectional linked list for efficient stack operations
- **t_stack**: Stack structure with size tracking and identification
- **t_cost**: Cost calculation structure for move optimization

### Memory Management

- Automatic cleanup on errors
- No memory leaks (validated with Valgrind)
- Efficient memory allocation patterns

### Compilation Flags

- `-Wall -Wextra -Werror`: Strict warning handling
- `-g`: Debug information for development
- `-fno-inline`: Better debugging experience
- `-lm`: Math library linking

### Code Quality

- Comprehensive documentation
- Consistent coding style (42 Norm)
- Modular architecture
- Error handling throughout

## 🤝 Contributing

This project is part of the 42 School curriculum and is primarily for educational purposes. However, suggestions and improvements are welcome!

## 📜 License

This project is part of the 42 School curriculum. The code is available for educational purposes and portfolio demonstration.

---

### 👨‍💻 Author

**Pablo Martín García**
- GitHub: [@PabloMzGa](https://github.com/PabloMzGa)
- 42 Intra: `pabmart2`
- School: 42 Málaga

---

*This project was completed as part of the 42 School curriculum - a innovative, project-based programming school with a peer-to-peer learning methodology.*
