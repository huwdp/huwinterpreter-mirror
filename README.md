# HuwCode
HuwInterpreter is a hand written interpreter designed to parse and execute HuwCode script.
## Code Example
```
function fac(n)
{
    return factailrec(1, n);
}

function factailrec(acc, n)
{
    if (n < 2)
    {
        return acc;
    }
    return factailrec(n * acc, n - 1);
}
print(fac(14));
```
More examples can be found within the examples folder.

## Documentation
Documentation can be found within the documentation folder.

## License
GNU GENERAL PUBLIC LICENSE Version 3 (GPL 3).
