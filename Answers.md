# Answers to the Questions in Homework 6

## 0. Header guards and `#pragma once`

Both `#pragma once` and the combination of `#ifndef MOVINGOBJECT_H`, `#define MOVINGOBJECT_H`, and `#endif` prevent a header file from being included more than once in the same translation unit.

The `#ifndef` directive checks whether a macro has already been defined. If it has not, the code between `#ifndef` and `#endif` is processed, and the macro is defined using `#define`. If the macro has already been defined, the code is skipped. The `#endif` marks the end of the conditional section.

The header guard therefore requires a macro name, which is usually based on the header filename.

`#pragma once` achieves the same purpose by telling the compiler to include the header only once. However, it does not require a macro name.

I chose `#pragma once` because it is simpler and avoids accidentally reusing the same macro name in different header files.

## 1. Explain the difference between the default access rules of `struct` and `class`.

A `struct` and a `class` differ in their default access rules. In a `class`, members are private by default, whereas in a `struct`, members are public by default.

## 2. Why do we need our class to be derived from `TObject`?

Deriving `MovingObject` from `TObject` allows ROOT to use its object-handling and input/output mechanisms for our custom class. This is needed for storing and reading our objects in a `TTree` in this assignment.

## 3. Implement the class interface and verify that the class compiles without errors.

Done. The class compiles without errors.

## 4. Add the three velocity components to your class and initialize them correctly in both constructors. Verify that the getters and `SetVelocity` work.

Done. The default constructor initializes the velocity components to zero, while the other constructor initializes them using its arguments. The getters and `SetVelocity` were tested.

## 5. Report both speeds for each example. Explain why changing $v_z$ changes the total speed but leaves the horizontal speed unchanged. Check that $0 \leq v_{xy} \leq v$.

The total speed is calculated as

$$
v = \sqrt{v_x^2 + v_y^2 + v_z^2},
$$

while the horizontal speed is

$$
v_{xy} = \sqrt{v_x^2 + v_y^2}.
$$

For Example A, with $v_x = 0.30\,\mathrm{m/s}$, $v_y = 0.40\,\mathrm{m/s}$, and $v_z = 0.00\,\mathrm{m/s}$, the results are

$$
v = 0.50000000\,\mathrm{m/s},
\qquad
v_{xy} = 0.50000000\,\mathrm{m/s}.
$$

For Example B, with $v_x = 0.30\,\mathrm{m/s}$, $v_y = 0.40\,\mathrm{m/s}$, and $v_z = 0.50\,\mathrm{m/s}$, the results are

$$
v = 0.70710678\,\mathrm{m/s},
\qquad
v_{xy} = 0.50000000\,\mathrm{m/s}.
$$

The horizontal speed does not depend on $v_z$, so changing $v_z$ does not change $v_{xy}$. However, the total speed depends on all three velocity components, so changing $v_z$ changes $v$.

Since $v_z^2 \geq 0$, the total speed is always greater than or equal to the horizontal speed. Therefore,

$$
0 \leq v_{xy} \leq v.
$$

## 6. Generate and store 10,000 measurements in `tree_file.root`, using the tree name `tree` and branch name `object`. Verify the entry count and include the random seed and generation parameters.

The tree contains 10,000 entries in the `object` branch. The random seed was set to `12345`. Each velocity component was generated independently from a Gaussian distribution with a mean of $0.0\,\mathrm{m/s}$ and a standard deviation of $0.30\,\mathrm{m/s}$.

The writing macro was executed using:

```cpp
.L MovingObject.cxx+
.x write.cxx
```

The entry count was verified using `GetEntries()`, which returned `10000`.

## 7. Plot the velocity components and interpret the plots.

The `velocity_components` plot shows similar distributions for the two velocity components. Both distributions are centred around zero, although their measured means are not exactly zero. The measured standard deviations are close to the specified value of $0.30\,\mathrm{m/s}$.

The `selected_measurements` plot shows the horizontal speed $v_{xy}$ as a function of $v_z$, for measurements satisfying $v > 0.50\,\mathrm{m/s}$. The distribution is symmetric with respect to $v_z = 0$, and the spread has an approximately curved boundary. This is consistent with the mathematical relationship between the velocity components and the total speed.

## Commands and Outputs

### Task 4: Testing the class

The following commands were used to test the default constructor, the parameterized constructor, the getters, and `SetVelocity`:

```cpp
MovingObject obj;
obj.Vx();
obj.Vz();
obj.Vy();

MovingObject obj2(0.30, 0.40, 0.00);
obj2.Vx();
obj2.Vy();
obj2.Vz();

obj2.SetVelocity(1.0, 2.0, 3.0);
obj2.Vx();
obj2.Vy();
obj2.Vz();
```

The default constructor returned zero for all three velocity components. The parameterized constructor returned the supplied values, and `SetVelocity` updated the components to $1.0$, $2.0$, and $3.0\,\mathrm{m/s}$.

### Task 6: Verifying the tree

The entry count was checked using:

```cpp
checkTree->GetEntries()
```

Output:

```text
(long long) 10000
```

The tree structure was inspected using:

```cpp
checkTree->Print()
```

The output confirmed that the tree was named `tree`, contained 10,000 entries, and included the `object` branch.

### Task 7: Reading the tree and generating the plots

The reading macro was executed in a separate ROOT session using:

```cpp
.L MovingObject.cxx+
.x read.C
```

ROOT reported that the following plot files were created successfully:

```text
velocity_components.pdf
velocity_components.png
selected_measurements.png
```

The tree was also printed, confirming 10,000 entries and the stored velocity components `fVx`, `fVy`, and `fVz`.


## Outputs

4. Proof
```cpp
root [5] MovingObject obj;
root [6] obj.Vx()
(double) 0.0000000
root [7] obj.Vz()
(double) 0.0000000
root [8] obj.Vy()
(double) 0.0000000
root [9] MovingObject obj2(0.30, 0.40, 0.00)
(MovingObject &) Name: MovingObject Title: 
root [10] obj2.Vx()
(double) 0.30000000
root [11] obj2.Vy()
(double) 0.40000000
root [12] obj2.Vz()
(double) 0.0000000
//Here I did some mistakes
root [15] obj2.SetVelocity(1.0,2.0,3.0);
root [16] obj2.Vx()
(double) 1.0000000
root [17] obj2.Vy()
(double) 2.0000000
root [18] obj2.Vz()
(double) 3.0000000
```

6.
```cpp
checkTree->GetEntries()
(long long) 10000
root [8] checkTree->Print()
******************************************************************************
*Tree    :tree      : data tree                                              *
*Entries :    10000 : Total =          365274 bytes  File  Size =     232539 *
*        :          : Tree compression factor =   1.56                       *
******************************************************************************
*Branch  :object                                                             *
*Entries :    10000 : BranchElement (see below) 

7. To run the read.C file I use

root [] .L MovingObject.cxx+
root [] .x read.C
and the output I get is:

root [0] .L MovingObject.cxx+

root [1] 
root [1] .x read.C
Info in <TCanvas::Print>: pdf file velocity_components.pdf has been created
Info in <TCanvas::Print>: file velocity_components.png has been created
Info in <TCanvas::Print>: file selected_measurements.png has been created
******************************************************************************
*Tree    :tree      : data tree                                              *
*Entries :    10000 : Total =          365274 bytes  File  Size =     232539 *
*        :          : Tree compression factor =   1.56                       *
******************************************************************************
*Branch  :object                                                             *
*Entries :    10000 : BranchElement (see below)                              *
*............................................................................*
*Br    0 :fUniqueID : UInt_t                                                 *
*Entries :    10000 : Total  Size=      40665 bytes  File Size  =        392 *
*Baskets :        2 : Basket Size=      32000 bytes  Compression= 102.43     *
*............................................................................*
*Br    1 :fBits     : UInt_t                                                 *
*Entries :    10000 : Total  Size=      80825 bytes  File Size  =      12878 *
*Baskets :        4 : Basket Size=      32000 bytes  Compression=   6.24     *
*............................................................................*
*Br    2 :fVx       : Double_t                                               *
*Entries :    10000 : Total  Size=      80703 bytes  File Size  =      72701 *
*Baskets :        3 : Basket Size=      32000 bytes  Compression=   1.10     *
*............................................................................*
*Br    3 :fVy       : Double_t                                               *
*Entries :    10000 : Total  Size=      80703 bytes  File Size  =      72785 *
*Baskets :        3 : Basket Size=      32000 bytes  Compression=   1.10     *
*............................................................................*
*Br    4 :fVz       : Double_t                                               *
*Entries :    10000 : Total  Size=      80703 bytes  File Size  =      72688 *
*Baskets :        3 : Basket Size=      32000 bytes  Compression=   1.10     *
``
