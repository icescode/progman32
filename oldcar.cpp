//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("oldcar.res");
USEFORM("U_Main.cpp", frmMain);
USEFORM("U_Group.cpp", frmGroup);
USEFORM("U_CreateGroup.cpp", frmCreateGroup);
USEFORM("U_AddItem.cpp", frmAddItem);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
