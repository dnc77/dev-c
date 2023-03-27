# testfaze

## Summary:
This is a very simple test case library that was mocked up quickly in favour of looking around for what was available.

## How it works:
1. Create a named test suite with `tfzCreate()`.
2. Call your `assert` functions as needed.
3. Display the results with `tfzShowResults()`.
4. Destroy the suite with `tfzDestroy()`.

## General `assert` function paramters:
| Parameter             | Purpose                                                |
| :-------------        |:-------------                                          |
| 1. `TFSuite suite`    | a test suite created with `tfzCreate()`.               |
| 2. `anytype res`      | the result obtained for the test.                      |
| 3. `anytype exp`      | the expected result from the test.                     |
| 4. `uint8_t noMetric` | true to not consider result of test in suite results.  |

