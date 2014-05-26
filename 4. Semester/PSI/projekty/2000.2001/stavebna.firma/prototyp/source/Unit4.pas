unit Unit4;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls;

type
  TForm4 = class(TForm)
    Panel1: TPanel;
    Button1: TButton;
    Label1: TLabel;
    Edit1: TEdit;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   Form4: TForm4;

implementation

uses Unit14, Unit8;

{$R *.DFM}

procedure TForm4.Button1Click(Sender: TObject);
var       NewForm: TForm14;
begin
     if ((Sender as TButton).Tag=3) or ((Sender as TButton).Tag=5) then
        if Form8.ShowModal=mrCancel then Exit;
     NewForm := TForm14.Create(Self);
     NewForm.Caption:='Výpis - ' + (Sender as TButton).Caption;
     NewForm.Show;
end;





end.
