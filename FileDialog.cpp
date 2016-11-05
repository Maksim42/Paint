#include "stdafx.h"
#include "FileDialog.h"

FileDialog *FileDialog::instance = NULL;

void FileDialog::Init(HWND hWnd) {
	if (FileDialog::instance == NULL) {
		instance = new FileDialog(hWnd);
	}
}

bool FileDialog::ShowOpenFileDialog() {
	dialog.lpstrTitle = _T("Load file");
	dialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return GetOpenFileName(&dialog);
}

bool FileDialog::ShowSaveFileDialog()
{
	dialog.lpstrTitle = _T("Save file");
	dialog.Flags = OFN_CREATEPROMPT;

	return GetSaveFileName(&dialog);
}

FileDialog::FileDialog(HWND hWnd) {
	file_name = new TCHAR[STRING_LENGTH];
	ZeroMemory(&dialog, sizeof(dialog));

	dialog.lStructSize = sizeof(OPENFILENAME);
	dialog.hwndOwner = hWnd;
	dialog.lpstrDefExt = 0;
	dialog.lpstrFile = file_name;
	dialog.lpstrFile[0] = '\0';
	dialog.nMaxFile = STRING_LENGTH;
	dialog.lpstrFilter = _T("Metafile (*.emf)\0*.emf\0Все файлы (*.*)\0*.*\0");
	dialog.nFilterIndex = 1;
	dialog.lpstrInitialDir = _T(".\\");
	dialog.lpstrDefExt = 0;
}


FileDialog::~FileDialog() {
	delete file_name;
	delete dialog.lpstrFilter;
	delete dialog.lpstrInitialDir;
}
