# Office

Welcome to *The Office*, you will need to write a simple office management program. This will involve structuring the data and and constructing queries and creation. The office is structured as a hierarchy where the boss is at the top and everyone else is below. Each employee can be in charge of other employees and will be ordered from first added to last.

Your program will not only have to support a tree data structure but it will need to support many different queries.

Each employee will have a name, supervisor and subordinates. Unlike most startups, this is not a "flat management" style company. You will need to implement all queries listed in the functions and documentation section.

## Structure

Use the following structures within your code base. You are not allowed to modify the structures.

```
struct employee {
  char* name;
  struct employee* supervisor;
  struct employee* subordinates;
  size_t n_subordinates;
};


struct office {
  struct employee* department_head;
};
```

## Functions and Documentation

```
/**
 * Places an employee within the office, if the supervisor field is NULL
 *  it is assumed the employee will be placed under the next employee that is
 * not superivising any other employee (top-down, left-to-right).
 * 
 * If the supervisor is not NULL, it will be added to the supervisor's list
 *  of employees (make sure the supervisor exists in hierarchy).
 * if the office or employee are null, the function not do anything.
 */
void office_employee_place(struct office* off, struct employee* supervisor,
  struct employee* emp);


/**
 * Fires an employee, removing from the office
 * If employee is null, nothing should occur
 * If the employee does not supervise anyone, they will just be removed
 * If the employee is supervising other employees, the first member of that 
 *  team will replace him.
 */
void office_fire_employee(struct employee* employee);


/**
 * Retrieves the first encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */ 
struct employee* office_get_first_employee_with_name(struct office* office,
  const char* name);

/**
 * Retrieves the last encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */ 
struct employee* office_get_last_employee_with_name(struct office* office,
  const char* name);


/**
 * This function will need to retrieve all employees at a level.
 * A level is defined as distance away from the boss. For example, all 
 * subordinates of the boss are 1 level away, subordinates of the boss's subordinates
 * are 2 levels away.
 * 
 * if office, n_employees or emplys are NULL, your function must do nothing
 * You will need to provide an allocation for emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_at_level(struct office* office, size_t level,
  struct employee** emplys, size_t* n_employees);

/**
 * Will retrieve a list of employees that match the name given
 * If office, name, emplys or n_employees is NULL, this function should do nothing
 * 
 * if office, n_employees, name or emplys are NULL, your function must do nothing
 * You will need to provide an allocation to emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_by_name(struct office* office, const char* name,
  struct employee** emplys, size_t* n_employees);

/**
 * You will traverse the office and retrieve employees using a postorder traversal
 * If off, emplys or n_employees is NULL, this function should do nothing
 *
 * You will need to provide an allocation to emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_postorder(struct office* off, struct employee** emplys,
  size_t* n_employees);

/**
 * The office disbands
 * (You will need to free all memory associated with employees attached to
 *   the office and the office itself)
 */
void office_disband(struct office* office);
```

## Tips

- Consider using a queue to traverse the office
- Consider how you will deallocate all employees in your office, consider what traversal you could use to deallocate the tree

## ASCII Examples

We will be using the current tree as our default tree

```
                                 +--+
                                 |1 |
                   +-----------+----+---+-----------+
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                 +-v+        +-v+      +v-+        +v-+
                 |2 |        |3 |      |4 |        |5 |
 +-------+-----+----+      +---++      ++-+--+     +--+
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
+v-+   +-v+  +-v+        +-v+ +v-+    +-v+ +-v+
|6 |   |7 |  |8 |        |9 | |10|    |11| |12|
+--+   +--+  +--+      +----+ +--+    +--+ +--+
                       |      |
                       |      |
                       |      |
                      +v-+  +-v+
                      |13|  |14|
                      +--+  +--+
```

### Example 1

Call site

```
char* name = malloc(sizeof(char)*40);
strcpy(name, "Jeff");
struct employee emp = { .name = name, .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0  } ;
struct employee* employee = &emp;
office_employee_place(office, NULL, employee)
                                 +--+
                                 |1 |
                   +-----------+----+---+-----------+
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                 +-v+        +-v+      +v-+        +v-+
                 |2 |        |3 |      |4 |        |5 |
 +-------+-----+----+      +---++      ++-+--+     +--+
 |       |     |           |   |        |    |     |
 |       |     |           |   |        |    |     |
 |       |     |           |   |        |    |     |
 |       |     |           |   |        |    |     |
+v-+   +-v+  +-v+        +-v+ +v-+    +-v+ +-v+   *v-*
|6 |   |7 |  |8 |        |9 | |10|    |11| |12|   |15|
+--+   +--+  +--+      +----+ +--+    +--+ +--+   *--*
                       |      |
                       |      |
                       |      |
                      +v-+  +-v+
                      |13|  |14|
                      +--+  +--+
```

### Example 2

Call site

```
office_employee_place(office, ten, employee)
                                 +--+
                                 |1 |
                   +-----------+----+---+-----------+
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                 +-v+        +-v+      +v-+        +v-+
                 |2 |        |3 |      |4 |        |5 |
 +-------+-----+----+      +---++      ++-+--+     +--+
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
+v-+   +-v+  +-v+        +-v+ +v-+    +-v+ +-v+
|6 |   |7 |  |8 |        |9 | |10|    |11| |12|
+--+   +--+  +--+      +----+ +--+--+ +--+ +--+
                       |      |     |
                       |      |     |
                       |      |     |
                      +v-+  +-v+  *-v*
                      |13|  |14|  |15|
                      +--+  +--+  *--*
```

### Example 3

Call Site

```
office_fire_employee(nine);
                                 +--+
                                 |1 |
                   +-----------+----+---+-----------+
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                   |           |        |           |
                 +-v+        +-v+      +v-+        +v-+
                 |2 |        |3 |      |4 |        |5 |
 +-------+-----+----+      +---++      ++-+--+     +--+
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
 |       |     |           |   |        |    |
+v-+   +-v+  +-v+        +-v+ +v-+    +-v+ +-v+
|6 |   |7 |  |8 |        |13| |10|    |11| |12|
+--+   +--+  +--+        +--+ +--+    +--+ +--+
                              |
                              |
                              |
                            +-v+
                            |14|
                            +--+
```

### Example 4

Call site

```
struct employee* emplys = NULL;
size_t n_emps = 0;
office_get_employees_at_level(office, 2, &emplys, &n_emps);
```

Visualisation

```
+v-+ +-v+ +-v+ +-v+ +v-+ +-v+ +-v+
|6 | |7 | |8 | |9 | |10| |11| |12|
+--+ +--+ +--+ +--+ +--+ +--+ +--+
```

### Example 5

Call Site

```
struct employee* emplys = NULL;
size_t n_emps = 0;
office_get_employees_postorder(office, &emplys, &n_emps);
```

Visualisation

```
+--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+
|6 | |7 | |8 | |2 | |13| |9 | |14| |10| |3 | |11| |12| |4 | |5 | |1 |
+--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+
```

### Run the Program

``` shell
make all
```

### Clean the Program

``` shell
make clean
```

### Sample Output

``` shell
example1:
Employee1

example2:
0
Employee2

example3:
Employee1
Employee2
address expect 0x6030000017b0
n_sub expect 1
Employee3

example4:
Employee1
Employee2
Employee3

example5:
sup of 2 Employee1

example6:
function output address is 0x606000000400
expected address is 0x606000000400
-------------------------
emp1 0x602000000170
emp2 0x6060000003e0
emp3 0x6030000019f0
emp4 0x603000001a20
emp5 0x606000000400
emp6 0x603000001a50

example7:
function output address is 0x603000001ae0
expected address is 0x603000001ae0

example8:
2

example9:
Employee2
Employee5

example10:

example11:
Employee4
Employee3
Employee2
Employee6
Employee5
Employee1

example12:
Employee3
Employee4
```

