# Basic Set Theory in C

This is a C project that performs basic operations on sets from a
mathematical view, like union and intersection.

------------------------------------------------------------------
Made by Cristian-Lucian Mocanu.
Faculty of Automatic Control and Computers, first year BSc.
February 2026.
https://github.com/M0KApointstoint
-------------------------------------------------------------------

---

## Description:

In this project, a set is a data structure that can contain ANY
type of data, but only one at the time, with the power of void
pointers and function pointers. The main operations implemented
are union and intersection of two sets containing the same data type,
however this is not the key idea for why this project is important,
please read more to find out!

## Project motivation:

The main motivation comes from me wanting to study more about C and
the best ways to write code of high quality.
Key concepts used:

#### Ownership details:

The sets own their properties, the user has the
freedom to define his own rules for creating a set
of some data type.

#### Deep-copy vs. shallow-copy:

The set has to be independent from other data structures that work
with pointers. If I free some memory that I allocate temporarely
to store in the set, the set has to remain intact, meaning that
more attention is required when working with data copies.

#### Encapsulation:

Hiding structure definitons from the users for security reasons.
Not all functions that are implemented are included in the
header files, only the ones that the users can use.

#### Error codes:

The status of the program needs to be monitored using an independent
data type that show different outcomes.

### Possible bugs:

The code is pretty bulletproof, tested for many edge cases
and a lot of outcomes that are usually passed by.
The project is still getting updates so there can be some bugs
that were not found while testing the program with many kinds
of tests that are targeting the worst possible outcomes.

### The code is still getting changes!

# ABOUT USE OF AI:

I put a lot of work in what I do and what I learn. AI did not
generate any of the code that I have written here, only ideas
and debugging tips. It would be a shame to vibe code such a 
beautiful idea that comes from one of the most wonderful
areas of science... *Mathematics!* 
