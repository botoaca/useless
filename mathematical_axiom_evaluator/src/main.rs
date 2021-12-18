/*
    In mathematics or logic, an axiom is an unprovable rule or first principle
    accepted as true because it is self-evident or particularly useful.
    "Nothing can both be and not be at the same time and in the same respect"
    is an example of an axiom.
*/

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        println!("Usage: {} <expression>", args[0]);
        return;
    }

    match meval::eval_str(&args[1]) {
        Ok(result) => {
            if result.to_string() == args[1] {
                println!("\"{}\" is an axiom.", args[1]);
            } else {
                println!("\"{}\" is not an axiom.", args[1]);
            }
        },
        Err(err) => println!("{}", err)
    }
}