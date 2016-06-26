program MechInfo;

uses
  Forms,
  Unit4 in 'Unit4.pas' {Form4},
  Unit14 in 'Unit14.pas' {Form14},
  Unit8 in 'Unit8.pas' {Form8};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm4, Form4);
  Application.CreateForm(TForm14, Form14);
  Application.CreateForm(TForm8, Form8);
  Application.Run;
end.
