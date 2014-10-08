unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    Panel4: TPanel;
    Button7: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses Unit2, Unit4, Unit5, Unit6, Unit7, Unit3, Unit8, Unit15;

{$R *.DFM}


procedure TForm1.Button1Click(Sender: TObject);
begin
     if Form8.ShowModal=mrOK then
     Form2.ShowModal;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
     if Form8.ShowModal=mrOK then
     Form3.ShowModal;
end;
function WinExecAndWait32(Path: PChar; Visibility: Word): integer;
var
	 Msg: TMsg;
	 lpExitCode : integer;
	 StartupInfo: TStartupInfo;
	 ProcessInfo: TProcessInformation;
begin
	FillChar(StartupInfo, SizeOf(TStartupInfo), 0);
	with StartupInfo do
	begin
		cb := SizeOf(TStartupInfo);
		dwFlags := STARTF_USESHOWWINDOW or STARTF_FORCEONFEEDBACK;
		wShowWindow := visibility; {you could pass sw_show or sw_hide as parameter}
	end;
	if CreateProcess(nil,path,nil, nil, False,
		NORMAL_PRIORITY_CLASS, nil, nil, StartupInfo, ProcessInfo) then begin
		repeat
			while PeekMessage(Msg, 0, 0, 0, pm_Remove) do
				begin
					if Msg.Message = wm_Quit then Halt(Msg.WParam);
					TranslateMessage(Msg);
					DispatchMessage(Msg);
				end;
				GetExitCodeProcess(ProcessInfo.hProcess,lpExitCode);
		until lpExitCode<>Still_Active;
		with ProcessInfo do {not sure this is necessary but seen in in some code elsewhere}
		begin
			CloseHandle(hThread);
			CloseHandle(hProcess);
		end;
		result := 0; {sucess}
	end
	else
		result:=GetLastError;{error occurs during CreateProcess see help for details}
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
     WinExecAndWait32('mechinfo.exe',sw_Show);
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
     if Form8.ShowModal=mrOK then
     Form5.ShowModal;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
     Form6.ShowModal;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
     Form7.ShowModal;
end;


procedure TForm1.Button7Click(Sender: TObject);
begin
     if Form8.ShowModal=mrOK then
     Form15.ShowModal;
end;

end.
