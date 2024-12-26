// single line comments start with //
/// documentation comments, support markdown notation

// Functions

fn add_two_ints(x: int, y: int) -> int {

}

// Generics
fn add_two(x: T, y: T) -> T 
    $(T: Numerical) where T.value:Comparable
{

}

struct Rectangle : Shape
    $(T: Numerical) where T.value:Countable
{

}