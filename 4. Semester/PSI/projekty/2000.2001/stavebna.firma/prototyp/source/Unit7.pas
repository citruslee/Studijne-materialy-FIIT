unit Unit7;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Grids;

type
  TForm7 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    StringGrid1: TStringGrid;
    Label1: TLabel;
    ComboBox1: TComboBox;
    Label2: TLabel;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    procedure Button2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form7: TForm7;

implementation

{$R *.DFM}

procedure TForm7.Button2Click(Sender: TObject);
begin
     InputBox('Nové umiestnenie','Názov/adresa','');
end;

procedure TForm7.FormCreate(Sender: TObject);
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
