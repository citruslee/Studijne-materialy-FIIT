unit Unit14;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids;

type
  TForm14 = class(TForm)
    StringGrid1: TStringGrid;
    procedure StringGrid1DblClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form14: TForm14;

implementation

uses Unit8;

{$R *.DFM}

procedure TForm14.StringGrid1DblClick(Sender: TObject);
begin
     if Form8.ShowModal=mrCancel then exit;
end;

end.
