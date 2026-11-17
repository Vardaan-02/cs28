# AI Lab Test -- Complete Solutions

**Date:** 17 November 2026

------------------------------------------------------------------------

# Q1. Blocks World -- Predicate Representation and Goal Stack

## 1. Predicates

The following predicates are used:

  Predicate      Meaning
  -------------- -----------------------------------
  `OnTable(x)`   Block `x` is on the table.
  `On(x, y)`     Block `x` is on block `y`.
  `Clear(x)`     No block is placed on top of `x`.
  `Holding(x)`   The robot is holding block `x`.
  `HandEmpty`    The robot's hand is empty.

## 2. STRIPS action definitions

### PICKUP(x)

**Preconditions** - `OnTable(x)` - `Clear(x)` - `HandEmpty`

**Add effects** - `Holding(x)`

**Delete effects** - `OnTable(x)` - `Clear(x)` - `HandEmpty`

### PUTDOWN(x)

**Precondition** - `Holding(x)`

**Add effects** - `OnTable(x)` - `Clear(x)` - `HandEmpty`

**Delete effects** - `Holding(x)`

### STACK(x, y)

**Preconditions** - `Holding(x)` - `Clear(y)`

**Add effects** - `On(x, y)` - `Clear(x)` - `HandEmpty`

**Delete effects** - `Holding(x)` - `Clear(y)`

### UNSTACK(x, y)

**Preconditions** - `On(x, y)` - `Clear(x)` - `HandEmpty`

**Add effects** - `Holding(x)` - `Clear(y)`

**Delete effects** - `On(x, y)` - `Clear(x)` - `HandEmpty`

## 3. Initial state

Blocks A, B, C and D are all on the table. Each block is clear, and the
robot's hand is empty.

\[ I = { OnTable(A), OnTable(B), OnTable(C), OnTable(D), Clear(A),
Clear(B), Clear(C), Clear(D), HandEmpty } \]

## 4. Goal state

-   Block A must be placed on block C.
-   Block D must be placed on block B.

\[ G = {On(A,C), On(D,B)} \]

## 5. Goal Stack Planning

One valid action sequence is:

    Step Action          Result
  ------ --------------- ----------------
       1 `PICKUP(A)`     Robot holds A.
       2 `STACK(A, C)`   A is on C.
       3 `PICKUP(D)`     Robot holds D.
       4 `STACK(D, B)`   D is on B.

### Goal-stack execution order

The resulting execution sequence is:

``` text
PICKUP(A)
STACK(A,C)
PICKUP(D)
STACK(D,B)
```

### Final state

\[
```{=tex}
\begin{aligned}
S_f = \{&
On(A,C), On(D,B),\\
&OnTable(B), OnTable(C),\\
&Clear(A), Clear(D), HandEmpty
\}
\end{aligned}
```
\]

Both required goal predicates are true:

\[ On(A,C) `\land `{=tex}On(D,B) \]

Therefore, the goal state is achieved.

------------------------------------------------------------------------

# Q2. Knowledge-Based System -- First-Order Logic

A university wants to identify students eligible for a research
fellowship.

## Predicates

  Predicate            Meaning
  -------------------- ------------------------------------------
  `Student(x)`         x is a student.
  `Course(x)`          x is a course.
  `Studies(x, y)`      x studies course y.
  `Passed(x, y)`       x has passed course y.
  `Professor(x)`       x is a professor.
  `Supervises(x, y)`   x supervises y.
  `Qualified(x)`       x is qualified for research.
  `Researcher(x)`      x is a researcher.
  `Eligible(x)`        x is eligible for a research fellowship.

## Given facts

``` text
Student(Ravi)
Student(Anu)
Course(AI)
Course(ML)
Studies(Ravi, AI)
Passed(Ravi, AI)
Studies(Anu, ML)
Professor(DrSharma)
Supervises(DrSharma, Ravi)
```

## (i) Represent all four university policies using FOL

### Policy 1: Every student studies at least one course.

\[ `\boxed{
\forall x\left(Student(x)\rightarrow
\exists y(Course(y)\land Studies(x,y))\right)
}`{=tex} \]

For every student x, there exists at least one course y that x studies.

### Policy 2: A student who studies a course and passes that same course is qualified for research.

\[ `\boxed{
\forall x\forall y\left(
\begin{aligned}
&(Student(x)\land Course(y)\land\\
&Studies(x,y)\land Passed(x,y))
\end{aligned}
\rightarrow Qualified(x)
\right)
}`{=tex} \]

A student becomes qualified if they study and pass the same course.

### Policy 3: A qualified student supervised by a professor is considered a researcher.

\[ `\boxed{
\forall x\forall y\left(
(Qualified(x)\land Professor(y)\land Supervises(y,x))
\rightarrow Researcher(x)
\right)
}`{=tex} \]

A qualified student becomes a researcher if a professor supervises them.

### Policy 4: Every researcher is eligible for a research fellowship.

\[ `\boxed{
\forall x(Researcher(x)\rightarrow Eligible(x))
}`{=tex} \]

Every researcher is eligible for the fellowship.

## (ii) Does the given statement imply that every student studies the same course? Can we conclude that every student studies AI?

Given statement:

\[ `\forall `{=tex}x`\left`{=tex}(Student(x)`\rightarrow`{=tex}
`\exists `{=tex}y(Course(y)`\land `{=tex}Studies(x,y))`\right`{=tex}) \]

### Does every student study the same course?

**No.**

The existential quantifier (`\exists `{=tex}y) is inside the universal
quantifier (`\forall `{=tex}x). This means that for every student, there
exists at least one course that the particular student studies. The
course may be different for different students.

For example: - Ravi studies AI. - Anu studies ML.

Both satisfy the given statement, even though they study different
courses.

### Can we conclude that every student studies AI?

**No.**

The statement guarantees only that every student studies at least one
course. It does not specify which course.

The knowledge base contains:

\[ Studies(Ravi,AI) \]

\[ Studies(Anu,ML) \]

Therefore, we cannot conclude:

\[ `\boxed{
\forall x(Student(x)\rightarrow Studies(x,AI))
}`{=tex} \]

### Conclusion

1.  Every student studies at least one course.
2.  Different students can study different courses.
3.  We cannot conclude that every student studies AI.

## (iii) Determine whether Eligible(Ravi) can be derived

We use **Forward Chaining**.

Forward chaining starts with known facts and repeatedly applies rules to
generate new facts until the required conclusion is obtained.

### Step 1: Initial knowledge base

``` text
Student(Ravi)
Student(Anu)
Course(AI)
Course(ML)
Studies(Ravi, AI)
Passed(Ravi, AI)
Studies(Anu, ML)
Professor(DrSharma)
Supervises(DrSharma, Ravi)
```

### Step 2: Apply Policy 2 -- Derive Qualified(Ravi)

Rule:

\[
```{=tex}
\begin{aligned}
&(Student(x)\land Course(y)\land\\
&Studies(x,y)\land Passed(x,y))\\
&\qquad\rightarrow Qualified(x)
\end{aligned}
```
\]

Substitute:

\[ x=Ravi,`\quad `{=tex}y=AI \]

Check the facts:

-   `Student(Ravi)` -- True
-   `Course(AI)` -- True
-   `Studies(Ravi, AI)` -- True
-   `Passed(Ravi, AI)` -- True

All conditions are satisfied. Therefore:

\[ `\boxed{Qualified(Ravi)}`{=tex} \]

### Step 3: Apply Policy 3 -- Derive Researcher(Ravi)

Rule:

\[
```{=tex}
\begin{aligned}
&(Qualified(x)\land Professor(y)\land\\
&Supervises(y,x))\\
&\qquad\rightarrow Researcher(x)
\end{aligned}
```
\]

Substitute:

\[ x=Ravi,`\quad `{=tex}y=DrSharma \]

Check the facts:

-   `Qualified(Ravi)` -- True
-   `Professor(DrSharma)` -- True
-   `Supervises(DrSharma, Ravi)` -- True

All conditions are satisfied. Therefore:

\[ `\boxed{Researcher(Ravi)}`{=tex} \]

### Step 4: Apply Policy 4 -- Derive Eligible(Ravi)

Rule:

\[ Researcher(x)`\rightarrow `{=tex}Eligible(x) \]

Substitute:

\[ x=Ravi \]

Since `Researcher(Ravi)` has already been derived:

\[ `\boxed{Eligible(Ravi)}`{=tex} \]

### Step 5: Forward-chaining derivation table

    Step Applied rule   Newly generated fact
  ------ -------------- ----------------------
       1 Policy 2       `Qualified(Ravi)`
       2 Policy 3       `Researcher(Ravi)`
       3 Policy 4       `Eligible(Ravi)`

### Step 6: Final inference chain

``` text
Given facts:
Student(Ravi)
Course(AI)
Studies(Ravi, AI)
Passed(Ravi, AI)

             |
             | Policy 2
             v

       Qualified(Ravi)

             |
             | Policy 3
             | Professor(DrSharma)
             | Supervises(DrSharma, Ravi)
             v

       Researcher(Ravi)

             |
             | Policy 4
             v

        Eligible(Ravi)
```

Hence:

\[ `\boxed{KB\models Eligible(Ravi)}`{=tex} \]

**Yes, Ravi is eligible for a research fellowship.**

### Important observation about Anu

The knowledge base contains `Studies(Anu, ML)`, but it does not contain
`Passed(Anu, ML)`. Therefore, we cannot derive `Qualified(Anu)` using
Policy 2, and consequently cannot derive `Researcher(Anu)` or
`Eligible(Anu)` from the given facts and rules.

------------------------------------------------------------------------

# Final Answer Summary

  -----------------------------------------------------------------------
  Question                            Result
  ----------------------------------- -----------------------------------
  Q1                                  Goal achieved: A on C and D on B.

  Q2 (i)                              All four university policies
                                      represented using FOL.

  Q2 (ii)                             No, students need not study the
                                      same course; we cannot conclude
                                      that everyone studies AI.

  Q2 (iii)                            Yes, `Eligible(Ravi)` is derived
                                      using forward chaining.
  -----------------------------------------------------------------------

**End of solutions.**