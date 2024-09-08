# FIND-HOTEL

## Overview

FIND-HOTEL is a project that uses a hash table and binary search tree to manage hotel information. The project allows you to:

- Insert new hotel records
- Search for specific hotels
- Find all hotels in a city
- Delete hotel records
- Export the data to a file

### Technologies Used

- C++ for the backend logic


You can find the source code for this project on [GitHub](https://github.com/EnockMagara/FIND-HOTEL).

## How to Run the Project

### Prerequisites

- Ensure you have `g++` installed on your system.
- Ensure you have `make` installed on your system.

### Steps to Build and Run

1. **Navigate to your project directory**:
   Open your terminal and navigate to the directory containing your `Makefile`.

2. **Build the project**:
   Run the `make` command to compile the source files and create the executable.

   ```sh
   make
   ```

3. **Run the executable**:
   After building the project, you can run the executable. If you want to run it with a specific input file, use the `-f` flag followed by the file name. Otherwise, you can run it without any arguments.

   ```sh
   ./hotelFinder
   ```

   Or, if you have an input file:

   ```sh
   ./hotelFinder -f hotels.csv
   ```

4. **Clean the project** (optional):
   If you want to remove the compiled executable, you can use the `make clean` command.

   ```sh
   make clean
   ```

### Example Commands

1. **Build the project**:
   ```sh
   make
   ```

2. **Run the project without an input file**:
   ```sh
   ./hotelFinder
   ```

3. **Run the project with an input file**:
   ```sh
   ./hotelFinder -f hotels.csv
   ```

4. **Clean the project**:
   ```sh
   make clean
   ```


