mod draw;
mod notes;

fn main() {
    let notes_dir = std::path::Path::new("notes");
    if !notes_dir.exists() {
        std::fs::create_dir("notes").unwrap();
    }

    let args: Vec<String> = std::env::args().collect();

    let intro = || {
        draw::draw_box(String::from(
            &format!(
                "Welcome to Notes!\n\nUsage: {}\n    + \'create <name>\'\n    + \'open <name>\'\n    + \'display <name\'\n    + \'delete <name>\'\n    + \'list\'", args[0]
            )
        ));
    };

    match args.len() {
        2 => {
            if args[1] == "list" {
                notes::list_notes();
            } else { intro() }
        }
        3 => {
            if args[1] == "create" {
                notes::create_note(String::from(&args[2]));
            } else if args[1] == "open" {
                notes::open_note(String::from(&args[2]));
            } else if args[1] == "display" {
                notes::display_note(String::from(&args[2]));
            } else if args[1] == "delete" {
                notes::delete_note(String::from(&args[2]));
            } else { intro() }
        }   
        _ => intro()
    }
}