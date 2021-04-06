# Setfile
My attempt at making a simplified config file type in Python.

Hopefully this will convince people that I'm still doing work on my Discord scraper.
I've just been trying to figure out a way to make it more user-friendly without adding a GUI.

# Syntax
```
// This is a single-line comment.
	// You can have them offset like this.
		// It doesn't matter how offset they are as long as they're on their own line.
	
// I might end up adding a multi-line comment method, but so far I feel that's a bit overkill.
// Open up a new issue on this if you're really needing a multi-line comment method.

// Declaring a variable is easy, do not use quotation marks unless you want them in the variable:
Variable Name = Variable Value

// Make sure that there's one space between the equals sign.
// Declaring a boolean is just as easy as declaring a variable:
True Boolean = TRUE
False Boolean = FALSE

// All-caps is used to differentiate the variable value as either a string or a boolean.
// This does not apply to the variable name itself, you can have a variable name TRUE or FALSE.

// Declaring a numerical value is easy too:
Number 1 = 1024
Number 2 = 1048576
Number 3 = 0001024

// Having numbers in our variable names are not an issue, variable names are always strings.
// Trailing zeroes will be removed from the final output, so be careful about that.

// Now we need a way to assign multiple values to a single variable.
// This is how we assign an array:
Array 1 => [Value 1, Value 2, Value 3]

// Each value in the array will be checked to determine if its a number or a boolean value.
// The rules for these are the same as for any variable.
```

# Details

### Valid data types:
**String**: Text of any kind, the script accepts any valid UTF-8 encoded input. Emotes/emojis are very broken right now.

**Number**: A string that only contains numerical characters (0 to 9).

**Boolean**: A string that is either TRUE or FALSE. This is case-sensitive to make boolean stand out from everything else.

**Array**: A collection of strings, numbers, and booleans.

### Declarations:
**Name = Value**: The way we declare a variable. No need to wrap the name or value in quotes unless we want quotes in them. The spacing in ` = ` is important.

**Name => [Values, ...]**: The way we declare an array. No need to wrap the name or values in quotes unless we want quotes in them. The spacing in ` => ` and `, ` are important.


# Simple usage:
```python
from setfile import Setfile

if __name__ == '__main__':
	try:
		set_file = Setfile('filename.set')
		set_file.parse()
		
		print(set_file.items)
	
	except Exception as ex:
		print(ex)
```