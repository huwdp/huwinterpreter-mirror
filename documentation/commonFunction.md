# Common functions
## Print
print(Node, Node, ...)
Print function prints all output of the Node arguments.
### Example
```
print("Hello World!")
```

## Scan
scan(Node, Node, …)
Scan function asks and reads user input for each node. Each node’s value is assigned with the user input via the terminal.

## Not
not(Node)
Returns an inverted value based on argument.
Inverts the Node’s value.

## Command
command(Node, Node, …)
Command function executes it’s arguments in the system’s terminal. This function is supported on Linux, Mac OS and Windows. This function has only been tested on Linux.
