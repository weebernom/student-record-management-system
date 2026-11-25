#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../core/StudentRepository.h"

class MainFrame : public wxFrame {
public:
    MainFrame();
    ~MainFrame() override;

private:
    StudentRepository repo;
    std::string dataFilePath;

    wxListCtrl* listCtrl = nullptr;
    wxTextCtrl* regNoField = nullptr;
    wxTextCtrl* nameField = nullptr;
    wxTextCtrl* deptField = nullptr;
    wxTextCtrl* semesterField = nullptr;
    wxTextCtrl* cgpaField = nullptr;
    wxTextCtrl* attendanceField = nullptr;

    void buildUi();
    void refreshList();
    bool readFormIntoStudent(Student& out);
    void clearForm();

    void onAdd(wxCommandEvent& evt);
    void onUpdate(wxCommandEvent& evt);
    void onDelete(wxCommandEvent& evt);
    void onSearch(wxCommandEvent& evt);
    void onClear(wxCommandEvent& evt);
    void onSortByName(wxCommandEvent& evt);
    void onSortByCgpa(wxCommandEvent& evt);
    void onSortByRegNo(wxCommandEvent& evt);
    void onListItemSelected(wxListEvent& evt);
    void onClose(wxCloseEvent& evt);
};
