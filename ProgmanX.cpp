//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ProgmanX.res");
USEFORM("U_Main.cpp", FormMain);
USEFORM("U_Group.cpp", FormGroup);
USEFORM("U_CreateGroup.cpp", FormCreateGroup);
USEFORM("U_AddItem.cpp", FormAddItem);
USEFORM("U_ProcessMonitor.cpp", FormProcessMonitor);
USEFORM("U_Background.cpp", FormBackground);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "ProgmanX";
         Application->CreateForm(__classid(TFormMain), &FormMain);
         Application->CreateForm(__classid(TFormBackground), &FormBackground);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
