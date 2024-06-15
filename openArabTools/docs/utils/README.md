# Library utilities

### RunConcurrentlyCallback
Function type. Returns `void`, takes in `const uint8_t` as ID of thread and `const uint64_t` as ID of job.

### init()
Initializes the library (any errors are printed to the screen and terminate the program)
- Parameters: none
- Returns: nothing

### terminate()
- Disables the library.
- Parameters: none
- Returns: nothing

### isLibInit()
Returns whether or not the library is initialized.
- Parameters: none
- Returns: true if library initialized, false otherwise

### buildID()
Returns build ID of current version.
- Parameters: none
- Returns: build id as integer

| Build Id | Version |
| -- | -- |
| 0 | Pre-0.1.0 |
| 1 | 0.1.0 |
| 2 | in development |

### version()
Returns version and copyright info.
- Parameters: none
- Returns: string literal (const char*) with version and copyright information

### NORMAL255(x)
Converts a number in range 0-255 to range 0-1

### NORMAL1023(x)
Converts a number in range 0-1023 to range 0-1

### train
Alias for `auto`

# Utilities (namespace Utils)

### sleep
Sleeps for some time.
- Parameters: aMs, milliseconds to sleep
- Returns: bool, always true for compatibility

### isEmpty
Returns if provided string is empty
- Parameters: aString (of type `const char*` OR `const std::string&`)
- Returns: bool, is string empty (true) of or (false)

### nonEmpty
Exact opposite of `isEmpty`, returns if string is not empty
- Parameters: aString (of type `const char*` OR `const std::string* const*`)
- Returns: Pointer to provided string if not empty, `nullptr` otherwise.

### runConcurrently
Runs functions on *all* threads
- Parameters: `uint64_t` aCount (times to run the function), `bool` aWaitReturn (whether or not to wait all functions done before returning), `RunConcurrentlyCallback` aFunction (function to call)
- Returns: nothing

### getRandomBool
Returns a random boolean
- Parameters: None
- Returns: random bool

### ScopedTimer
Class to measure time taken to execute a scope.
Prints time automatically on destruction.
```
{
ScopedTimer st("ScopeName");
...
}
```
