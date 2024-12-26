// single line comments start with //
/// triple line for document 

// Constants with bee assignment
DAYS_IN_YEAR ::= 365

// Enumeration Constants
enum Days {SUN, MON, TUE, WED, THU, FRI, SAT}

// Functions

fn add_two_ints(x: int, y: int) -> int {

}

// Generics
fn add_two(x: T, y: T) -> T 
    $(T: Numerical) where T.value:Comparable
{

}

struct Rectangle : Shape
    $(T: Numerical) where T.value is Countable
{

}