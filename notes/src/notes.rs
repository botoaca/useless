use std::fs;

fn make_path(name: &String) -> String {
    String::from(format!("notes/{}.txt", name))
}

pub fn create_note(name: String) {
    fs::File::create(make_path(&name)).expect("Unable to create file");
    open_note(name);
}

pub fn open_note(name: String) {
    let path = make_path(&name);
    let mut data = fs::read_to_string(&path).expect("Unable to read file");
    println!("{}", data);
    std::io::stdin().read_line(&mut data).unwrap();
    fs::write(path, data).expect("Unable to write file");
}

pub fn display_note(name: String) {
    super::draw::draw_box(
        String::from(
            format!(
                "Contents of \'{}\':\n\n{}",
                name,
                fs::read_to_string(make_path(&name)).expect("Unable to read file")
            )
        )
    );
}

pub fn delete_note(name: String) {
    fs::remove_file(make_path(&name)).expect("Unable to delete file");
}

pub fn list_notes() {
    let notes = fs::read_dir("notes").expect("Unable to read directory");
    let mut list: String = String::from("List of notes:\n\n");
    for note in notes {
        list.push_str(&format!("{}\n", note.unwrap().path().display()));
    }
    super::draw::draw_box(list);
}