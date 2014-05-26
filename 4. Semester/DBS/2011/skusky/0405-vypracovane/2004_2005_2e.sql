select distinct dbo.Predmet.nazov, dbo.Ucitel.priezvisko , dbo.Ucitel.meno, 
count(all dbo.Vyber.id_student) as pocet, avg(all dbo.Vyber.body_cvicenie) as body
from dbo.Ucitel, dbo.Predmet, dbo.Vyber
where dbo.Vyber.id_predmet = dbo.Predmet.id_predmet 
	and dbo.Vyber.id_ucitel_cvici = dbo.Ucitel.id_ucitel
group by dbo.Predmet.nazov, dbo.Ucitel.priezvisko , dbo.Ucitel.meno
order by dbo.Predmet.nazov, dbo.Ucitel.priezvisko , dbo.Ucitel.meno