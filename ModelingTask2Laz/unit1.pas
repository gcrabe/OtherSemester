unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil,
  TAGraph, TASeries, TARadialSeries,
  Forms, Controls, Graphics, Dialogs,
  StdCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Chart1: TChart;
    Chart1LineSeries1: TLineSeries;
    Chart1LineSeries2: TLineSeries;
    Chart1LineSeries3: TLineSeries;
    Chart1LineSeries4: TLineSeries;
    procedure Button1Click(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
var
  x, y, xp, yp, dt, t, l, g, c, m: extended;
begin
      l:= 10;
      g:= 9.8;
      m:= 5;
      c:= 0.3;   { c:= 0.0; }

      xp:= 1; yp:= 1; dt:= 0.01; t:= 0;

      while t < 100 do
      begin
        x:= xp + dt * (yp);
        y:= yp + dt * ( -(g / l) * sin(xp) - (c * yp / l * m));
        Chart1LineSeries1.AddXY(x,y,'',clRed);
        xp:= x; yp:= y;
        t:= t + dt;
      end;

      xp:= -1; yp:= 1; dt:= 0.01; t:= 0;

      while t < 100 do
      begin
        x:= xp + dt * (yp);
        y:= yp + dt * ( -(g / l) * sin(xp) - (c * y / l * m));
        Chart1LineSeries2.AddXY(x,y,'',clRed);
        xp:= x; yp:= y;
        t:= t + dt;
      end;

      xp:= -1; yp:= -1; dt:= 0.01; t:= 0;

      while t < 100 do
      begin
        x:= xp + dt * (yp);
        y:= yp + dt * ( -(g / l) * sin(xp) - (c * y / l * m));
        Chart1LineSeries3.AddXY(x,y,'',clRed);
        xp:= x; yp:= y;
        t:= t + dt;
      end;

      xp:= 1; yp:= -1; dt:= 0.01; t:= 0;

      while t < 100 do
      begin
        x:= xp + dt * (yp);
        y:= yp + dt * ( -(g / l) * sin(xp) - (c * y / l * m));
        Chart1LineSeries4.AddXY(x,y,'',clRed);
        xp:= x; yp:= y;
        t:= t + dt;
      end;
end;

end.

