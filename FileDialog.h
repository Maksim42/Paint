#pragma once
#include <CommDlg.h>

#define STRING_LENGTH 256

class FileDialog
{
public:
	static FileDialog *instance;
	TCHAR *file_name;

	static void Init(HWND hWnd);
	bool ShowOpenFileDialog();
	bool ShowSaveFileDialog();
private:
	OPENFILENAME dialog;

	FileDialog(HWND hWnd);
	~FileDialog();
};

