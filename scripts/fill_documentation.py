import copy
import docx

SRC = r"D:\SEM-3[NEW]\my own\dsa\2025581_Student Record Management System.docx"

d = docx.Document(SRC)
paras = d.paragraphs


def set_text(p, text):
    runs = p.runs
    if not runs:
        p.add_run(text)
        return
    runs[0].text = text
    for r in runs[1:]:
        r.text = ""


def insert_clone(template_p, after_p, text):
    """Deep-copy template_p's XML (style/numbering/indent level), insert it
    right after after_p, set its text, and return the new Paragraph (so it
    can be chained as the next after_p for sequential inserts)."""
    new_el = copy.deepcopy(template_p._p)
    after_p._p.addnext(new_el)
    new_p = docx.text.paragraph.Paragraph(new_el, after_p._parent)
    set_text(new_p, text)
    return new_p


def clone_after(p, text):
    """Shorthand for inserting a clone of p's own style right after itself."""
    return insert_clone(p, p, text)


# ---- Title ----
set_text(paras[2], "Semester Project Title: Student Record Management System")

# ---- Student Details table ----
members = [
    ("Muhammad Momin", "2025581", "BS(SE)"),
    ("Qasim Malik", "2025597", "[Confirm degree]"),
    ("Noor Uddin Malik", "2025376", "[Confirm degree]"),
    ("Muhammad Furqan", "2025514", "[Confirm degree]"),
]
table0 = d.tables[0]
for i, (name, reg, degree) in enumerate(members, start=1):
    row = table0.rows[i]
    row.cells[0].text = f"Student-{i}"
    row.cells[1].text = name
    row.cells[2].text = reg
    row.cells[3].text = degree

# ---- Main Features (paras 7-11 are bullets; add a 6th) ----
features = [
    "Desktop GUI application (built with C++ and wxWidgets)",
    "User roles: Admin, Faculty, and Student with role-based access",
    "Add, update, delete, and search student records",
    "Record and view attendance and grades",
    "Generate and sort reports (by name, GPA, registration number)",
    "Persistent local data storage (file handling)",
]
for idx, text in zip(range(7, 12), features[:5]):
    set_text(paras[idx], text)
clone_after(paras[11], features[5])

# ---- Types of Users & Requirements ----
# para15 header + paras16-21 (6 bullets) -> Admin
set_text(paras[15], "Admin")
admin_reqs = [
    "Will be able to log in with admin credentials.",
    "Will be able to add a new student record.",
    "Will be able to update or delete an existing student record.",
    "Will be able to add or remove faculty accounts.",
    "Will be able to search for any student record by registration number.",
    "Will be able to generate and sort reports of all students (by name, CGPA, reg. no.).",
]
for idx, text in zip(range(16, 22), admin_reqs):
    set_text(paras[idx], text)

# para22 was the "Captain" placeholder line -> turn into "Faculty" header,
# then add Faculty's requirement bullets (cloned from an admin bullet style).
set_text(paras[22], "Faculty")
faculty_reqs = [
    "Will be able to log in with faculty credentials.",
    "Will be able to record and update attendance for their students.",
    "Will be able to record and update grades for their students.",
    "Will be able to search for a specific student's record by registration number.",
]
bullet_template = paras[16]  # ilvl 1 bullet style, shared by this section
anchor = paras[22]
for text in faculty_reqs:
    anchor = insert_clone(bullet_template, anchor, text)

# para23 was the "Admin (Uber ...)" placeholder line -> turn into "Student" header
set_text(paras[23], "Student")
student_reqs = [
    "Will be able to log in with student credentials.",
    "Will be able to view their own academic record (grades, attendance, CGPA).",
    "Will not be able to view or edit any other student's record.",
]
anchor = paras[23]
for text in student_reqs:
    anchor = insert_clone(bullet_template, anchor, text)

# ---- Requirements Breakdown ----
header_template = paras[26]  # ilvl 0, numId 22
bullet_template2 = paras[27]  # ilvl 1, numId 22


def add_feature(after_p, title, reqs):
    h = insert_clone(header_template, after_p, title)
    anchor = h
    for r in reqs:
        anchor = insert_clone(bullet_template2, anchor, r)
    return anchor


set_text(paras[26], "1. Add Student Record:")
feat1_reqs = [
    "Take input of registration number, name, department, semester, CGPA, and attendance percentage.",
    "Check the hash table to ensure a student with that registration number does not already exist.",
    "Insert the record at the end of the linked list, index it in the hash table, then save to file.",
]
for idx, text in zip(range(27, 30), feat1_reqs):
    set_text(paras[idx], text)

set_text(paras[30], "2. Search Student Record:")
feat2_reqs = [
    "Take the registration number as input.",
    "Look it up directly in the hash table for O(1) average-time retrieval.",
    "Display the matched student's full record in the form fields.",
]
set_text(paras[31], feat2_reqs[0])
last = paras[31]
for text in feat2_reqs[1:]:
    last = insert_clone(bullet_template2, last, text)

last = add_feature(last, "3. Update Student Record:", [
    "Locate the record via the hash table using its registration number.",
    "Overwrite the modified fields (name, department, semester, CGPA, attendance).",
    "Persist the updated list to file.",
])
last = add_feature(last, "4. Delete Student Record:", [
    "Locate the record via the hash table using its registration number.",
    "Remove the corresponding node from the linked list.",
    "Remove the entry from the hash table and persist the updated list to file.",
])
last = add_feature(last, "5. Sort & Generate Report:", [
    "Let the user choose a sort key: name, CGPA, or registration number.",
    "Run merge sort on the linked list using the chosen comparison.",
    "Rebuild the hash table indices after reordering, then display the sorted list.",
])
last = add_feature(last, "6. Persistent File Storage (Save/Load):", [
    "On save, serialize every record in the linked list to a line in a data file.",
    "On startup, read the file and reconstruct both the linked list and the hash table.",
])

# ---- Features to Coding Matrix (Table 1) ----
table1 = d.tables[1]
feature_matrix = [
    ("Add Student Record", "Linked List, Hash Table", "Insertion", "O(1) avg insert"),
    ("Search Student Record", "Hash Table", "Lookup", "O(1) average"),
    ("Update Student Record", "Hash Table, Linked List", "Traversal + Update", "O(1) average"),
    ("Delete Student Record", "Hash Table, Linked List", "Deletion", "O(1) avg / O(n) worst case"),
    ("Sort & Generate Report", "Linked List, Merge Sort", "Sorting + Traversal", "O(n log n)"),
    ("Persistent File Storage", "File Handling", "Read / Write", "O(n)"),
]
for i, (name, concept, op, cx) in enumerate(feature_matrix):
    row_idx = i + 1
    if row_idx >= len(table1.rows):
        table1.add_row()
    row = table1.rows[row_idx]
    row.cells[0].text = str(i + 1)
    row.cells[1].text = name
    row.cells[2].text = concept
    row.cells[3].text = op
    row.cells[4].text = cx
    row.cells[5].text = "TBD (after implementation)"
    row.cells[6].text = "TBD (after implementation)"
    row.cells[7].text = "TBD (after implementation)"

d.save(SRC)
print("Saved: title, student table, features, user types, requirements breakdown, coding matrix.")
