# Array funcitons

## Array
array()
Array funciton returns an array. Array funciton requires 0 arguments.

Associative Array is an abstact collection of key, value pairs. The internal implementation of the array within HuwCode is implemented with std::unordered_map.

## ArrayGet
arrayGet(array, key)
ArratGet returns the value of the associative array by the key. ArrayGet requires 2 arguments.

Alternatively an element can be access by the key in an array by using square brackets. E.g. array["element1"];.

## ArraySet
arraySet(array, key, value)
ArraySet function sets the key in the associative array with the value. ArraySet funciton requires 3 arguments.

Alternatively an element can be set in an array by the key by using square brackets. E.g. array["element1"] = "Hello World!";

## ArrayUnset
arrayUnset(array, key)
ArrayUnset funciton removes the value in the associative array by the key.

## Example
```
let i = 0;
let list = array();

/* Add items to the hash table */
while (i < 10)
{
    arraySet(list, i, "Item " + i);
    i++;
}

/* Print items */
let i = 0;
while (i < 10)
{
    print(arrayGet(list, i));
    i++;
}

print("Array count: " + count(list));
```
