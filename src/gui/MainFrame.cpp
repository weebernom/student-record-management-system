#include "MainFrame.h"
#include "../persistence/FileManager.h"
#include <wx/filefn.h>
#include <wx/stdpaths.h>

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Student Record Management System", wxDefaultPosition, wxSize(900, 560)) {

    wxString dataDir = wxStandardPaths::Get().GetExecutablePath();
    dataDir = wxFileName(dataDir).GetPathWithSep() + "data";
    if (!wxDirExists(dataDir)) wxMkdir(dataDir);
    dataFilePath = (dataDir + wxFileName::GetPathSeparator() + "students.dat").ToStdString();

    buildUi();
    FileManager::load(repo, dataFilePath);
    refreshList();

    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
}

MainFrame::~MainFrame() = default;

void MainFrame::buildUi() {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Left: record list.
    listCtrl = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                               wxLC_REPORT | wxLC_SINGLE_SEL);
    listCtrl->InsertColumn(0, "Reg No", wxLIST_FORMAT_LEFT, 110);
    listCtrl->InsertColumn(1, "Name", wxLIST_FORMAT_LEFT, 160);
    listCtrl->InsertColumn(2, "Department", wxLIST_FORMAT_LEFT, 120);
    listCtrl->InsertColumn(3, "Sem", wxLIST_FORMAT_LEFT, 50);
    listCtrl->InsertColumn(4, "CGPA", wxLIST_FORMAT_LEFT, 60);
    listCtrl->InsertColumn(5, "Attendance %", wxLIST_FORMAT_LEFT, 100);
    listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, &MainFrame::onListItemSelected, this);
    mainSizer->Add(listCtrl, 2, wxEXPAND | wxALL, 8);

    // Right: form + actions.
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    auto addField = [&](const wxString& label, wxTextCtrl*& field) {
        rightSizer->Add(new wxStaticText(panel, wxID_ANY, label), 0, wxTOP, 6);
        field = new wxTextCtrl(panel, wxID_ANY);
        rightSizer->Add(field, 0, wxEXPAND | wxTOP, 2);
    };

    addField("Registration No.", regNoField);
    addField("Name", nameField);
    addField("Department", deptField);
    addField("Semester", semesterField);
    addField("CGPA", cgpaField);
    addField("Attendance %", attendanceField);

    rightSizer->AddSpacer(12);
    wxButton* addBtn = new wxButton(panel, wxID_ANY, "Add");
    wxButton* updateBtn = new wxButton(panel, wxID_ANY, "Update");
    wxButton* deleteBtn = new wxButton(panel, wxID_ANY, "Delete");
    wxButton* searchBtn = new wxButton(panel, wxID_ANY, "Search by Reg No");
    wxButton* clearBtn = new wxButton(panel, wxID_ANY, "Clear Form");
    rightSizer->Add(addBtn, 0, wxEXPAND | wxTOP, 4);
    rightSizer->Add(updateBtn, 0, wxEXPAND | wxTOP, 4);
    rightSizer->Add(deleteBtn, 0, wxEXPAND | wxTOP, 4);
    rightSizer->Add(searchBtn, 0, wxEXPAND | wxTOP, 4);
    rightSizer->Add(clearBtn, 0, wxEXPAND | wxTOP, 4);

    rightSizer->AddSpacer(16);
    rightSizer->Add(new wxStaticText(panel, wxID_ANY, "Sort records:"), 0, wxTOP, 4);
    wxButton* sortNameBtn = new wxButton(panel, wxID_ANY, "By Name");
    wxButton* sortCgpaBtn = new wxButton(panel, wxID_ANY, "By CGPA");
    wxButton* sortRegBtn = new wxButton(panel, wxID_ANY, "By Reg No");
    rightSizer->Add(sortNameBtn, 0, wxEXPAND | wxTOP, 4);
    rightSizer->Add(sortCgpaBtn, 0, wxEXPAND | wxTOP, 4);
    rightSizer->Add(sortRegBtn, 0, wxEXPAND | wxTOP, 4);

    addBtn->Bind(wxEVT_BUTTON, &MainFrame::onAdd, this);
    updateBtn->Bind(wxEVT_BUTTON, &MainFrame::onUpdate, this);
    deleteBtn->Bind(wxEVT_BUTTON, &MainFrame::onDelete, this);
    searchBtn->Bind(wxEVT_BUTTON, &MainFrame::onSearch, this);
    clearBtn->Bind(wxEVT_BUTTON, &MainFrame::onClear, this);
    sortNameBtn->Bind(wxEVT_BUTTON, &MainFrame::onSortByName, this);
    sortCgpaBtn->Bind(wxEVT_BUTTON, &MainFrame::onSortByCgpa, this);
    sortRegBtn->Bind(wxEVT_BUTTON, &MainFrame::onSortByRegNo, this);

    mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL, 10);
    panel->SetSizer(mainSizer);

    CreateStatusBar();
    SetStatusText("Ready");
}

void MainFrame::refreshList() {
    listCtrl->DeleteAllItems();
    long row = 0;
    for (const Student& s : repo.all()) {
        long idx = listCtrl->InsertItem(row, s.regNo);
        listCtrl->SetItem(idx, 1, s.name);
        listCtrl->SetItem(idx, 2, s.department);
        listCtrl->SetItem(idx, 3, wxString::Format("%d", s.semester));
        listCtrl->SetItem(idx, 4, wxString::Format("%.2f", s.cgpa));
        listCtrl->SetItem(idx, 5, wxString::Format("%d", s.attendancePercent));
        row++;
    }
    SetStatusText(wxString::Format("%d record(s)", repo.count()));
}

bool MainFrame::readFormIntoStudent(Student& out) {
    if (regNoField->GetValue().IsEmpty() || nameField->GetValue().IsEmpty()) {
        wxMessageBox("Registration No. and Name are required.", "Missing data", wxOK | wxICON_WARNING);
        return false;
    }
    out.regNo = regNoField->GetValue().ToStdString();
    out.name = nameField->GetValue().ToStdString();
    out.department = deptField->GetValue().ToStdString();
    long sem = 1;
    semesterField->GetValue().ToLong(&sem);
    out.semester = static_cast<int>(sem);
    double cgpa = 0.0;
    cgpaField->GetValue().ToDouble(&cgpa);
    out.cgpa = cgpa;
    long att = 100;
    attendanceField->GetValue().ToLong(&att);
    out.attendancePercent = static_cast<int>(att);
    return true;
}

void MainFrame::clearForm() {
    regNoField->Clear();
    nameField->Clear();
    deptField->Clear();
    semesterField->Clear();
    cgpaField->Clear();
    attendanceField->Clear();
}

void MainFrame::onAdd(wxCommandEvent&) {
    Student s;
    if (!readFormIntoStudent(s)) return;
    if (!repo.addStudent(s)) {
        wxMessageBox("A student with this registration number already exists.", "Duplicate", wxOK | wxICON_ERROR);
        return;
    }
    refreshList();
    clearForm();
}

void MainFrame::onUpdate(wxCommandEvent&) {
    Student s;
    if (!readFormIntoStudent(s)) return;
    if (!repo.updateStudent(s)) {
        wxMessageBox("No student found with that registration number.", "Not found", wxOK | wxICON_ERROR);
        return;
    }
    refreshList();
}

void MainFrame::onDelete(wxCommandEvent&) {
    wxString regNo = regNoField->GetValue();
    if (regNo.IsEmpty()) return;
    if (!repo.removeStudent(regNo.ToStdString())) {
        wxMessageBox("No student found with that registration number.", "Not found", wxOK | wxICON_ERROR);
        return;
    }
    refreshList();
    clearForm();
}

void MainFrame::onSearch(wxCommandEvent&) {
    wxString regNo = regNoField->GetValue();
    auto found = repo.findStudent(regNo.ToStdString());
    if (!found) {
        wxMessageBox("No student found with that registration number.", "Not found", wxOK | wxICON_INFORMATION);
        return;
    }
    nameField->SetValue(found->name);
    deptField->SetValue(found->department);
    semesterField->SetValue(wxString::Format("%d", found->semester));
    cgpaField->SetValue(wxString::Format("%.2f", found->cgpa));
    attendanceField->SetValue(wxString::Format("%d", found->attendancePercent));
}

void MainFrame::onClear(wxCommandEvent&) {
    clearForm();
}

void MainFrame::onSortByName(wxCommandEvent&) { repo.sortByName(); refreshList(); }
void MainFrame::onSortByCgpa(wxCommandEvent&) { repo.sortByCgpa(); refreshList(); }
void MainFrame::onSortByRegNo(wxCommandEvent&) { repo.sortByRegNo(); refreshList(); }

void MainFrame::onListItemSelected(wxListEvent& evt) {
    long row = evt.GetIndex();
    wxListItem item;
    item.SetId(row);
    item.SetColumn(0);
    item.SetMask(wxLIST_MASK_TEXT);
    listCtrl->GetItem(item);
    auto found = repo.findStudent(item.GetText().ToStdString());
    if (!found) return;
    regNoField->SetValue(found->regNo);
    nameField->SetValue(found->name);
    deptField->SetValue(found->department);
    semesterField->SetValue(wxString::Format("%d", found->semester));
    cgpaField->SetValue(wxString::Format("%.2f", found->cgpa));
    attendanceField->SetValue(wxString::Format("%d", found->attendancePercent));
}

void MainFrame::onClose(wxCloseEvent& evt) {
    FileManager::save(repo, dataFilePath);
    Destroy();
}
