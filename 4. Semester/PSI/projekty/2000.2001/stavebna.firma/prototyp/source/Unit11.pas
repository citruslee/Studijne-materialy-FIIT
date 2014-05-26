unit Unit11;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, Grids, ExtCtrls;

type
  TForm11 = class(TForm)
    Panel1: TPanel;
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    Panel2: TPanel;
    Label3: TLabel;
    Edit3: TEdit;
    Label4: TLabel;
    Edit4: TEdit;
    Label5: TLabel;
    Panel3: TPanel;
    StringGrid1: TStringGrid;
    StringGrid2: TStringGrid;
    SpeedButton1: TSpeedButton;
    Button1: TButton;
    Button2: TButton;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form11: TForm11;

implementation

{$R *.DFM}



procedure TForm11.FormCreate(Sender: TObject);
var i:byte;
begin
     StringGrid1.Rows[0].Append('ID');
     StringGrid1.Rows[0].Append('Názov');
     StringGrid2.Rows[0].Append('ID');
     StringGrid2.Rows[0].Append('Názov');
     for i:=1 to 14 do
         begin
              StringGrid1.Rows[i].Append('IDnum'+IntToStr(i+1));
              StringGrid1.Rows[i].Append('Mechanizmus '+IntToStr(i+1));
         end;

end;

end.
