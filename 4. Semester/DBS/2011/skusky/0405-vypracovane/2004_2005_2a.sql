select dbo.StudOdbor.nazov, dbo.Predmet.rocnik, sum(dbo.Predmet.kredity_akt) 
from dbo.Predmet, dbo.StudOdbor 
where  dbo.Predmet.id_odbor = dbo.StudOdbor.id_odbor
group by dbo.StudOdbor.nazov, dbo.Predmet.rocnik
order by dbo.StudOdbor.nazov, dbo.Predmet.rocnik