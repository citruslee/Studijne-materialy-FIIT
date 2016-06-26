unit Unit10;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Grids;

type
  TForm10 = class(TForm)
    Panel1: TPanel;
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Edit3: TEdit;
    Panel2: TPanel;
    Label4: TLabel;
    Edit4: TEdit;
    Label5: TLabel;
    Edit5: TEdit;
    Label7: TLabel;
    Label8: TLabel;
    Label6: TLabel;
    StringGrid1: TStringGrid;
    Label9: TLabel;
    Memo1: TMemo;
    Button1: TButton;
    Button2: TButton;
    Label10: TLabel;
    Edit6: TEdit;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form10: TForm10;

implementation

{$R *.DFM}


procedure TForm10.FormCreate(Sender: TObject);
begin
     StringGrid1.Rows[0].Append('ID');
     StringGrid1.Rows[0].Append('Názov');
     StringGrid1.Rows[1].Append('IDnum45');
     StringGrid1.Rows[1].Append('Automobil 45');
     StringGrid1.Rows[2].Append('IDnum46');
     StringGrid1.Rows[2].Append('Automobil 46');
end;


end.
