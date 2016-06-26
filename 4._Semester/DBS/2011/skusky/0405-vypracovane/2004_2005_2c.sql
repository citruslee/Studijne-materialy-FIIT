select dbo.Predmet.rocnik, dbo.Predmet.skratka, count(all dbo.Vyber.id_student) as prihlasenych
from dbo.Predmet left join  dbo.Vyber on dbo.Vyber.id_predmet = dbo.Predmet.id_predmet
group by dbo.Predmet.rocnik, dbo.Predmet.skratka
order by dbo.Predmet.rocnik, dbo.Predmet.skratka