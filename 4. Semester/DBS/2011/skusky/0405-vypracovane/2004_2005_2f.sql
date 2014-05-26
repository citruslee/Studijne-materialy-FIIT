select distinct dbo.Predmet.nazov, a.priezvisko as prednasajuci, b.priezvisko as cviciaci
from dbo.Predmet, dbo.Ucitel a, dbo.Ucitel b ,dbo.Vyber
where dbo.Predmet.id_ucitel_predn = a.id_ucitel 
	and dbo.Predmet.id_predmet = dbo.Vyber.id_predmet
	and dbo.Vyber.id_ucitel_cvici = b.id_ucitel
order by dbo.Predmet.nazov, a.priezvisko , b.priezvisko 