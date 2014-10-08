unit Unit15;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Grids;

type
  TForm15 = class(TForm)
    StringGrid1: TStringGrid;
    Button1: TButton;
    Edit1: TEdit;
    Label1: TLabel;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form15: TForm15;

implementation

{$R *.DFM}


procedure TForm15.FormCreate(Sender: TObject);
var i:byte;
begin
     StringGrid1.Rows[0].Append('ID');
     StringGrid1.Rows[0].Append('Názov');
     for i:=1 to 14 do
         begin
              StringGrid1.Rows[i].Append('IDnum'+IntToStr(i+1));
              StringGrid1.Rows[i].Append('Mechanizmus '+IntToStr(i+1));
         end;

end;

end.
