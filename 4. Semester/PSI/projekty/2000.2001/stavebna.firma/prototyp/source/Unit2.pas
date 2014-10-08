unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, Grids;

type
  TForm2 = class(TForm)
    Label2: TLabel;
    Label1: TLabel;
    StringGrid1: TStringGrid;
    StringGrid2: TStringGrid;
    SpeedButton1: TSpeedButton;
    Button2: TButton;
    Button1: TButton;
    Edit1: TEdit;
    Button3: TButton;
    Button4: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

uses Unit13;

{$R *.DFM}



procedure TForm2.FormCreate(Sender: TObject);
var i:byte;
begin
     StringGrid1.Rows[0].Append('Názov');
     StringGrid2.Rows[0].Append('Názov');
     for i:=1 to 14 do
         begin
              StringGrid1.Rows[i].Append('Mechanizmus '+IntToStr(i+1));
         end;


end;

procedure TForm2.Button2Click(Sender: TObject);
begin
     Form13.ShowModal;
end;

end.
 