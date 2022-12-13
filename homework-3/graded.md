# Did they follow the guidelines?
1. Are .c files in the “src” directory and .h files in the “include”?
    ```
    Yes=+10
    Total 10/10
    ```
2. There should be appropriately defined header guards in the .h files
     ```
    Yes diag=+5
    Yes trid=+5
    Yes upp=+5
    Total 15/15
    ```
   
3. Memory for each matrix is as specified (e.g., upper triangular is in a continuous chunk)
    ```
    Yes diag=+5
    Yes trid=+5
    Yes upp=+5
    Total 15/15
    ```
   
4. Free all the allocated memory at the end of their driver. This can use direct calls to “free(matrix_type->storage)” or can call a “free_matrixType” function.
     ```
    Yes diag=+5
    Yes trid=+5
    Yes upp=+5
    No the whole code. See logfile.out lines 131-137=-10.
    Total = 5/15 -> 15/15 (JC: the memory leak was my fault)
    ```
5. Deduct 1-2 points if the student does unnecessary things (like allocate unnecessary memory in the matrix-vector multiplication routines)
    ```
    Fine diag=+5
    Fine trid=+5
    Fine upp=+5
    Total = 15/15
    ```
## Total Section

```
Total=60/70
```   
# Does it work?
 1. Does “make” build correctly?
     ```
    NO. There is not makdi obj in the Makefile
    =+0/4
    ```
 2. Do the drivers run?
    ```
    Yes=+4/4
    ```
 3. Do they initialize the copy correctly
    ```
        Yes=+4
    ```
 4. For main.c, does the printout look correct for the matrix and matrix-vector product?
    ```
        Yes=+4/4
    ```
 5. For verify_and_time.c (this is also in the writeup) do they test the correct things (100 samples of matvec runtime) and get reasonable results for Diagonal and Tridiagonal Matrix types (e.g., faster than marvel the dense Matrix type)
    ```
        Yes=+4/4
    ```
 ## Total Section

```
Total=16/20
```   

# PDF and github
1. PDE
 ```
    Yes=+5/5
```
2. Github (tag, etc...)
 ```
 yes=+5/5
 ```
  ## Total Section

```
Total=10/10
```   

# Total Section
```
Total=86/100
```   
