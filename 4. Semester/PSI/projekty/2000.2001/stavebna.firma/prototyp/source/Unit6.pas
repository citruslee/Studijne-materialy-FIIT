unit Unit6;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Grids, ExtCtrls;

type
  TForm6 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    Label1: TLabel;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Panel1: TPanel;
    Panel2: TPanel;
    Button5: TButton;
    StringGrid1: TStringGrid;
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form6: TForm6;

implementation

uses Unit9, Unit8, Unit10, Unit11;

{$R *.DFM}




procedure TForm6.FormCreate(Sender: TObject);
var i:byte;
begin
     StringGrid1.Rows[0].Append('ID');
     StringGrid1.Rows[0].Append('Názov');
     StringGrid1.Rows[0].Append('Dátum');
     for i:=1 to 14 do
     begin
          StringGrid1.Rows[i].Append(IntToStr(i));
          StringGrid1.Rows[i].Append('Výjazd '+IntToStr(i));
          StringGrid1.Rows[i].Append('Dat'+IntToStr(i));
     end;
end;

procedure TForm6.Button2Click(Sender: TObject);
begin
     Form9.ShowModal;
end;

procedure TForm6.Button4Click(Sender: TObject);
begin
     Form8.ShowModal;
     Form10.ShowModal;
end;

procedure TForm6.Button3Click(Sender: TObject);
begin
     Form11.ShowModal;
end;

end.
 