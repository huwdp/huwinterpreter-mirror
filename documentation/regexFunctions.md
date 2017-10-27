# Regex functions

## Regex search
regexSearch(text, regex)
Regex search function returns true if the regular expression has at least one match, the function returns false otherwise.
### Example
```
regexSearch("Roses are #ff0000", "#([a-f0-9]{2})");
```

## Regex replace
regexReplace(text, regex, )
Regex replace function matches and replaces any matched text with the regex substitution.
### Example
```
regexReplace("Quick brown fox", "a|e|i|o|u", "[$&]");
```

## Regex match
regexMatch(text, regex)
Regex search function returns an associative array (Hash Table) with all regular expression matches.
### Example
```
regexMatch("huwcode.hco", "[a-z]+\\.txt");
```
