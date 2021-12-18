pub fn draw_box(s: String) {
    let mut len: usize = 0;

    for line in s.lines() {
        len = len.max(line.len());
    }
    
    print!("┌");
    for _i in 1..=len + 2 { print!("─"); }
    print!("┐");

    for line in s.lines() {
        print!("\n│ ");
        print!("{}", line);
        if line.len() < len {
            for _i in 0..len - line.len() { print!(" "); }
        }
        print!(" │");
    }
    print!("\n");
    
    print!("└");
    for _i in 0..=len + 1 { print!("─"); }
    print!("┘");
}