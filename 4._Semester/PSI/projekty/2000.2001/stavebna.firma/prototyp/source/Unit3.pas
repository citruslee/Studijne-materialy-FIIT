unit Unit3;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Grids, Buttons;

type
  TForm3 = class(TForm)
    StringGrid1: TStringGrid;
    Button1: TButton;
    Edit1: TEdit;
    Button3: TButton;
    Button4: TButton;
    StringGrid2: TStringGrid;
    SpeedButton1: TSpeedButton;
    Button2: TButton;
    Label1: TLabel;
    Label2: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form3: TForm3;

implementation

uses Unit12;

{$R *.DFM}



procedure TForm3.FormCreate(Sender: TObject);
var i:byte;
begin
     StringGrid1.Rows[0].Append('Názov');
     StringGrid2.Rows[0].Append('Názov');
     for i:=1 to 14 do
         begin
              StringGrid1.Rows[i].Append('Mechanizmus '+IntToStr(i+1));
         end;

end;



procedure TForm3.Button2Click(Sender: TObject);
begin
     Form12.ShowModal;
end;

end.
 